/*! \file
 * 
 */
#include "Atmosphere.h"

Atmosphere::Atmosphere(){
   	// if in the mode of spinup or spintransient
   	// initialize with spinup condition for prev
   	// here atmin is NULL , cause a runtime error which is hard to find

	wetdays = 10.; // cru has wetdays output from 1901 to 2002, but not for scenario run
	// temperarily assume wetdays = 10;

};

Atmosphere::~Atmosphere(){
	
};

void Atmosphere::prepareMonthDrivingData(){
     float lat = ed->gd->lat;
   
     int dinm[] ={31,28,31,30,31,30,31,31,30,31,30,31};
    	
     //ta degC, prec mm/mon, nirr w/m2, vap mbar, 
     for(int iy =0; iy<ed->gd->act_atm_drv_yr; iy++){
       	for (int im=0; im<12; im++){
       		ta[iy][im]   = ed->gd->ta[iy][im];
       		prec[iy][im] = ed->gd->prec[iy][im];
       		nirr[iy][im] = ed->gd->nirr[iy][im];
       		vap[iy][im]  = ed->gd->vap[iy][im];
       	}	
     }
     
     for(int iy =0; iy<ed->gd->act_atm_drv_yr; iy++){
       	for (int im=0; im<12; im++){
       		vap[iy][im] *=100; // convert from mbar to pa
       		precsplt(ta[iy][im], prec[iy][im], snow[iy][im],rain[iy][im]); // distinguish prec as snow or rainfall
       	}	
     }
            
    // for equilibrium
    	
    for(int im =0; im<12; im++){
    	eq_ta[im]=0.;
    	eq_prec[im]=0.;
    	eq_rain[im]=0.;
    	eq_snow[im]=0.;
    	eq_nirr[im]=0.;
    	eq_vap[im]=0.;
    			
    	for(int iy=0; iy<MAX_ATM_NOM_YR;iy++){    //Yuan: average over the first 30 yrs atm data
    		eq_ta[im] += ta[iy][im]/MAX_ATM_NOM_YR;
    		eq_prec[im] += prec[iy][im]/MAX_ATM_NOM_YR;
    		eq_rain[im] += rain[iy][im]/MAX_ATM_NOM_YR;
    		eq_snow[im] += snow[iy][im]/MAX_ATM_NOM_YR;
    		eq_nirr[im] += nirr[iy][im]/MAX_ATM_NOM_YR;
    		eq_vap[im] += vap[iy][im]/MAX_ATM_NOM_YR;
		}
	}
    		
    for(int im =0; im<12; im++){
    		ca_ta[im]=0.;
    		ca_prec[im]=0.;
    		ca_rain[im]=0.;
    		ca_snow[im]=0.;
    		ca_nirr[im]=0.;
    		ca_vap[im]=0.;
    		
    		for(int iy=ed->gd->act_atm_drv_yr-MAX_ATM_NOM_YR; iy<ed->gd->act_atm_drv_yr;iy++){    //Yuan: average over  the last 30 yrs atm data
    			ca_ta[im] += ta[iy][im]/MAX_ATM_NOM_YR;
    			ca_prec[im] += prec[iy][im]/MAX_ATM_NOM_YR;
    			ca_rain[im] += rain[iy][im]/MAX_ATM_NOM_YR;
    			ca_snow[im] += snow[iy][im]/MAX_ATM_NOM_YR;
    			ca_nirr[im] += nirr[iy][im]/MAX_ATM_NOM_YR;
    			ca_vap[im] += vap[iy][im]/MAX_ATM_NOM_YR;
    		}
    }
   
   	// prepare other variables
   	for(int iy=0; iy<ed->gd->act_atm_drv_yr; iy++){
   		yrsumday=0; //Yi: may 17, 2010
   		for(int im=0; im<12;im++){
	       girr[iy][im] = getGIRR(lat, dinm[im] );
	       cld[iy][im] = getCLDS(girr[iy][im], nirr[iy][im]);
	       par[iy][im] = getPAR( cld[iy][im],  nirr[iy][im] );
    	}
   	}
    	
   	for(int im=0; im<12;im++){
   		yrsumday=0; //Yi: may 17, 2010
	    eq_girr[im] = getGIRR(lat, dinm[im] );
	    eq_cld[im] = getCLDS(eq_girr[im], eq_nirr[im]);
	    eq_par[im] = getPAR( eq_cld[im],  eq_nirr[im] );
    }
    
    for(int im=0; im<12;im++){
   		yrsumday=0; //Yi: may 17, 2010
	    ca_girr[im] = getGIRR(lat, dinm[im] );
	    ca_cld[im] = getCLDS(ca_girr[im], ca_nirr[im]);
	    ca_par[im] = getPAR( ca_cld[im],  ca_nirr[im] );
    }
    
};
 
