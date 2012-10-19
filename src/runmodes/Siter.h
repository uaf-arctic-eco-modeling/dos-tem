/*! the Siter is a class used specifically for site run
 * Initialize all the necessary classes in this class, so that
 * for the regional run, there is no need to reinit all the classes for grid and cohort 
 * when a new grid or cohort appears.
 * */
#ifndef SITER_H_
#define SITER_H_

//headers in local source directory
#include "RunCohort.h"

#include "../input/RegionInputer.h"
#include "../run/Controller.h"

class Siter {
	public:
		Siter();
		~Siter();
	
		void init(const string &controlfile); // set pointer between classes
    	void run();
    
 	private:
    
    	//Inptuer
    	Controller configin;
    	RegionInputer rin;
    	GridInputer gin;
    	CohortInputer cin;
    	SiteinInputer sitein;
    	RestartInputer resin;
        
    	//data classes
    	EnvData  ed;
    	BgcData  bd;
    	FirData  fd;
    	ModelData md;
    
    	RegionData rd;    
    	GridData gd;
    	CohortData cd;  
    	
    	AtmOutData atmod;
    	VegOutData vegod;
    	SnowSoilOutData sslod;    	
    	RestartData resod;
    	
		//outputer
		SiteOutputer sout;
		AtmosphereOutputer satmout;
    	VegetationOutputer svegout;
    	SnowSoilOutputer ssslout;		

    	RestartOutputer resout;
    	
		//util
		Timer timer;

    	// site-specific
		Grid sgrid;
    	RunCohort runcht;
	
};
#endif /*SITER_H_*/
