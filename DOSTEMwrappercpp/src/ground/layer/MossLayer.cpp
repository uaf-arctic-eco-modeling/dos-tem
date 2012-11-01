/*! \file
 * 
 */
#include "MossLayer.h"



MossLayer::MossLayer(const double &pdz, const int & sphagnum){
	tkey=I_MOSS;

	dz = pdz;

// these properties will not change upon fire disturbance
// it is assumed that when fire occurs, the left moss will
// be converted to deep organic type
    tcsolid = 0.25;
	prtlden = 1.3e3 ; // kg/m3, from ATBalland22005a
	 
	fldcap = 0.516; // reference ? unit vwater/vtot ? // not used
	wltpnt = 0.321; // reference   // not used
	color = 3;// ATBeringer52001a;
    albsatvis = 0.1;
   	albsatnir = 0.2;
   	albdryvis = 0.2; 
   	albdrynir = 0.4;
  
   	bulkden = 25000; // g/m3
   	cfrac = 43.7; // %
   	
   	if(sphagnum ==1){
   	hksat = 0.15; //mm/s
	psisat = -10; // mm
	 
	bsw =1;// change to that of upper //1.;
	//bsw=1;//July 16
   	}else{
   	hksat = 0.15; //mm/s
	psisat = -10; // mm
	//psisat = -120; // mm  for sphagnum moss
	
	bsw =1;// change to that of upper //1.;
	//bsw=1;//July 16	
   	}
   	
   /*	// color =2  decrease sensitivity 
   	albsatvis = 0.11;
   	albsatnir = 0.22;
   	albdryvis = 0.22; 
   	albdrynir = 0.44; 
   	// color =4  increase sensitivity 
   	albsatvis = 0.09;
   	albsatnir = 0.18;
   	albdryvis = 0.18; 
   	albdrynir = 0.36; */
   	
   	
   	vhcsolid=2.5e6; //J/m3K
	poro = 0.98;
    deriveProperty();
};

   
bool MossLayer::isMoss(){
  return true;	
}

bool MossLayer::isMineral(){
  return false;	
}

bool MossLayer::isPeat(){
  return false;	
}
