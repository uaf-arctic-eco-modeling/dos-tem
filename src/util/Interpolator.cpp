/*! \file
 */
 #include "Interpolator.h"

Interpolator::Interpolator(){
	
};

void Interpolator::interpolate(float x[], float y[], const int & nmax, 
					 float xx[], float yy[], const int & nnmax){
	 //xx[nnmax +1]=1e10f;  //Yuan: why?
	 int m=0;
	 float slope, x1, x2, y1, y2;
	 //for(int n =1; n<nmax; n++){
	 for(int n =0; n<nmax; n++){   //Yuan:
	 	y1=y[n];
	 	y2=y[n+1];
	 	x1 =x[n];
	 	x2 = x[n+1];
	 	slope = (y2-y1)/(x2-x1);
	 	while(m<nnmax  && xx[m]<=x2){
	 	  yy[m] = y1+slope*(xx[m]-x1);
	 	  ++m;	
	 	}
	 }	
};
