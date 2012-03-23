#ifndef SOILCLMINPUTER_H_
#define SOILCLMINPUTER_H_
 
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

#include "netcdfcpp.h"

#include "../util/Exception.h"

#include "../run/SoilClm.h"

class SoilclmInputer{
	public:
		SoilclmInputer();
		~SoilclmInputer();
	
		void init(string & datadir);
		int getRecordId(const int &chtid);
		void getChtId(int &chtid, const int &recid);
		void getSoilClimate(SoilClm * sclm, const int & recid);

	private:
	   // nc file variables
		NcFile* sclmFile;

		NcDim* chtD;
		NcDim* yrD;
		NcDim* monD;
		NcDim* layerD;
		NcDim* mlayerD;

		NcVar* chtidV;

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

#endif /*SINPUTER_H_*/
