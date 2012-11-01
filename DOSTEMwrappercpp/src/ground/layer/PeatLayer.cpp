/*! \file
 * 
 */
#include "PeatLayer.h"

PeatLayer::PeatLayer(const double & pdz, const int & upper){
	
	tkey=I_PEAT;
	dz = pdz;
	isFibric =false;
	isHumic  =false;
	fromFire =false;

// these properties will not change upon fire disturbance
// it is assumed that when fire occurs, the left moss will
// be converted to deep organic type
    tcsolid = 0.25;
	prtlden = 1.3e3 ; // kg/m3, from ATBalland22005a
	
	//psisat = -120; // mm
	
	fldcap = 0.516; // reference ? unit vwater/vtot ? // not used
	wltpnt = 0.321; // reference   // not used
   	vhcsolid=2.5e6; //J/m3K

// the porosity might be changed with depth
// the porosity can also be changed with the occurrence of fire   
    if(upper==1){
		poro = 0.95;
		isFibric =true;
		color = 8;// ATBeringer52001a;
    	albsatvis = 0.075;
   		albsatnir = 0.15;
   		albdryvis = 0.15;
   		albdrynir = 0.3; 

   		hksat = 0.28;  
   	 	bsw=2.7;
   	    bulkden = 51000; // g/m3
   		cfrac = 44.2; // %
   		psisat =-10.0;
    }else{
    	poro = 0.8;
		isHumic =true;	
		color = 3;// ATBeringer52001a;
    	albsatvis = 0.075;
   		albsatnir = 0.15;
   		albdryvis = 0.15;
   		albdrynir = 0.3;
 
       	bulkden = 176000; // g/m3
   	  	cfrac = 35.2; // %
   		
   		bsw=8;
   		hksat =0.002;
   		psisat =-12;
    }

	//whenever poro is changed, deriveProperty need to be called again
    deriveProperty();
};

void PeatLayer::humify(){
	    poro = 0.8;
		isHumic =true;	
		isFibric=false;
		color =3;// ATBeringer52001a;
    	albsatvis = 0.075;
   		albsatnir = 0.15;
   		albdryvis = 0.15;
   		albdrynir = 0.3;
   	
   	 	hksat = 0.02;//0.1;//0.28; //mm/s
	 	deriveProperty();
};



bool PeatLayer::isMoss(){
  return false;	
}

bool PeatLayer::isMineral(){
  return false;	
}
bool PeatLayer::isPeat(){
  return true;	
}