void Atmosphere::prepareDayDrivingData(){
    	// first for equilibrium 
    	float tad1[31], vapd1[31], precd1[31];
    	int dinm[] ={31,28,31,30,31,30,31,31,30,31,30,31};
    	float pvalt, cvalt, nvalt;
    	float pvalv, cvalv, nvalv;
    	float pvalp, cvalp, nvalp;
    	int dinmprev, dinmcurr, dinmnext;
    	
    	for(int im =0; im<12;im++){
    		cvalt = eq_ta[im];
    		cvalv = eq_vap[im];
    		cvalp = eq_prec[im];
    		dinmcurr = dinm[im];
    		if(im==0){
    		  	  pvalt = eq_ta[11];
    		  	  pvalv = eq_vap[11];
    		  	  pvalp = eq_prec[11];
    		  	  
    		  	  nvalt = eq_ta[im+1];
    		  	  nvalv = eq_vap[im+1];
    		  	  nvalp = eq_prec[im+1];
    		  	  
    		  	  dinmnext = dinm[im+1];
    		  	  dinmprev = dinm[11];
    		  	  
    		  	  
    		}else if (im==11){
    		  	  pvalt = eq_ta[im-1];
    		  	  pvalv = eq_vap[im-1];
    		  	  pvalp = eq_prec[im-1];
    		  	  
    		  	  nvalt = eq_ta[0];
    		  	  nvalv = eq_vap[0];
    		  	  nvalp = eq_prec[0];
    		  	  
    		  	  dinmnext = dinm[0];
    		  	  dinmprev = dinm[im-1];
    		  	  
    		}else{
    		  	  pvalt = eq_ta[im-1];
    		  	  pvalv = eq_vap[im-1];
    		  	  pvalp = eq_prec[im-1];
    		  	  
    		  	  nvalt = eq_ta[im+1];
    		  	  nvalv = eq_vap[im+1];
    		  	  nvalp = eq_prec[im+1];
    		  	  
    		  	  dinmnext = dinm[im+1];
    		  	  dinmprev = dinm[im-1];
    		  	  
    		}
              
            autil.updateDailyDriver(tad1, pvalt ,cvalt, nvalt,
                       dinmprev, dinmcurr, dinmnext);
  			autil.updateDailyDriver(vapd1,  pvalv ,cvalv, nvalv,
                    dinmprev, dinmcurr, dinmnext);
  			autil.updateDailyPrec(precd1, dinmcurr, cvalt, cvalp);
  		   	
  		   	for (int id =0; id<31; id++){
  		      	eq_ta_d[im][id] = tad1[id];
  		      	eq_vap_d[im][id] = vapd1[id];
  		      	precsplt(eq_ta_d[im][id], precd1[id], eq_snow_d[im][id], eq_rain_d[im][id]);
  		      
  		      	eq_rhoa_d[im][id] = getDensity(tad1[id]);
  		      	eq_svp_d[im][id] = getSatVP(tad1[id]);
  		       	eq_vpd_d[im][id] = getVPD(eq_svp_d[im][id], eq_vap_d[im][id]);
  		       
  		      	eq_dersvp_d[im][id] = getDerSVP(tad1[id], eq_svp_d[im][id]);
  		      	eq_abshd_d[im][id] = getAbsHumDeficit(eq_svp_d[im][id], eq_vap_d[im][id], tad1[id]);
  		   	}
  		   
    	}
    	
    	///for runs, using the recent 30-yrs averaged
    	for(int im =0; im<12;im++){
    		cvalt = ca_ta[im];
    		cvalv = ca_vap[im];
    		cvalp = ca_prec[im];
    		dinmcurr = dinm[im];
    		if(im==0){
    		  	  pvalt = ca_ta[11];
    		  	  pvalv = ca_vap[11];
    		  	  pvalp = ca_prec[11];
    		  	  
    		  	  nvalt = ca_ta[im+1];
    		  	  nvalv = ca_vap[im+1];
    		  	  nvalp = ca_prec[im+1];
    		  	  
    		  	  dinmnext = dinm[im+1];
    		  	  dinmprev = dinm[11];
    		  	  
    		  	  
    		}else if (im==11){
    		  	  pvalt = ca_ta[im-1];
    		  	  pvalv = ca_vap[im-1];
    		  	  pvalp = ca_prec[im-1];
    		  	  
    		  	  nvalt = ca_ta[0];
    		  	  nvalv = ca_vap[0];
    		  	  nvalp = ca_prec[0];
    		  	  
    		  	  dinmnext = dinm[0];
    		  	  dinmprev = dinm[im-1];
    		  	  
    		}else{
    		  	  pvalt = ca_ta[im-1];
    		  	  pvalv = ca_vap[im-1];
    		  	  pvalp = ca_prec[im-1];
    		  	  
    		  	  nvalt = ca_ta[im+1];
    		  	  nvalv = ca_vap[im+1];
    		  	  nvalp = ca_prec[im+1];
    		  	  
    		  	  dinmnext = dinm[im+1];
    		  	  dinmprev = dinm[im-1];
    		  	  
    		}
            autil.updateDailyDriver(tad1, pvalt ,cvalt, nvalt,
                       dinmprev, dinmcurr, dinmnext);
  			autil.updateDailyDriver(vapd1,  pvalv ,cvalv, nvalv,
                     dinmprev, dinmcurr, dinmnext);
  			autil.updateDailyPrec(precd1, dinmcurr, cvalt, cvalp);
  		    for (int id =0; id<31; id++){
  		      ca_ta_d[im][id] = tad1[id];
  		      ca_vap_d[im][id] = vapd1[id];
  		      precsplt(ca_ta_d[im][id], precd1[id], ca_snow_d[im][id], ca_rain_d[im][id]);
  		      
  		      ca_rhoa_d[im][id] = getDensity(tad1[id]);
  		      ca_svp_d[im][id] = getSatVP(tad1[id]);
  		      ca_vpd_d[im][id] = getVPD(ca_svp_d[im][id], ca_vap_d[im][id]*0.1);
  		      ca_dersvp_d[im][id] = getDerSVP(tad1[id], ca_svp_d[im][id]);
  		      ca_abshd_d[im][id] = getAbsHumDeficit(ca_svp_d[im][id], ca_vap_d[im][id]*0.1, tad1[id]);

  		   	}
  		   
  		   
    	} 
  
  //// for transient
    	for(int iy=0; iy<ed->gd->act_atm_drv_yr; iy++){
      		for(int im =0; im<12;im++){
    		 	cvalt = ta[iy][im];
    		 	cvalv = vap[iy][im];
    		 	cvalp = prec[iy][im];
    		 	dinmcurr = dinm[im];
    		  	if(im==0){
    		  	  	if(iy==0){
    		  	  		pvalt = ta[0][0];
    		  	  		pvalv = vap[0][0];
    		  	  		pvalp = prec[0][0];
    		  	  	}else{
    		  	  		pvalt = ta[iy-1][11];
    		  	  		pvalv = vap[iy-1][11];
    		  	  		pvalp = prec[iy-1][11];
    		  	  	}
    		  	  	nvalt = ta[iy][im+1];
    		  	  	nvalv = vap[iy][im+1];
    		  	  	nvalp = prec[iy][im+1];
    		  	  	dinmnext = dinm[im+1];
    		  	  	dinmprev = dinm[11];
    		  	  
    		  	  
    		  	}else if (im==11){
    		  	  	pvalt = ta[iy][im-1];
    		  	  	pvalv = vap[iy][im-1];
    		  	  	pvalp = prec[iy][im-1];
    		  	 	if(iy==ed->gd->act_atm_drv_yr-1){
    		  	  		nvalt = ta[iy][11];
    		  	  		nvalv = vap[iy][11];
    		  	  		nvalp = prec[iy][11];
    		  	  	}else{
    		  	  		nvalt = ta[iy+1][0];
    		  	  		nvalv = vap[iy+1][0];
    		  	  		nvalp = prec[iy+1][0];
    		  	  	}
    		  	  	dinmnext = dinm[0];
    		  	  	dinmprev = dinm[im-1];
    		  	  
    		  	}else{
    		  	  	pvalt = ta[iy][im-1];
    		  	  	pvalv = vap[iy][im-1];
    		  	  	pvalp = prec[iy][im-1];
    		  	  
    		  	  	nvalt = ta[iy][im+1];
    		  	  	nvalv = vap[iy][im+1];
    		  	  	nvalp = prec[iy][im+1];
    		  	  
    		  	  	dinmnext = dinm[im+1];
    		  	  	dinmprev = dinm[im-1];
    		  	  
    		  	}
                autil.updateDailyDriver(tad1, pvalt ,cvalt, nvalt,
                       dinmprev, dinmcurr, dinmnext);
  				autil.updateDailyDriver(vapd1,  pvalv ,cvalv, nvalv,
                     dinmprev, dinmcurr, dinmnext);
  				autil.updateDailyPrec(precd1, dinmcurr, cvalt, cvalp);
  		   		
  		   		for (int id =0; id<dinmcurr; id++){
  		      		ta_d[iy][im][id] = tad1[id];
  		      		vap_d[iy][im][id] = vapd1[id];
  		      		precsplt(ta_d[iy][im][id], precd1[id],snow_d[iy][im][id], rain_d[iy][im][id]);
  		      
  		      		rhoa_d[iy][im][id] = getDensity(tad1[id]);
  		      		svp_d[iy][im][id] = getSatVP(tad1[id]);
  		      		vpd_d[iy][im][id] = getVPD(svp_d[iy][im][id], vap_d[iy][im][id]   );
  		      		dersvp_d[iy][im][id] = getDerSVP(tad1[id], svp_d[iy][im][id]);
  		      		abshd_d[iy][im][id] = getAbsHumDeficit(svp_d[iy][im][id], vap_d[iy][im][id] , tad1[id]); 		      
  		   		} //id
    		}//im
  
    	}//iy
    
}; 

