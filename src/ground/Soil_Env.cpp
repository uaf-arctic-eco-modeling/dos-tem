#include "Soil_Env.h"

Soil_Env::Soil_Env(){
 	    
};

Soil_Env::~Soil_Env(){
	
};


void Soil_Env::updateDailySurfFlux( Layer* frontl, const double & tsurf, const double & dayl){
	double albvis = frontl->getAlbedoVis();
	double albnir = frontl->getAlbedoNir();
	
	double insw =  ed->d_v2g.sw * ed->y_vegd.vegfrac + (1-ed->y_vegd.vegfrac) * ed->d_a2l.nirr;
 
	ed->d_soi2a.solrad =insw *0.5 * albvis + insw *0.5*albnir;
			
	double rad = insw-ed->d_soi2a.solrad;
	double availliq =0;
	
	
	//use top 10 cm for evaporation
	 
	double totthick =0.03; //m
	double dzsum =0; 
	double liq =0;
	Layer* currl = frontl;
	while(currl!=NULL){
	 if(dzsum <totthick){
	 	if(dzsum + currl->dz <totthick){
	 		dzsum +=currl->dz;
	 		liq += currl->liq-currl->minliq;
	 		
	 	}else{
	 		liq += (currl->liq-currl->minliq) * (totthick-dzsum)/totthick;
	 		dzsum = totthick;
	 		
	 	}
	 	
	 }else {
	 	break;	
	 }
	
	 currl= currl->nextl;	
	}
	if(liq<0) liq =0;
//	double dz = frontl->dz;

    availliq = liq;// - 0.05*dz * 1000; DEC172007
	double evap =0.;
	if(availliq>0 && frontl->frozen==-1){
		evap = getEvaporation(tsurf, dayl, rad);
		ed->d_soi2a.evap = min(availliq,evap);
	}else{
	    ed->d_soi2a.evap = 0;
	}

}


