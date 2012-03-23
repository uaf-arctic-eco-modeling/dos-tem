#ifndef FIRDATA_H_
#define FIRDATA_H_
/*! this class contains the fire at annually time steps.
*/

#include "../inc/diagnostics.h"
#include "../inc/fluxes.h"
#include "../inc/states.h"
#include "EnvData.h"
#include "../inc/timeconst.h"

#include <iostream>
#include <math.h>
#include "RegionData.h"
#include "GridData.h"
#include "CohortData.h"

class FirData{
 	public:
  		FirData();
  		~FirData();	

		veg2atm_fir y_v2a;
		veg2soi_fir y_v2soi;

		soi2atm_fir y_soi2a;
		soidiag_fir y_soid;
		atm2soi_fir y_a2soi;

		bool useseverity;

//in Eric's algorithm, season, fire size 


		void init();
    	void beginOfYear();
    	void endOfYear();    
    	void burn();    
    	
    	int ysf; 
  
		RegionData * rd;
		GridData * gd;
		CohortData * cd;
    
};

#endif /*FIRDATA_H_*/
