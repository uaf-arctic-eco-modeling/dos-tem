/*! \file
 * Ground is used to manipulate the structure of 
 * snow and soil layers
 * modified from \url http://24bytes.com/Double-linked-List.html
 * The structure of soil layers is determined at the begining of run (and after each change
 * of soil structure after disturbance), the frozen thermal conductivity and thermal capacity is used
 * to determine the minimum soil layer thickness.
 * While the structure of snow layers is determined every time step. At the begining of model run
 * the maixmum snow mass is calculated to constrain the miminum snow layer thickness using maximum 
 * snow density.
 * 
 * Problems encountered during implementing dynamic organic soil thickness
 * 1) When soil layer thickness is reduced, it is possible that freezing/thawing fronts in this layer
 *    exceeds the bottom , so adjust the fronts in updateOrganicThickness
 * 2) pure virtual method called
 *    This is caused by using pointer which is already deleted, e.g. by fire removal
 * 3) STATUS_ACCESS_VIOLATION
 *    When a layer is removed, it still existed, and later on can be accessed through ->prevl or ->nextl
 *    The layer is removed in DoubleLinkedList::removeLayer, when useing delete, only the memory is released
 *    for future use, but the pointer is not deleted
 * 
 */
 
#include "Ground.h"

Ground::Ground(){
   fstsoill = NULL;
   fstfntl  = NULL;
   lstfntl  = NULL;
   fstminl  = NULL;
   lstminl  = NULL;
   
   fstshlwl = NULL;
   lstshlwl = NULL;
   dtmax = 999.;
  
   rock.thick = 50;
   
   rocklayercreated=false;

  // updateDailySoilEnv=true;
   
};

Ground::~Ground(){
   clean();	
}

//////////////////////////////////////////////////////////////////////////////
void Ground::updateDaily(const int & yrcnt, const int & year,
			 const int & mind, const int & id, const double & tdrv2, const double & dayl){
	double tsurface;
	double trans, melt, evap, rnth;
	curyrcnt = yrcnt;
    curyear  = year;
    dtmax    = 0.3;
     
    ed->d_l2soi.perc   = 0.;
    ed->d_soi2l.qover  = 0.;
    ed->d_soi2l.qdrain = 0.;
    
    //update nfactor based on envlai         
	tsurface = tdrv2 *ed->d_soid.nfactor;
	
	//frontl->tem;	
	if(frontl->isSoil()){
		soil.updateDailySurfFlux(frontl, tsurface, dayl);
		ed->d_snw2a.solrad =0.;
		ed->d_snw2a.sublim=0;
	}else{
	 	snow.updateDailySurfFlux(frontl, tsurface);
	 	ed->d_soi2a.evap =0.;
	 	ed->d_soi2a.solrad =0.;
	}	
	
	double tdrv1 = tdrv2 * ed->d_soid.nfactor;	

    if(tdrv1>0){
    	ed->d_snwd.melt +=meltSnowLayers();
	}
    
 	bool slchg1= constructSnowLayers(tsurface);
    if(slchg1)	{       
    	resetSnowLayerIndex();
    }
    
	bool slchg2=combineSnowLayers();
	if(slchg2){		  
		 resetSnowLayerIndex();
	}
	
	bool slchg3=divideSnowLayers();	

	if( slchg1 || slchg2 || slchg3)	{		
		updateLayerIndex();
		updateSnowLayerZ();
	}
		 
	updateSWE();
    //checkSnowLayers();
    //added by shuhua on Apr. 18, 2008
    if(frontl->isSnow() && fstsoill->frozen ==-1){ //for cases with snow fall before ground surface freezing
    	SoilLayer* sl = dynamic_cast<SoilLayer*>(fstsoill);
    	sl->addOneFront5Top(0.0, 1);
    	//also set tem at top of layer to zero, otherwise problem of temperature calcu. occurs
    	//added by shuhua Apr 22, 2008
    	sl->tem=0.;
    	updateFstLstFntLay();
    	sl= NULL;
    }
   /* if(lstminl->frozen ==-1 && lstminl->nextl->tem <0   || lstminl->frozen ==1 && lstminl->nextl->tem >0){
    	Layer* currl = lstminl;
    	if(currl->isSoil()){
    	SoilLayer* sl1 = dynamic_cast<SoilLayer*>(currl);
    	if(currl->frozen ==1){
    	sl1->addOneFront5Top(currl->dz,1);
    	}else if(currl->frozen ==-1){
    	sl1->addOneFront5Top(currl->dz,-1);	
    	}
    	sl1 =NULL;
    	updateFstLstFntLay();
    	
    	}
    }*/
    
    if(fstfntl==NULL && lstfntl==NULL ){ // there is no front
     	if(frontl->isSoil()){
       		if((tstate==1 && tdrv1>0) || (tstate==-1 && tdrv1<0) || tstate==0){//create front
       	 		soil.stefan.updateFronts(tdrv1, frontl, backl,fstsoill, lstminl,mind);
       		// stefan.checkFrontsValidity(fstsoill);
       		}
     	}
    }else{
		soil.stefan.updateFronts(tdrv1, frontl, backl,fstsoill, lstminl,mind);
		soil.stefan.checkFrontsValidity(fstsoill);
    }
   
    updateFstLstFntLay();
	soil.stefan.updateTemps(tdrv1, frontl, backl,fstsoill, fstfntl, lstfntl);
    
   	ed->d_soid.itnum = soil.stefan.itsumall;

	// at end of the day, calculate the surface runoff and infiltration
	// and then soil water dynamics at a daily time step
	trans = ed->d_v2a.trans;  //mm/day
    evap  = ed->d_soi2a.evap; //mm/day
    rnth  = (ed->d_v2g.rthfl +ed->d_v2g.rdrip)+ (1-ed->y_vegd.vegfrac)*ed->d_a2l.rnfl; //mm/day
           //the first two items has already been adjust by ed->y_vegd.vegfrac in VE
           
    melt = ed->d_snwd.melt; //mm/day
    // soil.updateRunoffInfil(fstsoill, rnth, melt);
    ed->d_soid.watertab = soil.getWaterTable(fstsoill);
    ed->d_soid.frasat = soil.getFracSat(  ed->d_soid.frasat);
           
           
    updateThermState();

/* Yuan: Feb. 2011: let the Richards algorithm runs for all
    if(richardl->frozen > -1){//if the soil column is totally frozen
    //	if(frontl->isSnow()){
   	//change to if there is snow
 		if(rnth +melt>0){
         	//double runoff = soil.getRunoffVIC(fstsoill, rnth, melt); //mm/day
         	double runoff = soil.getRunoff(fstsoill, rnth, melt, ed->d_soid.frasat); //mm/day
           	 	
        	double infilf = rnth +melt - runoff; //mm/day
           	double leftinfil = soil.infilFrozen(fstminl, infilf);//mm/day
           		
           	//soil.infilFrozen2( fstsoill, fstnoinfil, rnth, melt);
           		
           	ed->d_l2soi.perc = infilf-leftinfil;//mm/day
           	ed->d_soi2l.qover =runoff +leftinfil;//mm/day
        }else{
       	    ed->d_soi2l.qover = 0.;//mm/day
        }
    
    } else {         
*/
        if(rnth+melt>0){
            // ed->d_soi2l.qover = soil.getRunoffVIC(fstsoill, rnth, melt); //mm/day
         	ed->d_soi2l.qover  = soil.getRunoff(fstsoill, rnth, melt, ed->d_soid.frasat); //mm/day
           	ed->d_l2soi.perc   = (rnth+melt) - ed->d_soi2l.qover;//mm/day
        }else{
           	ed->d_soi2l.qover  = 0.;
           	ed->d_l2soi.perc   = 0.;	
        }
        
        double infil = ed->d_l2soi.perc;
        double sinday= 24.*3600.; 
        
		trans /=sinday; // mm/day to mm/s
		infil /=sinday; // mm/day to mm/s
		evap /=sinday;  // mm/day to mm/s
				
	    //double watertab =  soil.getWaterTable(frontl);  
        double  drain = 0; //soil.getDrainage(watertab);
	        
	    soil.richard.update(frontl, backl,fstsoill, drainl,  drain,  trans,  evap,infil ,
	        		 ed->d_soid.watertab );
 	    
 	    // double permftab = soil.getPermafrostTable(fstsoill);
 	       
 	    //  ed->d_soi2l.qdrain =soil.update5BaseFlow(drainl);
 	   
 	    if(ed->cd->drgtype==0){
 	         ed->d_soi2l.qdrain =soil.update5Drainage(drainl, ed->d_soid.frasat, ed->d_soid.watertab);
 	    }else{
 	         ed->d_soi2l.qdrain =0;	
 	    }
 	         
 	    ed->d_soid.itnumliq = soil.richard.itsum;
 	      
//    }
    
    //at the end of water calculation, adjust water from fntl to nextl layer which is frozen or part frozen
    //May 19, 2010 yis
    if(fstfntl!=NULL && lstfntl!=NULL){
    	if(fstfntl->indl ==lstfntl->indl){
    		if(fstfntl->isSoil()){
    			SoilLayer* sl = dynamic_cast<SoilLayer*>(fstfntl);
          		if(sl->fronts[0]->frzing==-1){//thawing front
          			//put some water of upper layer into this layer
          			if(fstfntl->prevl!=NULL){
          				if(fstfntl->prevl->isSoil() && fstfntl->prevl->frozen==-1){
          					SoilLayer* slp =   dynamic_cast<SoilLayer*>(fstfntl->prevl);
          					if(slp->getVolLiq()>sl->getVolWater()){
          						double provide = (slp->getVolLiq()-sl->getVolWater())*slp->dz*1000.;
          						double receive = (sl->poro - sl->getVolWater())*sl->dz*1000.;
          						double delta =0;
          						if(provide >receive){
          							delta = receive;
          						}else{
          							delta = provide;
          						}
          						slp->liq -= delta;
          						sl->liq +=delta;
          					}
          				}
          			}
          		}
    		}
    	
    	} else { //not the same front

    		if(fstfntl->isSoil()){
    			if(fstfntl->prevl!=NULL){
    				SoilLayer* sl = dynamic_cast<SoilLayer*>(fstfntl);
          		    	if(sl->fronts[0]->frzing==-1){//thawing front
          		    		//put some water of upper layer into this layer
          		           	if(fstfntl->prevl->isSoil() && fstfntl->prevl->frozen==-1){
          		           	SoilLayer* slp =   dynamic_cast<SoilLayer*>(fstfntl->prevl);
          		           		if(slp->getVolLiq()>sl->getVolWater()){
          		           			double provide = (slp->getVolLiq()-sl->getVolWater())*slp->dz*1000.;
          		           			double receive = (sl->poro - sl->getVolWater())*sl->dz*1000.;
          		           			double delta =0;
          		           			if(provide >receive){
          		           				delta = receive;
          		           			}else{
          		           				delta = provide;
          		           			}
          		           			slp->liq -= delta;
          		           			sl->liq +=delta;
          		           		}

          		           	}
          		       }
    			}
          	}

          	if(lstfntl->isSoil()){
          		SoilLayer* sl = dynamic_cast<SoilLayer*>(lstfntl);
          		if(lstfntl->prevl!=NULL){
          			if(sl->fronts[0]->frzing==-1){//thawing front
          				//put some water of upper layer into this layer
          		        if(lstfntl->prevl->isSoil() && lstfntl->prevl->frozen==-1){
          		        	SoilLayer* slp =   dynamic_cast<SoilLayer*>(lstfntl->prevl);
          		        	if(slp->getVolLiq()>sl->getVolWater()){
          		        		double provide = (slp->getVolLiq()-sl->getVolWater())*slp->dz*1000.;
          		           		double receive = (sl->poro - sl->getVolWater())*sl->dz*1000.;
          		           		double delta =0;
          		           		if(provide >receive){
          		           			delta = receive;
          		           		}else{
          		           		    delta = provide;
          		           		}
          		           		slp->liq -= delta;
          		           		sl->liq +=delta;
          		           	}
          		        }
          			}
          		}
          	}

        }
    }
    
	// at end of each day, each layer should be updated
	updateAllLayers();
	soil.retrieveThawPercent(fstsoill);
		
	//snow.endOfDay(curyrcnt, tdrv );

	//soil.endOfDay(grow,  curyrcnt, tdrv);
		
};

