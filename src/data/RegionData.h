#ifndef REGIONDATA_H_
#define REGIONDATA_H_

#include <algorithm>
#include "../inc/timeconst.h"

class RegionData{
  	public:
  		RegionData();
  		~RegionData();
    
  		int act_co2_drv_yr;
    	int co2year[MAX_CO2_DRV_YR];
    	float co2[MAX_CO2_DRV_YR];

};

#endif /*REGIONDATA_H_*/
