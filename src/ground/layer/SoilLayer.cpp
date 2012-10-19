/*! \file
 * 
 */
#include "SoilLayer.h"
 
SoilLayer::SoilLayer(){
	tkey=I_SOIL;
	tcmin =0.1  ;
};

SoilLayer::~SoilLayer(){

};

double SoilLayer::getUnfrzColumn(){
	
	double unfrz =0;
	if(frozen ==1){
		unfrz =0;
	}else if (frozen ==-1){
		unfrz = dz;
	}else if (frozen ==0){
		int numfnt = fronts.size();
  	
  	// the dz above first front
		double dzbeforefst =  fronts[0]->dz;
		if(fronts[0]->frzing == -1){
			unfrz += dzbeforefst;
		}
		double dzafterlst = dz -  fronts[numfnt-1]->dz;
		if(fronts[numfnt-1]->frzing ==1){
			unfrz += dzafterlst;
		}
		double dzunfbetween=0;
  	
		if(numfnt>1){
			double tempdz =0;
			for(int i =1; i<numfnt; i++){
				tempdz = fronts[i]->dz - fronts[i-1]->dz;
				if(fronts[i]->frzing ==-1){
					dzunfbetween += tempdz;
				}
			}
  		
		}
  	
		unfrz += dzunfbetween;
  	
	}

	return unfrz;
};
	  	
void SoilLayer::combineFronts() {
	//it is possible that there are too many fronts exist in one layer
   		                    //combine them if there are too many
   	if(fronts.size()>=4){
   		int numfnt = fronts.size();
   		int removefntid =-1;
   		double mindz =100;
   		for(int i=0; i<numfnt-1; i++){
   			if(fronts[i]->dz - fronts[i+1]->dz <mindz){
   				mindz = 	fronts[i]->dz - fronts[i+1]->dz;
   				removefntid = i;
   			}
   	   }
   	   
   	   if(removefntid >=0){
   		   double fdz[numfnt-2];
   		   int ftype[numfnt-2];
   		   int find=-1;

   		   for(int i=0; i<numfnt ; i++){
   			   if(i!=removefntid && i!=removefntid+1){
   				   find++;
   				   fdz[find] = fronts[i]->dz;
   				   ftype[find] = fronts[i]->frzing;
   			   }
   
   		   }
   	   //remove all fronts
   		   removeAllFronts(0);
   	   	
   		   for(int i =0; i<numfnt-2; i++){
   			   addOneFront5Bot(fdz[i],ftype[i]);
   		   }
   	   	
   	   }	
   		
   	}	                    
   		                    
};
   		                    
void SoilLayer::clean(){
	  removeAllFronts(1);
};

double SoilLayer::getFrozenFraction(){
	 // the fraction of soil which is unfrozen

 		double fracfrozen =0.;  // fraction of a layer that is frozen
 		
 		int numfnt = fronts.size();
 		
 		if(numfnt==0){
 			if(frozen ==1){
 			  fracfrozen =1;	
 			}else if(frozen==-1){
 			  fracfrozen= 0;	
 			}else {
 		      //Yuan: bug here, but not yet know why, so tempoarily do the following
				if (tem>0) {
					frozen = -1;
					fracfrozen = 0;
				} else {
					frozen = 1;
					fracfrozen = 1;
				}

 			 string msg = "the numfnt ==0 and frozen ==0 ";
// 			char* msgc = const_cast< char* > ( msg.c_str());
// 			throw Exception(msgc, I_FRONT_STATE_INCON);

 			}
 			
 		}else {
 			double oldz = 0;
 			for(int i =0; i<numfnt; i++){
 			  if(fronts[i]->frzing==1){
 			  	fracfrozen += (fronts[i]->dz -oldz)/dz;
 			  }
 			  oldz = fronts[i]->dz;
 			  if(i==numfnt-1){
 			  	if(fronts[i]->frzing==-1){
 			     	fracfrozen += (dz- fronts[i]->dz)/dz;
 			 	 }
 			  }
 			}
 			
 		}
 		
 		return fracfrozen;
	 }

	// get frozen layer specific heat capcity
	 double SoilLayer::getFrzVolHeatCapa(){
//	   double vhc = vhcsolid * (1-poro) + (liq+ice)/dz *SHCICE;
	   double vhc = vhcsolid * (1-poro) + poro*(liq+ice)/dz *SHCICE;	//Yuan: bug here??
	 	return vhc;
	 };

	 double SoilLayer::getUnfVolHeatCapa(){
//	   double vhc= vhcsolid * (1-poro) + (liq+ice)/dz *SHCLIQ;
	   double vhc = vhcsolid * (1-poro) + poro*(liq+ice)/dz *SHCLIQ;	//Yuan: bug here??
	 	return vhc;
	 };	    
	   
	 //Yuan: unfrozen/frozen put together
	 double SoilLayer::getMixVolHeatCapa(){
	   double vhc = vhcsolid * (1-poro) + poro*liq/dz *SHCLIQ+poro*ice/dz *SHCICE;
	 	return vhc;
	 };
	  