void Ground::updateAllLayers(){
   	Layer* currl=frontl;
   	
   	while(currl!= NULL){
   		currl->advanceOneDay();
   		if(currl->isSnow()){
       		dynamic_cast<SnowLayer*>(currl)->updateDensity();
       		dynamic_cast<SnowLayer*>(currl)->updateThick();	
   		}
   		currl=currl->nextl;	
   	}
};

void Ground::checkSnowLayers(){
 	Layer* currl = frontl;
 	SnowLayer* sl;
 	
 	while(currl!=NULL){
    	if (currl->isSnow()){
      		sl = dynamic_cast<SnowLayer*>(currl);
      		//sl->check();
       		if(currl->tem>0){
           		//cout <<"Snow temprature >0\n";
           		currl->tem =-0.01;
         	}	
    	}	
    	
    	currl=currl->nextl;
 	}		
};

void Ground::updateFstLstFntLay(){
	// determine the first front and last front layer
  	 fstfntl=NULL;
  	 lstfntl=NULL;
  	 
  	 Layer* currl=fstsoill;
  	 SoilLayer* sl;
  	 
  	 while(currl!=NULL){
  	   	if(currl->isSoil() ){
  	   		sl = dynamic_cast<SoilLayer*>(currl);
  	   	 	if(sl->fronts.size()>0){
  	   	 		fstfntl=currl;
  	   	 		break;
  	   	 	}
  	   	}
  	   	
  	   	currl=currl->nextl;	
  	 }
  	 
  	 if(fstfntl!=NULL){
  	 	currl=backl;
  	 	while(currl!=NULL){
  	  		if(currl->isSoil() ){
  	  			sl = dynamic_cast<SoilLayer*>(currl);
  	   	 		if(sl->fronts.size()>0){
  	   	 			lstfntl=currl;
  	   	 			break;
  	   	 		}
  	  		}	
  	  		currl=currl->prevl;
  	 	}
  	 }
	
};

void Ground::updateThermState(){
	
	if(fstfntl!=NULL && lstfntl!=NULL){
	  	tstate =0; // part frozen and part unfrozen	
	}else if(fstfntl==NULL && lstfntl==NULL){
	 	tstate =fstsoill->frozen;	
	}
		
};

bool Ground::combineSnowLayers(){
	bool layerchanged =false;
	Layer* currl;
	Layer* tempnext;
	STARTCOMBINE:
	currl= frontl;
	
	while(currl!=NULL && currl->nextl!=NULL){
		// for case of first layer
		tempnext = currl->nextl;
		if(currl==frontl){
	 		if(currl->isSnow()){
	 			if(currl->dz < snow.mindz[currl->indl]){
	  				if(currl->nextl->isSnow()){
	  	  				currl->nextl->liq += currl->liq;
	  	  				currl->nextl->ice += currl->ice;
	  	  				currl->nextl->dz +=currl->dz;
	  	  				currl->nextl->rho = currl->nextl->ice/currl->nextl->dz;
	  	  				currl->nextl->age = currl->nextl->age/2. + currl->age/2.;
	  	   
	  	  				/* if(currl->nextl->age >1){
	  	     	 		string msg = "snow age should not greater than 1 year ";
 	 			 		char* msgc = const_cast< char* > ( msg.c_str());
 		 		 		throw Exception(msgc, I_SNOW_AGE);
	  	     			}*/
	  	     
	  	  
	  				}else{ // set extramass
	  	  				snow.extramass += currl->ice;
	  				}
	  	
	  				//remove current layer
	  				removeLayer(currl);
	  				//frontl=tempnext;
	  				resetLayerIndex();
	  				layerchanged =true;
	  				goto STARTCOMBINE;
	  			}			
			}
		
		}else{ // for other layers
			if(currl->isSnow()){
	    		if(currl->dz < snow.mindz[currl->indl]){
	  	 			if(currl->nextl->isSnow()){
	  	 				//find the thinest layer
	  	 				if(currl->nextl->dz<currl->prevl->dz){
	  		  				currl->nextl->liq += currl->liq;
	  		  				currl->nextl->ice += currl->ice;
	  		  				currl->nextl->dz +=currl->dz;
	  		  				currl->nextl->rho = currl->nextl->ice/currl->nextl->dz;
	  	 				}else{
	  	 	  				currl->prevl->liq += currl->liq;
	  	  	  				currl->prevl->ice += currl->ice;
	  	  	  				currl->prevl->dz +=currl->dz;
	  	  	  				currl->prevl->rho = currl->prevl->ice/currl->prevl->dz;  	 		
	  	 				}
	  	  
	  	 			}else{ // combine to upper snow layer
	  	  				currl->prevl->liq += currl->liq;
	  	  				currl->prevl->ice += currl->ice;
	  	  				currl->prevl->dz +=currl->dz;
	  	  				currl->prevl->rho = currl->prevl->ice/currl->prevl->dz;
	    			}
	  	
	  				//remove current layer
	  				removeLayer(currl);
	  				resetLayerIndex();
	  				layerchanged = true;
	  				goto STARTCOMBINE;
	  			}		
			}
		
		}
	
		currl= tempnext;
	
		if(currl->isSoil())break;
    }
	
	return layerchanged;
};

