#ifndef SOILCLM_H_
#define SOILCLM_H_

#include "../inc/timeconst.h"
#include "../inc/layerconst.h"

class SoilClm {
	public:
	
		SoilClm();
		~SoilClm();
		
		int chtid;
 		int drg;
 		int numsl;

 		float dz[MAX_SOI_LAY];
 		int   type[MAX_SOI_LAY];
 		int   minclay[MAX_MIN_LAY];
 		int   minsand[MAX_MIN_LAY];
 		int   minsilt[MAX_MIN_LAY];
 		float poro[MAX_SOI_LAY];
 		float rootfrac[MAX_SOI_LAY];

 		float pet[12];
 		float eet[12];
 		float ald[12];
 		float watb[12];

 		float ts[12][MAX_SOI_LAY];
 		float liq[12][MAX_SOI_LAY];
 		float vwc[12][MAX_SOI_LAY];
 		float ice[12][MAX_SOI_LAY];

 		float yreet;
 		float yrpet;
 		float prveetmx;
 		float prvpetmx;
};

#endif /*SOILCLM_H_*/
