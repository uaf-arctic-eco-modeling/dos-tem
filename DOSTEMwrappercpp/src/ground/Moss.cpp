#include "Moss.h"

Moss::Moss(){
	

}


void Moss::updateThicknesses(const double & thickness){
	thick = thickness;
	num =0;
	if(thickness>=0.02 && thickness<0.04){
	 dza[0]=thickness;
	 dza[1]=-1;
	 num =1;
	}else if (thickness>=0.04 ){
	 dza[0]=0.02;
	 dza[1]=thickness-0.02;
	 num =2;		
					
	}
};

void Moss::updateThicknesses(int type[], double dz[],const int & maxnum){
	num =0;
	thick =0.;
   for(int i=0;i<maxnum; i++){
   	  if(type[i] ==0){
   	  	dza[num] = dz[i];
   	  	num ++;
   	  	thick += dz[i];
   	  }else {
   	  	 if(type[i]>0){
   	  	  break;	
   	  	 }
   	  }
   } 
};

bool Moss::sameThickRange(const double & thickness){
  /// if the thickness and thick not in the same range, there is a need to reconstruct moss layers
  bool same =false;	
	
	 if(thickness <0.04  && thickness >=0.02&& thick <0.04 && thick>=0.02){
		return true;
	}else if(thickness >=0.04&&  thick>=0.04){
		return true;
	}
 
  return same;	
};
