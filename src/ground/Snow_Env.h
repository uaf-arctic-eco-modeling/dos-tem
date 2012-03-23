#ifndef SNOW_ENV_H_
#define SNOW_ENV_H_

#include "../data/EnvData.h"
#include "../data/FirData.h"
#include "../data/RestartData.h"

#include "../inc/parameters.h"
#include "layer/Layer.h"
#include "layer/SnowLayer.h"

#include "../lookup/CohortLookup.h"
#include "../inc/layerconst.h"

class Snow_Env{
  public:
  Snow_Env();
  ~Snow_Env();
		  /*! the thickness of snow column.(unit: m)*/
	    double dztot;
	    /*! number of snow layers */
	    int num;
	    
	    /*! the wind speed class (0, 1)? of a vegetation type*/
	    double wind;
	    
	    /*! density of snow */
	    double dense;
	    
	    /*! melt factor */
	    double fcmelt;
	    
	    /*! extra snow mass */
	    double extramass; // to make sure that the thickness of snowpack is not too small
	    // if the calculated layer thickness is less 1cm, then keep the snow mass in extramass
	    // until meet the requirement
	    
	    /*! the maximum snow mass that a layer can hold
	     * this is used to constrain the layer thickness
	     * for computing stability*/
	    double massmax;

	    double maxdz[MAX_SNW_LAY];
	    double mindz[MAX_SNW_LAY];
  
	    void setEnvData(EnvData* edp);

	    void setFirData(FirData* fdp);

	    void updateDailySurfFlux( Layer* frontl, const double & tdrv);

	    void setCohortLookup(CohortLookup * chtlup);

	    void initializeParameter(const int &chttypep);
	    void initializeState5restart(Layer* frontl, RestartData* resin);

	    void resetDiagnostic(); /*! reset diagnostic variables to initial values */
 	 
	    void retrieveDailyOutputs(Layer* frontl);


	    snwpar_env envpar;
 	 
  private:

	    int chttype;
	    double getSublimation(double const & rn, double const & swe, double const & ta);

	    EnvData * ed;
	    FirData * fd;
 
	    CohortLookup * chtlu;
};

#endif /*SNOW_ENV_H_*/
