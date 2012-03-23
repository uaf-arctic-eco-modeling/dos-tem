#include "EnvData.h"

EnvData::EnvData(){
//	initco2 = 280;//or 296.311 at year 1900, (mike use 296.311)
//	initco2 = 296.311; //Yuan: modified in init() below
	d_atms.dsr = 0;
};

EnvData::~EnvData(){
	
};

void EnvData::init(){
	initco2 = rd->co2[0]; //Yuan: take the first in co2.nc
  	permafrost =-999;
  	yrfrozensoil = -999; //Yuan:

	for(int il =0; il<MAX_SOI_LAY; il++){
		d_soid.tem[il]=-999.;
		d_soid.allvwc[il]=-999.;
		d_soid.alllwc[il]=-999.;
		d_soid.alliwc[il]=-999.;
		d_soid.allsws[il]=-999.;
		d_soid.allaws[il]=-999.;

		d_soid.tcond[il]=0.;
		d_soid.hcond[il]=0.;
	}

};

void EnvData::beginOfDay(){
	//reset diagnostic
	for (int i=0; i<MAX_NUM_FNT ; i++){
	    d_soid.frzfnt[i] = -999.;
	    d_soid.thwfnt[i] = -999.;	
	}
	 // need to set some diagnostic variables to zero
    d_snwd.melt =0.;
    d_ald = -999.;   //Yuan:
};

void EnvData::beginOfMonth(){
	//for atmosphere, prepare the driving
    // atmosphere part in atmosphere::
	//for veg, soil and snow reset the monthly variables
	m_l2a.eet = 0;
	m_l2a.pet=0.; 

	//based on the thickness of layer, determine the fraction of fine root in it
	veg_beginOfMonth();
	soi_beginOfMonth();
	snw_beginOfMonth();
	
};

void EnvData::beginOfYear(){

	y_ald =-999.;     //Yuan: m_ald is monthly max. depth of deep frozen horizon's top, so reset it in beginOfMonth()
	// y_soid.permafrost = 1;   // Yuan: re-initialing it if m_soid.permafrost  = 0 in endofMonth()
	
  	y_l2a.eet =0.;
  	y_l2a.pet =0.;
 
   	y_atms.ta=0.;
   	y_atms.co2=0;
   
   	y_soid.mossthick =0.;
   	y_soid.shlwthick =0.;
   	y_soid.deepthick =0.;
   	y_soid.minethick =0.;
   
    y_soid.mossnum =0.;
   	y_soid.shlwnum =0.;
   	y_soid.deepnum =0.;
   
   	y_soid.watertab =0.;
   
   	y_soi2l.qover =0.;
   	y_soi2l.qdrain=0.;
   	y_soi2a.evap =0.;
   	
   	y_sois.icesum = 0.;
   	y_sois.liqsum = 0.;
   	y_sois.tsave = 0.;
   	
   	y_snws.swe = 0.0;    //Yuan: yearly-averaged snow water equavlent
   	y_snws.thick = 0.0;  //Yuan: yearly-averaged snowpack thickness

   	for (int il=0; il<MAX_SOI_LAY; il++){
   		y_sois.ts[il] = 0.;
   		y_sois.liq[il]= 0.;
   		y_sois.ice[il]= 0.;
   		y_sois.por[il]= 0.;
   		y_sois.dz[il]=0.;
   		y_sois.z[il]=0.;

   		y_soid.tem[il] = 0.;
		y_soid.allvwc[il] = 0.;
		y_soid.alllwc[il] = 0.;
		y_soid.alliwc[il] = 0.;
		y_soid.allsws[il] = 0.;
		y_soid.allaws[il] = 0.;

		//Yuan: actual thermal/hydraulic conductivity
		y_soid.tcond[il] = 0.0;
		y_soid.hcond[il] = 0.0;
	}

 	y_soid.growstart=-999;
 	y_soid.growend=-999;
 	y_soid.snowfree1st=-999;
 
	y_soid.tmineral10cm =0;
	y_soid.trock34m =0;
	y_soid.unfrzcolumn =0;
	
	y_snw2a.sublim =0.;
	
	y_a2l.girr = 0;
	y_a2l.nirr = 0;
	y_a2l.prec = 0;
	y_a2l.par = 0;
	y_a2l.rnfl = 0;
	y_a2l.snfl = 0;
	
	y_v2a.evapo  = 0.;
	y_v2a.sublim = 0.;
	y_v2a.trans  = 0.;
      
};