double Soil_Env::getPenMonET(const double & ta, const double& vpd, const double &irad,
				const double &rv, const double & rh){
		double et; // out , mmH2O/m2s= kgH2o/m2s
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


double Soil_Env::getEvaporation(const double & tsurf, const double & dayl, const double &rad){
		//tsurf, soil surface temperature degC
	//dayl , dayl length  , hour
	//rad, radiation pass through vegetation, MJ/m2day
	double evap=0.;
	double tair = ed->d_atms.ta;
	//double rhoa = ed->d_atmd.rhoa;
	double vpdpa = ed->d_atmd.vpd;
	//double dsr = ed->d_atms.dsr;
	double daylsec =   dayl*3600;
	double daytimerad = rad  *86400/daylsec; //w/m2
	/* correct conductances for temperature and pressure based on Jones (1992)
	with standard conditions assumed to be 20 deg C, 101300 Pa */
	double rcorr = 1.0/(pow((tair+273.15)/293.15, 1.75) );
	
	double rbl = 107 * rcorr;
	
	double pmet = getPenMonET( tair, vpdpa, daytimerad,rbl, rbl);
	double dsr = ed->d_atms.dsr;
	double ratiomin =envpar.evapmin   ;// 0.15;
 
	evap = pmet *  daylsec;
	
	
	if(ed->d_v2g.rdrip + ed->d_v2g.rthfl+ ed->d_snwd.melt >= evap){
        evap *=0.6;
	}else{
		/* calculate the realized proportion of potential evaporation
		as a function of the days since rain */
		//double ratio =0.3/pow(dsr, 2.0);
		double ratio =0.3/pow(dsr, 2.0) ;
		//if(ratio<0.2) ratio =0.2;//good for dftc and dftb
		//first determine the minimum ratio for dftb, since it is burned site
		//the effect of transpiration is smaller than soil surface evaporation
		
		if(ratio<ratiomin) ratio  = ratiomin;
		
	    evap *=ratio;	
	}

	return evap;
}



void Soil_Env::initializeParameter(const int &drgtypep,const int &vegtypep){
	//set the parameters
	int vegtype = vegtypep;
	int drgtype = drgtypep;

	envpar.rootmass = chtlu->rootmass[vegtype];
	envpar.rootbeta = chtlu->rootbeta[vegtype];

    envpar.rootdp4infil = chtlu->rootdp4infil[vegtype];
    envpar.evapmin = chtlu->evapmin[vegtype];
    envpar.richardl = chtlu->richardl[vegtype];
    envpar.rootdp4gpp = chtlu->rootdp4gpp[vegtype];
    envpar.psimax = chtlu->psimax[vegtype];
    envpar.Ds = chtlu->Ds[drgtype];
    envpar.Ws = chtlu->Ws[drgtype];
    envpar.Dsmax = chtlu->Dsmax[drgtype];
    envpar.b_infilt = chtlu->b_infilt[drgtype];
    envpar.drainmax = chtlu->drainmax[drgtype];
    envpar.wfact = chtlu->wfact[drgtype];
    
//    for(int i =0; i<10; i++){
//    	envpar.frprod_frac[i]= chtlu->frprod_frac[vegtype][i];
//    }
//Yuan: above may have some problem, so modified below: acculmate first, then interpolate to
//      avoid suddent change of soil root distribution when cross layer boundary
    envpar.frprod_frac[0] = chtlu->frprod_frac[vegtype][0];
    for(int i =1; i<10; i++){
    	envpar.frprod_frac[i]= envpar.frprod_frac[i-1]+ chtlu->frprod_frac[vegtype][i];
    }
    
}

void Soil_Env::initializeState( Layer* fstsoill){
	
	initTempMois(fstsoill);

    resetFineRootFrac(fstsoill);
   
    layer2structmonthly(fstsoill);
	
}

//Yuan: better not to read netcdf file data here
void Soil_Env::initializeState5restart( Layer* fstsoill, RestartData* resin){
	
	double TSsoil[MAX_SOI_LAY];
	double LIQsoil[MAX_SOI_LAY];
	double ICEsoil[MAX_SOI_LAY];
	double frontZ[MAX_NUM_FNT];
	int frontFT[MAX_NUM_FNT];
	int FROZENsoil[MAX_SOI_LAY];

	for (int i=0; i<MAX_SOI_LAY; i++){
		TSsoil[i]=resin->TSsoil[i];
		LIQsoil[i]=resin->LIQsoil[i];
		ICEsoil[i]=resin->ICEsoil[i];
		FROZENsoil[i]=resin->FROZENsoil[i];	
	}

	for (int i=0; i<MAX_NUM_FNT; i++){
		frontZ[i]=resin->frontZ[i];
		frontFT[i]=resin->frontFT[i];
	}
	
	Layer* currl = fstsoill;
	SoilLayer* sl;
	int slind =-1;
	while(currl!=NULL){
		if(currl->isSoil()){
		  slind ++;
		 // sl = dynamic_cast<SoilLayer*>(currl);
		  currl->liq = LIQsoil[slind];
		  currl->tem = TSsoil[slind];
		  currl->ice = ICEsoil[slind];
		  currl->wat = currl->liq+currl->ice;
		  currl->age =0;
		  currl->rho =0;
		  currl->frozen = FROZENsoil[slind];
		  //sl->rootfrac = ROOTsoil[slind];
		  
			
		}else{
		  break;
		}
		
		currl = currl->nextl;
	};
	
	//update the front
	 
   
   int fntind=0;

   currl = fstsoill;
   double top, bot;
 
   while(currl!=NULL){
   	 top = currl->z;
   	 bot = top + currl->dz;
   	 sl = dynamic_cast<SoilLayer*>(currl);
   	 for(int lf = fntind; lf<MAX_NUM_FNT; lf++){
   	    if(frontZ[lf] >=top && frontZ[lf] <bot){
   	       //then frozen should be zero
   	      
   	      sl->addOneFront5Top4restart(frontZ[lf]-top, frontFT[lf]);
   	      fntind = lf +1;
   	      if(fntind >MAX_NUM_FNT){
   	      	goto FINISHFRONT;
   	      }
   	    }else if(frontZ[lf] >=bot){
   	    
   	       break;	
   	    }else if(frontZ[lf] <0){
   	      goto FINISHFRONT;	
   	    }	
   	 	
   	 }
   	
   	 currl = currl->nextl;
   }
   
   FINISHFRONT:
   
   //end of update front
   
	resetFineRootFrac(fstsoill);
    
    layer2structmonthly(fstsoill);

    //Yuan: need to know if the soil is permafrost or not
    if (resin->perma==1) {
    	ed->permafrost = 1;
    	ed->yrfrozensoil = 2.0;
    } else {
    	ed->permafrost = 0;
    	ed->yrfrozensoil = 0;
    }
 
}

void Soil_Env::initTempMois( Layer* backl){
	Layer* currl = backl;
	
	int permf =1;
	
	 while(currl!=NULL){
	   	 if(currl->isSoil()){
	   	  SoilLayer* sl = dynamic_cast<SoilLayer*>(currl);
	   	  if(permf==1){
		   	  currl->tem = -1;
		      currl->liq =currl->minliq;
		      if(sl->isMoss()){
		      currl->ice = currl->maxice;
		      }else if(sl->isMineral()){
		      currl->ice = currl->maxice;
		      }else{// peat
		      	currl->ice =  currl->maxice;
		      }
		      currl->wat= currl->liq + currl->ice;
		     sl->removeAllFronts(1);
	   	  }else if(permf==0){
	   	  	  currl->tem = 1;
		      currl->liq = currl->maxliq;
		     
		      	currl->ice = 0;
		    
		      currl->wat= currl->liq + currl->ice;
	   	  	  sl->removeAllFronts(-1);
	   	  }
	   	 }
	   	  currl = currl->nextl;

	   }

	    //Yuan: need to know if the soil is permafrost or not
	    if (permf==1) {
	    	ed->permafrost = 1;
	    	ed->yrfrozensoil = 2.0;
	    } else {
	    	ed->permafrost = 0;
	    	ed->yrfrozensoil = 0;
	    }

};


/*when soil column is frozen and there is snowmelt, assume that infiltration will  
 * saturate first 3 layers (change to all organic layers and first layer mineral
 */
double Soil_Env::infilFrozen(Layer* fstminl, const double & infilf){
	
	double infil;
  //  double liq, ice;
    infil=infilf;
    
    double tempinfil;
    // determine the last layer
	Layer * currl = fstminl->nextl->nextl;
	while(currl!=NULL){
	  if(currl->isSoil() && infil>0){
	  	 if(currl->liq-currl->ice <currl->maxice){
	  	 	tempinfil = currl->maxice- currl->liq - currl->ice;
	  	 	
	  	 	if(tempinfil>infil){
	  	 		tempinfil=infil;
	  	 	}
	  	 	currl->ice += tempinfil;
	  	 	infil -= tempinfil;
	  	 }
	  }else{
	  	break;	
	  }
	  currl = currl->prevl;	
	}

	return infilf; //this is the infiltration left
}


/*when soil column is frozen and there is snowmelt, assume that infiltration will  
 * saturate first 3 layers (change to all organic layers and first layer mineral
 */
double Soil_Env::infilFrozen2(Layer* fstsoill, Layer *fstnoinfil, const double &  rnth, const double & melt){
	double infilf; 
	double totinfl =rnth +melt;
	double tempinfl;

    infilf=0.;
    
    // determine the last layer
    
    
	Layer * currl = fstnoinfil;
///	Layer* currl = fstsoill;
	//while(currl!=NULL && totinfl>0){
	 while(currl->indl<=fstnoinfil->indl && totinfl>0){
	  if(currl->isSnow())break;
	  if(currl->frozen==0){
	  	 if(totinfl>(currl->maxice - currl->ice-currl->liq)&& (currl->maxice - currl->ice-currl->liq)>0 ){
	  	   tempinfl = (currl->maxice - currl->ice- currl->liq);
	  	   totinfl -=tempinfl;
	  	   infilf +=  tempinfl;
	  	   double leftinfl = updateLayerTemp5Lat(currl, tempinfl);
	  	   currl->ice += (tempinfl - leftinfl) ;
	  	   currl->liq += leftinfl;
	  	   currl->wat = currl->liq +currl->ice;
	  	   // change temperature by phase change
	  	 }else if((currl->maxice - currl->ice-currl->liq)>0){
	  	   tempinfl =totinfl;
	  	   totinfl -=tempinfl;
	  	   infilf +=  tempinfl;
	  	   double leftinfl = updateLayerTemp5Lat(currl, tempinfl);
	  	   currl->ice += (tempinfl-leftinfl);
	  	   currl->liq += leftinfl;
	  	   
	  	   currl->wat = currl->liq +currl->ice;
	  	 }
	  	
	  	
	  }else if(currl->frozen==1){ // totally frozen
	  	if(totinfl>(currl->maxice - currl->ice-currl->liq) && (currl->maxice - currl->ice-currl->liq)>0){
	  	   tempinfl = (currl->maxice - currl->ice -currl->liq);
	  	   totinfl -=tempinfl;
	  	   infilf +=  tempinfl;
	  	   double leftinfl =  updateLayerTemp5Lat(currl, tempinfl);
	  	   currl->ice += (tempinfl - leftinfl) ;
	  	   currl->liq += leftinfl;
	  	  
	  	   currl->wat = currl->liq +currl->ice;
	  	   // change temperature by phase change
	  	 }else if ((currl->maxice - currl->ice)>0){
	  	   tempinfl =totinfl;
	  	   totinfl -=tempinfl;
	  	   infilf +=  tempinfl;
	  	   double leftinfl =	  updateLayerTemp5Lat(currl, tempinfl);
	  	   currl->ice += (tempinfl-leftinfl);
	  	   currl->liq += leftinfl; 
	  	   
	  	   currl->wat = currl->liq +currl->ice;
	  	 }
	  	
	  }else if (currl->frozen ==-1){//unfrozen
	  	//fill the layer until saturated
	  	if(currl->ice>0){
	  	  currl->liq +=currl->ice;
	  	  currl->ice =0.;	
	  	}
	  	if(totinfl > currl->maxliq -currl->liq && currl->maxliq -currl->liq>0){
	  	   tempinfl = (currl->maxliq - currl->liq);
	  	   totinfl -=tempinfl;
	  	   infilf +=  tempinfl;
	  	   currl->liq += tempinfl;
	  	   currl->wat = currl->liq +currl->ice;
	  	}else if(currl->maxliq -currl->liq>0){
	  	   tempinfl =totinfl;
	  	   totinfl -=tempinfl;
	  	   infilf +=  tempinfl;
	  	   currl->liq += tempinfl; 
	  	   currl->wat = currl->liq +currl->ice;
	  	}

	  }
	  

	// currl=currl->nextl;	
	  currl=currl->prevl;	
	  if(currl==NULL)break;
	}
	
	return infilf;
}

double  Soil_Env::updateLayerTemp5Lat(Layer* currl, const double & infil){
	double extraliq =infil;
	int frozen = currl->frozen;
	
	if(frozen==1 || frozen ==0){ //frozen or partly frozen;
		double tem = currl->tem;

		//SoilLayer* sl = dynamic_cast<SoilLayer*>(currl);
		double vhp = currl->getHeatCapacity();
		double heatprovide = infil * 3.34e5; // provide latent heat
		double heatneed = fabs(tem) * vhp * currl->dz; // needed heat for increasing temperature from minus to zero
		if(heatprovide >=heatneed){
		  currl->tem =0.;	
		  extraliq = (heatprovide -heatneed)/3.34e5;
		  
		}else{
		  if(currl->tem<0){ // a double check
		  	currl->tem += heatprovide/(vhp *currl->dz);
		  }
		  extraliq =0.;	
		}
	};
	
	return extraliq;
}
double Soil_Env::getFracSat(const double & wtd){
	double temp1 = exp(-wtd);
	if(temp1>1) temp1=1;
	double fsat = envpar.wfact* temp1;
	return fsat;
	
}


double Soil_Env::getWaterTable(Layer* fstsoill){ 
	Layer* currl = fstsoill;
	double wtd=0;
	double s, dz, liq, ice, por;
	double thetai, thetal;
	double sums=0.;
	double ztot=0.;
	while (currl!=NULL){
		//sl = dynamic_cast<SoilLayer*>currl;
		if(currl->isRock())break;
		ice = currl->ice;
		liq = currl->liq;
		por = currl->poro;
		dz = currl->dz;
		thetai = ice/(dz * 917);
		thetai = min(por, thetai);
		thetal = liq/(dz * 1000.);
		thetal = min(por, thetal);
		

		s= (thetai + thetal)/por  ;
		s = min(s , 1.0);
		sums+=s * dz;
		ztot +=dz;
		
		currl=currl->nextl;
	}
	wtd = ztot - sums;
	return wtd;
}

 /*! reset diagnostic variables to initial values */
 void Soil_Env::resetDiagnostic(){
 	dztot=0.;
 	num=0; 	
 };
 
 
 double Soil_Env::getRunoffVIC(Layer* fstsoill, const double & rnth,const double & melt){
	double runoff; // overland runoff //mm/day
	/* prepare the top_moist and top_max_moist for the top 3 layers
	 * 
	 */
	//if (drgtype==1){ //poorly drained
	//  return 0;	
	//} 
	double top_moist=0.; //mm or kg/m2
	double top_max_moist =0;
    double por, dz, thetai, thetal;
    int numl=0;
  			Layer* currl = fstsoill;
			while (currl!=NULL){
				por = currl->poro;
				dz = currl->dz;
				thetai = currl->getVolIce();
				thetal = currl->getVolLiq();
				
				top_moist += currl->liq+currl->ice;
				top_max_moist += por*dz*1000;
				
				currl=currl->nextl;
				numl++;
				if(numl>=3)break;
				}
	
	if (top_max_moist <top_moist){
	  top_max_moist = top_moist;	
	}
	
	
	double inflow = rnth + melt;
	/* From Xiaogang Shi
		 * binf - [>0 to ~0.9] This parameter defines the shape of the Variable
	Infiltration Capacity curve. It describes the amount of available
	infiltration capacity as a function of relative saturated gridcell area. A
	higher value of binf gives lower infiltration and yields higher surface
	runoff.
	 * 
	 */
	double b_infilt = envpar.b_infilt;
	
	double max_infil = (1.+b_infilt) * top_max_moist;
	double ex = b_infilt/ (1+ b_infilt);
	double A = 1.0 - pow((1-top_moist/ top_max_moist), ex);
	double i_0 = max_infil * (1-pow((1.0-A), (1.0/b_infilt)));
	
	
	if(inflow ==0){
	  runoff =0;	
	}else if (max_infil ==0.) {
	  runoff = inflow;	
	}else if ((i_0 +inflow) > max_infil){
	  runoff = inflow - top_max_moist + top_moist;	
	}else{
	  double basis = 1.0 - (i_0 +inflow)/max_infil;
	  runoff = (inflow -top_max_moist + top_moist +top_max_moist * pow(basis, 1.+ b_infilt));	
		
	}
	if(runoff <0) runoff =0.;

	return runoff ;
};

 double Soil_Env::getBaseFlow(double const & wetness ){
 	double dt_bf=0;  //mm/s
 	/* From Xiaogang Shi
 	 * Dsmax: [>0 to ~25, depends on hydraulic conductivity] This is the
       maximum baseflow that can occur from the lowest soil layer (in mm/day).
       //here should change it to mm/s */
 	 double Dsmax = envpar.Dsmax/86400.;
 	 
 	 /* From Xiaogang Shi
 	  * [>0 to 1] This is the fraction of Dsmax where non-linear (rapidly
		increasing) baseflow begins. With a higher value of Ds, the baseflow will be
		higher at lower water content in lowest soil layer.
 	  * 
 	  */
 	 double Ds =envpar.Ds ; // a parameter
 	 
 	/*From Xiaogang Shi
 	 * [>0 to 1] This is the fraction of the maximum soil moisture (of
		the lowest soil layer) where non-linear baseflow occurs. This is analogous
		to Ds. A higher value of Ws will raise the water content required for
		rapidly increasing, non-linear baseflow, which will tend to delay runoff
		peaks.
 	 */  
 	 double Ws =  envpar.Ws;// 0.9 ; // a parameter
 	 
 	 double frac = Dsmax * Ds/Ws;
 	 dt_bf = frac * wetness;
 	 if(wetness >Ws){
 	   frac = (wetness -Ws)/ (1-Ws);	
 	   dt_bf  += Dsmax * (1-Ds/Ws)* pow(frac,2.); // in original code, 2 is replaced by c
 	   // but in Liang et al.,1994, 2 was used 
 	 }
 	 if(dt_bf<0) dt_bf=0;
 	return dt_bf;
 	
 };
 

 double Soil_Env::update5BaseFlow(Layer* drainl){
 	double base =0;
 	SoilLayer* sl;
 	Layer* currl =drainl;
 	double wetness;
 	double unffrac =0;
 	double dtbf, bf;
 	//first get the weighted wetness 
 	double sumwetness =0;
 	double sumdz=0;
 	while(currl!=NULL){
 		if(currl->isSoil()){
 			 sl= dynamic_cast<SoilLayer*>(currl);
 		  	wetness = sl->getVolWater()/sl->poro;
 		  	sumwetness+= wetness;
 		  	sumdz +=sl->dz;
 		}else{
 		 break;	
 		}
 		currl=currl->nextl;
 	}
 	wetness = sumwetness/sumdz;
 	
 	currl=drainl;
 	dtbf= getBaseFlow(wetness)* 86400;
 	while(currl!=NULL){
 	if(currl->isSoil()){
 		 sl= dynamic_cast<SoilLayer*>(currl);
 		  
 		 if(sl->frozen==-1){  //totally unfrozen
 		 	unffrac=1;
 		 }else if (sl->frozen==1){
 		 	unffrac=0;
 		 }else if(sl->frozen==0){ // partially unfrozen
 		 	unffrac = 1- sl->getFrozenFraction();
 		 }
 		 bf = dtbf * sl->dz/sumdz * unffrac ;
 		 if(sl->liq >bf+sl->minliq){
 		    sl->liq -= bf;	
 		 }else{ //add on Feb 14, 2008
 		     bf = sl->liq -sl->minliq;
 		     sl->liq = sl->minliq;	 
 		 }
 		 base += bf;
 		 
 	}else{
 	  break;	
 	}
 	currl =currl->nextl;	
 	}
 	
 	return base; // the daily baseflow
 }
 
double Soil_Env::getRunoff(Layer* fstsoill, const double & rnth,const double & melt, const double & frasat){
	double runoff; // overland runoff
//	double thetaimp =0.05;
	double s, dz, liq, ice, por;
	    ice = fstsoill->ice;
		liq = fstsoill->liq;
		por = fstsoill->poro;
		dz = fstsoill->dz;
	double	thetai = fstsoill->getVolIce();// ice/(dz * 917);
	//	thetai = min(por, thetai);
	double	thetal = fstsoill->getVolLiq();//liq/(dz * 1000.);
		//thetal = min(por, thetal);
		
			
			double sums=0.;
			double ztot=0.;
			int numl =0;
			Layer* currl = fstsoill;
			while (currl!=NULL){
		        
				
				por = currl->poro;
				dz = currl->dz;
				thetai = currl->getVolIce();
				thetal = currl->getVolLiq();
				
				s= (thetai + thetal)/por  ;
				s = min((double)s , 1.0);
				sums+=s * dz;
				ztot +=dz;
				currl=currl->nextl;
				numl++;
				if(numl>3)break;
				}
	         double avgs = sums/ztot;
	         runoff = (frasat  + (1-frasat)*pow((double)avgs, 4.) )* (rnth +melt);
	   
	return runoff;
};

double Soil_Env::getDrainage(const double & wtable){//not used
	double dsubmax =1.0e-5 ;// envpar.drainmax ; // from ATNiu42005a

	double f =1; 
	double dsub = dsubmax * exp(-f*wtable) *86400;
	dsub =0;
	return dsub;
};


double Soil_Env::update5Drainage(Layer* drainl, const double & fracsat, const double & wtd){
	//CLM method
	double qdrainwet =0;
	double qdraindry =0;
	double qdrain;
	double hksum =0;
	double hk;
	double zsat=0;
	double wsat=0;
	double unfrzcol=0;
	double dzksum =0;
	SoilLayer* sl;
	double wetness1;
	Layer* currl=drainl;
	double unffrac;
 
	while(currl!=NULL){
		if(currl->isSoil()){
 		 sl= dynamic_cast<SoilLayer*>(currl);
 		 if(sl->frozen==-1){  //totally unfrozen
 		 	unffrac=1;
 		 }else if (sl->frozen==1){
 		 	unffrac=0;
 		 }else if(sl->frozen==0){ // partially unfrozen
 		 	unffrac = 1- sl->getFrozenFraction();
 		 }
 		 if(unffrac>0){
 		 unfrzcol +=sl->dz*unffrac;
 		 wetness1= sl->getVolWater()/sl->poro;
 		 hk =sl->hksat * exp (-2*(sl->z + sl->dz/2))* pow((double)wetness1, (double)2*sl->bsw +2);
 		 hksum+=hk;
 		 zsat+= sl->dz*hk*unffrac;
 		 wsat += wetness1*sl->dz*hk*unffrac;
 		 dzksum +=hk*sl->dz*unffrac;
 		 }
		}else{
		  break;	
		}
		currl=currl->nextl;
	}
	
	if(unfrzcol<=0.1) return 0;
	wsat /= zsat;
	double bsw =4; // don't know why use bsw of first soil layer
	bsw=12; //Sept. 29, 2008
	qdraindry = (1-fracsat)*envpar.drainmax * pow(wsat, 2*bsw+3) ; 
		
	qdrainwet = fracsat* 1e-5 * exp(-wtd)  ; 
	qdrain = qdrainwet +qdraindry;
	
	currl = drainl;
	double onedrain;
	double alldrain=0;
	while(currl!=NULL){
		if(currl->isSoil()){
 		 sl= dynamic_cast<SoilLayer*>(currl);
 		 if(sl->frozen==-1){  //totally unfrozen
 		 	unffrac=1;
 		 }else if (sl->frozen==1){
 		 	unffrac=0;
 		 }else if(sl->frozen==0){ // partially unfrozen
 		 	unffrac = 1- sl->getFrozenFraction();
 		 }
 		 wetness1= sl->getVolWater()/sl->poro;
 		 hk =sl->hksat * exp (-2*(sl->z + sl->dz/2))* pow((double)wetness1, (double)2*sl->bsw +2);
 		 onedrain = 86400* qdrain *sl->dz*hk/dzksum *unffrac ;
 		 if(sl->liq >onedrain+sl->minliq){
 		    sl->liq -= onedrain;	
 		    
 		    alldrain+= onedrain;
 		 }else{ //add on Feb 14, 2008
 		     onedrain = sl->liq -sl->minliq;
 		     sl->liq = sl->minliq;	 
 		     alldrain+=onedrain;
 		 }
		}else{
		  break;	
		}
		currl=currl->nextl;
		
	}
	return alldrain;
}
 

void Soil_Env::resetFineRootFrac(Layer* fstsoill){
	Layer* currl = fstsoill;
	SoilLayer* sl;
	
	for(int il =0; il <MAX_SOI_LAY ; il++){
 	    ed->m_sois.rootfrac[il] =0;
 	   	
 	}
	double layertop, layerbot;//use the top of moss as zero
	//first get the thickness of moss
	double mossthick =0;
	while(currl!=NULL){
	  	if(currl->isSoil()){
		  sl= dynamic_cast<SoilLayer*>(currl);
		  if(sl->isMoss()){
		  mossthick += currl->dz;
		  }else{
		   break;
		  
		  }
		}
		
		currl = currl->nextl;
	}
	
	currl=fstsoill;
	layertop =0.;
	layerbot=0.;
	
	while(currl!=NULL){
		if(currl->isSoil()){
		  sl= dynamic_cast<SoilLayer*>(currl);
		  layertop = layerbot;
		  layerbot +=currl->dz;
		  if(layerbot>1) layerbot=1;
		  if(layertop>=1)break;
		  if(!sl->isMoss()){
		   sl->rootfrac = getFineRootFrac(layertop,layerbot, mossthick)/100.;
		  }else{
		   sl->rootfrac=0;
		  
		  }
		  ed->m_sois.rootfrac[sl->solind-1] = sl->rootfrac;
		}else{
		  break;	
		}
		
		currl = currl->nextl;
	};
	
	
   ed->m_soid.maxrootratio =0;
   ed->m_soid.maxrootind =0;
   for(int il =0; il <MAX_SOI_LAY; il++){
   	 if(ed->m_soid.maxrootratio < ed->m_sois.rootfrac[il]){
   	     ed->m_soid.maxrootratio =ed->m_sois.rootfrac[il]	;
   	     ed->m_soid.maxrootind =il;
   	 }
   	
   }
   
	
};

double Soil_Env::getFineRootFrac(const double & layertop, const double & layerbot, const double & mossthick){
	double totfrfrac ;
	double topcm = (layertop-mossthick) * 100.;   //Yuan: mossthick removed here
	double botcm = (layerbot-mossthick) * 100.;   //Yuan: mossthick removed here
	//determine the layer index of layertop and layerbot
	int indtop = (int) floor(topcm/10.);   //Yuan: the uppermost layer
	int indbot = (int) floor(botcm/10.);
	
	totfrfrac=0.;
/*
	double currfracfr; //the fraction of fine root for a layer;
	if(indtop ==indbot) { // in the same 10 cm interval
		currfracfr = envpar.frprod_frac[indtop];
//		if(indtop==0){
//			totfrfrac = (botcm -topcm)/(10-mossthick*100)  * currfracfr;
//		}else{
			totfrfrac = (botcm -topcm)/(10)  * currfracfr;
//		}
	}else{
	// for first interval
		currfracfr =  envpar.frprod_frac[indtop];
//		if(indtop==0){
//			totfrfrac= (10*(indtop+1)-topcm)/(10.-mossthick*100) * currfracfr;
//		}else{
			totfrfrac= (10*(indtop+1)-topcm)/10. * currfracfr;
//		}

		// for intervals between
		for(int il =indtop+1 ; il<=indbot-1; il++){
			currfracfr =  envpar.frprod_frac[il];
			totfrfrac += currfracfr;
		}

		//for last interval
	    currfracfr =  envpar.frprod_frac[indbot];
		totfrfrac += (botcm -10*indbot)/10. * currfracfr;
	}
*/

	//Yuan: calculating root fraction by interpolation
	double sumfractop = 0.0;
	double sumfracbot = 0.0;
	if (indtop ==0) {
		sumfractop = envpar.frprod_frac[indtop]/10.0*topcm;
	} else {
		sumfractop = (envpar.frprod_frac[indtop]-envpar.frprod_frac[indbot-1])/10.0
				    * (topcm-indtop*10.);
	}

	if (indbot ==0) {
		sumfracbot = envpar.frprod_frac[indbot]/10.0*botcm;
	} else {
		sumfracbot = (envpar.frprod_frac[indbot]-envpar.frprod_frac[indbot-1])/10.0
				    * (botcm-indtop*10.);
	}

	totfrfrac = sumfracbot - sumfractop;
	if (totfrfrac<0.0) totfrfrac = 0.0;
	
	return totfrfrac; 
	
}
/*! calculates the factor which provides controls from soil on transpiration
 *  from TROleson142004a*/
double Soil_Env::getSoilTransFactor(Layer* fstsoill){
	double btran =0;
	double rootfr;
	double psimax, psi, psisat;
	double rresis;
	SoilLayer* sl;
	Layer* currl=fstsoill;
	psimax = envpar.psimax;
	//psimax = -1.e7;
	//psimax =-1.5e5; CLM3 P144
	
	//first determine the total root in active layer
	double totrootfrac=0.;
	
	
	while(currl!=NULL){
		if(currl->isSoil()){
			sl =  dynamic_cast<SoilLayer*>(currl);
			rootfr = sl->rootfrac;
			if(rootfr<1.e-4 && currl->indl>10){
			 break;
			}
			if(sl->tem>=0 && rootfr>=1.e-4){
				totrootfrac+=rootfr;
			}
		}
				currl=currl->nextl;
	}
	
	if (totrootfrac <=0){
	  	btran =0.;
	  	return btran;
	}else{
		currl =fstsoill;
	  while(currl!=NULL){
		if(currl->isSoil()){
			sl =  dynamic_cast<SoilLayer*>(currl);
			rootfr = sl->rootfrac;
			if(rootfr<1.e-4 && currl->indl>10){
			 break;
			}
			if(sl->tem>=0 && rootfr>=1.e-4){
				//if(sl->tem>=0 && rootfr>=1.e-2){
				psisat = sl->psisat;
				psi= sl->getMatricPotential();
				
				psi = max(psimax, psi);
				psi = min(psisat, psi);
				rresis = (1.- psi/psimax)/(1- psisat/psimax);
				/*if(psi<=psimax){
				  rresis =0.;	
				}else if(psi>=psisat1){
				  rresis =1;	
				}else{
				  rresis = (psimax-psi)/(psimax - psisat1)	;
				}
				*/
				btran += rootfr* rresis;
				//btran += rootfr/totrootfrac * rresis;
				
			}else{
			    btran +=0.;	
			}
		}
				currl=currl->nextl;
		
	};
	
	}
	
	
	if(btran>1) {
		//cout <<"btran is greater than 1 " << btran <<"\n";
		btran =1;
		
	  	
	}
	return btran;
}

///at end of month, save information in layer into struct in envdata
void Soil_Env::layer2structmonthly(Layer* fstsoill){
	Layer * curr2;
	SoilLayer* sl;
	PeatLayer* pl;
	curr2= fstsoill;
	ed->m_soid.mossthick =0;
	ed->m_soid.shlwthick =0;
	ed->m_soid.deepthick =0;
	ed->m_soid.mossnum =0;
	ed->m_soid.shlwnum =0;
	ed->m_soid.deepnum =0;
    
    for(int il=0; il<MAX_SOI_LAY; il++){
      ed->m_sois.type[il]=-1;
      ed->m_sois.dz[il]=-999;	
    }
  
  	int ind=0;
//  	double nonicevol =0;
  
	while(curr2!=NULL) {
		if(curr2->isSoil()){
			sl = dynamic_cast<SoilLayer*>(curr2);
			if(sl->isPeat()){
				pl = dynamic_cast<PeatLayer*>(sl);
				if(pl->isFibric){
					ed->m_soid.shlwthick +=curr2->dz;
					ed->m_soid.shlwnum++;
				
					ed->m_sois.type[ind] = 1;
				}else if(pl->isHumic){
					ed->m_soid.deepthick +=curr2->dz;
					ed->m_sois.type[ind] = 2;
					ed->m_soid.deepnum++;
				}
			}else if(sl->isMoss()){
				ed->m_soid.mossthick +=curr2->dz;
				ed->m_sois.type[ind] = 0;
				ed->m_soid.mossnum++;
			}else{
				ed->m_sois.type[ind] = 3;
				ed->m_soid.minethick+=curr2->dz;
			}
			ed->m_sois.dz[ind] = curr2->dz;
			ed->m_sois.z[ind] = curr2->z;
			ed->m_sois.por[ind] = curr2->poro;
			ed->m_soid.minliq[ind] = curr2->minliq;

/*
			nonicevol = curr2->poro-curr2->getVolIce();
			if(nonicevol<=0) nonicevol = 0.01;
			ed->m_soid.allvwc[ind] =curr2->getVolLiq()+curr2->getVolIce(); //Theta (all water)
			ed->m_soid.allsws[ind] =(curr2->getVolLiq())/curr2->poro;      //liq. water saturation
			ed->m_soid.allaws[ind] =(curr2->getVolLiq())/nonicevol;        //adjusted liq. water saturation
			if(ed->m_soid.allvwc[ind] >1){
				ed->m_soid.allvwc[ind]=1;
			}
			if(ed->m_soid.allsws[ind] >1){
				ed->m_soid.allsws[ind]=1;
			}
			if(ed->m_soid.allaws[ind] >1){
				ed->m_soid.allaws[ind]=1;
			}
*/
			ind++;
		}

		curr2= curr2->nextl;
	};

	ed->m_soid.actual_num_soil=ind;
	if(ed->m_sois.dz[0] ==2){
		string msg = "the first soil layer cannot be deep organic";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_LAYER_FIRST_DEEP);
		 
	}
		 
}