//Yuan: climate/co2 change option
void Atmosphere::beginOfMonth(const int & curyrcnt ,const int& currmind,const int& dinmcurr, const bool & normal, const bool & changeclm, const bool & changeco2){

	if(normal){  //using normalized weather data of first 30 yrs (modified in inc/timeconst.h)

  		if (changeco2) {
  			ed->m_atms.co2  = ed->rd->co2[curyrcnt%ed->rd->act_co2_drv_yr];   //Yuan: this reuse CO2 data sets
  		} else {
  	    	ed->m_atms.co2  = ed->initco2;
  		}

  		ed->m_atms.ta   = eq_ta[currmind];
  		ed->m_atms.clds = eq_cld[currmind];
    	ed->m_atmd.vp   = eq_vap[currmind];
    	ed->m_a2l.prec  = eq_prec[currmind];
    	ed->m_a2l.rnfl  = eq_rain[currmind];
    	ed->m_a2l.snfl  = eq_snow[currmind];
   		ed->m_a2l.girr  = eq_girr[currmind];
    	ed->m_a2l.nirr  = eq_nirr[currmind];
    	ed->m_a2l.par   = eq_par[currmind];

  	}else {

  		if (changeco2) {
  			if (curyrcnt<MAX_CO2_DRV_YR) {
  				ed->m_atms.co2  = ed->rd->co2[curyrcnt];
  			} else {
 				ed->m_atms.co2  = ed->rd->co2[MAX_CO2_DRV_YR-1];
 				//Yuan: this reuse the last CO2 data
  			}
  		} else {
  	    	ed->m_atms.co2  = ed->initco2;
  		}

  		int yrind;
  		if (changeclm) {
    	    yrind = curyrcnt%ed->gd->act_atm_drv_yr;    //Yuan: this will reuse the whole atm data set
  		} else {
    	    yrind = curyrcnt%(min(30, ed->gd->act_atm_drv_yr));    //Yuan: this will reuse the atm data of first 30 yrs
  		}

  		ed->m_atms.ta   = ta[yrind][currmind];
  		ed->m_atms.clds = cld[yrind][currmind];
    	ed->m_atmd.vp   = vap[yrind][currmind];
    	ed->m_a2l.prec  = prec[yrind][currmind];
    	ed->m_a2l.rnfl  = rain[yrind][currmind];
    	ed->m_a2l.snfl  = snow[yrind][currmind];
    	ed->m_a2l.girr  = girr[yrind][currmind];
    	ed->m_a2l.nirr  = nirr[yrind][currmind];
    	ed->m_a2l.par   = par[yrind][currmind];

  	}

};

