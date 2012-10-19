#include "Stefan.h"

Stefan::Stefan(){
	 ITMAX =30;
     TSTEPMAX = 1;
     TSTEPORG =0.5;
     
     ttole =0.05;  // don't change this threshold
     // I have tried 0.5 , and got some unrealistic results
};

Stefan::~Stefan(){
	
};



int Stefan::updateFronts(const double & tdrv, Layer *frontl, Layer *backl,Layer *fstsoill, Layer* lstminl, const int & mind){

	int error = 0;

	for(int i=0; i<backl->indl; i++){
 	     temupdated[i]=false;;	
 	     temold[i] =-999.;
 	}
 	
 	// first , top->down propogation of front
 	Layer* currl; 
 	SoilLayer* sl;
	
 	double tdrv0=tdrv;
 	
 	currl=frontl;
 	double dse = fabs( tdrv0 * 86400); // the extra degree second, assume using one day time step
 	double sumresabv  =0. ; // sum of resistence for above layers;

    double tkres; // thermal conductivity for calculating resistence
 	double tkfront; // thermal conductivity for calculating part front depth
 	double tkunf, tkfrz;
 	int frozenstate; // the frozen state of a soil layer based on the driving temperature

    if(tdrv>0){
      frozenstate =-1;	
   	}else {
   	  frozenstate =1;	
   	}
    currl=frontl;
    while(currl!=NULL){
    // if(currl->isRock())break;
     temold[currl->indl -1] = currl->tem;
     currl=currl->nextl;	
    }
    
    currl =frontl;   
 	while(currl!=NULL && dse>0.){
 		if(currl->isRock())break; // for bedrock, break
 		
 		tkunf = currl->getUnfThermCond();
 	    tkfrz = currl->getFrzThermCond();
 		   if(tdrv<0){
 		   	 tkres = tkfrz;
 		   	 tkfront =tkunf;
 		   }else {
 		   	 tkres = tkunf;
 		   	 tkfront = tkfrz;
 		   }
 		    
 		  if(currl->isSnow()){
 		  	processSnowLayer( tkres,tkfront ,dse,sumresabv,  tdrv, currl);
 		  }else if(currl->isSoil()){
 		  	 sl = dynamic_cast<SoilLayer*>(currl);
 		     error = sl->checkFronts();
 		     if (error != 0) return error;

 		  	 processSoilLayer5Top(frozenstate, tkres, tkfront, dse,  sumresabv, tdrv0,
 								 sl, frontl, backl);
 			 error = sl->checkFronts();
 		     if (error != 0) return error;

 			 sl->updateWater5Front();
 							 
 		  }
 		
 		currl=currl->nextl;
 	};
 	
 	//bottom up
 	
 	Layer* lstfntl=NULL; // the last layer with front(s)
 	currl = backl;
 	while(currl!=NULL){
 	  if(currl->isSoil()){
 	  SoilLayer* sl = dynamic_cast<SoilLayer*>(currl);
 	  if(sl->fronts.size()>0){
 	  	lstfntl = currl;
 	  	break;
 	  } 	
 	  }else if (currl->isSnow()){
 	  	break;
 	  }
 	  currl=currl->prevl;	
 	}
 	
 
 	Layer* botdrvl; // bottom driving layer;
 	//determine the bottom driving layer
 	// 1) should be at least 2 meters away from the lstfntl
    
 	if(lstfntl!=NULL){
 	if(mind >8){ 	
 		if(lstminl->frozen ==0){
 		  botdrvl= lstminl ->nextl;	
 		}else{
 		  botdrvl =lstminl;
 		}
 	   
 	  //botdrvl= lstminl->nextl;	
 	}else{//during growing season using deeper temperature as bottom driving
 		botdrvl =lstminl ->nextl->nextl;
 	}
 	SoilLayer* slstfntl = dynamic_cast< SoilLayer*>(lstfntl);
 	int numfnt = slstfntl->fronts.size();
        if(slstfntl->fronts[numfnt-1]->frzing==1  && botdrvl->tem<0){
          botdrvl=NULL;	
        }else if(slstfntl->fronts[numfnt-1]->frzing==-1 && botdrvl->tem>0){
          botdrvl=NULL;	
        } 	 
 	}
 	
    
 	if(lstfntl!=NULL && botdrvl!=NULL){
 	double sumresblw=0 ;
 	//
 	currl =botdrvl;
 	Layer * prevl = currl->prevl;
 	double tdrv1 = botdrvl->tem;
 	if(tdrv1>0){
 	  frozenstate =-1;	
 	  }else if(tdrv1<0){
 	  frozenstate =1;	
    }
 		  	   	
 	dse = fabs(tdrv1 * 86400);
 	while(prevl!=NULL && dse>0){
 	       tkunf = currl->getUnfThermCond();
 		   tkfrz = currl->getFrzThermCond();
 		   if(tdrv1<0){
 		   	 tkres = tkfrz;
 		   	 tkfront =tkunf;
 		   }else {
 		   	 tkres = tkunf;
 		   	 tkfront = tkfrz;
 		   }
 		   
 		   if(prevl->isRock()){
 		   	 sumresblw += prevl->dz/tkres;
 		   }else if(prevl->isSoil()){
 		   	  SoilLayer* psl = dynamic_cast<SoilLayer*>(prevl);
 		   	  processSoilLayer5Bot(frozenstate, tkres, tkfront,dse,  sumresblw, tdrv1,
 								 psl, frontl, backl);
 		   }else if(prevl->isSnow()){
 		   	break;
 		   }
 	  prevl=prevl->prevl;	
 	}
 	
 	
 	
 	}

 	error = checkFrontsValidity(fstsoill);
 	//interpolate soil/snow temperatures
 	//interpolateUpperTemps5Front(tdrv, frontl);
    if (error != 0) return error;

    return 0;
 };
 
 void Stefan::processSnowLayer(double const & tkres, double const & tkfront ,
                        double & dse, double & sumresabv, const double & tdrv,
 						Layer* currl){
 	SnowLayer* sl; // check to see whether the dse can totally melt a snow layer
 	sl = dynamic_cast<SnowLayer*>(currl);
 	double dz = sl->dz;
 	double dsn;
 	if(tdrv>0){
 		
 		double volwat = sl->ice/(917*dz);
 		dsn = getDegSecNeeded(dz, volwat, tkfront, sumresabv);
 		if(dse>=dsn){
 		  sl->frozen =-1;
 		  sumresabv +=dz/tkres;
 		  dse -= dsn;	
 		}else{
 		  sl->frozen =0;	
 		  dse =0.;
 		}
 	}else{
 		//update the resistence
 		sumresabv +=dz/tkres;
 	}
 	
 	
 }
 
 