void EnvData::endOfDay(const int & dinm, const int & doy){
	atm_endOfDay(dinm);
	veg_endOfDay(dinm);
	soi_endOfDay(dinm, doy);
	snw_endOfDay(dinm);
	
/*	//update the  ald
	if(doy>150){          //Yuan:  ???
	for (int il =0; il<MAX_NUM_FNT; il++){
	  if(d_soid.thwfnt[il]>0){
	  	 if(ald<d_soid.thwfnt[il]){
	  	 	ald = d_soid.thwfnt[il];
	  	 }
	  
	  }else{
	  	break;
	  }	
	}
	}
*/
	//Yuan: ald is modified in soil_endOfDay - d_soid.thwfnt sometime no data, which causes issue
 	//      d_soid.thwfnt NOT stable from year to year as well
	
};

void EnvData::endOfMonth(const int & currmind, const bool &assign){
    if(currmind==0){
      eetmx = m_l2a.eet;
      petmx = m_l2a.pet;	
    }else{
      if ( m_l2a.eet > eetmx ) 
    	{ 
     	 eetmx = m_l2a.eet; 
   		}
    
      if ( m_l2a.pet > petmx ) 
    	{ 
     	 petmx = m_l2a.pet; 
   		}
     	
    }
    
    y_l2a.eet += m_l2a.eet;
    y_l2a.pet += m_l2a.pet;
    
    y_atms.ta += m_atms.ta/12.;
    y_atms.co2 += m_atms.co2/12.;
    
    y_soid.mossthick += m_soid.mossthick/12.;
    y_soid.shlwthick += m_soid.shlwthick/12.;
    y_soid.deepthick += m_soid.deepthick/12.;
    y_soid.minethick += m_soid.minethick/12.;
    
    y_soid.mossnum += m_soid.mossnum/12;
    y_soid.shlwnum += m_soid.shlwnum/12;
    y_soid.deepnum += m_soid.deepnum/12;
    
    y_soid.watertab += m_soid.watertab/12.;
    y_soid.tmineral10cm += m_soid.tmineral10cm/12.;
    y_soid.trock34m += m_soid.trock34m/12.;
    y_soid.unfrzcolumn+= m_soid.unfrzcolumn/12.;

    //Yuan: modified in the following permafrost determination
    //if(y_soid.permafrost==1){
    //  if(m_soid.permafrost==0){
    //  	 y_soid.permafrost=0;
    //  }
    //}
    if (m_soid.permafrost==0) {    //note: m_soid.permafrost is 1 or 0
    	yrfrozensoil = 0.0;     // if in any month permafrost degradation occurs, re-build the permafrost
    	permafrost = 0;
    	y_ald = -999.;
    } else {
    	yrfrozensoil+=m_soid.permafrost/12.;   // accumulative temporary permafrost time (unit: years) since degradation
        if (yrfrozensoil>=2.0) {   // if soil has frozen horizon with last 2 years (24 months)
        	permafrost = 1;
        	if (y_ald < m_ald) y_ald=m_ald;    // note: m_ald updated every month, which is the max. of d_ald; then y_ald is the max. of m_ald in a year (y_ald must be initialized in the begining of the year)
        } else {
        	permafrost = 0;
        	y_ald = -999;                      // if NOT permafrost, then y_ald is not available; SO, d_ald and m_ald is for both permafrost and seasonally-frozen soil
        }
    }

    y_soi2l.qover+= m_soi2l.qover;
    y_soi2l.qdrain+= m_soi2l.qdrain;
    y_soi2a.evap+= m_soi2a.evap ;
    
    y_sois.tsave+=m_sois.tsave/12.0;
    y_sois.icesum+=m_sois.icesum/12.0;
    y_sois.liqsum+=m_sois.liqsum/12.0;

	//Yuan:
	y_snws.thick += m_snws.thick/12.0;
	y_snws.swe   += m_snws.swe/12.0;

   	for (int il=0; il<MAX_SOI_LAY; il++){
   		y_sois.type[il]= m_sois.type[il];
   		y_sois.ts[il] += m_sois.ts[il]/12.0;
   		y_sois.liq[il]+= m_sois.liq[il]/12.0;
   		y_sois.ice[il]+= m_sois.ice[il]/12.0;
   		y_sois.por[il]+= m_sois.por[il]/12.0;
   		y_sois.z[il]+= m_sois.z[il]/12.0;
   		y_sois.dz[il]+= m_sois.dz[il]/12.0;
   		y_sois.type[il]= m_sois.type[il];
   	}

	for(int il =0; il<MAX_SOI_LAY; il++){
		y_soid.tem[il] += m_soid.tem[il]/12.0;
		y_soid.allvwc[il] += m_soid.allvwc[il]/12.0;
		y_soid.alllwc[il] += m_soid.alllwc[il]/12.0;
		y_soid.alliwc[il] += m_soid.alliwc[il]/12.0;
		y_soid.allsws[il] += m_soid.allsws[il]/12.0;
		y_soid.allaws[il] += m_soid.allaws[il]/12.0;

		//Yuan:
		y_soid.tcond[il] += m_soid.tcond[il]/12.0;
		y_soid.hcond[il] += m_soid.hcond[il]/12.0;

	}

	y_v2a.evapo  += m_v2a.evapo;
	y_v2a.sublim += m_v2a.sublim;
	y_v2a.trans  += m_v2a.trans;
	
	y_snw2a.sublim+=m_snw2a.sublim;
    
    y_a2l.par+=m_a2l.par;
    y_a2l.girr+=m_a2l.girr;
    y_a2l.nirr+=m_a2l.nirr;
    y_a2l.rnfl+=m_a2l.rnfl;
    y_a2l.snfl+=m_a2l.snfl;
    
    if(assign){  //for assigning soil climate, so that there is no need to calculate them all the timesteps
    	for (int il =0 ;il<MAX_SOI_LAY ; il++){
    	   	eq_ts[currmind][il]=m_sois.ts[il];
    	   	eq_liq[currmind][il]=m_sois.liq[il];
    	   	eq_ice[currmind][il]=m_sois.ice[il];
    	   	eq_vwc[currmind][il]=m_soid.allvwc[il];
    	   	eq_sws[currmind][il]=m_soid.allsws[il];
    	   	eq_aws[currmind][il]=m_soid.allaws[il];
    	   	
    	}
    	eq_ta[currmind] = m_atms.ta;
    	eq_co2[currmind] = m_atms.co2;
    	eq_par[currmind] = m_a2l.par;
    	eq_eet[currmind] = m_l2a.eet;
    	eq_pet[currmind] = m_l2a.pet;
    	eq_grow[currmind] = m_soid.growpct;
    }
};