void Atmosphere::updateDailyEnviron(const int &yrcnt, const int & mid, const int & dayid, const bool & normal, const bool & changeclm){

    if(normal){ //using normalized climatic driving
   
		ed->d_atms.co2 = ed->m_atms.co2;
		ed->d_atms.ta  = eq_ta_d[mid][dayid];
		ed->d_a2l.rnfl = eq_rain_d[mid][dayid];
		ed->d_a2l.snfl = eq_snow_d[mid][dayid];
		ed->d_a2l.par  = eq_par[mid];
		ed->d_a2l.nirr = eq_nirr[mid];
		ed->d_a2l.girr = eq_girr[mid];
		ed->d_atmd.vp  = eq_vap_d[mid][dayid] ;              //Pa
		ed->d_atmd.rhoa = eq_rhoa_d[mid][dayid];
		ed->d_atmd.svp  = eq_svp_d[mid][dayid];
		ed->d_atmd.vpd  = eq_vpd_d[mid][dayid];                
		ed->d_atmd.dersvp = eq_dersvp_d[mid][dayid];
		ed->d_atmd.abshd  = eq_abshd_d[mid][dayid];
    	
    }else {
    	
  		int yrind;
  		if (changeclm) {
    	    yrind = yrcnt%ed->gd->act_atm_drv_yr;    //Yuan: this will reuse the whole atm data set
  		} else {
    	    yrind = yrcnt%ed->gd->act_atm_drv_yr;    //Yuan: this will reuse the atm data of first 30 yrs
  		}

		ed->d_atms.co2 = ed->m_atms.co2;
		ed->d_atms.ta  = ta_d[yrind][mid][dayid];
		ed->d_a2l.rnfl = rain_d[yrind][mid][dayid];
		ed->d_a2l.snfl = snow_d[yrind][mid][dayid] ;
		ed->d_a2l.par  = par[yrind][mid];
		ed->d_a2l.nirr = nirr[yrind][mid];
		ed->d_a2l.girr = girr[yrind][mid];
		ed->d_atmd.vp  = vap_d[yrind][mid][dayid] ;
		ed->d_atmd.rhoa = rhoa_d[yrind][mid][dayid];
		ed->d_atmd.svp  = svp_d[yrind][mid][dayid];
		ed->d_atmd.vpd  = vpd_d[yrind][mid][dayid];
		ed->d_atmd.dersvp = dersvp_d[yrind][mid][dayid];
		ed->d_atmd.abshd  = abshd_d[yrind][mid][dayid];

    }
	
	if(ed->d_a2l.rnfl+ed->d_a2l.snfl >0){
	  	ed->d_atms.dsr =0;	
	}else{
	  	ed->d_atms.dsr++;	
	}
	
};


