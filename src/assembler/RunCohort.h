/*
 * This class is used to run a cohort: from input to output
 *  
 */
 
#ifndef RUNCOHORT_H_
#define RUNCOHORT_H_

#include <iostream>

//local headers
#include "../TEMMOD.h"
#include "../input/GridInputer.h"
#include "../input/CohortInputer.h"
#include "../input/SiteinInputer.h"
#include "../input/RestartInputer.h"
//#include "../input/SoilclmInputer.h"

#include "../output/SiteOutputer.h"
#include "../output/AtmosphereOutputer.h"
#include "../output/VegetationOutputer.h"
#include "../output/SnowSoilOutputer.h"
#include "../output/StatusOutputer.h"
#include "../output/RestartOutputer.h"
#include "../output/RegnOutputer.h"

#include "../run/Cohort.h"

class RunCohort {
	public:
	 	RunCohort();

	    void setGridInputer(GridInputer * cin);
	    void setCohortInputer(CohortInputer * cin);
	    void setRestartInputer(RestartInputer * resin);
	    void setSiteinInputer(SiteinInputer * sin);
	    
 	 	int reinit(const int &cid, const int &eqcid, const int &rescid);

     	void run();

	 	void siteoutput(const int & outputyrind, const int & currmind);
	    void setRestartOutputer(RestartOutputer * resoutp);
		void setOutputer(SiteOutputer *soutp, AtmosphereOutputer *satmoutp,
  				VegetationOutputer * svegoutp, SnowSoilOutputer * sssloutp);
		void setRegionalOutputer(RegnOutputer *routp);
	 	
 		Cohort cht;
 		
 		GridInputer *ginputer;
 		CohortInputer *cinputer;
 		RestartInputer *resinputer;

// 		SoilclmInputer sclminputer;
 		SiteinInputer *sinputer;
    	
 		SiteOutputer * sout;
 		AtmosphereOutputer * satmout;
 		VegetationOutputer * svegout;
 		SnowSoilOutputer * ssslout;
 		
 		RegnOutputer *rout;
 		
 		RestartOutputer *resout;

 		bool jcalifilein;
 		string jcalparfile;
 		
 		bool ccdriverout; 		

		void runEquilibrium();
		void setCalibrationParameters(CohortLookup* chtlu, string& jtxtfile);
		void setCalibrationInits(CohortLookup* chtlu, string& jtxtfile);

	private :
 	  		 	 
		stringstream svegtype;
		stringstream sdrgtype;

 		void runSpinup();
 		void runTransit();
 		void runScenario();
 		
};
#endif /*RUNCOHORT_H_*/