void EnvData::endOfYear(const bool &assign){
	//atmosphere, eet, pet, used in veg_bgc
	
	/*if(eetmx >0){
	  prveetmx =eetmx;	
	}
	
	if(petmx >0){
	  prvpetmx =petmx;	
	}*/
	/*if(prveetmx <eetmx){
	  prveetmx = eetmx;	
	}
	if(prvpetmx <petmx){
	  prvpetmx = petmx;	
	}*/
	
	//at end of year put the eetmx and petmx into deque, and update the prveetmx and prvpetmx,
	// which is the mean of the eetmx/petmx in the deque
	//it is assumed that the maximum number of year used is 10
	
	eetmxque.push_back(eetmx);
	petmxque.push_back(petmx);
	if(eetmxque.size()>10){
	  eetmxque.pop_front();	
	}
	if(petmxque.size()>10){
	  petmxque.pop_front();	
	}
	
	int numrec = eetmxque.size();
	int valideet =0;
	int validpet =0;
	
	double sumeet=0;
	double sumpet=0;
	for(int i=	0; i<numrec; i++){
	  	if(eetmxque[i]>0){
	  		valideet++;
	  		sumeet+=eetmxque[i];
	  	}
	  	if(petmxque[i]>0){
	  		validpet++;
	  		sumpet+=petmxque[i];
	  	}
	}
	if(valideet>0){
	  prveetmx = sumeet/valideet;	
	}
	if(validpet>0){
	  prvpetmx = sumpet/validpet;	
	} 	
	  		
	if(assign){
	  eq_y_eet = y_l2a.eet;
	  eq_y_pet = y_l2a.pet;
	  eq_y_co2 = y_atms.co2;
	  eq_prveetmx = prveetmx;	
	  eq_prvpetmx = prvpetmx;	
		
	}

};






