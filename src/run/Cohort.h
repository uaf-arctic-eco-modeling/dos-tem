#ifndef COHORT_H_
	#define COHORT_H_

// headers for TEMcore/
	#include "../atmosphere/Atmosphere.h"

	#include "../vegetation/Vegetation_Env.h"
	#include "../vegetation/Vegetation_Bgc.h"

	#include "../ground/Ground.h"
	#include "../ground/Snow_Env.h"
	#include "../ground/Soil_Env.h"
	#include "../ground/Soil_Bgc.h"
	#include "../ground/layer/Layer.h"
	#include "../ground/layer/SnowLayer.h"
	#include "../ground/layer/SoilLayer.h"
	#include "../ground/layer/PeatLayer.h"

	#include "../disturb/WildFire.h"

	#include "../data/EnvData.h"
	#include "../data/BgcData.h"
	#include "../data/FirData.h"
	#include "../data/RegionData.h"
	#include "../data/GridData.h"
	#include "../data/CohortData.h"
	#include "../data/RestartData.h"

	#include "../lookup/CohortLookup.h"

	#include "../util/Integrator.h"

	#include "../inc/layerconst.h"
	#include "../inc/parameters.h"   //Yuan: for resetting calibration parameters

// headers for run interface
	#include "Timer.h"
	#include "ModelData.h"
	#include "Grid.h"

	#include "SiteIn.h"
    #include "SoilClm.h"

	#include "AtmOutData.h"
	#include "VegOutData.h"
	#include "SnowSoilOutData.h"
	#include "RegnOutData.h"

	class Cohort{
		public :
			Cohort();
			~Cohort();
	
	    // model running status
			bool equiled;   // whether one cohort has reached equlibrium state
			bool spined;
			bool transed;
			bool watbaled;  // whether water balanced
			bool failed;    // when an exception is caught, set failed to be true
			int errorid;

			bool outputSpinup;
	
			bool friderived;  //Yuan: option for switching Grid-level fire occurrence (upon FRI)
			int firstfireyr;  //Yuan: prior to this, FRI controlled fire occurrence, otherwise as input from cohort fire.nc

     	//different modules
			bool envmodule;
			bool ecomodule;
			bool dsbmodule;
			bool dslmodule;
		
		//output options
			bool outRegn;
			bool outSiteDay;
			bool outSiteMonth;
			bool outSiteYear;

			bool outSoilClm;
		  
	 	CohortLookup chtlu;	 	 
	    Ground ground;
 	    Vegetation_Env ve;
 	    Vegetation_Bgc vb;
 	    Soil_Bgc sb;
 	    	        
		Integrator integrator; 

        WildFire fire;
    
        Timer * timer;
	 	Atmosphere * atm;
	 	        
        void init();
        int reset();
        void setTime(Timer * timerp);
      	void setModelData(ModelData* md);
      	void setInputData(RegionData * rd, GridData * gd, CohortData *cd);
        void setProcessData(EnvData * ed, BgcData * bd, FirData *fd);
	    void setAtmData(Grid *grid);
		void setSiteOutData(AtmOutData *atmodp, VegOutData * vegodp, SnowSoilOutData * sslodp);
		void setRegnOutData(RegnOutData * regnodp);
		void setRestartOutData(RestartData *resodp);
		
		bool testEquilibrium();
		
		void fireDrivingData(bool runsp, bool runtr, bool runsc);
		int  timerOutputYearIndex(bool equiled, bool spined, bool outputSpinup);
		
 	 	int updateMonthly(const int & yrcnt,const int &  curryr, const int & currmind,
 	 					 const int & dinmcurr , const bool & assigneq, const bool & useeq);
     	int updateMonthly_Env(const int & yrcnt,const int &  curryr,
     			const int & currmind, const int & dinmcurr , const bool & assigneq);

 	 	void updateMonthly_Bgc(const int & yrcnt,const int &  curryr, 
     			const int & currmind, const int & dinmcurr, const bool & useeq );
     	void updateMonthly_Fir(const int & yrcnt, const int & currmind  );
     
     	void updateMonthly_Dsl(const int & currmind);
     	
     	void getLitterFallRatio(double & deepvsshlw, double & minevsshlw);		
		
		void updateSiteDlyOutputBuffer_Env(const int &doy);
		void updateSiteMlyOutputBuffer_Env(const int & im);
		void updateSiteMlyOutputBuffer_Bgc(const int & im);

		void updateSiteYlyOutputBuffer_Env();
		void updateSiteYlyOutputBuffer_Bgc();
		void updateSiteYlyOutputBuffer_Fir();
		
		void updateRestartOutputBuffer(const int & stage);
		void updateRegionalOutputBuffer(const int &im);  //Yuan: monthly updated
		
		void updateSclmOutputBuffer(const int &im);

//  	protected:
 		EnvData * ed;
    	BgcData * bd;
    	FirData * fd;   
    
    	ModelData * md;
    	RegionData * rd;
    	GridData * gd;
    	CohortData * cd;
    	
    	RestartData resid;    //for input
    	SiteIn sitein;
    	
    	AtmOutData * atmod;
    	VegOutData * vegod;
    	SnowSoilOutData * sslod;
    	RegnOutData *regnod;
    	
    	RestartData * resod;  //for output
    	SoilClm *sclmod;      //for output

    	//Yuan: for java interface to do data exchange
		bool veupdateLAI5Vegc;
		double veenvlai[12];
		void resetBgcPar(vegpar_bgc *vbbgcpar, soipar_bgc *sbbgcpar);
		void getBgcPar(vegpar_bgc *vbbgcpar, soipar_bgc *sbbgcpar);

		void resetCalPar(vegpar_cal * vegcalpar, soipar_cal * soicalpar);
		void getCalPar(vegpar_cal * vegcalpar, soipar_cal * soicalpar);

		void setSiteStates(SiteIn * initstate);
		void getSiteStates(SiteIn * currstate);

		void updateSoilLayerType(int TYPEsoil[], int TYPEmin[]);
    	
	private:
   	 	double ctol;
 	 	double ntol;
 	 	int rheqflag ;   

};
#endif /*COHORT_H_*/