void  Stefan::processSoilLayer5Top(const int &frozenstate, double const & tkres, double const & tkfront ,
                        double & dse, double & sumresabv, const double & tdrv,
 						SoilLayer* sl,  Layer *frontl, Layer *backl){
 	//only deal with the front(s) in one layer	
 	
 	//create sublayer, based on the number of fronts in this layer
 	//??
 	
 
 	double volwat; // volumetric water content;
 	double dz; // thickness
 	double partd;//part of layer is freezed or thawed
 	double dsn ; // the degree seconds needed to fully freeze/thaw one layer
 	
 	 int numfnt = sl->fronts.size();
 	 
 	//first step is to create fronts at  the top of a layer
 	 if(numfnt>0){
 	 if((sl->fronts[0]->frzing==1 &&tdrv>0 ) or (sl->fronts[0]->frzing==-1 &&tdrv<0 )){
 	 	// in this way, the first front will be always freezing when tdrv<0
 	 	sl->addOneFront5Top(0., -sl->fronts[0]->frzing);
 	 }
 	 }else{
 	 	 if((sl->frozen==1 &&tdrv>0 ) or (sl->frozen==-1 &&tdrv<0 )){
 	 		sl->addOneFront5Top(0., - sl->frozen);
 	 		sl->frozen =0;
 		 }
 	 	
 	 }
 //	double secinday=86400.;
 	 
 	 double lastfntz =0.;
 	 double beforedse =0.;
 	 double afterdse =0.;
 	 
 	 while(dse>0 && lastfntz<sl->dz){
 	  numfnt = sl->fronts.size();

 	  if(numfnt==0){
 	  	dz = sl->dz - lastfntz;
 	  	sumresabv += (dz)/tkres;
 	  	sl->frozen =frozenstate;
 	  	lastfntz = sl->dz;
 	  	
 	  }else if(numfnt==1){	
 	  	dz = sl->fronts[0]->dz  -lastfntz;
 	  	
 	  	lastfntz = sl->fronts[0]->dz;
 	  	//double tempres = sl->fronts[0]->dz/tkres;
 	  	sumresabv += dz/tkres;
 	    dz =sl->dz  -  lastfntz;
 	   	
 	   	//top front will move down 
 	   	volwat = sl->getEffVolWater();
 		dsn = getDegSecNeeded(dz, volwat, tkfront, sumresabv);
 	   	if(dse>=dsn){
 	   	   beforedse =dse;
 	   	   dse -= dsn;
 	   	   afterdse = dse;
 	   	   //changed by sy Nov27
 	   	   //updateUpperTemps5Front(sl, beforedse,afterdse, tdrv, frozenstate, dz,tempres);
 	   	
 	   	  sl->removeTopFront();
 	   	  sl->frozen =frozenstate;
 	   	  Layer* nextl = sl->nextl;
 	   	  if(nextl!=NULL){
 	   	  	 if(nextl->isSoil()){
 	   	  	   SoilLayer* nsl = dynamic_cast<SoilLayer*>(nextl);
 	   	  	   nsl->addOneFront5Top(0, frozenstate);	
 	   	  	 }
 	   	  }
 	   	  // next step will go to no front branch;
 	   	}else{
 	   	  beforedse =dse;
 	   	  partd = getPartialDepth(volwat, tkfront, sumresabv, dse);
 	   	  afterdse = 0;
 	   	  //changed by sy Nov27
 	   	  //updateUpperTemps5Front(sl, beforedse,afterdse, tdrv, frozenstate, partd,tempres);

 		  sl->moveOneFrontDown(partd,0);
 		  dse =0;
 	   	}
 	  }else if(numfnt>=2){
 	  	dz = sl->fronts[0]->dz  -lastfntz;
 	  	double tempres = sl->fronts[0]->dz/tkres;
 	  	sumresabv += tempres;
 	  	lastfntz = sl->fronts[0]->dz;
 	  	dz = sl->fronts[1]->dz- sl->fronts[0]->dz;
 	  	volwat = sl->getEffVolWater();
 		dsn = getDegSecNeeded(dz, volwat, tkfront, sumresabv);
 	    if(dse>=dsn){
 	      beforedse = dse;
 	      dse -=dsn;
 	      afterdse = dse;
 	      //changed by sy Nov27
 	   	//updateUpperTemps5Front(sl, beforedse,afterdse, tdrv, frozenstate, dz,tempres);
 	      
 	      sl->removeTopFront(); //remove first two fronts	
 	      sl->removeTopFront();
 	      if(sl->fronts.size()>0){
 	      	  lastfntz = sl->fronts[0]->dz;
 	      }
 	    }else{
 	      beforedse =dse;
 	      partd = getPartialDepth(volwat, tkfront, sumresabv, dse);
 	      afterdse = 0;
 	   	  //changed by sy Nov27
 		  //updateUpperTemps5Front(sl, beforedse, afterdse, tdrv, frozenstate, partd, tempres);
 		  sl->moveOneFrontDown(partd,0);
 		  dse =0;
 		  
 	    }
 	  }
 	 	
	 }
	};
 
 
  
