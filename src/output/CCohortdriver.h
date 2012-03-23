#ifndef CCOHORTDRIVER_H_
#define CCOHORTDRIVER_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

#include "netcdfcpp.h"

#include "../util/Exception.h"
#include "../inc/layerconst.h"
#include "../inc/timeconst.h"

#include "../run/Cohort.h"

class CCohortdriver {
	public:
		CCohortdriver();
		~CCohortdriver();
		
 	 	void createSoilClimate(BgcData *bd, EnvData *ed, Vegetation_Env *ve, string& datadir);
 	 	
};

#endif /*CCohortdriver_H_*/