bool Ground::divideSnowLayers(){
	bool layerchanged =false;	
	Layer* currl;
	STARTOFDIVIDE:
	currl= frontl;
	
	while(currl!=NULL){
		if(currl->isSoil())break;
		if(currl->dz>snow.maxdz[currl->indl]){
			if(currl->nextl->isSnow()){//assume that the nextl meets the dz requirement
				currl->dz /=2;
				currl->liq /=2;
				currl->ice /=2;
				currl->nextl->liq += currl->liq;
	  			currl->nextl->ice += currl->ice;
	  			currl->nextl->dz +=currl->dz;
	  			currl->nextl->rho = currl->nextl->ice/currl->nextl->dz;
	  		
			}else{//create new layer
				if(currl->indl+1 <MAX_SNW_LAY-1){			
					if(currl->dz/2>snow.mindz[currl->indl+1]){
						currl->dz /=2;
			    		currl->liq /=2;
			    		currl->ice /=2;
			    		SnowLayer* sl = new SnowLayer();
		      			//  sl->ctype = soil.getCohortType();
		        		sl->denmax =snow.envpar.denmax;
		   	    		sl->albmax =snow.envpar.albmax;
			    		sl->albmin =snow.envpar.albmin;
			    		sl->newden =snow.envpar.newden;
			    
			    		sl->clone( dynamic_cast<SnowLayer*>(currl));
			    		sl->tem = currl->tem;
			    		insertAfter(sl, currl);
				
						resetSnowLayerIndex();
			    		layerchanged =true;
			    		goto STARTOFDIVIDE;
					}else if(currl->dz- snow.maxdz[currl->indl]>= snow.mindz[currl->indl+1]){
						double tempdz = currl->dz;
						double tempice = currl->ice;
						double templiq = currl->liq;
				
						currl->dz = snow.maxdz[currl->indl];
			    		currl->liq *= currl->dz/tempdz ;
			    		currl->ice *= currl->dz/tempdz ;
			    		SnowLayer* sl = new SnowLayer();
			  			//  sl->ctype = soil.getCohortType();
		        		sl->tem = currl->tem;
		         		sl->denmax =snow.envpar.denmax;
		   	    		sl->albmax =snow.envpar.albmax;
			    		sl->albmin =snow.envpar.albmin;
			    		sl->newden =snow.envpar.newden;
		   
			    		sl->clone( dynamic_cast<SnowLayer*>(currl));
			    		sl->dz =tempdz - currl->dz;
			    		sl->liq = templiq -currl->liq;
			    		sl->ice = tempice -currl->ice;
			    		insertAfter(sl, currl);
						resetSnowLayerIndex();
			    		layerchanged =true;
						goto STARTOFDIVIDE;
					}
				}else{
			  		break;	
				}
			
			}
		
		}

		currl= currl->nextl;
    }
	
	return layerchanged;
};


void Ground::updateSWE(){
	ed->d_snws.swe =0.;
	Layer* currl=frontl;
	while(currl!=NULL){
	  	if(currl->isSnow()){
	  		ed->d_snws.swe +=   currl->ice;	  	
	  	}else{
	  		break;
	  	}
		currl=currl->nextl;
	}
	ed->d_snws.swe += snow.extramass;
	
};

bool Ground::constructSnowLayers(const double & tdrv){
	 bool layerchanged=false;
     double dsmass = (ed->d_v2g.sthfl + ed->d_v2g.sdrip + (1-ed->y_vegd.vegfrac)* ed->d_a2l.snfl
	                  - ed->d_snw2a.sublim-ed->d_snwd.melt); // dsmass is the total snowfall during one timestep
	 //the first 2 items has already been adjusted by ed->y_vegd.vegfrac in VE
	 snow.extramass +=dsmass;	
	 double density  = snow.envpar.newden;
	 if(ed->d_v2g.sthfl==0){ 
	   	 //density = snow.maxden;
	 }
	 
	 if(snow.extramass>0){ // accumlate
	 	 double thick = snow.extramass/density;
	 if(frontl->isSnow()){ 
	 	 

		   SnowLayer * sl = new SnowLayer();
		 //  sl->ctype = soil.getCohortType();
		   sl->rho = snow.envpar.newden;
		   sl->dz = thick;
		   sl->denmax =snow.envpar.denmax;
		   	    sl->albmax =snow.envpar.albmax;
			    sl->albmin =snow.envpar.albmin;
			    sl->newden =snow.envpar.newden;
		   
		   sl->ice = snow.extramass;
		   snow.extramass =0;
		   sl->frozen =1;
	 	   insertFront(sl);
	 	   frontl->tem = tdrv;
           return  true;
	 }else{ // snow layer does not exist
	 	 double tsno =frontl->tem;
	 	 if(tsno>0){
	 	    ed->d_snws.swe =0.;
		   	ed->d_snwd.melt =snow.extramass;
		   	ed->d_snw2soi.infl += snow.extramass; 
		   	snow.extramass =0.;		   	
		   	return false; // when the initial soil temperature >0, no snow will accumulate
	 	 }else{
	 	   SnowLayer * sl = new SnowLayer();
	 	 //  sl->ctype = soil.getCohortType();
	 	   sl->denmax =snow.envpar.denmax;
		   	    sl->albmax =snow.envpar.albmax;
			    sl->albmin =snow.envpar.albmin;
			    sl->newden =snow.envpar.newden;
			    
		   sl->rho = snow.envpar.newden;
	 if(ed->d_v2g.sthfl==0){ 
	  // sl->rho= snow.maxden;
	 }else{
	 	//sl->rho = snow.newden;
	 }
	 
		   
		   sl->dz = thick;
		   sl->ice = snow.extramass;
		   snow.extramass =0;
		   sl->frozen =1;
	 	   insertFront(sl);
	 	   frontl->tem = tdrv;
           return true;	
	 	 }
	 	
	 }
	 }else{ // ablate
	 	double ablat = -snow.extramass;
	 	snow.extramass =0;
	 	
	 	if(frontl->isSnow()){
	 	  while(ablat>= frontl->ice){
	 	  	ablat -= frontl->ice;
	 	  	removeFront();
	 	  	layerchanged =true;
	 	  	if(frontl->isSoil())break;
	 	  	
	 	  }	
	 	}
	 	if(frontl->isSnow()){
	 	 	frontl->dz = frontl->dz * (frontl->ice -ablat)/(frontl->ice);		
		    frontl->ice -= ablat;	
	 	}
	 }
	 return layerchanged;
}

void Ground::resetSnowLayerIndex(){
//every time there is a change of layer, reset the layer index	
	Layer* currl = frontl;
	int ind =0;
	while(currl!=NULL){
		if(currl->isSnow()){
		ind++;
		currl->indl= ind;
		currl=currl->nextl;
		}else{
		 break;	
		}
	}
}

void Ground::resetLayerIndex(){
//every time there is a change of layer, reset the layer index	
	Layer* currl = frontl;
	int ind =0;
	while(currl!=NULL){
		ind++;
		currl->indl= ind;
		currl=currl->nextl;
	}
}

double  Ground::meltSnowLayers(){ // based on the state and front of snow
	//based on the temperatures of snow layer 
	double melt=0;
	double lf =  3.337e5 ;//latent heat of fusion J/kg
	double vlh ; // snow layer volumetric heat capcity J/m3K
	Layer* currl ;

	currl= frontl;
	while(currl!=NULL){
	 if(currl->isSnow()){
	 
      if(currl->frozen==-1){
      	melt += currl->ice;
      }else {
      	if(currl->tem>0){
      		vlh = currl->getHeatCapacity();
	  		if(vlh *currl->tem *917 /lf >=1){ //melt all the ice in layer
		  		melt += currl->ice;
	  		}else{
	  			melt += vlh *currl->tem *917 /lf * currl->ice;
	  		}
	  	currl->tem=-0.1;
      	currl->frozen=-1;
      	}
      }
	  currl=currl->nextl;
	  
	 }else{
	    break;	
	 }
	
	}
	if(melt>0){
	  melt += snow.extramass;
	  snow.extramass=0.;	
	}
	return melt;
};