void  Stefan::processSoilLayer5Bot(const int &frozenstate, double const & tkres, double const & tkfront ,
                        double & dse, double & sumresblw, const double & tdrv,
 						SoilLayer* sl,  Layer *frontl, Layer *backl){
 
 	double volwat; // volumetric water content;
 	double dz; // thickness

 	double partd;//part of layer is freezed or thawed
 	double dsn ; // the degree seconds needed to fully freeze/thaw one layer
 	
 	int numfnt = sl->fronts.size();

 	 if(numfnt>0){
 	 if((sl->fronts[numfnt-1]->frzing==1 &&tdrv<0 ) or (sl->fronts[numfnt-1]->frzing==-1 &&tdrv>0 )){
 	 	// there should be no new front created from bottom;
 	  
 		string msg = "there should be no new front created from bottom 1";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_BOTTOM_NEW_FRONT);
 		
 	 }
 	 }else{
 	 	 if((sl->frozen==1 &&tdrv>0 ) or (sl->frozen==-1 &&tdrv<0 )){
 	 	 	if(sl->nextl->isRock()){//to exclude of the case that rock layer change from very small minus temperature
 	 	 		// to very small positive temperature added by shuhua Apr 22, 2008
 	 	 	  return;	
 	 	 	}else{
 	 		string msg = "there should be no new front created from bottom 2";
 			char* msgc = const_cast< char* > ( msg.c_str());
 			throw Exception(msgc, I_BOTTOM_NEW_FRONT);
 	 	 	}
 		 }
 	 	
 	 } 

 	 
 	 double lastfntz =0.;//used to record the latest front processesd;
 	 //the difference between the bottom of a layer to the front
 	 while(dse>0 && lastfntz<sl->dz){
 	  numfnt = sl->fronts.size();
        
 	   	  
 	  if(numfnt==0){
 	  	dz = sl->dz - lastfntz;
 	  	sumresblw += (dz)/tkres;
 	  	sl->frozen =frozenstate;
 	  	lastfntz = sl->dz;
 	  }else if(numfnt==1){	
 	  	dz = sl->dz - sl->fronts[numfnt-1]->dz  -lastfntz;
 	  	lastfntz = sl->dz -sl->fronts[numfnt-1]->dz;
 	  	sumresblw += dz/tkres;
 	    dz = sl->fronts[numfnt-1]->dz;
 	   
 	   	//bot front will move up 
 	   	volwat = sl->getEffVolWater();
 		dsn = getDegSecNeeded(dz, volwat, tkfront, sumresblw);
 	   	if(dse>=dsn){
 	   	  dse -= dsn;
 	   	  sl->removeBotFront();
 	   	  sl->frozen =frozenstate;
 	   	  Layer* prevl = sl->prevl;
 	   	  if(prevl!=NULL){
 	   	  	 if(prevl->isSoil()){
 	   	  	   SoilLayer* psl = dynamic_cast<SoilLayer*>(prevl);
 	   	  	   psl->addOneFront5Bot(psl->dz, -frozenstate);	
 	   	  	 }
 	   	  }
 	   	  // next step will go to no front branch;
 	   	}else{
 	   	  partd = getPartialDepth(volwat, tkfront, sumresblw, dse);
 		  sl->moveOneFrontUp(partd,numfnt-1);
 		  dse =0;
 	   	}
 	  }else if(numfnt>=2){
 	  	dz = sl->dz - sl->fronts[numfnt-1]->dz  -lastfntz;
 	  	sumresblw += dz/tkres;
 	  	lastfntz = sl->dz - sl->fronts[numfnt-1]->dz;
 	  	dz =  sl->fronts[numfnt-1]->dz- sl->fronts[numfnt-2]->dz;
 	  	volwat = sl->getEffVolWater();
 		dsn = getDegSecNeeded(dz, volwat, tkfront, sumresblw);
 	    if(dse>=dsn){
 	      dse -=dsn;
 	      sl->removeBotFront(); //remove first two fronts	
 	      sl->removeBotFront();
 	      //added by shuhua on Apr 20, 2008, 
 	      //there is a case that the while loop can be break, when there is/are fronts in one layer
 	        if(sl->fronts.size()>0){
 	          
 	      	  lastfntz = sl->dz -sl->fronts[sl->fronts.size()-1]->dz;
 	      }
 	    }else{
 	      partd = getPartialDepth(volwat, tkfront, sumresblw, dse);
 		  sl->moveOneFrontUp(partd,numfnt-1);
 		  dse =0;
 		
 	    }
 	  }
 	 	
 }
 	 }


 
 
 
 
 double Stefan::getDegSecNeeded( const double & dz, 
 				const double & volwat,  const double & tk, const double & sumresabv){
 	/*input
 	 * 	   dz: the thickness of  fraction of (or whole)  soil layer: 
 	 *     volwat: volumetric water content, either ice or liquid water
 	 *     tk: thermal conductivity of that part of (or whole) layer
 	 *     tdrv: the driving temperature
 	 *     sumresabv: the sum of resistance for all the layers above
 	 */
 	 double needed=0.;
 	 
 	 double effvolwat = volwat;
 	// double lhfv = LHFUS *1000.; // volumetric latent heat fusion of water
 	 double lhfv = 3.34e8;
 	 needed = lhfv * effvolwat * dz * (sumresabv +0.5 * dz/tk);
 	 
 	 return needed;
 };
 
 //calculate partial depth based on extra degree seconds
 double Stefan::getPartialDepth(const double & volwat, const double & tk,
 								const double & sumresabv, const double & dse){
/* input
 *  dse: extra degree second
 */ 									
 	double partd;
 	double effvolwat = volwat;
 
 	//double lhfv = LHFUS *1000.; // volumetric latent heat fusion of water
 	double lhfv = 3.34e8;
 	double firstp = tk * sumresabv;
 	double second1 = tk * tk * sumresabv * sumresabv;
 	double second2 = 2 * tk * dse/(lhfv * effvolwat);
 	partd = -1 * firstp  + sqrt(second1 + second2) ;
 	
 	return partd;
 };
 
 //check the validity of fronts in soil column
 int Stefan::checkFrontsValidity(Layer *fstsoill){
 	Layer*currl=fstsoill;
 	SoilLayer* sl;
 	//int upfrnt =0;
 	//int curfrnt;
 	//int numfnt =0;
 	/*
 	int prevfrozen = fstsoill->frozen;

 	vector<int> fntattv;
 	while(currl!=NULL){
 		if(currl->isSoil()){
 		  sl = dynamic_cast<SoilLayer*>(currl);
 		  if(fabs(sl->frozen -prevfrozen +0.0)>1){
 		  	 cout <<"frozen and unfrozen discontinuity in stefan\n";
 		  	 exit(-1);
 		  }
 		  sl->checkFronts();
 		  prevfrozen = sl->frozen;
 		}else{
 		  break;
 		}

 		currl=currl->nextl;
 	};*/

 	int prevfnt =0;
 	int numfnt;
 	while(currl!=NULL){
 			if(currl->isSoil()){
 		  sl = dynamic_cast<SoilLayer*>(currl);
 		  numfnt=sl->fronts.size();
 		  for(int i=0; i<numfnt; i++){
 		  	if(i==0){
 		  	 if(currl->prevl !=NULL){
 		  	 	if(currl->prevl->isSoil()){
 		  	 	SoilLayer* psl = dynamic_cast<SoilLayer*>(currl->prevl);
 		  	 	if(psl->fronts.size()==0){
 		  	 		if(psl->frozen != sl->fronts[i]->frzing){
 		  	 			string msg = "front should have same attribute as previous layer frozen state";
  						char* msgc = const_cast< char* > ( msg.c_str());
  						//throw Exception(msgc, I_FRONT_INCONSISTENT);
  						return -1;
 		  	 		}

 		  	 	}

 		  	 }
 		  	 }
 		  	}

 		  	 if(sl->fronts[i]->frzing ==prevfnt){

 		  	 	 string msg = "adjacent fronts should be different";
 // 						char* msgc = const_cast< char* > ( msg.c_str());
 // 						throw Exception(msgc, I_FRONT_INCONSISTENT);     //Yuan: don't crash the model
 		  	 }else{
 		  	    prevfnt = sl->fronts[i]->frzing ;
 		  	 }
 		  };

 		}else{
 		  break;
 		}

 		currl=currl->nextl;
 	};


 	/*
 	Layer*currl=fstsoill;
 	SoilLayer* sl;

 	while(currl!=NULL){
 		if(currl->isSoil()){
 		  sl = dynamic_cast<SoilLayer*>(currl);

 		  if(sl->fronts.size()==1||sl->fronts.size()==3 ){
 		  	if(sl->prevl!=NULL  && sl->nextl!=NULL){
 		  	if(sl->prevl->frozen == sl->nextl->frozen  && sl->nextl->frozen !=0){

 		  			 cout <<"frozen states are the same above and below layer with front\n";
 		  	       exit(-1);
 		  	}

 		  }
 		  } else   if(sl->fronts.size()==2){
 		  	if(sl->prevl!=NULL  && sl->nextl!=NULL){
 		  	if(sl->prevl->frozen != sl->nextl->frozen  && sl->nextl->frozen !=0  && sl->prevl->frozen !=0 ){

 		  			 cout <<"frozen states should be  the same above and below layer with front\n";
 		  	       exit(-1);
 		  	}

 		  }
 		  }

 		}else{
 		  break;
 		}

 		currl=currl->nextl;
 	}*/

 	return 0;
 };

 void Stefan::interpSnowTemp(Layer* frontl, Layer* fstsoill,const double & tdrv){


   	double tsoil = fstsoill->nextl->tem;
   	// get total snow depth
   	double dzsum =frontl->z+fstsoill->dz;
   	double deltat = tdrv -tsoil;
   	double dzsno;
   	double dzsoi;
   	double dz;
   	double gradient;
   	if(dzsum >0){
   		gradient = deltat/dzsum;

   		Layer* currl =fstsoill;
   		while(currl!=NULL){
   			if(currl->isSoil()){
   				dzsoi = currl->dz;
   				dz = dzsoi;
   			}else{
   				dzsno = currl->z;
   				dz = dzsno +dzsoi;
   			}
   			currl->tem = tsoil + gradient * dz;
   			currl=currl->prevl;
   		}
   	}

 };

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // update soil temperatures
 