/*at end of day, save information in layers into struct in envdata*/

void Soil_Env::layer2structdaily(Layer* fstsoill){
	Layer * curr2;
	curr2= fstsoill;
	
  	int ind=0;
	while(curr2!=NULL) {
		if(!curr2->isSoil()) break;
		ed->d_sois.ts[ind] = curr2->tem;
		ed->d_sois.liq[ind] = curr2->liq;
		ed->d_sois.ice[ind] = curr2->ice;
		curr2= curr2->nextl;
		ind++;
			
	};
}

void Soil_Env::retrieveThawPercent(Layer* fstsoill){
 Layer* curr2;
 curr2 = fstsoill;
 SoilLayer* sl;
 double totdep=0;
 while (curr2!=NULL){
 	if(curr2->isSoil()){
	  	sl = dynamic_cast<SoilLayer*>(curr2);
	  	if(sl->rootfrac>0){//moss has no root
	  		if(sl->frozen==1){
	  			break;
	  		}else if(sl->frozen==-1){//unfrozen
	  		    totdep+=sl->dz;
	  		    if(totdep>=envpar.rootdp4gpp){
	  		    	ed->d_soid.growpct =1;
	  		    	return;
	  		    }
	  		}else if(sl->frozen==0){//with front
	  			if(sl->fronts[0]->frzing==1){
	  			  break;	
	  			}else{
	  			  totdep +=sl->fronts[0]->dz;	
	  			}
	  		}
	  	}

		}else{
			break;
		}

		curr2 =curr2->nextl;
	}

    if(totdep>=envpar.rootdp4gpp){
    	ed->d_soid.growpct =1;
    }else{
    	ed->d_soid.growpct =0;
    }

    return;
};


