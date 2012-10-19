#ifndef SOILCLMOUTPUTER_H_
#define SOILCLMOUTPUTER_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

#include <netcdfcpp.h>
#include <ncvalues.h>

#include "../util/Exception.h"

#include "../run/SoilClm.h"

class SoilclmOutputer {
	public:
		SoilclmOutputer();
		~SoilclmOutputer();
		
 	 	void initSoilClimate(string & outdir);
 	 	void createSoilClimate(const int &chtcnt, const int &yrcnt);
 	 	void setSoilClm(SoilClm *soilclm);

 	 	SoilClm *sclm;
 	 	
 	 	// nc file variables
 		NcFile* sclmFile;

 		NcVar* chtV;

 		NcVar* drgV;
 		NcVar* numslV;

 		NcVar* dzV;
 		NcVar* typeV;
 		NcVar* mintypeV;
 		NcVar* poroV;
 		NcVar* rootfracV;

 		NcVar* petV;
 		NcVar* eetV;

 		NcVar* tsV;
 		NcVar* aldV;
 		NcVar* liqV;
 		NcVar* vwcV;
 		NcVar* iceV;

 		NcVar* yreetV;
 		NcVar* yrpetV;
 		NcVar* prveetmxV;
 		NcVar* prvpetmxV;

};

#endif /*SoilclmOutputer_H_*/
