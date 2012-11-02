/*! this class contains the bgc at monthly and annually time steps.
 *  It also provides fuctions for sum/avg short timestep data to long timestep.
 * 
 */
#ifndef BGCDATA_H_
#define BGCDATA_H_

#include "../inc/diagnostics.h"
#include "../inc/fluxes.h"
#include "../inc/states.h"
#include "EnvData.h"

#include "RegionData.h"
#include "GridData.h"
#include "CohortData.h"

#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;


class BgcData{
 	public:
  		BgcData();
  		~BgcData();	
	
		//monthly
		vegstate_bgc m_vegs;
		soistate_bgc m_sois;
		vegdiag_bgc m_vegd;
		soidiag_bgc m_soid;
		lnd2atm_bgc m_l2a;
		atm2veg_bgc m_a2v;
		veg2atm_bgc m_v2a;
		veg2soi_bgc m_v2soi;
		soi2veg_bgc m_soi2v;
		veg2veg_bgc m_v2v;
		soi2lnd_bgc m_soi2l;
		soi2atm_bgc m_soi2a;
		atm2soi_bgc m_a2soi;
		soi2soi_bgc m_soi2soi;

		//annually
		vegstate_bgc y_vegs;
		soistate_bgc y_sois;
		vegdiag_bgc y_vegd;
		soidiag_bgc y_soid;
		lnd2atm_bgc y_l2a;
		atm2veg_bgc y_a2v;
		veg2atm_bgc y_v2a;
		veg2soi_bgc y_v2soi;
		soi2veg_bgc y_soi2v;
		veg2veg_bgc y_v2v;
		soi2lnd_bgc y_soi2l;
		soi2atm_bgc y_soi2a;
		atm2soi_bgc y_a2soi;
		soi2soi_bgc y_soi2soi;

		deque <double> toptque;
		deque <double> unleafmxque;

		double foliagemx;
	
		double topt;
		double unleafmx;
		double prvunleafmx;
		double prvtopt;
		double c2n;
		double kdfib;
		double kdhum;
		double kdmin;
		double kdslow;
	
		void init();
    
    	void beginOfMonth(const int & curmrind);
    	void beginOfYear();
    
   		void endOfMonth(const int & currmind); 
    	void endOfYear(const double & cnsoil);
    
    	void setEnvData(EnvData* edp);
    
     	int baseline; //=1 allowing ninput and nlost to be used for adjusting c/n of soil
     	int nfeed;
		int avlnflg;
 
        RegionData * rd;
		GridData * gd;
		CohortData * cd;

    private:
    	EnvData * ed;
		void veg_beginOfMonth();
		void soi_beginOfMonth();
};

#endif /*BGCDATA_H_*/