/*
double  Ground::meltSnowLayers(){
	//based on the temperatures of snow layer 
	double melt=0;
	double lf =  3.337e5 ;//latent heat of fusion J/kg
	double vlh ; // snow layer volumetric heat capcity J/m3K

	Layer* currl ;

	currl= frontl;
	while(currl!=NULL){
	 if(currl->isSnow()){
	 
	  if(currl->tem>0){
	  	vlh = currl->getHeatCapacity();
	  	if(vlh *currl->tem *917 /lf >=1){ //melt all the ice in layer
	  		melt += currl->ice;
	  	}else{
	  		melt += vlh *currl->tem *917 /lf * currl->ice;
	  	}
	  	currl->tem=-0.1;
	  }
	  
	  currl=currl->nextl;
	  
	 }else{
	    break;	
	 }
	
	}
	if(melt>0){
	  melt += snow.extramass;
	  snow.extramass=0.;	
	}
	return melt;
};*/

/* when there is a disturbance, the moss/org layer may be removed
 * then the soil structure will be update
 */

/* when snow layer is melt or accumlated , the layer indl should be updated
 */
void Ground::updateLayerIndex(){
	Layer* curr2 = frontl;
	int ind =0;
	int sind=0;
	while (curr2!=NULL){
	 ind++;	
	 curr2->indl =ind;
	 if(curr2->isSoil()){
	 	sind++;
	 }else{
	    sind=0;	
	 }
	 curr2->solind = sind;
	 
	 curr2 =curr2->nextl;	
	}
	/*if(sind>MAX_SOI_LAY){
	   cout << "there are more soil layers than maximum allowed " << MAX_SOI_LAY <<"\n";
	   exit(-1);	
	 }*/
};

void Ground::updateSoilLayerZ(){
		//update the z, which is the distance between soil surface and top of a soil layer
		soil.resetDiagnostic();
		Layer* curr2=fstsoill->nextl;
		fstsoill->z=0;
		double oldz= 0.;
		while(curr2!=NULL){
			
		  curr2->z = oldz+ curr2->prevl->dz;
		  oldz = curr2->z;
		  
		  curr2=curr2->nextl;	
		}
		soil.dztot = backl->z +backl->dz;
		soil.num = backl->indl;
	
};


void Ground::updateSnowLayerZ(){
		//update the z, which is the distance between soil surface and top of a snow layer
		snow.resetDiagnostic();
		Layer* curr2=fstsoill;
		double oldz= 0.;
		while(curr2!=NULL){
		  if(curr2->isSnow()){
		  curr2->z = oldz + curr2->dz;
		  oldz = curr2->z;
		  }
		  curr2=curr2->prevl;	
		}
		if(frontl->isSnow()){
		  snow.dztot= frontl->z;	
		}
};



void Ground::checkTemperatures(){
	/*	Layer* curr2 = frontl;
		while(curr2!=NULL){

			
			if(curr2->tem>50. || curr2->tem<-50){
			  cout <<"soil temperature is out of range -50 to 50 " << curr2->tem<< "\n";
			  exit(-1);
			}
			curr2=curr2->nextl;
		}*/
};

double Ground::getSoilTransFactor(){
  return soil.getSoilTransFactor(fstsoill);	
};

void Ground::initializeLayerStructure(){ 

	if(rocklayercreated){
		cleanSnowSoilLayers();
		initSnowSoilLayers5Thickness();
	
		
	}else{
		initRockLayers();
		initSnowSoilLayers5Thickness();
		
	}
    setFstSoilLayer();
    setFstLstMineLayers();
    setFstLstShlwLayers();
	setFstLstDeepLayers();
    
    
	updateLayerIndex();
	updateSoilLayerZ();

	updateSnowLayerZ();	
	
	
	soil.initializeState(fstsoill);
	rock.initializeState(backl);
	//no need to initialize snow since there is no snow layer for first two types initialization
	setLayer5Depth();
	//snow.initializeState();
	
    soil.richard.updateSoilStructure(fstsoill);
	 
};  


void Ground::initializeLayerStructure5restart(RestartData * resin){ 

	if(rocklayercreated){
		cleanSnowSoilLayers();
		initSnowSoilLayers5Restart(resin);
	}else{
		initRockLayers();
		initSnowSoilLayers5Restart(resin);
		
	}
    setFstSoilLayer();
    setFstLstMineLayers();
    setFstLstShlwLayers();
	setFstLstDeepLayers();
    
    
	updateLayerIndex();
	updateSoilLayerZ();
	updateSnowLayerZ();	
	
	snow.initializeState5restart(frontl, resin);
	
	soil.initializeState5restart(fstsoill, resin); //soil temperature, moisture, front
	setLayer5Depth();
	
	rock.initializeState5restart(lstminl, resin);
	soil.richard.updateSoilStructure(fstsoill);
    soil.stefan.checkFrontsValidity(fstsoill);	 
}; 

void Ground::setFstSoilLayer(){// only called at the time of initializing soil layers
  Layer* currl = frontl;
  while(currl!=NULL){
    if(currl->isSoil()){
    	fstsoill =currl;
    	break;
    }
  	
  	
  	currl = currl->nextl;
  }
  
};



void Ground::setLayer5Depth(){
	// for infiltration of snowmelt into the frozen soil
	Layer* currl = fstsoill;

	double maxdepth = soil.envpar.richardl;//
	while(currl!=NULL){
		if(currl->z<maxdepth && currl->z +currl->dz>=maxdepth){
	  		richardl = currl;
	  		break;	
		}
	
		currl = currl ->nextl;	
	}
	
};
    
void Ground::setFstLstMineLayers(){  // only perform this at initialization of cohort
	//th mineral layer will never be removed/added
  	Layer* currl = frontl;
  	SoilLayer* sl; 
  
  	while(currl!=NULL){
    	if(currl->isSoil()){
    		sl = dynamic_cast<SoilLayer*>(currl);
    		if(sl->isMineral()){
    	   		fstminl =currl;
    	   		break;
    		}
    	
    	}
  		currl = currl->nextl;
  	}
  
  	currl =backl;
  	while(currl!=NULL){
  		if(currl->isSoil()){
  	  		sl = dynamic_cast<SoilLayer*>(currl);
  	  		if(sl->isMineral()){
  	  	 		lstminl=	currl;
  	  	 		break;
  	  		}
  		}
  		currl=currl->prevl;	
  	}
	
};

void Ground::setFstLstShlwLayers(){  
  fstshlwl =NULL;
  lstshlwl =NULL;
  //after setFstLstMineralLayer
  Layer* currl = fstsoill;
  SoilLayer* sl; 
  PeatLayer* pl;
  while(currl!=NULL){
    if(currl->isSoil()){
    	sl = dynamic_cast<SoilLayer*>(currl);
    	if(sl->isPeat()){
    	  pl = dynamic_cast<PeatLayer*>(sl);
    	  if(pl->isFibric){
    	  	fstshlwl = currl;
    	  	break;
    	  }
    	}
    	
    }else{
      break;	
    }
  	currl = currl->nextl;
  }
  
  currl =fstminl;
  while(currl!=NULL){
  	if(currl->isSoil()){
  	  	sl = dynamic_cast<SoilLayer*>(currl);
    	if(sl->isPeat()){
    	  pl = dynamic_cast<PeatLayer*>(sl);
    	  if(pl->isFibric){
    	  	lstshlwl = currl;
    	  	break;
    	  }
    	}
  	}else{
  	  break;	
  	}
  	currl=currl->prevl;	
  }
	
}


void Ground::setFstLstDeepLayers(){  
  fstdeepl =NULL;
  lstdeepl =NULL;
  //after setFstLstMineralLayer
  Layer* currl = fstsoill;
  SoilLayer* sl; 
  PeatLayer* pl;
  while(currl!=NULL){
    if(currl->isSoil()){
    	sl = dynamic_cast<SoilLayer*>(currl);
    	if(sl->isPeat()){
    	  pl = dynamic_cast<PeatLayer*>(sl);
    	  if(pl->isHumic){
    	  	fstdeepl = currl;
    	  	break;
    	  }
    	}
    	
    }else{
      break;	
    }
  	currl = currl->nextl;
  }
  
  currl =fstminl;
  while(currl!=NULL){
  	if(currl->isSoil()){
  	  	sl = dynamic_cast<SoilLayer*>(currl);
    	if(sl->isPeat()){
    	  pl = dynamic_cast<PeatLayer*>(sl);
    	  if(pl->isHumic){
    	  	lstdeepl = currl;
    	  	break;
    	  }
    	}
  	}else{
  	  break;	
  	}
  	currl=currl->prevl;	
  }
	
}

