#ifndef SOIL_ENV_H_
#define SOIL_ENV_H_

#include "Stefan.h"  
#include "Richard.h"

#include "../data/EnvData.h"
#include "../data/FirData.h"
#include "../data/RestartData.h"

#include "layer/Layer.h"
#include "layer/SoilLayer.h"
#include "layer/PeatLayer.h"

#include "../inc/parameters.h"
#include "../lookup/CohortLookup.h"
#include "../inc/layerconst.h"

#include "Moss.h"
#include "Peat.h"
#include "Mineral.h"
#include "../inc/ErrorCode.h"
#include "../util/Exception.h"


class Soil_Env{
  public:
  Soil_Env();
  ~Soil_Env();	
	
	
	 /*! the thickness of soil column , which is from the the top
	     * of moss layer, if exists, to the bottom of last mineral layer.(unit: m)*/
	 double dztot;
	 /*! number of soil layers */
	 int num;
	 double initem[MAX_SOI_LAY];
	 double inivwc[MAX_SOI_LAY];
	 
	  /*! reset diagnostic variables to initial values */
 	 void resetDiagnostic();
 	 
 	Moss moss;
	Peat peat;
	Mineral mineral;
	
 	 
  Richard richard;
  Stefan stefan;

  void setEnvData(EnvData* edp);
   void setFirData(FirData* fdp);
  void setCohortLookup(CohortLookup * chtlup);
 
  void updateDailySurfFlux(Layer* frontl, const double & tsurf, const double & dayl);
  
  double getWaterTable(Layer* fstsoil);

  
  void initializeParameter(const int &drgtypep, const int &vegtypep);
  void initializeState(Layer* fstsoill);
  void initializeState5restart( Layer* fstsoill,RestartData* resin);
  
  
  double infilFrozen2(Layer* fstsoill, Layer *fstminl, const double &  rnth, const double & melt);
  
  double infilFrozen(Layer* fstminl, const double & infilf);

  double getDrainage(const double & wtable);
  double getRunoff(Layer* fstsoill, const double & rnth,const double & melt, const double & frasat);
  double update5Drainage(Layer* drainl, const double & fracsat, const double & wtd);
  
  double  getSoilTransFactor(Layer* fstsoill);


 double update5BaseFlow(Layer* drainl);
 
 double getBaseFlow(double const & wetness );

double getRunoffVIC(Layer* fstsoill, const double & rnth,const double & melt);

///////////////////
void layer2structdaily(Layer* fstsoill);
void layer2structmonthly(Layer* fstsoill);
void retrieveDailyOutputs(Layer* fstsoill, Layer* fstminl, Layer* lstminl, Layer* backl);
void retrieveDailyFronts(Layer* fstsoill);
void retrieveThawPercent(Layer* fstsoill);

//////////////////////

void resetFineRootFrac(const int & yrcnt, Layer* fstsoill);
void resetTypeDZ(Layer* fstsoill);
soipar_env envpar;

 double getFracSat(const double & wtd);

  private:
  
  
  double getEvaporation(const double & tsurf, const double & dayl, const double &rad);  
  double getPenMonET(const double & ta, const double& vpd, const double &irad, const double &rv, const double & rh);
  double updateLayerTemp5Lat(Layer* currl, const double & infil); 
  double getFineRootFrac(const int & yrcnt, const double & layertop, const double & layerbot, const double & mossthick);

  EnvData * ed;	
  FirData * fd;
  CohortLookup* chtlu;

  void initTempMois(Layer* frontl);
  void initRootMass(Layer* fstsoill);

};

#endif /*SOIL_ENV_H_*/