void Stefan::updateTemps(const double & tdrv, Layer *frontl, Layer *backl ,Layer* fstsoill,
  						Layer* fstfntl, Layer *lstfntl ){
  	   
     itsumall =0;
     itsumabv =0;
     itsumblw =0;
  	 
     for(int i=0; i<MAX_GRN_LAY+2; i++){
    	 t[i] =-999.;
     }
  	
  	 
  //	 Layer* currl=frontl;
  	 
  	 if(fstfntl ==NULL && lstfntl==NULL){
  		 // no fronts in soil column
  		 // for virtual layer
  		 processWholeColumn(frontl, backl, fstfntl, lstfntl, tdrv);
  		 itsumall =itsum;

  	 }else if(fstfntl->indl ==lstfntl->indl){
  		  //added
  		  processAboveLayers(frontl, backl, fstfntl, lstfntl, tdrv);

  		  if(lstfntl->indl<backl->indl){
  			  processBelowLayers(frontl, backl, fstfntl, lstfntl, tdrv);
  			  itsumblw=itsum;
  		  }

  		  //Yuan: The below-frontLayer calculation seems not correct, so the following added
  		  if (fstfntl->indl>frontl->indl && fstfntl->indl<backl->indl) {
  			  fstfntl->tem = (fstfntl->prevl->tem*fstfntl->prevl->dz
  					         +fstfntl->nextl->tem*fstfntl->nextl->dz)
  		                  /(fstfntl->prevl->dz+fstfntl->nextl->dz);
  		  }
  		  itsumall=itsumabv +itsumblw;

  	 }else if(fstfntl->indl !=lstfntl->indl){
  	   		 // there are two different layers which contain front(s)

  		 processAboveLayers(frontl, backl, fstfntl, lstfntl, tdrv);
  	  
  		 if(lstfntl->indl<backl->indl){
  			 processBelowLayers(frontl, backl, fstfntl, lstfntl, tdrv);
  			 itsumblw=itsum;
  	  	
  			 processBetweenLayers(frontl, backl, fstfntl, lstfntl, tdrv);
  		 }

  		 itsumall=itsumabv +itsumblw;
  	  
  	 }
  	 
  	 //check wheter is nan
  	 for(int il=0 ; il<MAX_GRN_LAY+2; il++){
   	
  		 if(isnan(tld[il])){
	 
  			 string msg = "tld is nan";
  			 //char* msgc = const_cast< char* > ( msg.c_str());
  			 //throw Exception(msgc, I_NAN_TLD); //Yuan: don't crash the model
  			 tld[il]=tid[il];       //Yuan: rather the initial values (this is a temperary settle!!!!)
  			 break;
  		 }
  	 }
  	
};