/////////////////private functions ////////////////

void EnvData::veg_beginOfMonth(){
	
	m_vegd.sinter =0.;
	m_vegd.rinter =0.;
	m_vegd.btran =0.;
	m_vegd.rac =0.;

	m_vegs.rain =0.;
	m_vegs.snow =0.;
	

	m_v2g.sw = 0.;
	m_v2g.rdrip =0.;
	m_v2g.sdrip =0.;
	m_v2g.rthfl =0.;
	m_v2g.sthfl =0.;
	m_v2a.evapo=0.;
	m_v2a.trans=0.;
	m_v2a.sublim=0.;
	
};

void EnvData::soi_beginOfMonth(){

	for(int il =0; il<MAX_SOI_LAY; il++){
		m_sois.ts[il] = 0;
		m_sois.liq[il]=0.;
		m_sois.ice[il] =0.;
	}
	
	m_sois.liqsum =0.;
	m_sois.icesum =0.;
	m_sois.tsave =0.;
	m_soid.growpct=0.;
	m_soid.degday10=0.;
	m_soid.watertab=0.;
	m_soid.tmineral10cm =0;
	m_soid.trock34m =0;
	m_soid.unfrzcolumn =0;
	m_soid.permafrost = 1;
	for(int il =0; il<MAX_SOI_LAY; il++){
		m_soid.tem[il] = 0;
		m_soid.allvwc[il]=0.;
		m_soid.alllwc[il]=0.;
		m_soid.alliwc[il]=0.;
		m_soid.allsws[il]=0.;
		m_soid.allaws[il]=0.;

		//Yuan:
		m_soid.tcond[il]=0.;
		m_soid.hcond[il]=0.;

	}
    m_ald = 0.;  //Yuan: monthly ALD initialization

	m_soi2l.qover =0.;
	m_soi2l.qdrain =0.;	
	m_soi2a.evap =0.;
	//m_soi2v.nuptake =0.;
	
};

void EnvData::snw_beginOfMonth(){
	m_snw2a.sublim=0.;

	//Yuan:
	//Yuan:
	m_snws.thick = 0.;
	m_snws.swe   = 0.;

};


/// end of day, accumulate daily to monthly
// accumulate fluxes, average state and diagnostics
void EnvData::veg_endOfDay(const int & dinm){

	m_vegs.rain +=d_vegs.rain/dinm;
	m_vegs.snow +=d_vegs.snow/dinm;
		
	m_vegd.sinter += d_vegd.sinter/dinm;
	m_vegd.rinter += d_vegd.rinter/dinm;
	m_vegd.btran +=d_vegd.btran/dinm;
	m_vegd.rac += d_vegd.rac/dinm;
	
	
	m_v2g.sw += d_v2g.sw;
	m_v2g.rdrip += d_v2g.rdrip;
	m_v2g.sdrip += d_v2g.sdrip;
	m_v2g.rthfl += d_v2g.rthfl;
	m_v2g.sthfl += d_v2g.sthfl;
	
	m_v2a.evapo +=d_v2a.evapo;
	m_v2a.sublim +=d_v2a.sublim;
	m_v2a.trans +=d_v2a.trans;
	
};

void EnvData::atm_endOfDay(const int & dinm){
//prepare some variables that are needed by veg, but not available in Atmosphere.cpp 
//e.g. eet
  m_l2a.eet += (d_v2a.evapo + d_v2a.sublim + d_v2a.trans +
   				d_snw2a.sublim + d_soi2a.evap);

  m_l2a.pet += (d_v2a.evapo_pet + d_v2a.sublim + d_v2a.trans_pet +
   				d_snw2a.sublim + d_soi2a.evap);	  
};

