#ifndef SITEININPUTER_H_
#define SITEININPUTER_H_
 
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
#include "../inc/ErrorCode.h"

#include "../run/SiteIn.h"

class SiteinInputer{
	public:
		SiteinInputer();
		~SiteinInputer();
	
		void initSiteinFile(string & dirfile);
		int getRecID(const int &siteid);
		int getSiteinData(SiteIn * sid, const int & recid);

	private:
		string siteinfname;

};

#endif /*SINPUTER_H_*/
