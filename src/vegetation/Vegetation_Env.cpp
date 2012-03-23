#include "Vegetation_Env.h"

Vegetation_Env::Vegetation_Env(){
	updateLAI5Vegc=false;
	
}

Vegetation_Env::~Vegetation_Env(){
	
}

void Vegetation_Env::initializeParameter(const int & drgtypep, const int &vegtypep){
	//set the parameters
	//int drgtype = drgtypep;
	int vegtype = vegtypep;
	
	envpar.gl_bl =chtlu->gl_bl[vegtype];
    envpar.gl_c =chtlu->gl_c[vegtype];
	envpar.matureage = chtlu->matureage[vegtype];

    envpar.albvisnir = chtlu->albvisnir[vegtype];
    envpar.er =chtlu->er[vegtype];
    envpar.ircoef =chtlu->ircoef[vegtype];
    envpar.iscoef =chtlu->iscoef[vegtype];
    
    envpar.vpd_close = chtlu->vpd_close[vegtype];
    envpar.vpd_open = chtlu->vpd_open[vegtype];
    envpar.glmax = chtlu->glmax[vegtype];
    envpar.all2prj =chtlu->all2prj[vegtype];
    envpar.ppfd50 = chtlu->ppfd50[vegtype];
    
	
};


void Vegetation_Env::initializeState(const int & drgtypep, const int &vegtypep){
	for (int i=0; i<12; i++){
		envlaiall[i]=chtlu->envlai[vegtypep][i];
	}
};

void Vegetation_Env::initializeState5restart(RestartData* resin){
	
    ed->prveetmx = resin->prveetmx; //resin->getPRVEETMX(ed->prveetmx, ed->cd->reschtid);
    ed->prvpetmx = resin->prvpetmx; //resin->getPRVPETMX(ed->prvpetmx, ed->cd->reschtid);
 
	double eetmxa[10];
	double petmxa[10];
	
	for(int i=0; i<10; i++){
		eetmxa[i]=resin->eetmxA[i]; //resin->getEETMXA(eetmxa, ed->cd->reschtid);
		if(eetmxa[i]>0){
			ed->eetmxque.push_back(eetmxa[i]);
		}

		petmxa[i]=resin->petmxA[i]; //resin->getPETMXA(petmxa, ed->cd->reschtid);
		if(petmxa[i]>0){
			ed->petmxque.push_back(petmxa[i]);
		}
	 	
	} 
}

void Vegetation_Env::updateEnvLai(const int & currmind, const double & lai){
  //specify the value for one month
 int ysf = fd->ysf;
  if(!updateLAI5Vegc){
  	if(ysf<10){
  	 	envlai =0.05;
  	}else{
    	envlai = envlaiall[currmind];
  	}
  }else{
  	envlai =lai;
  };
  ed->d_vegd.envlai =envlai;
}

void Vegetation_Env::beginOfMonth(const double & dayl){
	//calculate some variables which will not change in one month
	//so that there is no need to calculate every day
	//m_ppfd which is only related to LAI
	double er = envpar.er; // extinction coefficient
	double EPAR = 4.55 ; //an average energy for PAR photo(umol/J)
	double par =ed->m_a2l.par * 24/dayl;
	//double all2prj = envpar.all2prj;
	double downpar = par*(1 -  envpar.albvisnir) ;
	double ppfd50 = envpar.ppfd50 ;//mumol/m2s, ppfd for 0.5 stomatal closure
    //ed->m_vegd.parabsorb = downpar*(1-   exp(-er * envlai/all2prj)) ;//*(1.e6/(24.*3600.));//from MJ/m2day to J/m2s m_ppfd max 0.25
	
	ed->m_vegd.parabsorb = downpar*(1-   exp(-er * envlai)) ;// J/m2s m_ppfd 
	
	ed->m_vegd.ppfdabsorb = EPAR *ed->m_vegd.parabsorb; // umol/m2/s
	
	ed->m_vegd.m_ppfd=downpar*EPAR/(downpar*EPAR + ppfd50) ;//ed->m_vegd.ppfdabsorb/(ed->m_vegd.ppfdabsorb+ppfd50);
	
	ed->d_v2a.solrad =ed->m_a2l.nirr *envpar.albvisnir; // unit W/m2
	double downsw = (ed->m_a2l.nirr -ed->d_v2a.solrad ) ;
	ed->d_v2g.sw = getRadiationThrough(downsw, envlai);
	ed->d_vegd.rac = downsw - ed->d_v2g.sw;
	
}
 
