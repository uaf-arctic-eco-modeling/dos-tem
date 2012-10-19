/*! \file
 * 
 */
 #include "RockLayer.h"
 
RockLayer::RockLayer(const double & thick){
 	tkey=I_ROCK;
 	dz = thick;
 	updateProperty(); 
};

RockLayer::~RockLayer(){

};

void RockLayer::updateProperty(){
    	poro =  0;
    	tcsolid =2;// 
  	    tcsatunf= tcsolid;
  	    tcsatfrz= tcsolid;
   	    vhcsolid = 2700000; //bulkdensity 2700, porosity 0, //specific heat capacity 1000 J/kgk
};

// get frozen layer specific heat capcity
double RockLayer::getFrzVolHeatCapa(){
	 double vhc = vhcsolid ;
	 return vhc;
};

double RockLayer::getUnfVolHeatCapa(){
	   double vhc= vhcsolid ;
	 	return vhc;
};
	   
double RockLayer::getMixVolHeatCapa(){
	   double vhc= vhcsolid ;
	 	return vhc;
};
	  
// get frozen layer thermal conductivity
double RockLayer::getFrzThermCond(){
	  	double tc=tcsolid;
	  	
	  	return tc;
};
	  
// get unfrozen layer thermal conductivity
double RockLayer::getUnfThermCond(){
  	double tc=tcsolid;
	  	
  	return tc;
};
	  
// get albedo of visible radition
double RockLayer::getAlbedoVis(){//should not used
       	double vis=0.2;
       	return vis;
};
     
// get albedo of nir radition
double RockLayer::getAlbedoNir(){//should not used
       	double nir=0.2;
       	
       	return nir;
};
     

bool RockLayer::isSnow(){
  return false;	
}
bool RockLayer::isSoil(){
  return false;	
}
bool RockLayer::isRock(){
  return true;	
}