void Ground::initRockLayers(){
	rock.updateThicknesses(rock.thick); //rock thick in m
	for(int il =rock.num-1; il>=0; il--){
		RockLayer* rl = new RockLayer(rock.dza[il]);
		insertFront(rl);

	}
 
	rocklayercreated=true;
  
};

void Ground::initSnowSoilLayers5Thickness(){
  
  soil.mineral.initThicknesses(soil.mineral.thick); //mineral thick in m
  soil.mineral.updateType(soil.mineral.type, MAX_MIN_LAY);   //Yuan:

  for(int il =soil.mineral.num-1; il>=0; il--){
  	 MineralLayer* ml = new MineralLayer(soil.mineral.dza[il],soil.mineral.type[il], &soillu);
	 insertFront(ml);
	 if(soil.mineral.dza[il]==0.3){
	   drainl = frontl;	
	 }
  }

  //need to do this before deep,
 //since the layers of deep are determined by the thickness of last shlw layer 
   soil.peat.initShlwThicknesses(soil.peat.shlwthick); //fibthick in m
 
   soil.peat.initDeepThicknesses(soil.peat.deepthick); //humthick in m
   for(int il =soil.peat.deepnum-1; il>=0; il--){
	   PeatLayer* pl = new PeatLayer(soil.peat.deepdza[il], 0);//0 means deep organic
	   insertFront(pl);
   }
  
   soil.peat.initShlwThicknesses(soil.peat.shlwthick); //fibthick in m
  for(int il =soil.peat.shlwnum-1; il>=0; il--){
  	 PeatLayer* pl = new PeatLayer(soil.peat.shlwdza[il], 1);//1 means shallow organic
  	 insertFront(pl);
  }
  
  
  soil.moss.updateThicknesses(soil.moss.thick); //moss thick in m
  for(int il =soil.moss.num-1; il>=0; il--){
  	 MossLayer* ml = new MossLayer(soil.moss.dza[il], ed->cd->drgtype);
  	 insertFront(ml);
  }
  


}

void Ground::checkSnowBlwSoil(){
 //there is a case that snow occured belw soil
 /*
 Layer* currl = frontl;
 bool foundsoil=false;
 while(currl!=NULL){
 	if(currl->isSoil()){
 	   foundsoil =true;	
 	}
 	if(currl->isSnow()&& foundsoil){
 	   cout <<"Snow blew soil \n";
 	   exit(-1);
 	  }
 	  currl = currl->nextl;
 	
 };	*/
	
}

void Ground::initSnowSoilLayers5Restart(RestartData * resin){
  
   // cleanSnowSoilLayers();
  
    int numsoil=0;
	
	double dzsoil[MAX_SOI_LAY];
	for (int i=0; i<MAX_SOI_LAY; i++){
		dzsoil[i]=resin->DZsoil[i]; //resin->getDZsoil(dzsoil, ed->cd->reschtid);
	}
	
	int  soiltype[MAX_SOI_LAY];
	for (int i=0; i<MAX_SOI_LAY; i++){
		soiltype[i]=resin->TYPEsoil[i]; //	resin->getTYPEsoil(soiltype, ed->cd->reschtid);
	}
		
	int  mintype[MAX_MIN_LAY];
	for (int i=0; i<MAX_MIN_LAY; i++){
		mintype[i]=resin->TYPEmin[i]; //	resin->getTYPEmin(mintype, ed->cd->reschtid);
	}
	
	soil.mineral.updateThicknesses(soiltype, dzsoil,MAX_SOI_LAY);
	soil.mineral.updateType(mintype, MAX_MIN_LAY);
	for(int il =soil.mineral.num-1; il>=0; il--){
		MineralLayer* ml = new MineralLayer(soil.mineral.dza[il], soil.mineral.type[il], &soillu);//0 means deep organic
		insertFront(ml);
  	  	//if(soil.mineral.dza[il]==0.1){//july 16
  	  	if(soil.mineral.dza[il]==0.3){
  	  		drainl = frontl;	
  	  	}
  	  	numsoil++;
	}
  
	soil.peat.updateShlwThicknesses(soiltype, dzsoil, MAX_SOI_LAY); //fibthick in m
	
	soil.peat.updateDeepThicknesses(soiltype, dzsoil,MAX_SOI_LAY); //humthick in m
	
	  
  for(int il =soil.peat.deepnum-1; il>=0; il--){
  	 PeatLayer* pl = new PeatLayer(soil.peat.deepdza[il], 0);//0 means deep organic
  	 insertFront(pl);
  	 numsoil++;
  }
  
  soil.peat.updateShlwThicknesses(soiltype, dzsoil, MAX_SOI_LAY); //fibthick in m

  for(int il =soil.peat.shlwnum-1; il>=0; il--){
  	 PeatLayer* pl = new PeatLayer(soil.peat.shlwdza[il], 1);//1 means shallow organic
  	 insertFront(pl);
  	 numsoil++;
  }
  
  
  	soil.moss.updateThicknesses(soiltype, dzsoil, MAX_SOI_LAY); //moss thick in m
  	for(int il =soil.moss.num-1; il>=0; il--){
  		MossLayer* ml = new MossLayer(soil.moss.dza[il], ed->cd->drgtype);
  		insertFront(ml);
  		numsoil++;
  	}
  	ed->m_soid.actual_num_soil = numsoil;
	
	//get snow dzs
	double dzsnow[MAX_SNW_LAY];
	for (int i=0; i<MAX_SNW_LAY; i++){
		dzsnow[i]=resin->DZsnow[i]; //resin->getDZsnow(dzsnow, ed->cd->reschtid);
	}
	
	for(int il =MAX_SNW_LAY-1; il>=0; il--){
		if(dzsnow[il]>0){
			SnowLayer* sl = new SnowLayer();
			sl->dz = dzsnow[il];
			insertFront(sl);
		}
  	
	}
	

}
 
//only clean dynamic layers , e.g. snow, organic soil layers
//the mineral and rock is set constant
void Ground::cleanSnowSoilLayers(){
	Layer* currl = frontl;
	Layer* templ;
	SoilLayer* sl;
	SnowLayer* snl;
	//RockLayer* rl;
	while(currl!=NULL){
	  	templ = currl->nextl;
	  	//remove current layer
	  	//cout <<"there are " << "   " <<backl->indl -frontl->indl  << " Layers\n";
	  	if(currl->isSnow()){
	  	 // cout <<"remove snow layer: " <<currl->indl <<"\n";	
	  	  snl = dynamic_cast<SnowLayer*>(currl);
	  	  removeLayer(snl);
	  	
	  	}else if(frontl->isSoil()){
	  	  
	  	  sl = dynamic_cast<SoilLayer*>(currl);
	  	  
	  	  //cout <<"remove soil layer: " <<currl->indl<<"\n";	
	  	  sl->clean();////
	  	  removeLayer(sl);
	  	  
	  	}else{
	  		break;
	  	}
	  currl = templ ;
		 
	}
	
	//removeLayer(frontl);

  
}
//clean all
void Ground::clean(){
	//Layer* currl = frontl;
	//Layer* nextl;
	SoilLayer* sl;
	SnowLayer* snl;
	RockLayer* rl;
	while(frontl!=backl){
	  	//nextl = currl->nextl;
	  	//remove current layer
	  	//cout <<"there are " << "   " <<backl->indl -frontl->indl  << " Layers\n";
	  	if(frontl->isSnow()){
	  	//  cout <<"remove snow layer: " <<frontl->indl <<"\n";	
	  	  snl = dynamic_cast<SnowLayer*>(frontl);
	  	  removeLayer(snl);
	  	}else if(frontl->isRock()){
	  	 // cout <<"remove rock layer: " <<frontl->indl<<"\n";	
	  	  rl = dynamic_cast<RockLayer*>(frontl);
	  	  removeLayer(rl);
	  	}else if(frontl->isSoil()){
	  	 // cout <<"remove soil layer: " <<frontl->indl<<"\n";	
	  	  sl = dynamic_cast<SoilLayer*>(frontl);
	  	  sl->clean();
	  	  removeLayer(sl);
	  	}
	  //if(
		 
	}
	
	//removeLayer(frontl);

  
}