void Stefan::processWholeColumn(Layer* frontl, Layer *backl, Layer*fstfntl, Layer*lstfntl, const double & tdrv){
     double tc, hcap;
  	 int startind, endind;

     int ind=0;
  	 t[ind] = tdrv;
  	 e[ind] = tdrv;
  	 s[ind] =0.;
  	 cn[ind] =1e20f;// assume very big thermal conductivity for t his virtual layer
  	 cap[ind] =0.; // assume no heat capacity for this virtual layer
   //  cn[ind] =  frontl->getThermalConductivity() * 10/frontl->dz; //1e20f;// assume very big thermal conductivity for this virtual layer
  //	 cap[ind] = frontl->getHeatCapacity()/10. * frontl->dz; //0.; // assume no heat capacity for this virtual layer

  	 Layer* currl =frontl;
  	 while(currl!=NULL){
  	 	ind++;
  	 	t[ind] =currl->tem;
  	 	dx[ind] = currl->dz;
  	 	tc = currl->getThermalConductivity();
  	 	hcap= currl->getHeatCapacity();
  	 	cn[ind] = tc/dx[ind];
  	 	cap[ind] = hcap * dx[ind];
  	 	currl=currl->nextl;
  	 }

  	 ind =backl->indl+1;
  	 t[ind] = t[ind-1];
 	 s[ind] = 0.;
 	 e[ind]= t[ind];
     startind =0; //always zero
     endind= ind; //
     iterate(startind, endind, true, true, frontl);

     currl=frontl;
     while(currl!=NULL){

       currl->tem= tld[currl->indl];
       // Yuan: for output
	   currl->tcond = currl->getThermalConductivity();

       currl=currl->nextl;
     }
     if(tdrv<0 && frontl->tem<tdrv){
       frontl->tem = tdrv;
     }else if(tdrv>0 && frontl->tem>tdrv){
       frontl->tem = tdrv;
     }

};

