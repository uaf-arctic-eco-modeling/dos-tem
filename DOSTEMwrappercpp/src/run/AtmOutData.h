/*
 * 
 */
 
#ifndef ATMOUTDATA_H_
#define ATMOUTDATA_H_
#include <iostream>

#include "../inc/timeconst.h"

class AtmOutData {
  public:
	  AtmOutData();
	  ~AtmOutData();
	  
	  //daily
	 	float tdrvd[DYINY];
	 	float raind[DYINY];
	 	float snowd[DYINY];
	 	float svpd[DYINY];
	 	float dersvpd[DYINY];
	 	float rhoad[DYINY];
		float abshdd[DYINY];
	 	float dsrd[DYINY];
 	 	 
	 	// 	monthly
		float ta[MINY];	      //Atmosphere - Env
		float clds[MINY];	
		float co2[MINY];	
		float eet[MINY];	
		float pet[MINY];	
		float rnfl[MINY];	
		float snfl[MINY];	
		float girr[MINY];		    
		float nirr[MINY];
		float par[MINY];	

		// yearly

		float yrrnfl;	     //Atmosphere - Env
		float yrsnfl;	
		float yrta;	 

};
#endif /*ATMOUTDATA_H_*/
