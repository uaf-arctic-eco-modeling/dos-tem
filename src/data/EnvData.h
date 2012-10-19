#ifndef ENVDATA_H_
#define ENVDATA_H_

#include "../inc/diagnostics.h"
#include "../inc/fluxes.h"
#include "../inc/states.h"
#include "../inc/layerconst.h"

#include "../inc/timeconst.h"
#include "RegionData.h"
#include "GridData.h"
#include "CohortData.h"

#include <algorithm>
#include <deque>
using namespace std;

class EnvData{
  public:
  	EnvData();
  	~EnvData();

    double daylengths[365];
  	// for daily
    atmstate_env d_atms;
    vegstate_env d_vegs;
    snwstate_env d_snws;
    soistate_env d_sois;
    
    atmdiag_env d_atmd; //first d is daily, last d is diagnostic
    vegdiag_env d_vegd; 
    snwdiag_env d_snwd;
    soidiag_env d_soid;
    
    lnd2atm_env d_l2a;
    atm2lnd_env d_a2l;
    atm2veg_env d_a2v;
    veg2atm_env d_v2a;
    veg2gnd_env d_v2g;
    lnd2soi_env d_l2soi;
    soi2lnd_env d_soi2l;
    soi2atm_env d_soi2a;
    snw2atm_env d_snw2a;
    snw2soi_env d_snw2soi;
    
   // monthly
    atmstate_env m_atms;
    vegstate_env m_vegs;
    snwstate_env m_snws;
    soistate_env m_sois;
    
    atmdiag_env m_atmd; 
    vegdiag_env m_vegd; 
    snwdiag_env m_snwd;
    soidiag_env m_soid;
    
    lnd2atm_env m_l2a;
    atm2lnd_env m_a2l;
    atm2veg_env m_a2v;
    veg2atm_env m_v2a;
    veg2gnd_env m_v2g;
    lnd2soi_env m_l2soi;
    soi2lnd_env m_soi2l;
    soi2atm_env m_soi2a;
    snw2atm_env m_snw2a;
    snw2soi_env m_snw2soi;
  
  // annually
  	atmstate_env y_atms;
    vegstate_env y_vegs;
    snwstate_env y_snws;
    soistate_env y_sois;
    
    atmdiag_env y_atmd; 
    vegdiag_env y_vegd; 
    snwdiag_env y_snwd;
    soidiag_env y_soid;
    
    lnd2atm_env y_l2a;
    atm2lnd_env y_a2l;
    atm2veg_env y_a2v;
    veg2atm_env y_v2a;
    veg2gnd_env y_v2g;
    lnd2soi_env y_l2soi;
    soi2lnd_env y_soi2l;
    soi2atm_env y_soi2a;
    snw2atm_env y_snw2a;
    snw2soi_env y_snw2soi;
    
    double eetmx;
    double petmx;

    double prveetmx;
    double prvpetmx;
    
    /*! initial concentration of carbon dioxide in ppmv*/
    double initco2;

    // yr value
    int permafrost; // whether a site is a permafrost
    double y_ald; // active layer depth  //Yuan: yearly max.
    double m_ald; // active layer depth  //Yuan: monthly max.
    double d_ald; // active layer depth  //Yuan: daily
    
    double yrfrozensoil; //Yuan: the time (years) since frozen a soil bottom horizon

    void init();

    void beginOfDay();
    void beginOfMonth();
    void beginOfYear();
    
    void endOfDay(const int & dinm, const int & doy );
    void endOfMonth(const int & currmind, const bool & assign);
    void endOfYear(const bool & assign);
    
    // monthly soil climate
    double eq_ts[12][MAX_SOI_LAY];
    double eq_liq[12][MAX_SOI_LAY];
    double eq_ice[12][MAX_SOI_LAY];
    double eq_vwc[12][MAX_SOI_LAY];  //(all) volume water content
    double eq_sws[12][MAX_SOI_LAY];  //soil water saturation
    double eq_aws[12][MAX_SOI_LAY];  //adjusted soil water saturation (porosity adjusted by ice)
    double eq_ta[12];
    double eq_co2[12];
    double eq_eet[12];
    double eq_pet[12];
    double eq_par[12];
    double eq_grow[12];
    double eq_y_eet;
    double eq_y_pet;
    double eq_y_co2;
    double eq_prveetmx;
    double eq_prvpetmx;
     
	deque <double> eetmxque;
	deque <double> petmxque;

	RegionData * rd;
	GridData * gd;
	CohortData * cd; 

   // for java interface
    double eq_ts1d[12*MAX_SOI_LAY];
    double eq_liq1d[12*MAX_SOI_LAY];
    double eq_vwc1d[12*MAX_SOI_LAY];
    double eq_sws1d[12*MAX_SOI_LAY];
    double eq_ice1d[12*MAX_SOI_LAY];
    void d1tod2();
    void d2tod1();
    // for java interface
   
  private:
	
	void veg_beginOfMonth();
	void soi_beginOfMonth();
	void snw_beginOfMonth();
	
	void atm_endOfDay(const int & dinm);
	void veg_endOfDay(const int & dinm);
	void soi_endOfDay(const int & dinm, const int & doy);
	void snw_endOfDay(const int & dinm);
	   
};

#endif /*ENVDATA_H_*/