void Stefan::processAboveLayers(Layer* frontl, Layer *backl, Layer*fstfntl, Layer*lstfntl, const double & tdrv){
	double tc, hcap;
  	int startind, endind;
  	//If during spring, when the thawing front is within 15 cm and the soil thickness is
  	//not in increasing order, it is possible that updated soil temperature is greater than 50 degC
  	// when this case happened use linear interpolation
  	SoilLayer* fsl = dynamic_cast<SoilLayer*>(fstfntl);

  	int frzfnt = fsl->fronts[0]->frzing;
  	/*SoilLayer* fsl = dynamic_cast<SoilLayer*>(fstfntl);
  	float fstfntz = fsl->fronts[0]->dz + fsl->z;
  	int frzfnt = fsl->fronts[0]->frzing;

  	bool dzincreasing =true;
  	if(frzfnt==-1 && fstfntz<0.2){


  		if(fstfntl->solind>=3){
  		   if(fstfntl->prevl->dz < fstfntl->prevl->prevl->dz){
  		   	 dzincreasing =false;
  		   }else if(fsl->fronts[0]->dz  < fstfntl->prevl->dz){
  		     	dzincreasing =false;
  		   }

  		}

  		if(!dzincreasing){
  			//cout <<"interpolate upper layers\n";
  			interpolateUpperTemps5Front(tdrv, frontl);
  			return;
  		}

  	}else 	if (fstfntl->indl<2) {
  		interpolateUpperTemps5Front(tdrv, frontl);
  		return;
  	}*/

  	int ind=0;
  	t[ind] = tdrv;
  	e[ind] = tdrv;
  	s[ind] =0.;
  	cn[ind] =1e20f;// assume very big thermal conductivity for this virtual layer
  	cap[ind] =0.; // assume no heat capacity for this virtual layer

  	Layer* currl =frontl;
  	while(currl!=NULL){
  	 	ind++;
  	 	t[ind] =currl->tem;
  	 	if(currl->frozen==1 && t[ind]>0){
  	 		t[ind] =-0.01;
  	 	}else if (currl->frozen==-1 &&t[ind]<0){
  	 		t[ind] =0.01;
  	 	}
  	 	dxold[ind] = dx[ind];
  	 	dx[ind] = currl->dz;
  	 	tc = currl->getThermalConductivity();
  	 	hcap= currl->getHeatCapacity();
  	 	cn[ind] = tc/dx[ind];
  	 	cap[ind] = hcap * dx[ind];

  	 	currl=currl->nextl;
  	 	if(currl!=NULL){
  	 		if(currl->indl >fstfntl->indl)break;
  	 	}
  	 }

  	 if(frzfnt==1){
  		 t[ind] = -0.1; //near front tem can be assumed to be zero
  	 }else{
  		 t[ind] =0.1;
  	 }
  	 ind =fstfntl->indl+1;
  	 t[ind] = 0;
 	 s[ind] = 0.;
 	 e[ind]= t[ind];
     startind =0; //always zero
     endind= ind; //
     iterate(startind, endind, false, true, frontl);

     currl=frontl;
     while(currl!=NULL){

       currl->tem= tld[currl->indl];

       // Yuan: for output
	   currl->tcond = currl->getThermalConductivity();

       currl=currl->nextl;
       if(currl!=NULL){
    	   if(currl->indl>fstfntl->indl) break;
       }
     }

     if(tdrv<0 && frontl->tem<tdrv){
    	 frontl->tem = tdrv;
     }else if(tdrv>0 && frontl->tem>tdrv){
    	 frontl->tem = tdrv;
     }

};

void Stefan::processBelowLayers(Layer* frontl, Layer *backl, Layer*fstfntl, Layer*lstfntl, const double & tdrv){
    double tc, hcap;
  	int startind, endind;

     int ind=lstfntl->indl;;
  	 t[ind] = -0.1; //assume the front is the top interface of virtual layer
  	 e[ind] = 0.;
  	 s[ind] = 0.;

     SoilLayer* slstfntl = dynamic_cast<SoilLayer*>(lstfntl);
     int numfnt = slstfntl->fronts.size();

     dx[ind] = max( (double)0.5 * lstfntl->dz,(double) lstfntl->dz -slstfntl->fronts[numfnt-1]->dz);
     if(slstfntl->fronts[numfnt-1]->frzing==1){
  	 	cn[ind] = slstfntl->getUnfThermCond()/dx[ind];
  	 	cap[ind] = slstfntl->getUnfVolHeatCapa()*dx[ind];
  	 }else if(slstfntl->fronts[numfnt-1]->frzing==-1){
  	 	cn[ind] = slstfntl->getFrzThermCond()/dx[ind];
  	 	cap[ind] = slstfntl->getFrzVolHeatCapa()*dx[ind];
  	 }

     Layer*	 currl =lstfntl->nextl;
  	 while(currl!=NULL){
  	 	ind++;
  	 	t[ind] =currl->tem;
  	 	if(currl->frozen ==1 && t[ind]>0){
  	 		t[ind] =-0.01;
  	 	}else if(currl->frozen ==-1 && t[ind]<0){
  	 		t[ind] =0.01;
  	 	}

  	 	dx[ind] = currl->dz;
  	 	tc = currl->getThermalConductivity();
  	 	hcap = currl->getHeatCapacity();
  	 	cn[ind] = tc/dx[ind];
  	 	cap[ind] = hcap * dx[ind];
  	 	currl=currl->nextl;
  	 }

  	 ind =ind+1;
  	 double deltat = t[ind-1]-t[ind-2];
  	 t[ind] = t[ind-1] +deltat;
 	 s[ind] = 0.;
 	 e[ind]= t[ind];

 	 startind =lstfntl->indl;
     endind= ind; //
     iterate(startind, endind, true, false, frontl);

     currl=lstfntl->nextl;
     int il=0;
     while(currl!=NULL){

       il++;
       currl->tem= tld[lstfntl->indl+il];
       if(currl->frozen==1 && currl->tem>0){
       	 currl->tem=-0.01;
       }else if(currl->frozen==-1 && currl->tem<0){
       	 currl->tem=0.01;
       }

       // Yuan: for output
	   currl->tcond = currl->getThermalConductivity();

       currl=currl->nextl;
     }

};