void Soil_Env::retrieveDailyOutputs(Layer* fstsoill, Layer* fstminl, Layer* lstminl, Layer* backl){
	
	Layer * curr2;
	
	curr2 =fstsoill;
	SoilLayer* sl ;
	double unfrzcolumn=0;
	int ind =0;
	while(curr2!=NULL){
	  if(curr2->isSoil()){
		  sl = dynamic_cast<SoilLayer*>(curr2);
		  unfrzcolumn+= sl->getUnfrzColumn();
	  	
		  ed->d_soid.tem[ind]= curr2->tem;
	  	  ed->d_soid.allvwc[ind]= curr2->getVolWater();
	  	  ed->d_soid.alliwc[ind]= curr2->getVolIce();
	  	  ed->d_soid.alllwc[ind]= curr2->getVolLiq();
	  	  	
	  	  ed->d_soid.allsws[ind]= curr2->getVolLiq()/curr2->poro;
	  	  ed->d_soid.allaws[ind]= curr2->getVolLiq()/(curr2->poro-curr2->getVolIce());

	  	  //ed->d_soid.tcond[ind] = curr2->tcond;     //missing value is reported sometime!
	  	  ed->d_soid.tcond[ind] = curr2->getThermalConductivity();
	  	  if ((isnan(curr2->hcond)) || (curr2->frozen==1)) {
	  		  ed->d_soid.hcond[ind] = 0.;
	  	  } else {
		  	  ed->d_soid.hcond[ind] = curr2->hcond;
	  	  }

	  	  ind++;
	  	}
	  	
	  curr2 = curr2->nextl;
	}	
	
	ed->d_soid.unfrzcolumn = unfrzcolumn;
	ed->d_soid.tmineral10cm = fstminl->tem; //first minl layer is 10 cm
	ed->d_soid.trock34m = backl->tem;
	
	if(lstminl->frozen==-1){        //Yuan: -1 should be unfrozen (this NOT used)
		ed->d_soid.permafrost =0;
	}else{
		ed->d_soid.permafrost =1;
	}

}

