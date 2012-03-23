/*! \file
 * 
 */
#ifndef VEGETATIONOUTPUTER_H_
#define VEGETATIONOUTPUTER_H_

#include "netcdfcpp.h"
#include "ncvalues.h"

#include "SiteOutputer.h"
#include "../inc/timeconst.h"
#include "../run/VegOutData.h"

using namespace std;

class VegetationOutputer {
	public:
	VegetationOutputer();
	
	/*! define the output variables in netcdf */
	#ifdef ODAY
		void defineDayCohortVars();
		void outputDayCohortVars(const int & yrcnt);

		NcFile * daycf;
		// for daily
		NcDim * dcyearD;
		NcDim * dcdayD;

		NcVar* sthflCDV;
		NcVar* rthflCDV;
		NcVar* sinterCDV;
		NcVar* rinterCDV;
		NcVar* sdripCDV;
		NcVar* rdripCDV;
	
		NcVar* scanopyCDV;
		NcVar* rcanopyCDV;
	
		NcVar* cansubCDV;
		NcVar* canevpCDV;
		NcVar* cantrsCDV;
	
		NcVar* racCDV;
		NcVar* radthrouCDV;
		NcVar* radreflCDV;
	
		NcVar* btranCDV;
		NcVar* m_ppfdCDV;
		NcVar* m_vpdCDV;
		NcVar* ccCDV;

	#endif

//monthly output
		NcFile * moncf;	
		// for monthly	
	
		NcDim * mcmonD;
		NcDim * mcyearD;
		void defineMonthCohortVars();
		void outputMonthCohortVars(const int & yrcnt);
    // monthly var
		NcVar* vegcCMV;
		NcVar* strnCMV;
		NcVar* stonCMV;
		NcVar* ingppCMV;
		NcVar* gppCMV;
		NcVar* innppCMV;
		NcVar* nppCMV;
		NcVar* rmCMV;
		NcVar* rgCMV;
		NcVar* ltrfalcCMV;
		NcVar* ltrfalnCMV;
		NcVar* innuptakeCMV;
		NcVar* nuptakeCMV;
		NcVar* luptakeCMV;
		NcVar* suptakeCMV;
		NcVar* nmobilCMV;
		NcVar* nresorbCMV;
		NcVar* laiCMV;
		NcVar* fpcCMV;
		NcVar* unnormleafCMV;
		NcVar* leafCMV;
		NcVar* foliageCMV;
		NcVar* btranCMV;
		NcVar* racCMV;
		NcVar* rcCMV;
		NcVar* transCMV;
		NcVar* vevapCMV;
		NcVar* vsublCMV;
		NcVar* rinterCMV;
		NcVar* sinterCMV;
		NcVar* rthflCMV;
		NcVar* sthflCMV;
		NcVar* radthflCMV;	
	
//yearly output
		NcFile * yrcf;

		NcDim* ycyearD;
		void defineYearCohortVars();
		void outputYearCohortVars(const int & yrcnt);
  
		NcVar* nppCYV;
		NcVar* ltrfalcCYV;
		NcVar* rgCYV;
		NcVar* rmCYV;
		NcVar* ltrfalnCYV;
		NcVar* vnuptakeCYV;
		NcVar* evapoCYV;
		NcVar* sublimCYV;
		NcVar* transCYV;
    
		NcVar* c2nCYV;
		NcVar* vegcCYV;
		NcVar* strnCYV;
		NcVar* stonCYV;
    
		NcVar* abvgndcCYV;     
		NcVar* foliageCYV;
		NcVar* leafCYV;  //Yuan:
		NcVar* laiCYV;
		NcVar* fpcCYV;   //Yuan:
     
		NcVar* burnorgcCYV;
		NcVar* burnorgnCYV;
    
		NcVar* ninputCYV; //Yuan:
		NcVar* nlostCYV;  //Yuan:
         
	void setOutputer(SiteOutputer * outer);
	void setOutdata(VegOutData * outdata);
    VegOutData * vegod;
    		    	
	private :

		int daycnt;
		void reinit();
		SiteOutputer * siteoutputer;

};

#endif /*VEGETATIONOUTPUTER_H_*/

