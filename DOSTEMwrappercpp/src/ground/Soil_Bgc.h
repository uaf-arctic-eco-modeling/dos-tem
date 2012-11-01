#ifndef SOIL_BGC_H_
#define SOIL_BGC_H_

#include "../data/EnvData.h"
#include "../data/FirData.h"
#include "../data/BgcData.h"
#include "../data/RestartData.h"

#include "../lookup/CohortLookup.h"
#include "../inc/states.h"
#include "../inc/fluxes.h"
#include "../inc/diagnostics.h"
#include "../inc/parameters.h"
#include "../inc/layerconst.h"

#include "layer/Layer.h"
#include "layer/SoilLayer.h"
#include "layer/MossLayer.h"
#include "layer/PeatLayer.h"

#include <cmath>
using namespace std;
#include "../util/Exception.h"

class Soil_Bgc{
  public:
  	Soil_Bgc();
 	~Soil_Bgc();	
	
  	void setEnvData(EnvData* edp);
  	void setBgcData(BgcData* bdp);
  	void setFirData(FirData* fdp);
 
  	double shlw2cmcarbon; //the amount of carbon for 2cm shallow
  	double deep2cmcarbon; //the amount of carbon for 2cm deep
	
  	void setCohortLookup(CohortLookup* chtlup);
  
  	void initializeParameter(const int & drgtypep, const int & vegtypep);
  
  	void initializeState( Layer* fstshlwl,Layer* fstminl, const int & drgtypep,const int & vegtypep);
  	void initializeState5restart(Layer* fstsoill, RestartData * resdata);

  	void delta();
  	void deltaavln();
  	void deltastate();
 
  	double  getMossThickness();
  
  	void updateShallowThickness(Layer* fstshlwl, Layer* lstshlwl);
  	void updateDeepThickness(Layer* fstdeepl, Layer* lstdeepl);
  	void updateShallowCarbonAfterLayerDivide(Layer* fstshlwl, Layer* lstshlwl);
  	void updateDeepCarbonAfterLayerDivide(Layer* fstdeepl);

  	void  assignCarbon5Struct2Layer(Layer* fstsoill);
  	void  assignCarbon5Layer2Struct(Layer* fstsoill, const double & wdebris);

  	double getLitterFall(const int & type);
  	void updateMineralKdRatio(Layer* lstshlwl,Layer* lstdeepl);
 	void updateHumicKdRatio(Layer* lstshlwl, Layer* lstdeepl);
  
  	soistate_bgc tmp_sois;
  	veg2soi_bgc del_v2soi;
  	soi2veg_bgc del_soi2v;
  	soistate_bgc del_sois;
  	soistate_bgc del_soid;
  	soi2soi_bgc del_soi2soi;
  	atm2soi_bgc del_a2soi;
  	soi2atm_bgc del_soi2a;
  	soi2lnd_bgc del_soi2l;

//called from vegetatation_bgc::delta
  	double getNuptake(const double & foliage, const double & raq10, const double & kn1, const double & nmax); 
  	void prepareIntegration();
  	void afterIntegration();
  
  	soipar_bgc bgcpar;//used by calibrator
  	soipar_cal calpar; //used by calibrator
  	void updateKdyrly4all(const int & yrcnt );

  private:
  	double getKdyrly(  double& yrltrc, double& yrltrn, const double lcclnc, const int & nfeed, const double & kdc);
  
  	int nfeed;
  	int avlnflg;
  
  	void initSoilCarbon(Layer* fstshlwl,Layer* fstminl, double & initsoilc);
  	void initShlwCarbon(Layer* fstshlwl, double & allreac, double & allnonc);
  	void initDeepCarbon(Layer* fstshlwl, double & allreac, double & allnonc);
  	void initMineralCarbon (Layer* fstminl, double & minec, double & allreac, double & allnonc);
	double meanksoil;
	double totsolliq;   
	double nitroadd; //nitrogen added to orgn to compensate nitrogen emit by fire

	//// for initializing soil carbon
	double getCumulativePeatCarbonHAM(const double & ham);    
	//// end for initializing soil carbon

	double getCumulativeCarbonBD(const double & bdep);  
  	double blwfrac, blwlfcfrac[MAX_SOI_LAY];
  	double abvfrac, abvlfcfrac[MAX_SOI_LAY];
 	double kdshlw, kddeep;
  	
  	EnvData * ed;	
  	BgcData * bd;
  	FirData * fd;

  	CohortLookup * chtlu;

  	double decay;
  	double nup;
  
   	int numsl ;//num of soils
  
  	double getRhmoist(const double &vsm, 
	const double & moistmin, const double & moistmax, const double & moistopt);
  	double getNimmob(const double & soilh2o, const double & soilorgc, const double & soilorgn,
					 const double & availn, const double & ksoil, const double   kn2);	
					 
  	double getNetmin(const double & nimmob, const double & soilorgc, const double & soilorgn,
					 const double & availn, const double & rh, const double & tcnsoil,
					  const double & decay, const double & nup );
  	double getKSoil(const double & vsm);
  	double getRhq10(const double & tsoil);
					  					 
};
#endif /*SOIL_BGC_H_*/
