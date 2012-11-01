/*! \file
*/

#include "Front.h"

Front::Front(){
	reset();
};


void Front::reset(){
	dz =-999.; //initialize one with minus value;
	frzing=0;  //+1 freezing, -1 thawing, and 0 is initial value
}

void Front::setFrzing(const double & tsur, const double & tf){
	       if(tsur>tf){
	 		  frzing = -1;	
	 		}else{
	 		   frzing = 1;	
	 		}	
};

void Front::assign(const Front & of){
	dz = of.dz;
	frzing = of.frzing;
}

void Front::set(const double & dz1, const int  & frz){
	dz = dz1;
	frzing = frz;
}



