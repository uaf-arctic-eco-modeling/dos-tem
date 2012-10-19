/*output snow/soil variables */


#ifndef SNOWSOILOUTPUER_H_
#define SNOWSOILOUTPUER_H_
#include <iostream>
#include <netcdfcpp.h>
#include <ncvalues.h>

#include "SiteOutputer.h"
#include "../run/SnowSoilOutData.h"
#include "../inc/timeconst.h"
#include "../inc/layerconst.h"

using namespace std;

class SnowSoilOutputer{
	public:
		SnowSoilOutputer();
				
		void outputCohortErrorCode(int errorids[]);

	 // for daily
		#ifdef ODAY
 			NcFile * daycf;
			NcDim * dcchtD;
			NcDim * dcdayD;
			NcDim * dcyearD;
			NcDim * dcfrontD;
			NcDim * dcsnlayD;
			NcDim * dclayerD;
	
			void defineDayCohortVars();
			
			NcVar* errorCDV;//error code

			NcVar* layerCDV;
			NcVar* snzCDV;
	//		NcVar* sndenCDV;
			NcVar* growCDV;
	
			NcVar* frzfntCDV;
			NcVar* thwfntCDV;
			NcVar* snowthickCDV;
	
			NcVar* sweCDV;
			NcVar* smeltCDV;
			NcVar* ssublCDV;
			NcVar* sevapCDV;

			NcVar* infilCDV;
			NcVar* wtCDV;
			NcVar* fsatCDV;
			NcVar* qoverCDV;
			NcVar* qdrainCDV;
	
			NcVar* liqCDV ;
			NcVar* iceCDV ;
			NcVar* tcondCDV ;
	
			NcVar* snradreflCDV ;
			NcVar* slradreflCDV ;
			NcVar* tsCDV ;
			NcVar* numiterCDV ;
			NcVar* numiterliqCDV ;

			NcVar* aldCDV;  //Yuan

			void outputDayCohortVars(const int & yrcnt);
           
		#endif

	// for monthly
	 		NcFile * moncf;
	 		void defineMonthCohortVars();
	 		void outputMonthCohortVars(const int & yrcnt);
	 
			NcDim * mclayerD;
			NcDim * mcchtD;
			NcDim * mcmonD;
			NcDim * mcyearD;
	
			// monthly var
    		NcVar* errorCMV;
    		NcVar* growpctCMV;
    		NcVar* sninflCMV;
    		NcVar* sevapCMV;
 			NcVar* ssublCMV;
			NcVar* reacsumCMV;
			NcVar* noncsumCMV;
			NcVar* shlwcsumCMV;
			NcVar* deepcsumCMV;
			NcVar* minecsumCMV;
			
			NcVar* temCMV;
			NcVar* tsCMV;
			NcVar* liqCMV;
			NcVar* vwcCMV;	
			NcVar* iceCMV;

			NcVar* aldCMV;  //Yuan
		
			NcVar* dzCMV ;
			NcVar* zCMV ;
			NcVar* porCMV ;
			NcVar* typeCMV ;
	
			NcVar* reacCMV ;
			NcVar* rrhCMV;
	
			NcVar* noncCMV ;
			NcVar* nrhCMV;
	
			NcVar* orgnCMV ;
			NcVar* avlnCMV ;
			NcVar* nimmobCMV ;
			NcVar* netnminCMV;
			NcVar* nuptakelCMV;
	
			NcVar* ninputCMV;
			NcVar* nlostCMV;
	
			NcVar* rhmoistCMV;
			NcVar* rhq10CMV;
			NcVar* ksoilCMV;
			NcVar* kdlCMV;
			NcVar* kdrCMV;
			NcVar* kdnCMV;
	
			NcVar* mossdzCMV;
			NcVar* shlwdzCMV;
			NcVar* deepdzCMV;
			NcVar* watertabCMV;
		
	// for yearly
  			NcFile * yrcf;
  			NcDim* ycchtD;
  			NcDim* ycyearD;
  			NcDim* yclayerD;
  
  			void defineYearCohortVars();
  			void outputYearCohortVars(const int & yrcnt);
 
    		NcVar* sevapCYV;
    		NcVar* qdrainCYV;
    		NcVar* qoverCYV;
    		NcVar* ssublCYV;
    
    		NcVar* netnminCYV;
    		NcVar* snuptakeCYV;
    		NcVar* degday10CYV;
   
    		NcVar* watertabCYV;
    
     		NcVar* errorCYV;
     
     		NcVar* tsaveCYV;
     		NcVar* icesumCYV;
     		NcVar* liqsumCYV;

     		NcVar* tmin10CYV;
     		NcVar* tshlwCYV;
     		NcVar* tdeepCYV;
     		NcVar* tmineCYV;
     
     		NcVar* vwcmin10CYV;
     		NcVar* vwcshlwCYV;
     		NcVar* vwcdeepCYV;
     		NcVar* vwcmineCYV;

     		NcVar* reacsumCYV;
     		NcVar* noncsumCYV;
     
     		NcVar* shlwcsumCYV;
     		NcVar* deepcsumCYV;
     		NcVar* minecsumCYV;
     
     		NcVar* orgnCYV;
     		NcVar* avlnCYV;
     
     		NcVar* rrhsumCYV;
    		NcVar* nrhsumCYV;
  
			NcVar* orgdzCYV;
			NcVar* orgtypeCYV;
	
			NcVar* mossdzCYV;
			NcVar* shlwdzCYV;
			NcVar* deepdzCYV;
			NcVar* mossnumCYV;
			NcVar* shlwnumCYV;
			NcVar* deepnumCYV;
			NcVar* permCYV;
			NcVar* aldCYV;
			NcVar* burnthickCYV;
			NcVar* burnsoilcCYV;
			NcVar* burnsoilnCYV;
			NcVar* orgnreturnCYV;

			NcVar* ninputCYV;
			NcVar* nlostCYV;
	
			NcVar* wdebrisCYV;
			NcVar* wdrhCYV;
	
 		void reinit();
	 
		void setOutputer(SiteOutputer * outer);
		void setOutdata(SnowSoilOutData * outdata);
		SnowSoilOutData * sslod;
				
	private :
	 	int sodaycnt;
	 	int sndaycnt;
  		int numstout; // num of layers for output soil temperature
  		int numsmout; // num of layers for output soil moisture
  		float   zstout[10];
  		float   zsmout[10];
  
		SiteOutputer * siteoutputer;
	
};


#endif /*SNOWSOILOUTPUER_H_*/
