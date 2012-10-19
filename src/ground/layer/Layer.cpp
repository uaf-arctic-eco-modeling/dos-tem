/*! \file
 * 
 */
 #include "Layer.h"
 
 Layer::Layer(){
 	nextl= NULL;
 	prevl= NULL;
 	
 	//tkey=I_LAY;
 	tem =-999.;
    frozen =0;
    dbdw = 1.;
    age =0.;
    
};
 
Layer::~Layer(){
 	//cout <<"delete one layer \n";
};
 
 
void Layer::advanceOneDay(){
  age+=1/365.;
};
 
void Layer::check(){
 	/*if(isnan(dz)){
 	 cout <<"dz is nan in Layer::check \n";
 	 exit(-1);	
 	}
 	if(isnan(z)){
 	 cout <<"z is nan in Layer::check \n";
 	 exit(-1);	
 	}*/
 	
};

/*! the unit of unfrozen water is kgh2o/kgsolid
 * since dbdw ==1, so the ufw= theta liq 
 * In original code, porority is used to confine the value of ufw
 * Here we use the actual water content to confine ufw, in another
 * word, we don't assume saturation*/
/*double Layer::getUnfrzWater(const double & temp){
	double thetawat = getVolWater();
	double ufw= thetawat/(dbdw);
	//if(temp < t0unfp){
	//  ufw =0.01;
	//}else
	
	 if(temp <tfrzp){
	  ufw = aunf * pow(fabs(temp -cunf), bunf);	
	}
	if(dbdw * ufw > thetawat) ufw = thetawat/dbdw;
	return ufw;
}*/

double Layer::getHeatCapacity(){ // volumetric heat capacity
    	double hcap = 0.;;
    	      if(isSoil()){
				if(frozen==-1){
					//hcap = spht;
					hcap = getUnfVolHeatCapa();
				}else if(frozen ==1){
					//hcap = sphf;
					hcap = getFrzVolHeatCapa();
				}else if(frozen ==0){
				    //hcap = sphf;// for snow	
				    //hcap = getFrzVolHeatCapa();
					hcap = getMixVolHeatCapa();   //Yuan
				}
    	      }else if(isSnow()){
				    hcap = getFrzVolHeatCapa();	
			  }else if(isRock()){
			  	    hcap = getFrzVolHeatCapa();
    	      }
		return hcap;		
};
    
double Layer::getThermalConductivity(){
    	double tc = 0.;
				//if(tem>0){
				//	tc = getUnfThermCond();
				//}else {
				//	tc = getFrzThermCond();
				//}
		if(isSoil() || isSnow()){
			if(frozen==1){
				tc = getFrzThermCond();
			}else{
				tc = getUnfThermCond();
			}
		}else if (isRock()){
		    tc = getFrzThermCond();
		}
				
		return tc;		

};

/*
 void Layer::logLayerInfo(Logger * logger){
 	stringstream ss;
 	ss<<"Layer " << indl << " : " << tkey << "  " 
			        <<  dz << " (m) " << z << " " <<tem;
			        
	 
	logger->writeln(ss);
 };
*/
 
double Layer::getVolWater(){
 	double vice = getVolIce();
 	double vliq = getVolLiq();
 	return min((double)poro,(double)vice+vliq);
};
 
 //effective vol water
double Layer::getEffVolWater(){
 	double effvol =0.;
 	if(isSoil()){
 	  effvol = getVolWater() -0.05 * poro;	
 	}else if (isSnow()){
 	  effvol = getVolWater();	
 	}
 	if(effvol<0){
 	 effvol =0.;	
 	}
 	return effvol;
};
 
double Layer::getVolIce(){
    double vice = ice/917./dz;
    vice = min((double)vice, (double)poro);
    return vice;
};
 
double Layer::getVolLiq(){
    double vliq = liq/1000./dz;
    vliq = min((double)vliq,(double)poro);
    return vliq;
};
 
 
 