//VEGETATION DAILY WATER BALANCE CALCULATION
void Vegetation_Env::updateDaily(   const double & dayl){
  	/* temporary for Nirr sensitivity test*/
  	double er = envpar.er; // extinction coefficient
	double EPAR = 4.55 ;   //an average energy for PAR photon (umol/J)
	double par =ed->d_a2l.par;
	
	double downpar = par*(1 -  envpar.albvisnir) ;
	double ppfd50 = envpar.ppfd50 ;//mumol/m2s, ppfd for 0.5 stomatal closure
    //ed->m_vegd.parabsorb = downpar*(1-   exp(-er * envlai/all2prj)) ;// *(1.e6/(24.*3600.));//from MJ/m2day to J/m2s m_ppfd max 0.25
	
	ed->d_vegd.parabsorb = downpar*(1-   exp(-er * envlai)) ;// J/m2s m_ppfd 
	
	ed->d_vegd.ppfdabsorb = EPAR *ed->d_vegd.parabsorb; // umol/m2/s
	
	ed->d_vegd.m_ppfd= downpar*EPAR/(downpar*EPAR + ppfd50) ;//ed->d_vegd.ppfdabsorb/(ed->d_vegd.ppfdabsorb+ppfd50);
	
	ed->d_v2a.solrad =ed->d_a2l.nirr *envpar.albvisnir; // unit W/m2
	double downsw = ed->d_a2l.nirr -ed->d_v2a.solrad;
	ed->d_v2g.sw = getRadiationThrough(downsw, envlai);
	ed->d_vegd.rac = downsw - ed->d_v2g.sw;
	
	
 //  double nirr = ed->d_a2l.nirr;
   	double vpd = ed->d_atmd.vpd;
   
   	double ta = ed->d_atms.ta;
   	double snfl=ed->d_a2l.snfl;
   	double rnfl=ed->d_a2l.rnfl;
   	double daylsec = dayl* 3600;// from hour to sec
	ed->d_a2v.snfl = snfl ;
	ed->d_a2v.rnfl=  rnfl;
	
	if(envlai >0){
		ed->d_vegd.rinter = getRainInterception(ed->d_a2v.rnfl);
		ed->d_vegd.sinter = getSnowInterception(ed->d_a2v.snfl, envlai);
		ed->d_v2g.rthfl = ed->d_a2v.rnfl- ed->d_vegd.rinter;
		ed->d_v2g.sthfl = ed->d_a2v.snfl -ed->d_vegd.sinter;
	
		//temperature and pressure correction factor for conductances
		double gcorr = 1.; //pow( (atmsd->ta +273.15)/293.15, 1.75); // * 101300/pa;
		ed->d_vegd.m_vpd=0.;
		double gl_st =0.;
		
		if(ed->d_vegd.btran>0){
	 		//gl_st = getLeafStomaCond(ta,ed->m_vegd.ppfdabsorb, vpd, envlai, ed->d_vegd.btran, 
			//				ed->d_vegd.m_ppfd, ed->d_vegd.m_vpd);
     		gl_st = getLeafStomaCond(ta,downpar*EPAR, vpd, envlai, ed->d_vegd.btran, 
					ed->d_vegd.m_ppfd, ed->d_vegd.m_vpd);
					
		}
		
		gl_st *= gcorr; 
		double gl_bl = envpar.gl_bl; //boundary layer conductance (projected area basis) m/s
		gl_bl *= gcorr;
		double gl_c = envpar.gl_c; // cuticular conductance m/s
		gl_c *=gcorr;
	
		double gl_t_wv = (gl_bl *gl_st)/(gl_bl+gl_st+gl_c);
		double gl_sh = gl_bl;
		double gl_e_wv = gl_bl;
		double gc_e_wv = gl_e_wv * envlai ;///envpar.all2prj;
		double gc_sh =gl_sh * envlai;// /envpar.all2prj;
		double gl_t_wv_pet = (gl_bl *envpar.glmax)/(gl_bl+envpar.glmax+gl_c);
		double gl_sh_pet = gl_bl;
		double gl_e_wv_pet = gl_bl;
		double gc_e_wv_pet = gl_e_wv_pet * envlai;// /envpar.all2prj;
		double gc_sh_pet =gl_sh_pet * envlai;// /envpar.all2prj;
	
		double sw =ed->d_vegd.rac ; // absorbed solar radiation
		double daytimesw = sw;// *24./dayl;
		double rainsw = sw;
		double rv, rh;
		double rv_pet, rh_pet;
		double vpdpa = vpd; //Pa
	
		if(ed->d_vegd.rinter>0){
		
			rv = 1./gc_e_wv;
			rh = 1./gc_sh;
			rv_pet = 1./gc_e_wv_pet;
			rh_pet = 1./gc_sh_pet;
		
			double et1= getPenMonET(ta,vpdpa, rainsw, rv, rh);
			double et1_pet= getPenMonET(ta,vpdpa, rainsw, rv_pet, rh_pet);
			double dayl1 = ed->d_vegd.rinter/et1;
			
			if(dayl1>daylsec){
		  		if(daylsec>0){
		  			ed->d_v2a.trans =0.;
		  			ed->d_v2a.evapo = et1 *daylsec;
		  			//v2gd.rdrip = vegdd.rinter-v2ad.evapo; // assume the rest will become drip
		  		} else{
		  			ed->d_v2a.trans=0.;
		  			ed->d_v2a.evapo=0.;
		  		}
			} else {
		  		ed->d_v2a.evapo = ed->d_vegd.rinter;
		  		daylsec -= dayl1;
		  		rv = 1.0/gl_t_wv;
		  		rh =1.0/gl_sh;
		  		double et2= getPenMonET(ta,vpdpa, rainsw, rv, rh);
		  		ed->d_v2a.trans = et2 * daylsec;
			}
		
			double dayl1_pet = ed->d_vegd.rinter/et1_pet;
			if(dayl1_pet>daylsec){
		  		if(daylsec>0){
		  			ed->d_v2a.trans_pet =0.;
		  			ed->d_v2a.evapo_pet = ed->d_v2a.evapo;
		  			//v2gd.rdrip = vegdd.rinter-v2ad.evapo; // assume the rest will become drip
		  		} else {
		  			ed->d_v2a.trans_pet=0.;
		  			ed->d_v2a.evapo_pet=0.;
		  		}
			} else {
		  		ed->d_v2a.evapo_pet = ed->d_vegd.rinter;
		  		daylsec -= dayl1_pet;
		  		rv_pet = 1.0/gl_t_wv_pet;
		  		rh_pet =1.0/gl_sh_pet;
		  		double et2_pet= getPenMonET(ta,vpdpa, rainsw, rv_pet, rh_pet);
		  		ed->d_v2a.trans_pet = et2_pet * daylsec;
			}
	
		} else { // no interception
		  
		  	ed->d_v2a.evapo = 0;
		  	rv = 1.0/gl_t_wv;
		  	rh =1.0/gl_sh;
		  	double et3= getPenMonET(ta, vpdpa, daytimesw, rv, rh);
		  	ed->d_v2a.trans = et3 * daylsec;
		  	ed->d_v2a.evapo_pet = 0;
		  	rv_pet = 1.0/gl_t_wv_pet;
		  	rh_pet =1.0/gl_sh_pet;
		  	double et3_pet= getPenMonET(ta, vpdpa, daytimesw, rv_pet, rh_pet);
		  	ed->d_v2a.trans_pet = et3_pet * daylsec;
		  
		} 
	
		ed->d_v2a.sublim = getCanopySubl(ed->d_vegd.rac,ed->d_vegd.sinter, envlai );
		ed->d_vegd.cc = gc_e_wv;
		ed->d_vegd.rc = 1./ed->d_vegd.cc;

	 	ed->d_v2g.rdrip = ed->d_vegd.rinter - ed->d_v2a.evapo;
	 	ed->d_v2g.sdrip = ed->d_vegd.sinter-ed->d_v2a.sublim;
	
	 	ed->d_vegs.snow += ed->d_vegd.sinter-ed->d_v2g.sdrip -ed->d_v2a.sublim;
	 	ed->d_vegs.rain += ed->d_vegd.rinter-ed->d_v2g.rdrip -ed->d_v2a.evapo;
		// ed->d_v2g.sw =  nirr-ed->d_v2a.solrad -ed->d_vegd.rac;
	 
	} else {   //envlai <=0, i.e., no vegetation?
		ed->d_vegd.cc =0.;
		ed->d_vegd.rc =0.;
		ed->d_vegd.rinter =0.;
		ed->d_vegd.sinter =0.;
		ed->d_v2a.sublim =0.;
		ed->d_v2a.trans =0.;
		ed->d_v2a.evapo =0.;
		
		ed->d_v2a.trans_pet =0.;
		ed->d_v2a.evapo_pet =0.;
		
		ed->d_v2a.sublim =0.;
	    ed->d_v2g.rdrip = 0;
	    ed->d_v2g.sdrip = 0;
	    ed->d_v2g.rthfl = rnfl;
	    ed->d_v2g.sthfl = snfl ;
	    ed->d_vegs.snow =0.;
	    ed->d_vegs.rain =0.;
	   //  ed->d_v2g.sw =  nirr;   ///?? nirr or girr
	    	
	}
	 //

	ed->d_v2a.sublim *= ed->y_vegd.vegfrac;
	ed->d_v2a.trans *= ed->y_vegd.vegfrac;
	ed->d_v2a.evapo *= ed->y_vegd.vegfrac;
 
    ed->d_v2g.rthfl *= ed->y_vegd.vegfrac;
    ed->d_v2g.sthfl *= ed->y_vegd.vegfrac ;
 	         
	
}


