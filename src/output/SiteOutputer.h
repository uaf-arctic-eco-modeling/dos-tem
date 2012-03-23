/*
 *  This class is used to output modeling results in the netcdf format
 *
 * for a single site run of TEM (usually much more detailed)
 *
 */

#ifndef SITEOUTPUTER_H_
#define SITEOUTPUTER_H_
#include "netcdfcpp.h"
#include "ncvalues.h"

#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;
#include <string>
using std::string;

//from TEMcore/..
#include "../inc/layerconst.h"
#include "../inc/timeconst.h"

//local
#include "../run/ModelData.h"

//local
#include "../TEMMOD.h"

class SiteOutputer {
   public :
	SiteOutputer();
	~SiteOutputer();

	void init();
	void setModelData(ModelData* mdp);

	ModelData* md;

	#ifdef ODAY		// for daily

    // cohort level
		NcFile* dayChtFile;   
		void defineDailyCohortDimension();
		NcDim * dcdayD;
		NcDim * dcyearD;
		NcDim * dcfrontD;
		NcDim * dcsnlayD;
		NcDim * dclayerD;
	
	// grid level
		NcFile* dayGrdFile; 
		void defineDailyGridDimension();
		NcDim * dgdayD;
		NcDim * dgyearD;
		NcDim * dggrdD;
	
	#endif	

// for monthly
		NcFile* monChtFile;
		void defineMonthlyCohortDimension();
		NcDim * mcchtD;
		NcDim * mcyearD;
		NcDim * mcmonD;
		NcDim * mclayerD;
		NcDim * mcstrD;
		NcDim * mcgrdD;
	
		NcFile* monGrdFile;
		void defineMonthlyGridDimension();
		NcDim * mgyearD;
		NcDim * mgmonD;
		NcDim * mglayerD;
		NcDim * mggrdD;	
	
//yearly output
		NcFile* yrChtFile;
		void defineYearlyCohortDimension();

		NcDim * ycchtD;
		NcDim * ycyearD;
		NcDim * yclayerD;
	
		NcFile* yrGrdFile;
		void defineYearlyGridDimension();

		NcDim * ygyearD;
		NcDim * yggrdD;	

    	
};

#endif /*SiteOutputer_H_*/
