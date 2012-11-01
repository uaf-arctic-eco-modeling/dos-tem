/*! \file
 * 
 */
#include "MineralLayer.h"



MineralLayer::MineralLayer(const double & pdz, int sttype , SoilLookup * soillup){
	tkey=I_MINE;
	stkey =  STKEY(sttype);
	soillu = soillup;
	dz = pdz;
    updateProperty5Lookup();
	
};



 void MineralLayer::updateProperty5Lookup(){
    	poro =  soillu->poro[stkey];
    	
    	tcsolid = soillu->Ksolids[stkey];
	   
		hksat = soillu->Ksat[stkey];
		psisat =  soillu->Psisat[stkey];
		bsw = soillu->b[stkey];
		bulkden =soillu->bulkden[stkey];
		 tcdry = soillu->tcdry[stkey];
		 
		// 
		 prtlden =2700.;
		 tcdry = getDryThermCond(bulkden);
		//tcdry = getDryThermCond(tcsolid, bulkden, prtlden);
		 
		fldcap = soillu->fieldcap[stkey];
		wltpnt =soillu->wiltp[stkey];
  	    tcsatunf= soillu->tcunfsat[stkey];
  	    tcsatfrz= soillu->tcfrzsat[stkey];
   	    vhcsolid = soillu->Csolids[stkey];
  	    
   	    albsatvis = soillu->albsatvis[stkey];
   	    albsatnir = soillu->albsatnir[stkey];
   	    albdryvis = soillu->albdryvis[stkey];
   	    albdrynir = soillu->albdryvis[stkey];
   	    
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