/*! get the totthickness and extrathickness for moss, shallow organic and deep organic*/

void  Ground::updateMossThickness(const double & mossthick){
	
//////First Step/////////////////////
//apply moss change and deep organic change (shallow organic has been changed in Soil_bgc)

// the mimimum thickness of moss is 1.5 cm, and maximum thickness is 4 cm
// the maximum thickness of moss for an ecocystem is 3.7 cm (from the fited equation)
// so there are at most 2 moss layers

bool samerange  = soil.moss.sameThickRange(mossthick);
int oldmossnum = soil.moss.num;
if(samerange){ // no need to change moss layer structure
	
	if(oldmossnum ==1){ //It must be the first soil layer
		fstsoill->dz = mossthick;
		SoilLayer* sl = dynamic_cast<SoilLayer*>(fstsoill);
		sl->updateProperty4LayerChange();
		sl->adjustFronts();
	}else if(oldmossnum ==2){
		fstsoill->nextl->dz = mossthick- fstsoill->dz;
		SoilLayer* sl = dynamic_cast<SoilLayer*>(fstsoill->nextl);
		sl->updateProperty4LayerChange();
		sl->adjustFronts();
	}
	
	
}else{
 //need to change the structure of moss 
 
 soil.moss.updateThicknesses(mossthick);
 
 if(oldmossnum ==0  && soil.moss.num ==1){ //can only increase with time
 	//create a new moss layer
 	MossLayer* ml = new MossLayer(mossthick, ed->cd->drgtype);
      	ml->tem = fstsoill->tem;
		insertBefore(ml, fstsoill);
		fstsoill=ml;
		if(ml->tem>0){
		  ml->liq = ml->maxliq;	
		  ml->ice = 0.;
		  ml->frozen =-1;
		}else{
		  ml->liq = ml->minliq;
		  ml->ice = ml->maxice;	
		  ml->frozen =1;
		}
		
 }else if(oldmossnum==1 && soil.moss.num ==2){ //can only increase with time
 	    
 	      fstsoill->dz = mossthick;
 	      double updz = soil.moss.dza[0] ;
 	       
 	      double lwdz = soil.moss.dza[1];
		  
	  	  MossLayer* ml = new MossLayer(lwdz, ed->cd->drgtype);
	  	  //SoilLayer* mladded=dynamic_cast<SoilLayer*>(ml);
          SoilLayer* mltop=dynamic_cast<SoilLayer*>(fstsoill);

          divideOneSoilLayerU2L(mltop, ml, updz, lwdz);
          mltop->dz = updz;
          mltop->updateProperty4LayerChange();
		  insertAfter(ml, mltop);	
 }
	
}


};

void Ground::updateShlwThickness(){
	//first get the new thickness and number of shlw layers
	double thick =0.;
	int num =0;	
	bool thin=false;
	bool upthick =false;//upper layer is thickner than lower layer

	Layer* currl;
	if(fstshlwl!=NULL){
		num =lstshlwl->solind - fstshlwl->solind +1;
		currl =fstshlwl;
		double prevdz =-1;
		while(currl!=NULL){
			if(currl->indl<=lstshlwl->indl){
				thick +=currl->dz;
				if(currl->dz<0.02){
			 		thin =true;	
				}
				if(currl->dz<prevdz){
			 		upthick =true;	
				}
				prevdz = currl->dz;
			}else{
		 		break;	
			}
			currl =currl->nextl;
		}
	}

	bool samerange =soil.peat.sameShlwThickRange(thick);
	
	SoilLayer* upsl ;
	SoilLayer* lwsl;
	soil.peat.shlwchanged =false;	
	if(upthick||thin || !samerange){
		//combine all shlw layers
		soil.peat.shlwchanged =true;
		soil.peat.initShlwThicknesses(thick);
		//get the ice and liq water, tem for each layer
		//double liq[3], ice[3], tem[3];

		COMBINEBEGIN:
		currl =fstshlwl;
		while(currl!=NULL){
		
			if(currl->indl<lstshlwl->indl){
				upsl = dynamic_cast<SoilLayer*>(currl);
				lwsl = dynamic_cast<SoilLayer*>(currl->nextl);
				//combine this layer and next layer
				combineTwoSoilLayersL2U(lwsl,upsl);
				lwsl->clean();
				upsl->indl = lwsl->indl;
				removeLayer(currl->nextl);
				goto COMBINEBEGIN;
			}else{
				break;
			}
			currl =currl->nextl;
		};
	
		///Divide this one shallow layer into up to 3 layers
		if(num>0 && soil.peat.shlwnum==0){ //remove this layer
			int indl = fstshlwl->solind;
			Layer* nextpl = fstshlwl->nextl;
			removeLayer(fstshlwl);
			if(indl==1){//frontl
				fstsoill= nextpl;
				fstsoill->solind =1;
			}
		
		}else if(soil.peat.shlwnum ==1){
			//only change the properties of layer
			fstshlwl->dz = soil.peat.shlwdza[0];
			SoilLayer* shlwsl = dynamic_cast<SoilLayer*>(fstshlwl);
			shlwsl->updateProperty4LayerChange();
		}else if (soil.peat.shlwnum ==2){//split shlw layer into two
			PeatLayer* plnew1 = new PeatLayer(soil.peat.shlwdza[1], 1);
			SoilLayer* shlwsl = dynamic_cast<SoilLayer*>(fstshlwl);
			divideOneSoilLayerU2L(shlwsl, plnew1, soil.peat.shlwdza[0],soil.peat.shlwdza[1]);
			insertAfter(plnew1, shlwsl);
		}else if (soil.peat.shlwnum ==3){//split shlw layer into 3 layers
			PeatLayer* plnew2 = new PeatLayer(soil.peat.shlwdza[2],1);
			SoilLayer* shlwsl = dynamic_cast<SoilLayer*>(fstshlwl);
			divideOneSoilLayerU2L(shlwsl, plnew2, soil.peat.shlwdza[0]+soil.peat.shlwdza[1],soil.peat.shlwdza[2]);
			insertAfter(plnew2, shlwsl);
		
			PeatLayer* plnew1 = new PeatLayer(soil.peat.shlwdza[1],1);
			divideOneSoilLayerU2L(shlwsl, plnew1, soil.peat.shlwdza[0],soil.peat.shlwdza[1]);
			insertAfter(plnew1, shlwsl);
		}
	
	}else{
		soil.peat.oldshlwthick = soil.peat.shlwthick;
	  	soil.peat.shlwthick    = thick;
	    soil.peat.olddlstshlw  = soil.peat.dlstshlw;
	    //need to change the front in a layer so that the frontdz should not be greater than the layer thickness
	    currl =fstshlwl;
	    SoilLayer* sl;
	    while(currl!=NULL){
		
		if(currl->indl<=lstshlwl->indl){
			sl = dynamic_cast<SoilLayer*>(currl);
			sl->adjustFronts();
		}else{
		 break;	
		}
		currl =currl->nextl;
	};
	
	}
	
	
}

