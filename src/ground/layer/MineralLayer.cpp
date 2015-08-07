/*! \file
 * 
 */
#include "MineralLayer.h"
#include <iostream>


MineralLayer::MineralLayer(const double & pdz, int stclay, int stsand, int stsilt){
	tkey=I_MINE;
//	stkey =  STKEY(sttype);
//	soillu = soillup;
	dz = pdz;
	clay = stclay;
	sand = stsand;
	silt = stsilt;
    	updateProperty5Lookup();
	
};



 void MineralLayer::updateProperty5Lookup(){
//    	poro =  soillu->poro[stkey];
//  	tcsolid = soillu->Ksolids[stkey];
//	hksat = soillu->Ksat[stkey];
//	psisat =  soillu->Psisat[stkey];
//	bsw = soillu->b[stkey];
//	bulkden =soillu->bulkden[stkey];
//	tcdry = soillu->tcdry[stkey];

    	poro =  0.489 - 0.00126*sand;
    	tcsolid = (8.8 * sand +2.92 * clay)/(sand + clay);
	hksat = 0.0070556 *pow( 10.,(-0.884+0.0153*sand) );
	psisat =  -10. * pow( 10.,(1.88-0.0131*sand) );
	bsw = 2.91 + 0.159*clay;
	bulkden = 2700 *(1-poro);
	tcdry = (0.135*bulkden +64.7)/(2700-0.947*bulkden);

	//cout << "poro" << poro << "\n";		 
	// 
	prtlden =2700.;
//	tcdry = getDryThermCond(bulkden);
//	tcdry = getDryThermCond(tcsolid, bulkden, prtlden);
		 
//	fldcap = soillu->fieldcap[stkey];
//	wltpnt =soillu->wiltp[stkey];
//  	tcsatunf= soillu->tcunfsat[stkey];
//  	tcsatfrz= soillu->tcfrzsat[stkey];
//   	vhcsolid = soillu->Csolids[stkey];

//	fldcap = soillu->fieldcap[stkey];
//	wltpnt =soillu->wiltp[stkey];
  	tcsatunf= pow(tcsolid , 1- poro) * pow((double)TCLIQ, poro);
  	tcsatfrz= pow(tcsolid , 1- poro) * pow((double)TCICE, poro);
   	vhcsolid = (2.128*sand +2.385*clay)/(sand+clay) * 1.0e6;
  	    
//   	albsatvis = soillu->albsatvis[stkey];
//   	albsatnir = soillu->albsatnir[stkey];
//   	albdryvis = soillu->albdryvis[stkey];
//   	albdrynir = soillu->albdryvis[stkey];

   	albsatvis = 0.09;
   	albsatnir = 0.18;
   	albdryvis = 0.18;
   	albdrynir = 0.36;
   	    
   	minliq = 0.05 *  1000. *dz;
   	//minliq = 0.05 * poro * 1000. *dz;
   	maxliq = poro*1000.*dz;
   	maxice =poro*1000*dz -minliq;  
   	  //maxice =poro*917*dz -minliq;  
    };


///// some properties
double MineralLayer::getDryThermCond(const double & bulkden){
   // from ATBalland22005a
   double kdry =0.;
  
   kdry = (0.135*bulkden +64.7)/(2700-0.947*bulkden);
   return kdry;
}  

double MineralLayer::getDryThermCond(const double & tcsolid, const double & bulkden, const double & partden){
   // from ATBalland22005a
   double kdry =0.;
   double par_a = 0.053;
   double tcair = TCAIR;
   kdry = ((par_a* tcsolid - tcair) *bulkden + tcair*partden)/(partden - (1-par_a)*bulkden)	;
   return kdry;
}     


bool MineralLayer::isMoss(){
  return false;	
}

bool MineralLayer::isMineral(){
  return true;	
}
bool MineralLayer::isPeat(){
  return false;	
}