void Stefan::processBetweenLayers(Layer* frontl, Layer *backl, Layer*fstfntl, Layer*lstfntl, const double & tdrv){

/*
	//simply assign zeros between fronts
	Layer* currl=fstfntl->nextl;
	SoilLayer* sl  	;

     while(currl!=NULL){
       if(currl->indl> lstfntl->indl){
       	 break;
       }else{
       	 sl = dynamic_cast<SoilLayer*>(currl);
       	 sl->adjustTem5State();    //update the temperature based on fronts
       }

 	   currl->tcond = currl->getThermalConductivity();  //Yuan: needed for output

       currl=currl->nextl;
     }
*/

	double tc, hcap;
  	int startind, endind;
    if(lstfntl->indl - fstfntl->indl <2){
        fstfntl->nextl->tem = 0.;
        return;
    }

     int ind=fstfntl->indl;
  	 t[ind] = 0; //assume the front is the top interface of virtual layer
  	 if(fstfntl->nextl->frozen ==1){
  		 t[ind] =-0.1;
  	 }else  if(fstfntl->nextl->frozen ==-1){
  		 t[ind] =0.1;
  	 }

  	 e[ind] = 0.;
  	 s[ind] = 0.;

  	 Layer*	 currl =fstfntl->nextl;
  	 while(currl!=NULL){
  	 	ind++;
  	 	t[ind] =currl->tem;
  	 	dx[ind] = currl->dz;
  	 	tc = currl->getThermalConductivity();
  	 	hcap= currl->getHeatCapacity();
  	 	cn[ind] = tc/dx[ind];
  	 	cap[ind] = hcap * dx[ind];
  	 	currl=currl->nextl;
  	 	if(currl->indl >= lstfntl->indl) break;
  	 }

  	 ind =ind+1;
  	 t[ind] = t[ind-1];
 	 s[ind] = 0.;
 	 e[ind]= t[ind];

 	 startind =fstfntl->indl;
     endind= ind; //
     iterate(startind, endind, false, false, frontl);

     currl=fstfntl; //->nextl;
     int il = 0;
     while(currl!=NULL){
    	 il++;
    	 currl->tem= tld[startind +il];
    	 if(currl->tem>0 && currl->frozen==1){
    		 currl->tem=-0.01;
    	 }else if (currl->tem<0 && currl->frozen==-1){
    		 currl->tem =0.01;
    	 }

    	 currl->tcond = currl->getThermalConductivity();  //Yuan: needed for output

    	 currl=currl->nextl;
    	 if(currl->indl >= lstfntl->indl) break;
     }

};

void Stefan::iterate(const int &startind, const int &endind, const bool & lstlaybot, const bool & fstlaytop, Layer *frontl){
  	
	tschanged = true;
	tmld =0; // tmld is time that is last determined
	
	itsum =0;
	/* at beginning of update, tleft is one day*/
	tleft = 1;
	tstep =TSTEPORG; ;
	
	for(int il =startind ; il<=endind; il++){
	  tid[il] = t[il]; // temperature at the begin of one day	
	  tld[il] = t[il]; // the last determined temperature
	}

	while(tmld<1){
		//cout <<"TMLD " << tmld << " time step " << tstep << "\n";
		for(int i=startind; i<=endind; i++){
	 		tis[i] = tld[i];	
		}
		int st = updateOneTimeStep(startind, endind, lstlaybot, fstlaytop, frontl);

		if(st==-1) {
	  	// half the time step	
	  	 tstep = tstep/2;
	  	 if(tstep < 1.e-6){
//	  	   throw Exception("tstep is too small in Stefan", ERRORKEY(I_TEM_TSTEP_SMALL));
//	  	   cout<<"tstep is too small in Stefan\n";
	  	   return;     //Yuan: don't break
	  	 }
	  	 tschanged = true;
		}else if(st==0){
		 // find one solution for one timestep, advance to next one
		 tleft -= tstep;
		 tmld += tstep;
		 
		 // find the proper timestep for rest period
		 
		 if(!tschanged){ // if timestep has not been changed during last time step 
		 	if(tstep<TSTEPMAX){
		 	  tstep *=2;
		 	  tschanged = true;
		    }		    
		 }else{
		    tschanged =false;	
		 }
		 // make sure tleft is greater than zero
		 tstep = min(tleft, tstep);	
		 if(tstep==0)tmld=1;
		}
	}// end of while
  	
  };
  
 
int Stefan::updateOneTimeStep(const int startind, const int & endind, const bool & lstlaybot, const bool & fstlaytop, Layer *frontl){
	int status =-1;
	int is;
	
	for(int i=startind; i<=endind; i++){
	 		tii[i] = tis[i];	
	}
		 
	for (int it=1; it<=ITMAX; it++){
	  is = updateOneIteration( startind, endind, lstlaybot,fstlaytop, frontl);
	  if(is==0){// success
	  	status = is;
	  	for(int i=startind; i<=endind; i++){
	 		tld[i] = tit[i];	
		}
		
	  	
	   return status;
	  }else if(is ==-1){// the difference between iteration is too big, iterate again
	  	for(int i=startind; i<=endind; i++){
	 		tii[i] = tit[i];
		}
		status = is;
	  }
	  
	}
	// for iterating five times, there is no solution,
	// reduce the time step redo it.

	return status;
}; 
  
  
/*! the main calculation will be done here*/
int Stefan::updateOneIteration( const int startind, const int & endind, const bool & lstlaybot ,const bool & fstlaytop, Layer *frontl){
	itsum++;
	double tself, tdown, tup, t1, t2;
	double hclat;
    double dt = tstep *86400.;
    if(fstlaytop){
      Layer* currl =frontl;
      int il=0;
      while(currl!=NULL){
      	if(currl->isSnow()){
      		il =currl->indl;
      		if(currl->indl==1){
      		   tself = tii[1];
	  	       tdown = tii[2];
	  		   t1 = tself;
	  		   t2 = (tdown + tself)/2.;	
	  		   if(t1>0 || t2>0){
	  		   	 hclat =3.337e5 *(currl->ice)/currl->dz;
	  		   	 cap[1] = ( currl->getHeatCapacity()+hclat)*currl->dz;
	  		   }else{
	  		   	 cap[1] = currl->getHeatCapacity()*currl->dz;
	  		   }
      		}else{
      			tself = tii[il];
	  			tup = tii[il-1];
	  			t2 = tself;
	  			t1 = (tup + tself)/2.;
	  			if(t1*t2<0){
	  		   	 hclat =3.337e5 *(currl->ice)/currl->dz;
	  		   	 cap[il] = ( currl->getHeatCapacity()+hclat)*currl->dz;
	  		   }else{
	  		   	 cap[il] = currl->getHeatCapacity()*currl->dz;
	  		   }
      			
      		}
      	}else if(currl->isSoil()){
      	    break;
      	}
      	currl=currl->nextl;
      }	
    }

/*    for(int il=startind+2 ; il<endind; il++){
   	
    	if(isnan(tii[il])){
    		string msg = "tii is nan";
    		char* msgc = const_cast< char* > ( msg.c_str());
    		throw Exception(msgc, I_NAN_TLD);
    	}
		
    	if(isnan(tit[il])){
    		string msg = "tit is nan";
    		char* msgc = const_cast< char* > ( msg.c_str());
    		throw Exception(msgc, I_NAN_TLD);
    	}
	 
		if(tii[il]>50){  
			string msg = "tii too big";
			char* msgc = const_cast< char* > ( msg.c_str());
			throw Exception(msgc, I_TOO_BIG_TII);
	  	}else if(tii[il]<-70){	  	  
	  		string msg = "tii too small";
	  		char* msgc = const_cast< char* > ( msg.c_str());
	  		throw Exception(msgc, I_TOO_SMALL_TII);  	 
	  	}
	  	
    }
*/	
    cns.geBackward(startind, endind, tii, dx, cn,cap, s, e, dt , lstlaybot); 
	cns.cnForward(startind, endind, tii, tit, s, e );		
  
	for(int il =startind +2; il<endind ; il++){
         
	  	if( fabs(tii[il]-tit[il])>ttole){ // always return 0
	  		if(il>1){
	  		    return -1;  // first layer will be changed accoring to driving tem, so don't compare this layer
	  		}
	  	}
	  	
	  	if(tit[il]>50){
//	  	    cout << "Error in Stefan:updateOneIteration\n";
	        return -1;	  
	    }
	} 	
  
	return 0; 
};
  