double Vegetation_Env::getPenMonET(const double & ta, const double& vpd, const double &irad,
				const double &rv, const double & rh){
		double et; // out , mmH2O/m2s
		double CP =1004.64 ; // specific heat capacity of dry air [J/kgK)
		double tk = ta+273.15;
		double pa = 101300;// pressure , Pa
		double rho = 1.292- (0.00428 * ta); // air density	kg/m3
		double EPS=0.6219; // ratio of mole weights
		double SBC= 5.67e-8; //Stefan-boltzmann constant W/m2K4
		/*resistance to raiative heat transfer through air*/
		double rr = rho * CP /(4.0 * SBC * tk* tk*tk);		
		/* resistance to convective heat tranfer: rh*/
		/*resistance to latent heat transfer rv*/
		/*combined resistance to convectie and radiative heat transfer,
		 * parallel resistances:rhr= (rh*rr)/(rh+rr)*/
		 double rhr = (rh*rr)/(rh+rr);
		/*latent heat of vaporization as a function of ta*/
		double lhvap = 2.5023e6 -2430.54 *ta;
		double dt =0.2;
		double t1 = ta+dt;
		double t2 =ta-dt;
		/*saturated vapor pressure at t1, t2*/
		double pvs1 = 610.7 *exp(17.38 *t1/(239.+t1));
		double pvs2 = 610.7 *exp(17.38 *t2/(239.+t2));
		/*slope of pvs vs. T curve at T*/
		double slope = (pvs1-pvs2)/(t1-t2);	
		/*evapotranspiration*/
		et = (slope*irad+ rho*CP *vpd/rhr)/((pa * CP *rv)/(lhvap*EPS *rhr)+slope);
		return et/lhvap;		
}