// get frozen layer thermal conductivity
double SoilLayer::getFrzThermCond(){
	  double tc;
	  double vice = getVolIce();
	  double vliq = getVolLiq();
	  double s = (vice + vliq)/poro;
	  s = min((double)s, 1.0);
	  double ke= s; // for frozen case
	  if(s < 1.e-7){
	  	 tc = tcdry;	
	  }else{
	  	 tc = ke *tcsatfrz + (1-ke)*tcdry;
	  }
  	//	tc = max(tc, mintc);
	  
	  return tc;
};
	  
	   // get unfrozen layer thermal conductivity
double SoilLayer::getUnfThermCond(){
  	double tc;
  	double vice = getVolIce();
  	double vliq = getVolLiq();
  	double s = (vice + vliq)/poro;
  	s = min(s, 1.0);
  	double ke= log(s) +1; // for unfrozen case
  	ke = max(ke, 0.);
  	if(s < 1.e-7){
	  	 tc = tcdry;	
  	}else{
	  	 tc = ke *tcsatunf + (1-ke)*tcdry;
  	}
	  	//if(tc<tcmin){
	  	 //cout <<"tc is less " <<tc <<"\n";
	  	//}
	  //	if(poro>0.9 || (poro>=0.8 &&solind ==1)){
  	if(poro>=0.9 || (poro>=0.8 &&solind ==1)){
	  	tc = max(tc, tcmin);
  	}

  	return tc;
};
	  
double SoilLayer::getMatricPotential(){
  	double psi;
  	double lf = 3.337e5 ;// latent heat of fusion J/kg
	double g =9.8;
	if(tem<0){
		psi =1000. * lf/g *(tem/(tem+273.16));
		if (psi<-1.e8)psi=-1.e8;
	}else{
	  	double voliq = getVolLiq()/(poro-getVolIce());

	  	double ws = max(0.01, voliq);
	  	ws = min(1. , ws);
	  	/*if(isMineral()){
	  	int fws = (int)floor(ws*1000)-1;
	  	int cws = (int)ceil(ws*1000)-1;
	  
        if(fws ==cws) {
        	psi = soillu->psi[stkey][fws];
        }else{
        	double fac = (ws *1000.-fws)/(cws -fws);
        	psi = soillu->psi[stkey][fws] *(1-fac)    +soillu->psi[stkey][cws]*fac;        	
        }
	  	}else{
	  		
	  			psi = psisat * pow(ws, -bsw*1.0);
	  	}*/
	  	psi = psisat * pow(ws, -bsw*1.0);
	  	if (psi<-1.e8){	
	  		psi=-1.e8;
	  	}

	}

	return psi;
};
	  