void Atmosphere::precsplt(const float & tair,const float & prec, float & snfl, float & rnfl){
  /* *************************************************************
  Willmott's assumptions on snow/rain split:
  ************************************************************** */
  	if ( tair >= 0.0 ) { // monthly use -1.0
    	rnfl = prec;
    	snfl = 0.0;
  	} else  {
    	rnfl = 0.0;
    	snfl = prec;
  	}

};
   
float Atmosphere::getDensity(const float & ta){
 	float rhoa ; // atmosphere density 
 	rhoa =1.292 - (0.00428 *ta);	
 	return rhoa;	
};

float Atmosphere::getSatVP(const float & tair){
 	float svp; // saturated vapor pressure (Pa)
 	//if(tair>0){
 	//see Zhuang et al., 2004
 	 svp = 0.61078 * exp(17.27 * tair/ (237.3 + tair) ) * 1000;	
 	//}
 	//else{
 	// svp = 61078. * exp(21.874*tair/(tair -7.66));	
 	//}
 	
 	
 	return svp;
};
 
float Atmosphere::getDerSVP( const float & tair){//Pa/degC
   float beta ;
   float deltat =0.2;
   float t1, t2;
   float svp1, svp2;
   t1 = tair +deltat;
   t2 = tair -deltat;
   svp1 = getSatVP(t1);
   svp2 = getSatVP(t2);
   
   beta = (svp1-svp2)/(t1-t2);
   return beta;	
};	
 
