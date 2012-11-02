#ifndef ATMOSPHERE_H_
#define ATMOSPHERE_H_

#include "../inc/timeconst.h"

#include "AtmosUtil.h"
#include "../data/EnvData.h"
#include "../data/GridData.h"
#include "../data/RegionData.h"

#include <iostream>
#include <cmath>
using namespace std;
class Atmosphere{
   public:
   		Atmosphere();
   		~Atmosphere();
	
		void updateDailyEnviron(const int &yrcnt, const int & mid, const int & dayid,
				const bool & normal, const bool & changeclm);
	
    	void prepareMonthDrivingData();
    	void prepareDayDrivingData();
		void setEnvData(EnvData* edp);

    	float tam[12];

    	void beginOfMonth(const int & curyrcnt, const int& currmind ,const int& dinmcurr,
    			const bool & normal, const bool & changeclm, const bool & changeco2);
 	
	private:									            
	
	// monthly
     
		float ta[MAX_ATM_DRV_YR][12];
		float prec[MAX_ATM_DRV_YR][12];
		float cld[MAX_ATM_DRV_YR][12];
		float snow[MAX_ATM_DRV_YR][12];
		float rain[MAX_ATM_DRV_YR][12];
		float vap[MAX_ATM_DRV_YR][12];
		float par[MAX_ATM_DRV_YR][12];
		float ppfd[MAX_ATM_DRV_YR][12];
		float nirr[MAX_ATM_DRV_YR][12];
		float girr[MAX_ATM_DRV_YR][12];
	// daily
		float ta_d[MAX_ATM_DRV_YR][12][31];
		float rain_d[MAX_ATM_DRV_YR][12][31];
		float snow_d[MAX_ATM_DRV_YR][12][31];
		float vap_d[MAX_ATM_DRV_YR][12][31];
	
		float rhoa_d[MAX_ATM_DRV_YR][12][31];
		float svp_d[MAX_ATM_DRV_YR][12][31];
		float dersvp_d[MAX_ATM_DRV_YR][12][31];
		float abshd_d[MAX_ATM_DRV_YR][12][31];
		float vpd_d[MAX_ATM_DRV_YR][12][31];

	// for Equilibrium run, using the first 30 yrs-averaged
		float eq_ta[12];
		float eq_prec[12];
		float eq_cld[12];
		float eq_vap[12];
		float eq_rain[12];
		float eq_snow[12];
	
		float eq_par[12];
		float eq_ppfd[12];
		float eq_nirr[12];
		float eq_girr[12];
	
		float eq_ta_d[12][31];
		float eq_rain_d[12][31];
		float eq_snow_d[12][31];
		float eq_vap_d[12][31];
	
		float eq_rhoa_d[12][31];
		float eq_svp_d[12][31];
		float eq_dersvp_d[12][31];
		float eq_abshd_d[12][31];
		float eq_vpd_d[12][31];

	// for run, using the current last 30 yrs-averaged
		float ca_ta[12];
		float ca_prec[12];
		float ca_cld[12];
		float ca_vap[12];
		float ca_rain[12];
		float ca_snow[12];
	
		float ca_par[12];
		float ca_ppfd[12];
		float ca_nirr[12];
		float ca_girr[12];
	
		float ca_ta_d[12][31];
		float ca_rain_d[12][31];
		float ca_snow_d[12][31];
		float ca_vap_d[12][31];
	
		float ca_rhoa_d[12][31];
		float ca_svp_d[12][31];
		float ca_dersvp_d[12][31];
		float ca_abshd_d[12][31];
		float ca_vpd_d[12][31];
		
		AtmosUtil autil;
	
		float getAirDensity(float const & ta);
		float getVPD (const float & svp, const float vp);
		float getAbsHumDeficit(const float & svp, const float &vp, const float & ta);
		float wetdays ;

		float yrsumday;
		void precsplt(const float & tair,const float & prec, float & snfl, float & rnfl);

   		EnvData * ed;
   	         
    	float getPET( const float & nirr, const float & tair,const int & dinm );
		float getGIRR( const float &lat, const int& dinm);			
		float getNIRR( const float& clds, const float& girr );				
		float getPAR( const float& clds, const float& nirr );	
		float getCLDS( const float& girr, const float& nirr );
 		float getSatVP(const float & t);		
	 
		float getDensity(const float & ta);
		float getDerSVP( const float & t); 	
		float getDerSVP( const float & tair, const float & svp);
   	
};

#endif /*ATMOSPHERE_H_*/