void Ground::updateDeepThickness(){
	//first get the new thickness and number of deep layers
	double thick =0.;
	int num =0;	
	bool thin=false;    //check if too thin of a layer (<2cm)
	bool upthick =false;//check if upper layer is thickner than lower layer

	Layer* currl;
	if(fstdeepl!=NULL){
		num =lstdeepl->solind - fstdeepl->solind +1;
		currl =fstdeepl;
		double prevdz =-1;
		while(currl!=NULL){
			if(currl->indl<=lstdeepl->indl){
				thick +=currl->dz;
				if(currl->dz<0.02){
			 		thin =true;	
				}
			
				if(currl->dz<prevdz){
			 		upthick =true;	
				}
				prevdz = currl->dz;
			
			}else{
		 		break;	
			}
			currl =currl->nextl;
		}
	}

	bool samerange =soil.peat.sameDeepThickRange(thick);
	SoilLayer* upsl ;
	SoilLayer* lwsl;
	if(upthick|| thin || !samerange){
		//combine all deep layers	
		soil.peat.initDeepThicknesses(thick);
		//get the ice and liq water, tem for each layer
		//double liq[3], ice[3], tem[3];
	
		COMBINEBEGIN:	
		currl =fstdeepl;
		while(currl!=NULL){
		
			if(currl->indl<lstdeepl->indl){
				upsl = dynamic_cast<SoilLayer*>(currl);
				lwsl = dynamic_cast<SoilLayer*>(currl->nextl);
				//combine this layer and next layer
				combineTwoSoilLayersL2U(lwsl,upsl); 
				lwsl->clean();
				upsl->indl = lwsl->indl;
				removeLayer(currl->nextl);
	      	
				goto COMBINEBEGIN;
			}else{
		 		break;	
			}
			currl =currl->nextl;
		}
	
		///Divide this one shallow layer into up to 3 layers
		if(num>0 && soil.peat.deepnum==0){ //remove this layer
			int indl = fstdeepl->solind;
			Layer* nextpl = fstdeepl->nextl;
			removeLayer(fstdeepl);
	  		if(indl==1){//frontl
            	fstsoill= nextpl;	
	  			fstsoill->solind =1;
        	}
		
		}else if(soil.peat.deepnum ==1){
			//only change the properties of layer
			fstdeepl->dz = soil.peat.deepdza[0];
			SoilLayer* deepsl = dynamic_cast<SoilLayer*>(fstdeepl);
			deepsl->updateProperty4LayerChange();
		}else if (soil.peat.deepnum ==2){//split deep layer into two
			PeatLayer* plnew1 = new PeatLayer(soil.peat.deepdza[1],0);
			SoilLayer* deepsl = dynamic_cast<SoilLayer*>(fstdeepl);
			divideOneSoilLayerU2L(deepsl, plnew1, soil.peat.deepdza[0],soil.peat.deepdza[1]);
			insertAfter(plnew1, deepsl);
		}else if (soil.peat.deepnum ==3){//split deep layer into 3 layers
			PeatLayer* plnew2 = new PeatLayer(soil.peat.deepdza[2], 0);
			SoilLayer* deepsl = dynamic_cast<SoilLayer*>(fstdeepl);
			divideOneSoilLayerU2L(deepsl, plnew2, soil.peat.deepdza[0]+soil.peat.deepdza[1],soil.peat.deepdza[2]);
			insertAfter(plnew2, deepsl);
		
			PeatLayer* plnew1 = new PeatLayer(soil.peat.deepdza[1],0);
			divideOneSoilLayerU2L(deepsl, plnew1, soil.peat.deepdza[0],soil.peat.deepdza[1]);
			insertAfter(plnew1, deepsl);
		}	
	
	}else{
	  	soil.peat.olddeepthick =soil.peat.deepthick;
	  	soil.peat.deepthick =thick;
	  	
	  	//need to change the front in a layer so that the frontdz should not be greater than the layer thickness
	    currl =fstdeepl;
	    SoilLayer* sl;
	    while(currl!=NULL){
		
			if(currl->indl<=lstdeepl->indl){
				sl = dynamic_cast<SoilLayer*>(currl);
				sl->adjustFronts();
			}else{
		 		break;	
			}
			currl =currl->nextl;
		}
	
	}

};

void  Ground::adjustLayerThickness( const double & mossthick){
    
    updateMossThickness(mossthick);
    updateShlwThickness();
    updateDeepThickness();
	
    setFstSoilLayer();
  	resetLayerIndex();// set
	//updateLayerStructure();
	
	updateLayerIndex();
	updateSnowLayerZ();
	updateSoilLayerZ();
	setLayer5Depth();
	setFstLstShlwLayers();
	setFstLstDeepLayers();
	
	soil.resetFineRootFrac(fstsoill);

    soil.richard.updateSoilStructure(fstsoill);
    	
	
    soil.layer2structmonthly(fstsoill);
   
};

void Ground::updateLayer5FireGrowth(){
	//first update the depth from growth
    //only for the organic layer   
    
    // then if burndepth >0, remove burndepth from layer
    
    // then update diagnostic varibles
	
	// then update the variables in envdata
};



void Ground::burn(const bool & dslmodule){
	//for later version , only set burndepth here, do not change layer
	// change layer at begin of a month in updatelayer5firegrowth
	
 	bool k2run = false;
 	
	//cout<<"burn " <<burndepth <<"\n";
	double burndepth = fd->y_soid.burnthick;
  
  	if(k2run){
  		burndepth =0.08;
  	}
  
  	double rdepth =burndepth;
  	Layer *currl =frontl;
  	// if there is snow, remove it
  	while(currl!=NULL){
  		if(currl->isSnow()){
  	  		removeLayer(currl);   
  		}else{
  	  		break;	             
  		}
//  		currl = currl->nextl;
  		currl = frontl;            //Yuan: currl->nextl does NOT exist at this point
  	}
  
  	while(rdepth>0){
  		currl= fstsoill;
  		SoilLayer* sl= dynamic_cast<SoilLayer*>(currl);
		if(sl->isMineral())	break; 
		
		// later, add the constraints of frozen state
  		if(rdepth >=currl->dz){
  	  		rdepth -= currl->dz;	
  	  		removeLayer(currl);
  	  		fstsoill = frontl;
  	  
  		}else{
  	 		// double tempdz = currl->dz;
  	  		currl->dz -= rdepth;
  	  		if(currl->dz<0.01){
  	  			removeLayer(currl);
  	  			fstsoill=frontl;
  	  		}
  	  		rdepth =0.;
  		}
  	
  	}
  
  	//The left organic layer should be turned into deep organic
  	currl = fstsoill;
  	while (currl!=NULL){
  		if(currl->isSoil()){
  	  		SoilLayer* sl= dynamic_cast<SoilLayer*>(currl);
	  		if(sl->isPeat()){ //there should be no moss left when fire occurs (only 3~4 cm)
	  			//insert
	  			PeatLayer * pl = dynamic_cast<PeatLayer*>(sl);  	
	  			if(pl->isFibric){
	  				pl->humify();
	  			}else{
	  	    		break;	
	  			}
	  		}else{
	  			break;
	  		} 
  		
  		}else {
  	 		break;	
  		}
  		currl = currl->nextl;
  	}
  
   	//for all the organic layers, update soil property
  
  	currl =fstsoill;
   	while (currl!=NULL){
  		if(currl->isSoil()){
  	  		SoilLayer* sl= dynamic_cast<SoilLayer*>(currl);
	  		if(sl->isPeat()){ //there should be no moss left when fire occurs
	  			sl->updateProperty4LayerChange();
	  		}else{
	  			break;
	  		} 
  		}else {
  	 		break;	
  		}
  		currl = currl->nextl;
  	}
  	
  	//remove the fronts of first soil layer
  	//added by shuhua on Apr. 24, 2008
  	SoilLayer* fstss = dynamic_cast<SoilLayer*>(fstsoill);
  	if(fstss->fronts.size()>0){
  		if(fstsoill->nextl->frozen!=0){
  	   		fstss->removeAllFronts(fstsoill->nextl->frozen);	
  		}else{
  			if(fstsoill->nextl->isSoil()){
  				SoilLayer* nsl = dynamic_cast<SoilLayer*>(fstsoill->nextl);
  	   			fstss->removeAllFronts(nsl->fronts[0]->frzing);	
  			}
  		}
  	}
  	
  	if(dslmodule  ){
  	// create one shlw organic from deep organic , so that the orgc can accumulate in this layer
  		PeatLayer* pl = new PeatLayer(0.02, 1);
  		pl->tem = fstsoill->tem;
  		pl->liq = pl->minliq;
  		pl->ice =0.;
  		pl->reac = 0.;
  		pl->nonc = 0.;
  
  		//added by shuhua on Apr 24, 2008
  		//for the case of fire with snow on ground
  		//fstsoil is frozen
  		if(fstsoill->frozen !=0){
  	  		pl->frozen = fstsoill->frozen;
  		}else if (fstsoill->frozen==0){
  	 		SoilLayer* fstsl = dynamic_cast<SoilLayer*>(fstsoill);
  			pl->frozen = fstsl->fronts[0]->frzing;
  		}
  		
  		pl->updateProperty4LayerChange();
  		insertBefore(pl, fstsoill);
  		fstsoill = pl;
  	}
 	
 	//added by shuhua on Apr 22, 2008
 	//manipulate deep organic after burn 
    setFstSoilLayer();
  	resetLayerIndex();  
	updateLayerIndex();
	updateSnowLayerZ();
	updateSoilLayerZ();
	setLayer5Depth();
	setFstLstShlwLayers();
	setFstLstDeepLayers();
  
  	if(k2run){	
  	    PeatLayer* plnew1 = new PeatLayer(0.05, 0);
		SoilLayer* plremain = dynamic_cast<SoilLayer*>(frontl);
		divideOneSoilLayerU2L(plremain, plnew1, 0.02, 0.05);
		insertAfter(plnew1, plremain);
  	}else{
  		soil.peat.dlstshlw =0.02;
 		updateDeepThickness();
  	}
    
    setFstSoilLayer();
  	resetLayerIndex();
	updateLayerIndex();
	updateSnowLayerZ();
	updateSoilLayerZ();
	setLayer5Depth();
	setFstLstShlwLayers();
	setFstLstDeepLayers();
	
	soil.resetFineRootFrac(fstsoill);

    soil.richard.updateSoilStructure(fstsoill);
    soil.layer2structmonthly(fstsoill);
  
};