float Atmosphere::getDerSVP( const float & tair, const float & svp){//not used
   float beta ;
   beta = 4099. * svp /pow((tair +237.3),2.);
   return beta;	
};	
 
float Atmosphere::getAirDensity(float const & ta){
	// input air temperature, ta (degC)
	// output air density , rhoa (kg/m3)
	float rhoa;
	rhoa = 1.292 - (0.00428 * ta);
	return rhoa;
}; 
 
// Monthly solar radition at the top of atmosphere
float Atmosphere::getGIRR(const float &lat, const int& dinm ){

  	const float pi = 3.141592654;                // Greek "pi"
  	const float sp = 1368.0 * 3600.0 / 41860.0;  // solar constant

  	float lambda;
  	float sumd;
  	float sig;
  	float eta;
  	float sinbeta;
  	float sb;
  	float sotd;
  	int day;
  	int hour;
  	float gross;

  	lambda = lat * pi / 180.0;
  	gross = 0.0;
  	for ( day = 0; day < dinm; day++ ) {
    	++yrsumday;
    	sumd = 0;
    	sig = -23.4856*cos(2 * pi * (yrsumday + 10.0)/365.25);
    	sig *= pi / 180.0;

    	for ( hour = 0; hour < 24; hour++ ){
      		eta = (float) ((hour+1) - 12) * pi / 12.0;
      		sinbeta = sin(lambda)*sin(sig) + cos(lambda)*cos(sig)*cos(eta);
      		sotd = 1 - (0.016729 * cos(0.9856 * (yrsumday - 4.0) 
             * pi / 180.0));

      		sb = sp * sinbeta / pow((double)sotd,2.0);
      		if (sb >= 0.0) { sumd += sb; }
    	}

    	gross += sumd;
  	}

  	gross /= (float) dinm;
  	gross *= 0.484; // convert from cal/cm2day to W/m2
 
  	return gross;

};


float Atmosphere::getAbsHumDeficit(const float & svp, const float &vp, const float & ta){
	const float Mw = 18; // g/mol;
	const float R = 8.3143; // J/mol/k
	float dewpnt; //degC
	float ashd;
  	
  	float temp = (17.502 - log(vp/0.611));	
  	if(temp>0 || temp< 0){
  		dewpnt = (240.97 * log(vp/0.611))/temp;
  	}else{
  		dewpnt = ta;
  	}
  	
  	ashd = fabs((Mw/R) * ((svp * 1000./(273.2 + dewpnt)) - (vp *1000/(273.2 + ta))));
  	return ashd;
};

float Atmosphere::getVPD (const float & svp, const float vp){
	float vpd =svp -vp;
	if (vpd<0) {vpd =0;}
  	return vpd; // unit Pa	
};

float Atmosphere::getNIRR( const float& clds, const float& girr ){
	//W/m2
  	float nirr;

  	if ( clds >= 0.0 ) {
    	nirr = girr * (0.251 + (0.509*(1.0 - clds/100.0)));
  	} else { 
  		nirr = -9999.; 
  	}

  	return nirr;

};


float Atmosphere::getCLDS( const float & girr, const float& nirr ){

  	float clouds;

  	if ( nirr >= (0.76 * girr) ) { 
  		clouds = 0.0; 
  	}else {
    	clouds = 1.0 - (((nirr/girr) - 0.251)/0.509);
    	clouds *= 100.0;
  	}
  
  	if ( clouds > 100.0 ) { clouds = 100.0; }

  	return clouds;

};

float Atmosphere::getPAR( const float& clds, const float& nirr ){
	//W/m2
  	float par;

  	if ( clds >= 0.0 ) {
      	par = nirr * ((0.2 * clds / 100.0) + 0.45);
  	} else { 
  		par = -9999.; 
  	}

  	return par;
};

void Atmosphere::setEnvData(EnvData* edp){
	ed = edp;
};