double SoilLayer::getHydraulicCond1(){//not used
	  	double hk;
	  //	double voliq = getVolLiq()/(poro-getVolIce());
	  	double voliq = getVolLiq()/(poro);
	  	double ws = max(0.001, voliq);
	  	ws = min(1., ws);
	  	if(isMineral()){
	  	int fws = (int)floor(ws*1000-1);
	  	int cws = (int)ceil(ws*1000)-1;
	  	
        if(fws ==cws) {
        	hk = soillu->hk[stkey][fws];
        }else{
        	double fac = (ws *1000.-fws)/(cws -fws);
        	hk = soillu->hk[stkey][fws] *(1-fac)    + soillu->hk[stkey][cws]*fac;        	
        }
           
	  	}else{
	  		hk =0.;
	  	}

	  	return hk;
};

// get albedo of visible radition
double SoilLayer::getAlbedoVis(){
       	double vis;
      	double liq1 = getVolLiq();
      	double ice1 = getVolIce();
       	double delta = 0.11-0.4*(liq1+ice1);
       	delta =max(0., delta);
       	vis = albsatvis + delta;
       	vis = min(vis, (double)albdryvis);
       //vis =0.12; //from DFTB measurement of albedo
      // vis =0.16;
       	return vis;
};
     
// get albedo of nir radition
double SoilLayer::getAlbedoNir(){
       	double nir;
       	double wat = getVolLiq()+getVolIce();
       	double delta = 0.11-0.4*wat;
       	delta =max(0., delta);
       	nir = albsatnir + delta;
       	nir = min(nir, (double)albdrynir);
       //	nir =0.12;
       //	nir =0.16;
       	return nir;
};
     
void SoilLayer::updateWater5Front(){
 // when a front moves through or in a layer
 // the corresponding liq and ice content should be changed
 
        double tice =ice;
 		double tliq =liq;
 		double fracfrozen =getFrozenFraction();  // fraction of a layer that is frozen

 		ice = (tice +tliq ) * fracfrozen;
 		liq = (tice +tliq ) * (1-fracfrozen);
 		if(liq<minliq){
 			double delta =minliq-liq;
 			liq =minliq;
 		  	ice -=delta;
 		  	if(ice<0)ice=0.;
 		}
 		
};

//when a layer's thickness changed, update corresponding properties
void SoilLayer::updateProperty4LayerChange(){
	minliq = 0.05*1000.*dz;
	
	maxliq = poro*1000.*dz;
   	maxice =poro*1000*dz -minliq;
   	
   	if(frozen==1){
   	  double deltaliq =0;
   	  if(liq>minliq){
   	  	 deltaliq = liq-minliq;
   	  	 liq = minliq;
   	  	 ice += deltaliq;
   	  	 if(ice>maxice){
   	  	   ice = maxice;
   	  	 }
   	  }	
   		
   	}else if(frozen ==-1){ //unfrozen
   		if(ice>0){
   		  liq += ice;
   		  if(liq>maxliq){
   		  	 liq = maxliq;
   		  }	
   		}
   		
   	}else if(frozen==0){// with front(s)
   		int numfronts =fronts.size();
   		
   		for(int i=0;i<numfronts;i++){
   		    if(fronts[i]->dz>dz){
   		      	fronts[i]->dz=dz-0.000001;
   		    }		
   		}
   	}
   	
   	 if( frozen ==1 &&  tem>0){
	  	  tem = -0.01;
	 }else if( frozen ==-1 &&  tem<0){
	  	tem =0.01;
	 }else if (frozen==0){
	     if(fronts[0]->frzing==1 && tem>0){
	      tem =-0.01;	
	     }else  if(fronts[0]->frzing==-1 && tem<0){
	      tem =0.01;	
	     }
   	 }

   	 /*if(poro<0.3){
   	 cout <<"porosity in soillayer is less than 0.3\n";
   	 exit(-1);	
   	}*/
   	tcmin =0.1;
};