double Vegetation_Env::getRadiationThrough(const double & rac, const double & lai){
		double radthr;
          //if(vegtype >0){
		  //radthr = rac * exp(-envpar.er * lai/envpar.all2prj);
		  radthr = rac * exp(-envpar.er * lai);
          //}else{
          //	radthr = rac;
          //}
		  
		return radthr;
	}


double Vegetation_Env::getCanopySubl(const double & rac, const double & sinter, const double & lai ){
    double sub;
    double psub; //potential sub
    double snow_int =envpar.iscoef;
    double lamdaw = 2.501e6; // latent heat of vaporization J/kg
    double lf = 3.337e5 ;// latent heat of fusion J/kg	
    //rac in unit W/m2
    // change the unit from J/kg to MJ/mm
    double phasechange = (lamdaw+lf)/10e6 ;
    double sub1 = (rac*86400)/phasechange; 
    //double sub2 = lai/envpar.all2prj * snow_int;
    double sub2 = lai * snow_int;
    
    if(sub1 <sub2){
      psub = sub1;	
    }else{
      psub =sub2;	
    }
    if(sinter<=psub){
      sub =sinter;	
    }else{
      sub = psub;
    }
    return sub;
}
double Vegetation_Env::getLeafStomaCond(const double & ta, const double &  ppfdabsorb,
		 const double & vpdin, const double & lai, const double& btran,
		  double & m_ppfd, double & m_vpd ){
	double gl; // leaf conductance m/s, per unit LAI
	//double m_ppfd; // ppfd multiplier
	//double m_vpd; // vpd multiplier
	double m_psi; // soil water matric potential effect
	double m_co2;
	double m_tmin;
	
	double m_tot; // total effect of different factos
	/* the following parameters are from biome-bgc,
	 * for evergreen boreal forest*/
	 
	 
	double vpd_open = envpar.vpd_open ; //Pa , start of conductance reduction
	double vpd_close =envpar.vpd_close; //Pa , complete conductance reduction
	double glmax = envpar.glmax; //m/s, maximum stomata conductance
	//double ppfd50 = 75.0 ;//mumol/m2s, ppfd for 0.5 stomatal closure
	
	
	
	
	m_ppfd= ppfdabsorb/(ppfdabsorb+envpar.ppfd50);
	
	double vpd = vpdin; //
	if(vpd <vpd_open)
		m_vpd=1.0;
	else if(vpd>vpd_close)
		m_vpd =0.;
	else
		m_vpd =(vpd_close-vpd)/(vpd_close-vpd_open);
		
	 m_psi = btran;
	
	 m_co2=1;
	
	double tmin = ta-5;  
	// here ta is average air temperature (degC)  ;
	// 5 is derived from mean air temperature and minimum air temeperature difference from station data of Fairbanks
	if(tmin>0)
		m_tmin=1;
	else if(tmin<-8)
		m_tmin=0.;
	else
		m_tmin = 1.0 +(0.125*tmin);
	
	m_tot = m_ppfd * m_vpd * m_co2* m_tmin*m_psi;	
	
	
	gl =  m_tot * glmax;
	
	return gl;
}


