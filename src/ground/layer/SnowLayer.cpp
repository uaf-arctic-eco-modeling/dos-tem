/*! \file
 * 
 */
#include "SnowLayer.h"

SnowLayer::SnowLayer(){
	tkey=I_SNOW;
/*
	conf=0.2;
	sphf =2093.;

	cont = 0.56;
	spht = 4086;*/
    liq =0;
     
    minliq =0;
    maxliq =0;
    
	frozen =1;
};

SnowLayer::~SnowLayer(){
	//cout <<"delete on snow layer\n";
};
void SnowLayer::clone(SnowLayer* sl){
  liq =sl->liq;
  ice =sl->ice;
  dz = sl->dz;
  age = sl->age;
  rho = sl->rho;
}
 bool SnowLayer::isSnow(){
  return true;	
}
bool SnowLayer::isSoil(){
  return false;	
}

bool SnowLayer::isRock(){
  return false;	
}

/*! from ATVerseghy11991a*/
void SnowLayer::updateDensity(){
	double adjust=0.24; // corresponding to e-folding time of 4 days
	//from  http://www.ecmwf.int/research/ifsdocs/CY25r1/Physics/Physics-08-05.html
	//rho = (rho-denmax)* exp(-0.01 *age*365  * adjust) + denmax;
    double tao1 = 86400.; //s
    double tao = 86400.; // one day time step
	rho = (rho-denmax)* exp(- tao/tao1* adjust) + denmax;
	if(rho>denmax)rho= denmax;
};

void SnowLayer::updateThick(){
// after the update of density, snow thickness should also be changed	
   dz = ice/rho;
}
 // get frozen layer thermal conductivity
 // from Jordan 1991
	  double SnowLayer::getFrzThermCond(){
	  	//if (ctype==0){// tundra
	      return getThermCond5Jordan();
	  	 
	  	//}else{
	  //return getThermCond5Sturm();
	  	//}
	  };
	    // get unfrozen layer thermal conductivity
	  double SnowLayer::getUnfThermCond(){
	   //if(ctype==0){
	   return getThermCond5Jordan();
	   //}else{
	   //return getThermCond5Sturm();
	   //}
	  };
	  
	  double SnowLayer::getThermCond5Sturm(){
	  	double tc=0;
	    //tc = TCAIR + (7.75e-5 * rho + 1.105e-6*pow(rho , 2.))*(TCICE-TCAIR);
	    double rhogcm = rho / 1000; // convert from  kg/m3 to g/cm3, from ATSturm41997a..
	    if(rhogcm<=0.6 && rhogcm>=0.156){
	    	tc = 0.138 -1.01* rhogcm +3.233* rhogcm*rhogcm;
	    }else if(rhogcm<0.156){
	        tc =0.023 +0.234 *rhogcm;	
	    }else{
	    	//cout<<"snow density too big";
	       // exit(-1);	
	    }
	  	return tc; 
	  };
	  
	  //in TROleson142004a
	  double SnowLayer::getThermCond5Jordan(){
	  	double tc=0;
	    tc = TCAIR + (7.75e-5 * rho + 1.105e-6*rho*rho)*(TCICE-TCAIR);
	    tc = 2.9*1.e-6 * rho*rho;
	    if(tc<0.04) tc =0.04;
	  	return tc;
	  }
	 

	 double SnowLayer::getFrzVolHeatCapa(){
	 
	   double vhc = SHCICE * ice/dz;	
	 	return vhc;
	 };

	 double SnowLayer::getUnfVolHeatCapa(){
	   double vhc = SHCICE * ice/dz;	
	 	return vhc;
	 };	  

	 double SnowLayer::getMixVolHeatCapa(){
	   double vhc = SHCICE * ice/dz;
	 	return vhc;
	 };
	 
	       // get albedo of visible radition
	       // from ATRoesh42001
     double SnowLayer::getAlbedoVis(){
       	double vis;
       	if(tem<-10){
       	  vis =0.9;
       	}else{
        vis = albmax - (albmax -albmin) * (tem+10)/(10);
        vis = min(albmax , vis);
        vis = max(albmin , vis);
       	}
        //vis =0.65; // from the albedo of DFTB in winter
       // vis =0.70;
       	return vis;
     };
     
          // get albedo of visible radition
     double SnowLayer::getAlbedoNir(){
       	double nir;
        nir = getAlbedoVis();
       	return nir;
     };
     
     void SnowLayer::check(){
      
       if(tem>0 || frozen==-1){
       	  cout <<"snow layer therm error\n";
       	  //exit(-1);
       }
     	 
     }
	   

