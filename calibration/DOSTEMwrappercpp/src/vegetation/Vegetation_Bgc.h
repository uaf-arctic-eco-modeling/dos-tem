#ifndef VEGETATION_BGC_H_
	#define VEGETATION_BGC_H_
	#include "../lookup/CohortLookup.h"
	#include "../data/EnvData.h"
	#include "../data/FirData.h"
	#include "../data/BgcData.h"
	#include "../data/RestartData.h"

	#include "../inc/states.h"
	#include "../inc/fluxes.h"
	#include "../inc/diagnostics.h"
	#include "../inc/parameters.h"

	#include "../ground/Soil_Bgc.h"

	#include <cmath>

//	using namespace std;

	class Vegetation_Bgc{
  		public:
   			Vegetation_Bgc();
   			~Vegetation_Bgc();	
  	
    		void initializeParameter(const int & drgtypep,const int & vegtypep);
    		void initializeState(const int & drgtypep,const int & vegtypep);
    		void initializeState5restart(RestartData *resin);
    
  			void delta();
  			void deltanfeed();
  			void deltastate();
  
   			void setCohortLookup(CohortLookup* chtlup);
   			void setEnvData(EnvData* edp);
   			void setBgcData(BgcData* bdp);
   			void setFirData(FirData* fdp);
  
  			vegstate_bgc tmp_vegs;
  
			atm2veg_bgc del_a2v;
			veg2atm_bgc del_v2a;
			veg2soi_bgc del_v2soi;
			soi2veg_bgc del_soi2v;
			veg2veg_bgc del_v2v;
			vegstate_bgc del_vegs;

			void updateToptUnleafmx(const int & currmind);

			void adapt();

			void prepareIntegration(const bool & equil); //before integration
			void afterIntegration();

			void setSoilBgc(Soil_Bgc * sbp);

			vegpar_cal calpar;
			vegpar_bgc bgcpar;

			double cneven;

  		private:
 			int nfeed;
			int avlnflg;
   
   			/*!factor for changing C:N per ppmv of enhanced CO2*/
   			double dc2n;
   
   			double getUnnormleaf(double &prveetmx, const double & eet, const double & prvunleaf);
  
			/*!  rq10: effect of temperature on plant respiration, updated every month */                    
			double  getRaq10(const double & tair);
			double getTempFactor4GPP(const double & tair);
			/*! kr: for calculating plant maintanence respiration*/
			double getKr(const double & vegc);
			/*! c2n*/
			void updateC2N(const double & yreet,const double & yrpet, const double & initco2,const double & currentco2 );
 			bool equiled;
			double getFoliage();

//Fluxes
/*!**************************************************************
   gpp:    gpp as influenced by carbon dioxide (co2), moisture
	   (gv), phenology (leaf), photosynthetically active
	   radiation (par), air temperature (temp) and freeze-
	   thaw index (thawpercent)	   
************************************************************** */	

/*! **************************************************************
   rm: plant maintenance respiration as influenced by plant
       biomass (vegc) and air temperature (respq10)
************************************************************** */
			double getRm(const double & vegc,const double & raq10, const double &kr);
			double getGV(const double & eet,const double & pet );

			double getLeaf(const double & unnormleaf);
			double getGPP(const double &co2, const double & par, 
            const double &leaf, const double & foliage,
            const double &ftemp, const double & gv);
   
   			EnvData * ed;	
   			BgcData * bd;
   			FirData * fd;
   			CohortLookup * chtlu;
   
		   	Soil_Bgc * sb;                
	};

#endif /*VEGETATION_BGC_H_*/
