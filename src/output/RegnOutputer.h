#ifndef REGNOUTPUTER_H_
#define REGNOUTPUTER_H_
/*! this class is used to output modeling results in the netcdf format
 * when running TEM at regional-mode (i.e., multiple sites)
 * 
 */

#include "netcdfcpp.h"
#include "ncvalues.h"

#include <iostream>
#include <string>
using namespace std;

#include "../run/RegnOutData.h"

class RegnOutputer{
	
	public:
		RegnOutputer();
		~RegnOutputer();
	
 		void init(string& outputdir, const int & myid, string& stage, int MAX_DRV_YR);
  
 		void outputYearCohortVars(const int & yrind, const int & chtid);
  
  		void missingValues(const int & MAX_YR, const int & chtid);
  		void setOutData(RegnOutData *regnodp);
  		  
    	NcFile* rFile;

		NcDim * chtD;
		NcDim * yearD;
		NcDim * monthD;
 
    	NcVar* chtidCYV;
   		NcVar* statusCYV;
   		NcVar* ysfCYV;

   		NcVar* burnthickCYV;
   		NcVar* burnsoicCYV;
   		NcVar* burnvegcCYV;

   		NcVar* growstartCYV;
   		NcVar* growendCYV;

   		NcVar* permCYV;

   		NcVar* mossdzCYV;
   		NcVar* shlwdzCYV;
   		NcVar* deepdzCYV;

      	NcVar* laiCYV;
   		NcVar* vegcCYV;
   		NcVar* vegnCYV;

   		NcVar* gppCYV;
   		NcVar* nppCYV;
   		NcVar* rhCYV;
        NcVar* ltrfalcCYV;
        NcVar* ltrfalnCYV;

   		NcVar* shlwcCYV;
   		NcVar* deepcCYV;
   		NcVar* minecCYV;
   		NcVar* orgnCYV;
   		NcVar* avlnCYV;

   		NcVar* netnminCYV;
        NcVar* nuptakeCYV;
      	NcVar* ninputCYV;
      	NcVar* nlostCYV;

   		NcVar* eetCYV;
   		NcVar* petCYV;
   		NcVar* qdrainCYV;
      	NcVar* qrunoffCYV;

      	NcVar* sthickCYV;
      	NcVar* sweCYV;

   		NcVar* wtdCYV;
      	NcVar* aldCYV;

   		NcVar* vwcshlwCYV;
   		NcVar* vwcdeepCYV;
   		NcVar* vwcminetopCYV;
      	NcVar* vwcminebotCYV;

   		NcVar* tshlwCYV;
   		NcVar* tdeepCYV;
   		NcVar* tminetopCYV;
   		NcVar* tminebotCYV;
   
   		NcVar* hkshlwCYV;
   		NcVar* hkdeepCYV;
   		NcVar* hkminetopCYV;
   		NcVar* hkminebotCYV;

   		NcVar* tcshlwCYV;
   		NcVar* tcdeepCYV;
   		NcVar* tcminetopCYV;
   		NcVar* tcminebotCYV;

   		NcVar* trock34CYV;

   		NcVar* somcaldCYV;
      	NcVar* vwcaldCYV;
      	NcVar* taldCYV;

   		RegnOutData *regnod;
   		
};

#endif /*REGNOUTPUTER_H_*/