double Vegetation_Env::getRainInterception(const double & rain){// assume calculated at daily timestep
   // input: rain mm/day
   double rinter;
   //double IRmax =0.26 ; // this is parameter for rain interception by canopy
            
   double raincm = rain/10.; // convert to cm
   double max_int = raincm - ((raincm*0.77-0.05)+0.02 * raincm);
  // if(vegtype >0){
   max_int *= 10 ; // convert back to mm;
   if(rain <= max_int){ // all intercepted
   	 rinter = rain;
   }else{ //partly intercepted
   	 rinter= max_int;
   }              
   //}else{
   //	 rinter =0;
  // }
   return rinter; 
  	
}

double Vegetation_Env::getSnowInterception(const double & snow, const double & lai){
   double sinter;
   double psinter; // potential snow interception
   double ISmax = envpar.iscoef ; // this is parameter for snow interception by canopy
                  // it should be vegetation specific [mm /LAI /day ]
                  
              //if(vegtype >0){
              psinter = ISmax * lai;///envpar.all2prj;
              //psinter = ISmax * lai/envpar.all2prj;
              
              if(psinter >= snow){
              	sinter = snow;
              }else{
              	sinter = psinter;
              }
             // }else{ //tussuck tundra, no interception
              	  sinter =0;
             // }
              return sinter; 
  	
}


void Vegetation_Env::setCohortLookup(CohortLookup * chtlup){
   chtlu = chtlup;	
}

void Vegetation_Env::setEnvData(EnvData* edatap){
	ed = edatap;	
}
void Vegetation_Env::setFirData(FirData* fdp){
  	 fd =fdp;
  };