void Soil_Env::retrieveDailyFronts(Layer* fstsoill){
   for (int il=0; il<MAX_NUM_FNT; il++){
   	 ed->d_soid.frzfnt[il] =-999.;
   	 ed->d_soid.thwfnt[il] =-999.;
   }	
   Layer * curr2= fstsoill;
   SoilLayer* sl;
   int itf=-1;
   int iff=-1;

   double top;
   while(curr2!=NULL){
   	// the following method is from directly simulated fronts
   	top =curr2->z;
   	if(curr2->isSoil()){
   		sl = dynamic_cast<SoilLayer*>(curr2);
   		sl->combineFronts();//it is possible that there are too many fronts exist in one layer
   		                    //combine them if there are too many
   		if(sl->fronts.size()>0){
   			
   		  for(unsigned int i =0;i<sl->fronts.size();i++){
   		  	if(sl->fronts[i]->frzing==1){
   		  		iff++;
   		  		if(iff>=MAX_NUM_FNT){
   		  		 
   		  		 string msg = "The number of freezing fronts is more than MAX_OUT_FNT ";
 				char* msgc = const_cast< char* > ( msg.c_str());
 				throw Exception(msgc, I_TOO_MANY_FRZ_FRONTS);
   		  		}
   		  		ed->d_soid.frzfnt[iff] = top + sl->fronts[i]->dz;
   		  	}else if(sl->fronts[i]->frzing==-1){
   		  		itf++;
   		  		if(itf>=MAX_NUM_FNT){
   		  		 string msg = "The number of Thawing fronts is more than MAX_OUT_FNT ";
 				char* msgc = const_cast< char* > ( msg.c_str());
 				throw Exception(msgc, I_TOO_MANY_THW_FRONTS);
   		  		}
   		  		ed->d_soid.thwfnt[itf] = top + sl->fronts[i]->dz;
   		  	}
   		  }	
   		}
   	}else if(curr2->isRock()){
   	  break;
   	}
   	
   	
   	curr2=curr2->nextl;
   }
	
};

/*
int Soil_Env::getCohortType(){
	return vegtype;
};*/
void Soil_Env::setCohortLookup(CohortLookup * chtlup){
  chtlu =chtlup;	
}

void Soil_Env::setEnvData(EnvData* edp){
	ed = edp;
	
}
void Soil_Env::setFirData(FirData* fdp){
  	 fd =fdp;
  }
  