// derive properties from the assigned property
//called when porosity is changed
void SoilLayer::deriveProperty(){
	 tcsatunf= pow((double)tcsolid , (double)1- poro) * pow((double)TCLIQ, (double)poro);
	 tcsatfrz= pow((double)tcsolid ,(double) 1- poro) * pow((double)TCICE, (double)poro);
	 tcdry = pow((double) tcsolid , (double) 1- poro) * pow((double)TCAIR, (double) poro);
	 
   	 minliq = 0.05 * 1000. *dz;
   	 maxliq = poro*1000.*dz;
   	 maxice = poro*1000*dz -minliq;
   	 tcmin = tcdry;   //Yuan
   	 
};

void SoilLayer::addOneFront5Top4restart(const double & deltaz,const int & frzing){
   //deltaz is the distance between the front and top interface of a layer
   frozen =0;
   Front* fnt = new Front();
   fnt->set(deltaz, frzing);
   fronts.push_back(fnt);
};
 
void SoilLayer::addOneFront5Top(const double & deltaz,const int & frzing){
   //deltaz is the distance between the front and top interface of a layer
   frozen =0;
   Front* fnt = new Front();
   fnt->set(deltaz, frzing);
   fronts.push_front(fnt);
};

void SoilLayer::addOneFront5Bot(const double & deltaz,const int & frzing){
  //add one front at the bottom of fronts
   frozen =0;
   Front* fnt = new Front();
   fnt->set(deltaz, frzing);
   fronts.push_back(fnt);
};
 
void SoilLayer::moveOneFrontDown(const double & partd, const int & fntind){
    fronts[fntind]->dz += partd;

};
 
void SoilLayer::moveOneFrontUp(const double & partd, const int & fntind){
 	fronts[fntind]->dz -= partd;
};
 
void SoilLayer::removeAllFronts(const int & frzing){
  //	deque<Front*>::iterator iter;
  //	for(iter=fronts.begin(); iter!=fronts.end; iter++){
  //	   delete 	
  //	}
    for(unsigned int i =0; i<fronts.size(); i++){
      delete fronts[i];	
    }
    
    frozen =frzing;
 	fronts.clear();
};

void SoilLayer::removeTopFront(){
 	delete fronts[0];
 	fronts.pop_front();
};
 
void SoilLayer::removeBotFront(){
 	delete fronts[fronts.size()-1];
 	fronts.pop_back();
};
  
void SoilLayer::adjustFronts(){
	int numfnt = fronts.size();
	for(int i=0; i<numfnt; i++){
		if(fronts[i]->dz >dz){
			fronts[i]->dz=dz;
		}
	}
 	
};

void SoilLayer::adjustTem5State(){
 	 if( frozen ==1 &&  tem>0){
	  	 tem = -0.01;
	 }else if( frozen ==-1 &&  tem<0){
		 tem = 0.01;
	 }else if (frozen==0){
	     if(fronts[0]->frzing==1 && tem>0){
	    	 tem =-0.01;
	     }else  if(fronts[0]->frzing==-1 && tem<0){
	    	 tem =0.01;
	     }
	 	
   	 } 
};
 
int SoilLayer::checkFronts(){
	int numfnt = fronts.size();
	for(int i=0; i<numfnt; i++){
		if(fronts[i]->dz >dz){
 
  	     //string msg = "the front should be located in soil layer ";
 	 	//	char* msgc = const_cast< char* > ( msg.c_str());
 		 //	throw Exception(msgc, I_FRONT_POSITION);
			return -1;
  	  
		}
	}
	
	return 0;

};
   
///// some properties
double SoilLayer::getDryThermCond(const double & tcsolid, const double & bulkden, const double & partden){
   // from ATBalland22005a
   double kdry =0.;
   double par_a = 0.053;
   double tcair = TCAIR;
   kdry = ((par_a* tcsolid - tcair) *bulkden + tcair*partden)/(partden - (1-par_a)*bulkden)	;
   return kdry;
};

bool SoilLayer::isSnow(){
	return false;
};

bool SoilLayer::isSoil(){
	return true;
};

bool SoilLayer::isRock(){
	return false;
};