void Ground::divideOneSoilLayerU2L(SoilLayer*usl, SoilLayer* lsl, const double & updz, const double & lwdz ){
	 	     
	 	  	//lwdz  is not used
	 	  	// totdepth is the distance between peat surface and a layer's bottom
	 	    int oldfrozen = usl->frozen;
	 	    int oldtopfront =0;
	 	    int oldbotfront =0;
	 	    
	 	    if(usl->fronts.size()>0){
	 	      oldtopfront = usl->fronts[0]->frzing;	
	 	      oldbotfront = usl->fronts[usl->fronts.size()-1]->frzing;	
	 	    }
	 	  	double frac = updz/usl->dz;
	  	     lsl->liq = usl->liq *(1- frac);
	  	     lsl->ice = usl->ice*(1-frac);
	  	     lsl->reac = usl->reac*(1-frac);
	  	     usl->reac = usl->reac*frac;
	  	     lsl->nonc = usl->nonc*(1-frac);
	  	     usl->nonc = usl->nonc*frac;
	  		 usl->liq *= frac;
	  	 	 usl->ice *= frac;
	  	  	 usl->dz = updz;
	  	  	 //lsl->dz =lwdz;
	  	  	 
  		 
	  	 
	  	 if(usl->nextl==NULL){
	  	 	lsl->tem = usl->tem;
	  	 	}else{
	  	 	 double ntem = usl->nextl->tem;
	  	 	 double gradient = (usl->tem - ntem)/(- usl->dz -lsl->dz);
	  	 	 lsl->tem = updz * gradient + usl->tem;	
	  	 	}
	  	 	
	  	 
	  	 	if(usl->fronts.size()>=1){
	  	 		for (unsigned int i =0; i<usl->fronts.size(); i++){
	  	 		  if(usl->fronts[i]->dz>=updz){
	  	 		  lsl->addOneFront5Bot(usl->fronts[i]->dz-updz, usl->fronts[i]->frzing);
	  	 		}
	  	 		}
	  	 		
	  	 		while(usl->fronts.size()>0){
	  	 			if(usl->fronts[usl->fronts.size()-1]->dz >=updz){
	  	 				usl->removeBotFront();
	  	 			}else{
	  	 			  break;	
	  	 			}  	 		  	
	  	 		}
	  	 		
	  	 	}
	  	 	
	  	 	if(usl->fronts.size()>0){
	  	 	  usl->frozen =0;	
	  	 	}else{
	  	     if(oldfrozen!=0){
	  	 	 usl->frozen = oldfrozen;
	  	 	 }else if(oldtopfront!=0){
	  	       usl->frozen = oldtopfront;
	  	     }else{
	  	     	 string msg = "cannot determine soil frozen state ";
 	 			 char* msgc = const_cast< char* > ( msg.c_str());
 		 		 throw Exception(msgc, I_FROZEN_STATE);
	  	     }
	  	     
	  	 	  
	  	     
	  	 	}
	  	 	
	  	 	if(lsl->fronts.size()>0){
	  	 	  lsl->frozen =0;	
	  	 	}else{
	  	 	  //added by shuhua on Apr 18, 2008
	  	 	  if(usl->fronts.size()>0){
	  	 	  	 int numfnt = usl->fronts.size();
	  	 	  	 lsl->frozen = -  usl->fronts[numfnt-1]->frzing;
	  	 	  	
	  	 	  }else{
	  	 	  if(oldfrozen!=0){
	  	 	  lsl->frozen = oldfrozen;
	  	 	  }else if(oldbotfront!=0){
	  	 	  	lsl->frozen= - oldbotfront;
	  	 	  }else{
	  	 	  	 string msg = "cannot determine soil frozen state ";
 	 			 char* msgc = const_cast< char* > ( msg.c_str());
 		 		 throw Exception(msgc, I_FROZEN_STATE);
	  	 	  }
	  	 	 
	  	 	  }
	  	 	}
	  	 	
	  	 	lsl->updateProperty4LayerChange();
	  	 	usl->updateProperty4LayerChange();
	  	 	
	  	 	
	  	 		//usl->checkFronts();
	  	 		//lsl->checkFronts();
}

void Ground::combineTwoSoilLayersU2L(SoilLayer* usl, SoilLayer* lsl){
 
   	  	  lsl->reac +=usl->reac;
   	  	  lsl->nonc +=usl->nonc;
   	  	  
   	  	  lsl->liq +=usl->liq;
   	  	  lsl->ice +=usl->ice;
   	  	  lsl->tem = usl->tem;	
	  	  lsl->dz += usl->dz;	
	  	  
	  	  
	  		int lfnum =lsl->fronts.size();
	  		if(lfnum>0){
	  		  for(int i =0; i<lfnum; i++){
	  		  	 lsl->fronts[i]->dz += usl->dz;
	  		  }	
	  		}
	  		int ufnum = usl->fronts.size();
	  		if( ufnum>0){
	  		   for( int i=ufnum-1 ; i>=0; i--){
	  		   	 double tempfdz = usl->fronts[i]->dz;
	  		   	 int tempfrzing = usl->fronts[i]->frzing;
	  		   	 
	  		   	 lsl->addOneFront5Top(tempfdz, tempfrzing);
	  		   }	
	  			
	  		}
	  		if(lsl->fronts.size()>0){
	  	 	  lsl->frozen =0;	
	  	 	}else{
	  	 	   if(lsl->frozen==1 && lsl->tem>0){
	  	 	  	 lsl->tem =-0.01;
	  	 	  }else if(lsl->frozen==-1 && lsl->tem<0){
	  	 	  	 lsl->tem =0.01;
	  	 	  }
	  	 	}
	  	 	
	  lsl->updateProperty4LayerChange(); 			
	  usl->updateProperty4LayerChange(); 			
}


void Ground::combineTwoSoilLayersL2U(SoilLayer* lsl, SoilLayer* usl){
 
   	  	  usl->reac +=lsl->reac;
   	  	  usl->nonc +=lsl->nonc;
   	  	  usl->liq +=lsl->liq;
   	  	  usl->ice +=lsl->ice;
   	  	  
   	  	 // usl->orgc +=lsl->orgc;
   	  	 
	  	  	if(lsl->fronts.size()>0){
	  		  for(unsigned int i =0; i<lsl->fronts.size(); i++){
	  		  	 
	  		  	 usl->addOneFront5Bot(lsl->fronts[i]->dz +usl->dz, lsl->fronts[i]->frzing);
	  		  }	
	  		}
	  		
	  		 usl->dz += lsl->dz;
	        if(usl->fronts.size()>0){
	  	 	  usl->frozen =0;	
	  	 	}else{
	  	 	  //if(usl->frozen == lsl->frozen){
	  	 	  	//nothing will change
	  	 	  //}
	  	 	  if(usl->frozen==1 && usl->tem>0){
	  	 	  	 usl->tem =-0.01;
	  	 	  }else if(usl->frozen==-1 && usl->tem<0){
	  	 	  	 usl->tem =0.01;
	  	 	  }
	  	 	}
	  	usl->updateProperty4LayerChange(); 			
	  	lsl->updateProperty4LayerChange(); 			
	  	   	  	  
}




void Ground::setCohortData(const int & drgtypep,const int & vegtypep){
     vegtype = vegtypep;
     drgtype = drgtypep;	
};

void Ground::setEnvData(EnvData* edp){
	ed = edp;
	soil.setEnvData(ed);
	soil.richard.setEnvData(ed);
	snow.setEnvData(ed);
	rock.setEnvData(ed);
};

void Ground::setFirData(FirData* fdp){
  	 fd =fdp;
  	 soil.setFirData(fd);
  	 snow.setFirData(fd);
  	 
};

