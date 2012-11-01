#include "Mineral.h"

Mineral::Mineral(){
	
}

void Mineral::initThicknesses(const double & thickness){
	// The following is the default thickness and number of mineral layers (Yuan)
	num = MAX_MIN_LAY;
	thick = 0.0;
	for (int i=0; i<MAX_MIN_LAY; i++) {
		dza[i]=MINETHICK[i];
		thick+=dza[i];
	}

	//Yuan: if thickness IS NOT the default, then refresh the soil mineral structure
	thick = 0.0;
	num = 0;
	for (int i=0; i<MAX_MIN_LAY; i++){
		thick +=dza[i];
		if (thick > thickness) {
			thick = thickness;
			dza[i] = 0.0;
		} else {
			num ++;
		}
	}
};


void Mineral::updateType(int types[], const int & numtype){
	for(int i=0; i<numtype;i++){
		 type[i] = types[i];
	};

};

void Mineral::updateThicknesses(int type[], double dz[],const int & maxnum){

	num =0;
	thick =0.;
	for(int i=0;i<maxnum; i++){
   	  if(type[i] ==3){
   	  	dza[num] = dz[i];
   	  	num ++;
   	  	thick += dz[i];
   	  }else {
   	  	 if(type[i]>3){
   	  		 break;	
   	  	 }
   	  }
    } 
};
	