void Stefan::interpolateUpperTemps5Front(const double & tdrv, Layer* frontl){
	//find the first layer with front
	Layer * currl =frontl;
	Layer* fstfntl1=NULL;
	SoilLayer* sl;

	while(currl!=NULL){
		if(currl->isRock())break;
 	
		if(currl->isSoil()){
 	 	  sl = dynamic_cast<SoilLayer*>(currl);
		  if(sl->fronts.size()>0){
		  	fstfntl1 = currl;
		  	break;
		  } 		
		}

		currl =currl->nextl;
	}

	if(fstfntl1==NULL)return;
	if(fstfntl1->indl<=1)return;
	SoilLayer* fsl = dynamic_cast<SoilLayer*>(fstfntl1);
    double soildzsum = fstfntl1->z+fsl->fronts[0]->dz;
 	double dzsum = soildzsum;
 	
 	if(frontl->isSnow()){
 	  dzsum +=frontl->z;	
 	}
 	
  	double deltat = tdrv -0;
  	double gradient;
  	if(dzsum >0){
  		gradient = deltat/dzsum;
  		currl=frontl;
  	
  		double localdz;
  		double orgtemp, interptemp;
  		while (currl!=NULL){
  			orgtemp = currl->tem;
  			if(currl->isSnow()){
  				localdz = currl->z + soildzsum;
  				interptemp = localdz * gradient;
  				currl->tem = (orgtemp + interptemp)/2.;
  			}else if(currl->isSoil()){
  				localdz =soildzsum-currl->z;
  				interptemp = localdz * gradient;
  	 	
  				currl->tem =(orgtemp + interptemp)/2.;
  	 	
  				if(currl->indl == fstfntl1->indl)break;
  	 	
  			}

  			currl=currl->nextl;
  		}
  	
	}

};

void Stefan::updateUpperTemps5Front(Layer* fstfntl, const double & beforedse , const double & afterdse, 
				const double & tdrv, const int & frzing, const double & dz, const double & abvres){
			
			
	return; // for test		
	//frzing and dz are for lstfntl
    //return;
	double secinday =86400.;
	
	double sumresabv =abvres;
	
	//double dsused= beforedse - afterdse;
	//double secused = dsused/fabs(tdrv);//time used to have zero leftdse after the move of soil fronts
	
	
	Layer *currl;
	double volwat = fstfntl->getEffVolWater();

	double tkfrontorg;
	double tkres;
	
	if(tdrv>0){
		tkfrontorg = fstfntl->getFrzThermCond();
	}else {
		tkfrontorg = fstfntl->getUnfThermCond();
	}

	double dsn = getDegSecNeeded(  dz, volwat,tkfrontorg, sumresabv);
	
	
    if(temupdated[fstfntl->indl-1]){
    if(frzing==1){
      fstfntl->tem +=-dsn/secinday;
	 }else if(frzing==-1){
	  fstfntl->tem +=dsn/secinday;
	}
    }else{// first time
    	if(frzing==1){
    	  fstfntl->tem =-dsn/secinday ;
		 }else if(frzing==-1){
		  fstfntl->tem =dsn/secinday;
		}
		temupdated[fstfntl->indl-1]=true;
    }
    
	
	
	currl=fstfntl->prevl;//no phase changed above
	while(currl!=NULL){
			if(tdrv>0){
				tkres = currl->getUnfThermCond();
			}else {
				tkres = currl->getFrzThermCond();
			}
			sumresabv += currl->dz/tkres;
			// here the dz, volwat, tkfront are all for the partd 
			dsn =  getDegSecNeeded(  dz, volwat,tkfrontorg,sumresabv);

			
			if(temupdated[currl->indl-1]){
			    if(frzing==1){
			      currl->tem +=-dsn/secinday;
				 }else if(frzing==-1){
				  currl->tem +=dsn/secinday;
				}
			}else{// first time
			    	if(frzing==1){
			    	  currl->tem =-dsn/secinday ;
					 }else if(frzing==-1){
					  currl->tem =dsn/secinday;
					}
					temupdated[currl->indl-1]=true;
			    }

		currl=currl->prevl;
		
	};
	
	
};