void EnvData::soi_endOfDay(const int & dinm, const int & doy){

	for(int il =0; il<MAX_SOI_LAY; il++){
		m_sois.ts[il] += d_sois.ts[il]/dinm;
		m_sois.liq[il] += d_sois.liq[il]/dinm;
		m_sois.ice[il] += d_sois.ice[il]/dinm;
		
	}
	
	int numsoi = m_soid.actual_num_soil;
//	for(int il =0; il<MAX_SOI_LAY; il++){   //Yuan: a bug ?	
	for(int il =0; il<numsoi; il++){
		m_sois.liqsum += d_sois.liq[il]/dinm;
		m_sois.icesum += d_sois.ice[il]/dinm;
		m_sois.tsave+= d_sois.ts[il]/numsoi/dinm;	
	}

	m_soid.growpct +=d_soid.growpct/dinm;
	if(y_soid.growstart<0){
	    if(d_soid.growpct >0){
	      y_soid.growstart = doy;	
	    }	
		
	}else if (y_soid.growend<0){
		if(d_soid.growpct<=0){
		  y_soid.growend = doy;	
		}
		
	}
	m_soid.degday10 +=d_soid.degday10;
	
	m_soid.watertab += d_soid.watertab/dinm;
	
	for(int il=0; il<MAX_SOI_LAY; il++){
	   	m_soid.tem[il] += d_soid.tem[il]/dinm;
	   	m_soid.allvwc[il] += d_soid.allvwc[il]/dinm;
	   	m_soid.alllwc[il] += d_soid.alllwc[il]/dinm;
	   	m_soid.alliwc[il] += d_soid.alliwc[il]/dinm;
	   	m_soid.allsws[il] += d_soid.allsws[il]/dinm;
	   	m_soid.allaws[il] += d_soid.allaws[il]/dinm;

		//Yuan:
		m_soid.tcond[il] += d_soid.tcond[il]/dinm;
		m_soid.hcond[il] += d_soid.hcond[il]/dinm;

	}
	
    m_soi2l.qover += d_soi2l.qover ; //only for output
	m_soi2l.qdrain += d_soi2l.qdrain ; //only for output
	
	m_soi2a.evap += d_soi2a.evap;
  
    m_soid.tmineral10cm += d_soid.tmineral10cm/dinm;
    m_soid.trock34m += d_soid.trock34m/dinm;
    m_soid.unfrzcolumn += d_soid.unfrzcolumn/dinm;

	for (int il =0; il<MAX_NUM_FNT; il++){
	  if(d_soid.thwfnt[il]>0){
	  	 if(d_ald<d_soid.thwfnt[il]){
	  	 	d_ald = d_soid.thwfnt[il];
	  	 }

	  }else{
		  break;
	  }
	}

	if (m_ald<d_ald) m_ald = d_ald;   //m_ald is the max. of d_ald in a month

 	//Yuan: d_soid.permafrost re-do here (that one in Soil_Env.cpp not used)
 	if (d_ald >= m_sois.z[numsoi-1]+m_sois.dz[numsoi-1]) {
 		d_soid.permafrost = 0;
 	} else {
 		d_soid.permafrost = 1;
 	}

    if(m_soid.permafrost==1){
    	if(d_soid.permafrost==0){
    		m_soid.permafrost =0;
    	}
    }


};

void EnvData::snw_endOfDay(const int & dinm){
	m_snw2a.sublim += d_snw2a.sublim;

	//Yuan:
	m_snws.thick += d_snws.thick/dinm;
	m_snws.swe   += d_snws.swe/dinm;
};

   // for java interface
void EnvData::d1tod2(){
	for (int i=0; i<12; i++) {
		for (int j=0; j<MAX_SOI_LAY; j++) {
           	eq_ts[i][j]=eq_ts1d[i*MAX_SOI_LAY+j];
    		eq_liq[i][j]=eq_liq1d[i*MAX_SOI_LAY+j];
    		eq_vwc[i][j]=eq_vwc1d[i*MAX_SOI_LAY+j];
    		eq_sws[i][j]=eq_sws1d[i*MAX_SOI_LAY+j];
    		eq_ice[i][j]=eq_ice1d[i*MAX_SOI_LAY+j];
		}
	}
};

void EnvData::d2tod1(){
	for (int i=0; i<12; i++) {
		for (int j=0; j<MAX_SOI_LAY; j++) {
           	eq_ts1d[i*MAX_SOI_LAY+j] = eq_ts[i][j];
    		eq_liq1d[i*MAX_SOI_LAY+j]= eq_liq[i][j];
    		eq_vwc1d[i*MAX_SOI_LAY+j]= eq_vwc[i][j];
    		eq_sws1d[i*MAX_SOI_LAY+j]= eq_sws[i][j];
    		eq_ice1d[i*MAX_SOI_LAY+j]= eq_ice[i][j];
		}
	}
	
};





