#include "Cohort.h"

Cohort::Cohort(){
 	rheqflag   = 1;
 	cohortcount= 0;
 	friderived = false;   //this is default, can be modified
};

Cohort::~Cohort(){

};

// initialization
void Cohort::init(){ 
 	ctol = 0.1;
 	ntol = 0.001;

	ve.setEnvData(ed);
	ground.setEnvData(ed);

	sb.setBgcData(bd);
	sb.setEnvData(ed);
	sb.setCohortLookup(&chtlu);

	vb.setBgcData(bd);
	vb.setEnvData(ed);
	vb.setCohortLookup(&chtlu);
	vb.setSoilBgc(&sb);

	fire.setEnvData(ed);
	fire.setCohortLookup(&chtlu);
	fire.setBgcData(bd);

	ve.setFirData(fd);
	vb.setFirData(fd);
	sb.setFirData(fd);

	ground.setFirData(fd);
	fire.setFirData(fd);

 	ve.setCohortLookup(&chtlu);
 	ground.soil.setCohortLookup(&chtlu);
 	ground.snow.setCohortLookup(&chtlu);
 
 	integrator.setSoil_Bgc(&sb);
 	integrator.setVegetation_Bgc(&vb);
 	integrator.setBgcData(bd);
 	integrator.setEnvData(ed);
 
};

void Cohort::reset() {
  
	 int drgtype = cd->drgtype;
 	 int vegtype = cd->vegtype;
 	  
 	 // initial state variables

	if(md->initmode < 3){    //lookup or sitein

		// first read in the default initial values
	 	ground.soil.moss.thick = chtlu.mossthick[drgtype][vegtype];
    	ground.soil.peat.shlwthick = chtlu.fibthick[drgtype][vegtype];
    	ground.soil.peat.deepthick = chtlu.humthick[drgtype][vegtype];

		// reset the soil texture data from grid-level soil.nc, rather than 'chtlu',
 	    // Note that the default mineral layer structure is defined in layerconst.h
 		 float z=0;
 		 for (int i=0; i<MAX_MIN_LAY; i++){
	 			 z+=MINETHICK[i];
	 			 if (z<=0.21) {   //assuming the grid top-soil texture is for top 20 cm
	 				 ground.soil.mineral.type[i] = gd->topsoil;
	 			 } else {
	 				 ground.soil.mineral.type[i] = gd->botsoil;
	 			 }

	 	 }
 		 ground.soil.mineral.thick = z;

 		 // then if we have sitein.nc, as specified. In this way, if sitein.nc may not provide
 		 // all data, then model will still be able to use the default.
	    if(md->initmode ==2){ //from sitein.nc specified as md->initialfile
	    	setSiteStates(&sitein);
	    }
	} else {    //restart
		ground.soil.moss.thick = 0.0;
		ground.soil.peat.shlwthick = 0.0;
		ground.soil.peat.deepthick = 0.0;
		for (int i=0; i<MAX_SOI_LAY; i++){
			if (resid.TYPEsoil[i]==0) ground.soil.moss.thick += resid.DZsoil[i];
			if (resid.TYPEsoil[i]==1) ground.soil.peat.shlwthick += resid.DZsoil[i];
			if (resid.TYPEsoil[i]==2) ground.soil.peat.deepthick += resid.DZsoil[i];
			if (resid.TYPEsoil[i]==3) ground.soil.mineral.thick += resid.DZsoil[i];

		}
		for(int j=0; j<MAX_MIN_LAY; j++){
			ground.soil.mineral.type[j] = resid.TYPEmin[j];
		}

		for(int i=0; i<12; i++){
 			ve.envlaiall[i] =  chtlu.envlai[vegtype][i] ;
 		}
	}
  
 	fire.initializeParameter(drgtype, vegtype);
 	sb.initializeParameter(drgtype, vegtype);
 	vb.initializeParameter(drgtype, vegtype);
 	ve.initializeParameter(drgtype, vegtype);
 
 	ground.soil.initializeParameter(drgtype, vegtype);
 	ground.snow.initializeParameter(vegtype);
 
 	ed->init();
 	bd->init();
 	fd->init();
 
 	if(md->initmode<3){
 		fire.initializeState();
 		vb.initializeState(drgtype, vegtype);
 		ve.initializeState(drgtype, vegtype);
 		ground.initializeLayerStructure();
 		sb.initializeState(ground.fstshlwl, ground.fstminl, drgtype, vegtype);
 	} else {
 		if(md->runsp){
 	  		cd->reschtid = cd->spchtid;	
 		} else if (md->runtr){
 	  		cd->reschtid = cd->trchtid;	
 		}
 		
 		fire.initializeState5restart(&resid);
 		vb.initializeState5restart(&resid);
 		ve.initializeState5restart(&resid);
 		ground.initializeLayerStructure5restart(&resid);
 		sb.initializeState5restart(ground.fstsoill,&resid);
 	}	 

 	//for output calibration driver
 	for(int i=0; i<12; i++){
		veenvlai[i] =  ve.envlaiall[i];
	}

};

void Cohort::setTime(Timer * timerp){
  	timer = timerp;
}; 
  
void Cohort::setModelData(ModelData* mdp){
  	md = mdp;
};

void Cohort::setInputData(RegionData * rdp, GridData * gdp, CohortData *cdp){

  	rd = rdp;
  	gd = gdp;
  	cd = cdp;	
  
  	fd->rd = rd;
  	bd->rd = rd;
  	ed->rd = rd;
  
  	fd->gd = gd;
  	bd->gd = gd;
  	ed->gd = gd;
  
  	fd->cd = cd;
  	bd->cd = cd;
  	ed->cd = cd;
  
};

void Cohort::setProcessData(EnvData * edp, BgcData * bdp, FirData *fdp){
	ed = edp;
	bd = bdp;
	fd = fdp;
};

void Cohort::setAtmData(Grid *grid){
  	atm = &grid->atm;
  
};

void Cohort::setRestartOutData(RestartData *resodp){
	resod = resodp;
};

void Cohort::setSiteOutData(AtmOutData *atmodp, VegOutData * vegodp, SnowSoilOutData * sslodp){
    atmod = atmodp;
    vegod = vegodp;
    sslod = sslodp;				
};

void Cohort::setRegnOutData(RegnOutData *regnodp){
    regnod = regnodp;
};

bool Cohort::testEquilibrium(){
  	bool eqed =false;
  	int nfeed = bd->nfeed;
 
  	if(nfeed ==0 && rheqflag==0) {
  	  	if(ctol>= fabs(bd->y_a2v.npp - bd->y_v2soi.ltrfalc) ) {
  	  	 	eqed = true;
  	  	}
  	}else if(nfeed ==0 && rheqflag==1) {
  	  	if(ctol>=fabs(bd->y_a2v.npp   - bd->y_soid.nrhsum - bd->y_soid.rrhsum) &&		
  	  	   ctol>= fabs(bd->y_a2v.npp  - bd->y_v2soi.ltrfalc) &&
  	  	   ctol>=fabs(bd->y_v2soi.ltrfalc -  bd->y_soid.nrhsum - bd->y_soid.rrhsum) 
  	  	  ) {
  	  	 		eqed = true;
  	  	}
  	}else if(nfeed ==1 && rheqflag==1) {
  		if(ctol>=fabs(bd->y_a2v.npp   - bd->y_soid.nrhsum - bd->y_soid.rrhsum) &&		
  	  	   ctol>= fabs(bd->y_a2v.npp  - bd->y_v2soi.ltrfalc) &&
  	  	   ctol>=fabs(bd->y_v2soi.ltrfalc - bd->y_soid.nrhsum - bd->y_soid.rrhsum)  &&
  	  	   ntol >= fabs(bd->y_a2soi.ninput - bd->y_soi2l.nlost)  &&
  	  	   ntol >=fabs(bd->y_soi2v.nuptake - bd->y_v2soi.ltrfaln) &&
  	  	   ntol >=fabs(bd->y_soi2v.nuptake- bd->y_soi2soi.netnmin)&&
  	  	   ntol >=fabs(bd->y_v2soi.ltrfaln- bd->y_soi2soi.netnmin)
  	  	  ) { 
  	  	 		eqed = true;
  	  	 }
  	
  	}

  	return eqed;
  
};

void Cohort::setSiteStates(SiteIn *initstate){

	if (initstate->ysf!=-999) fd->ysf = initstate->ysf;

	// the following variables are changing through 'lookup', so be sure they're updated in the module
	for(int im=0; im<12; im++){
		if (initstate->lai[im]!=-999) chtlu.envlai[cd->vegtype][im] =  initstate->lai[im] ;
	}

	if (initstate->vegc!=-999)
		chtlu.initvegc[cd->drgtype][cd->vegtype] = initstate->vegc;
	if (initstate->vegn!=-999)
		chtlu.initstrn[cd->drgtype][cd->vegtype] = initstate->vegn*0.96;
	if (initstate->vegn!=-999)
		chtlu.initston[cd->drgtype][cd->vegtype] = initstate->vegn*0.04;

	if (initstate->soilc!=-999) {
		chtlu.initsolc[cd->drgtype][cd->vegtype]= initstate->soilc;
	} else if (initstate->fibc!=-999 &&
			initstate->humc!=-999 && initstate->minc!=-999) {
		chtlu.initsolc[cd->drgtype][cd->vegtype] = initstate->fibc +
				initstate->humc + initstate->minc;
	}

	if (initstate->avln!=-999)
		chtlu.initavln[cd->drgtype][cd->vegtype] = initstate->avln;
	if (initstate->orgn!=-999)
		chtlu.initsoln[cd->drgtype][cd->vegtype] = initstate->orgn;

	//the following are changing through direct operation of module's data
	if (initstate->mossthick!=-999)
		ground.soil.moss.thick     = initstate->mossthick;
	if (initstate->fibthick!=-999)
		ground.soil.peat.shlwthick = initstate->fibthick;
	if (initstate->humthick!=-999)
		ground.soil.peat.deepthick = initstate->humthick;

	for(int i=0; i<MAX_MIN_LAY; i++){
 		if (initstate->mintype[i]!=-999) 
 			ground.soil.mineral.type[i] = initstate->mintype[i];
 	}

 	for (int i=0; i<MAX_SOI_LAY; i++) {
 		if (initstate->initz[i]!=-999) {
 			ground.soil.mineral.thick=initstate->initz[i];
 			if (initstate->initz[i+1]==-999 || i==MAX_SOI_LAY)
 				ground.soil.mineral.thick -= ground.soil.moss.thick
 				                            +ground.soil.peat.shlwthick
 				                            +ground.soil.peat.deepthick;
 		}
 		if (initstate->initst[i]!=-999) ground.soil.initem[i]=initstate->initst[i];
 		if (initstate->initsm[i]!=-999) ground.soil.inivwc[i]=initstate->initsm[i];
	}

 	//update the variables in the module, due to above modification
	ground.initializeLayerStructure();
	sb.initializeState(ground.fstshlwl, ground.fstminl, cd->drgtype, cd->vegtype);

	ve.initializeState(cd->drgtype, cd->vegtype);
	vb.initializeState(cd->drgtype, cd->vegtype);
};

//for java interface data exchange (so no need to define 'ground' in Java)
void Cohort::getSiteStates(SiteIn *currstate){
	
	currstate->ysf = fd->ysf;
	
    currstate->mossthick = ground.soil.moss.thick; 
    currstate->fibthick = ground.soil.peat.shlwthick; 
    currstate->humthick = ground.soil.peat.deepthick;
		    
	for(int i=0; i<12; i++){
		currstate->lai[i] = ve.envlaiall[i];
	}

	currstate->vegc = bd->m_vegs.c;
	currstate->vegn = bd->m_vegs.strn+ bd->m_vegs.ston;
	
	double soilc = 0.0;
	double fibc  = 0.0;
	double humc  = 0.0;
	double minc  = 0.0;
	int TYPEsoil[MAX_SOI_LAY];
	int TYPEmin[MAX_MIN_LAY];
	updateSoilLayerType(TYPEsoil, TYPEmin);
	for (int il=0; il<MAX_SOI_LAY; il++){
		soilc+=bd->m_sois.nonc[il]+bd->m_sois.reac[il];
		if (TYPEsoil[il]==1){
			fibc+=bd->m_sois.nonc[il]+bd->m_sois.reac[il];
		}else if (TYPEsoil[il]==2){
			humc+=bd->m_sois.nonc[il]+bd->m_sois.reac[il];
		}else if (TYPEsoil[il]==3){
			minc+=bd->m_sois.nonc[il]+bd->m_sois.reac[il];	
		}
	}
	currstate->soilc = soilc;
	currstate->fibc  = fibc;
	currstate->humc  = humc;
	currstate->minc  = minc;
	
	currstate->avln = bd->m_sois.avln;
	currstate->orgn = bd->m_sois.orgn;
	
	for (int il=0; il<MAX_MIN_LAY; il++){
		currstate->mintype[il]=TYPEmin[il];
	}
	
    for (int i=0; i<MAX_SOI_LAY; i++) {
 		currstate->initst[i]=ed->m_soid.tem[i];
 		currstate->initsm[i]=ed->m_soid.allvwc[i];
    }

};

//for java interface data exchange (so no need to define 'vb' and 'sb' in Java)
//Tip: this is for needs to modify the embeded model parameters, so could add more
void Cohort::resetBgcPar(vegpar_bgc *vbbgcpar, soipar_bgc *sbbgcpar){

	//better to refresh the individual variable rather than the whole structure
	//in case some variables not update, which then still using the default (lookup table value)

	//for leaf phenology
	vb.bgcpar.m1    = vbbgcpar->m1;
	vb.bgcpar.m2    = vbbgcpar->m2;
	vb.bgcpar.m3    = vbbgcpar->m3;
	vb.bgcpar.m4    = vbbgcpar->m4;

	//for som component fraction
	sb.bgcpar.fsoma  = sbbgcpar->fsoma;
	sb.bgcpar.fsompr = sbbgcpar->fsompr;
	sb.bgcpar.fsomcr = sbbgcpar->fsomcr;
	sb.bgcpar.som2co2= sbbgcpar->som2co2;

};

//for java interface data exchange (so no need to define 'vb' and 'sb' in Java)
//Tip: this is for needs to modify the embeded model parameters, so could add more
void Cohort::getBgcPar(vegpar_bgc *vbbgcpar, soipar_bgc *sbbgcpar){

	//better to refresh the individual variable rather than the whole structure
	//in case some variables not update, which then still using the default (lookup table value)

	//for leaf phenology
	vbbgcpar->m1  = vb.bgcpar.m1;
	vbbgcpar->m2  = vb.bgcpar.m2;
	vbbgcpar->m3  = vb.bgcpar.m3;
	vbbgcpar->m4  = vb.bgcpar.m4;

	//for som component fraction
	sbbgcpar->fsoma  = sb.bgcpar.fsoma ;
	sbbgcpar->fsompr = sb.bgcpar.fsompr;
	sbbgcpar->fsomcr = sb.bgcpar.fsomcr;
	sbbgcpar->som2co2= sb.bgcpar.som2co2;

};

//for java interface data exchange (so no need to define 'vb' and 'sb' in Java)
void Cohort::resetCalPar(vegpar_cal *vbcalpar, soipar_cal *sbcalpar){
	
	//better to refresh the individual variable rather than the whole structure (like above)
	//in case some variables not update, which then still using the default (lookup table value)
	vb.calpar.cmax  = vbcalpar->cmax;
	vb.calpar.nmax  = vbcalpar->nmax;
	vb.calpar.cfall = vbcalpar->cfall;
	vb.calpar.nfall = vbcalpar->nfall;
	vb.calpar.krb   = vbcalpar->krb;

	sb.calpar.nup    = sbcalpar->nup;
	sb.calpar.kdcfib = sbcalpar->kdcfib;
	sb.calpar.kdchum = sbcalpar->kdchum;
	sb.calpar.kdcmin = sbcalpar->kdcmin;
	sb.calpar.kdcslow = sbcalpar->kdcslow;

};

//get the calibration pars for output in java
//for java interface data exchange (so no need to define 'vb' and 'sb' in Java)
void Cohort::getCalPar(vegpar_cal *vbcalpar, soipar_cal *sbcalpar){
	vbcalpar->cmax = vb.calpar.cmax;
	vbcalpar->nmax = vb.calpar.nmax;
	vbcalpar->cfall= vb.calpar.cfall;
	vbcalpar->nfall= vb.calpar.nfall;
	vbcalpar->krb  = vb.calpar.krb;

	sbcalpar->nup    = sb.calpar.nup;
	sbcalpar->kdcfib = sb.calpar.kdcfib;
	sbcalpar->kdchum = sb.calpar.kdchum;
	sbcalpar->kdcmin = sb.calpar.kdcmin;
	sbcalpar->kdcslow = sb.calpar.kdcslow;

};

void Cohort::fireDrivingData(bool runsp, bool runtr, bool runsc){
	fire.prepareDrivingData(runsp, runtr, runsc);
	firstfireyr = fire.firstfireyr;
};

int Cohort::timerOutputYearIndex(bool equiled, bool spined, bool outputSpinup){
	return timer->getOutputYearIndex(equiled, spined, outputSpinup);
};

void Cohort::updateMonthly(const int & outputyrind,const int & yrcnt, const int & currmind, 
             const int & dinmcurr, const bool & assigneq, const bool & useeq){
	
	if (veupdateLAI5Vegc) {
		ve.updateLAI5Vegc=true;
	}else{
		ve.updateLAI5Vegc=false;	
	}
	
   	if(currmind ==0){
  	 	fd->beginOfYear();
   	}	
   
   	if(dsbmodule){	
  		updateMonthly_Fir(yrcnt, currmind);
   	}
  
  	if(dslmodule ){
    	updateMonthly_Dsl(currmind);
  	}
  
  	int calyr = timer->getCalendarYear(equiled, spined);
  	if(envmodule){
  		updateMonthly_Env( yrcnt,calyr, currmind, dinmcurr, assigneq );
  	}
  
  	if(ecomodule){
  		updateMonthly_Bgc( yrcnt,calyr, currmind, dinmcurr ,useeq);
  	}

  	if(currmind==11){
  		fd->endOfYear();
  	}
    
  	//for regional run output ONLY; for site-run, this was executed in updateMonthly_Fir, _Env, and _Bgc
	if(outRegn){
		if (envmodule && ecomodule) {    // Yuan: otherwise will cause fatal default?
			updateRegionalOutputBuffer(currmind);
		}
	}  	

};

/////////////////////////////////////////////////////////////////////////////////
//fire disturbance (yearly timestep)
/////////////////////////////////////////////////////////////////////////////////
void Cohort::updateMonthly_Fir(const int & yrcnt, const int & currmind  ){ 
  
  	int fireoccur = fire.getOccur(yrcnt, currmind, friderived);
       
   	if(fireoccur==1 ){
   	
    	double inputnonc = bd->m_sois.wdebris;
  		fire.burn(yrcnt, friderived);

   		sb.assignCarbon5Struct2Layer(ground.fstsoill);
   	
 		if(dslmodule){
 			ground.burn(dslmodule);
		   	sb.updateDeepCarbonAfterLayerDivide(ground.fstdeepl);
 		}

 		sb.assignCarbon5Layer2Struct(ground.fstsoill, inputnonc);
 		bd->m_sois.wdebris = 0.0; //Yi: May 21, 2010: there is a need to set wdebris to zero
   	} 

    if(currmind==11){
	  	if(outSiteYear){
  			updateSiteYlyOutputBuffer_Fir();
	  	}
    }
   
};

/////////////////////////////////////////////////////////////////////////////////
//   Dynamical Soil Layer Module (DSL) calling, but only at yearly timestep
////////////////////////////////////////////////////////////////////////////////
void Cohort::updateMonthly_Dsl(const int & currmind){
	if(currmind==0){ 
		//only update the thickness at begin of year , since it is a slow process 	
//  		if(equiled){   //Yuan: so that this module can be used for eq-run
  	     	
			double mossthick = sb.getMossThickness(); 
		    sb.assignCarbon5Struct2Layer(ground.fstsoill);
		    sb.updateShallowThickness(ground.fstshlwl, ground.lstshlwl);

		    sb.updateDeepThickness(ground.fstdeepl, ground.lstdeepl);
		   
		   	if(ground.fstshlwl!=NULL && ground.lstshlwl!=NULL){
		   	  	if(ground.fstshlwl->indl == ground.lstshlwl->indl){
		   	  		SoilLayer* sl = dynamic_cast<SoilLayer*>(ground.fstshlwl);
		   	  		double shlwc = sl->reac + sl->nonc;
		   	  	 	if(shlwc < sb.shlw2cmcarbon){
		   	  	 	//	ground.fstshlwl->tcmin= 8;
		   	  	   		ground.fstshlwl->dz =0.02;
		   	  	 	}else{
		   	  	 	//	ground.fstshlwl->tcmin = 0.1;
		   	  	 	}
		   	  	}
		   	}
		  
		    if(ground.fstdeepl!=NULL && ground.lstdeepl!=NULL){
		   	 	if(ground.fstdeepl->indl == ground.lstdeepl->indl){
		   	  		SoilLayer* sl = dynamic_cast<SoilLayer*>(ground.fstdeepl);
		   	  		double deepc = sl->reac + sl->nonc;
		   	  	 	if(deepc < sb.deep2cmcarbon){
		   	  	 	//	ground.fstdeepl->tcmin= 8;
		   	  	   		ground.fstdeepl->dz =0.02;
		   	  	 	}else{
		   	  	 	//	ground.fstdeepl->tcmin = 0.1;
		   	  	 	}
		   	  	}
		   	}
		   
//		    if(envmodule && ecomodule){    //Yuan: this doesn't make sense

		    	ground.adjustLayerThickness(mossthick);
		           	
	     	 	sb.updateShallowCarbonAfterLayerDivide(ground.fstshlwl, ground.lstshlwl);
	     	 	sb.updateDeepCarbonAfterLayerDivide(ground.fstdeepl);
		     	 
	         	sb.assignCarbon5Layer2Struct(ground.fstsoill,0);
		         
//		    }
  	    }	
//  	}
};

/////////////////////////////////////////////////////////
//Environment Module Calling at monthly time-step, but involving daily time-step running
/////////////////////////////////////////////////////////
void Cohort::updateMonthly_Env(const int & yrcnt,const int &  calyr, 
			const int & currmind, const int & dinmcurr, const bool & assigneq){
				
	double tdrv, daylength; 

	//update the atmosphere first
    int inputyrind = timer->getInputYearIndex(equiled, spined);

//	atm->beginOfMonth(inputyrind,currmind,dinmcurr, equiled);
    //Yuan: change climate/co2 option added
    if (md->runeq) {
    	atm->beginOfMonth(inputyrind,currmind,dinmcurr, true, false, false); //first t/f: for normal/dynamical, 2nd t/f: for change clm
    } else if (md->runsp) {
    	if (md->changeclimate) {    //when define this option for sp-run, remember it controls normal/dynamical weather option
        	atm->beginOfMonth(inputyrind,currmind,dinmcurr, false, false, md->changeco2);
    	} else {
        	atm->beginOfMonth(inputyrind,currmind,dinmcurr, true, false, md->changeco2);
    	}
    } else {
    	atm->beginOfMonth(inputyrind,currmind,dinmcurr, false, md->changeclimate, md->changeco2);
    }

 	if(currmind==0){ //begin of year
		ed->beginOfYear();
	} 
	
	ed->y_vegd.vegfrac =1;
	
	//if(currmind>=5 && currmind<=9){  //for warm season
		
		if(cd->vegtype ==0){
		   ed->d_soid.nfactor =1;      //tundra	
		}else if(cd->vegtype==1){      //aspen
		   ed->d_soid.nfactor = 0.94;  //derived from tower
		}else{
		    if(fd->ysf <ve.envpar.matureage){
		        ed->d_soid.nfactor = 1.1 -(fd->ysf)/ve.envpar.matureage * (1.1 -0.66);	
		     }else{
		     	ed->d_soid.nfactor =0.66; 
		     }
		}
    
    //}else{
    //   	ed->d_soid.nfactor =1;
    //}
      
	//when the soil carbon changed, the soil layer thickness will change, and the thickness
	//might become too small or too big , so there is a need to combine or divide a layer	
	double meandayl = gd->alldaylengths[currmind*30+15];
	ve.updateEnvLai(currmind, bd->m_vegd.lai);
	ve.beginOfMonth(meandayl);//update some variables which will not change in one month
	
	ed->beginOfMonth();
		
	for(int id =0; id<dinmcurr; id++){

        ed->beginOfDay();
        
        int doy =timer->getDOYIndex(currmind, id);
         
		daylength = gd->alldaylengths[doy];
		
		//Yuan: climate change OR NOT:
//        atm->updateDailyEnviron(yrcnt, currmind, id, equiled, spined);
		if (md->runeq) {
			atm->updateDailyEnviron(yrcnt, currmind, id, true, false);   //normal: averaged over first 30-yrs
		} else if(md->runsp){
			if (md->changeclimate) {
				atm->updateDailyEnviron(yrcnt, currmind, id, false, false);  //dynamical, but only the first 30-yrs
			} else {
				atm->updateDailyEnviron(yrcnt, currmind, id, true, false);   //normal: averaged over first 30-yrs
			}
		} else {
			atm->updateDailyEnviron(yrcnt, currmind, id, false, true);   //dynamical: over the whole data
		}

		tdrv = ed->d_atms.ta;  
		 
	    // for some factors from other components
		ed->d_vegd.btran =  ground.getSoilTransFactor();
		
		// calculate vegetation water dynamics
		ve.updateDaily(daylength);
		// ground/soil water dynamics
		ground.updateDaily(yrcnt, calyr, currmind, id, tdrv, daylength);
		
		ground.soil.layer2structdaily(ground.fstsoill);
		ground.soil.retrieveDailyOutputs(ground.fstsoill,ground.fstminl, ground.lstminl, ground.backl);
        ground.soil.retrieveDailyFronts(ground.fstsoill);
        ground.snow.retrieveDailyOutputs(ground.frontl);
		ed->endOfDay(dinmcurr, doy);//accumulate daily var into monthly var    

//	    #ifdef ODAY
		if(outSiteDay){
	      	updateSiteDlyOutputBuffer_Env(doy);
	    }
//	    #endif
		    		
		if(id==dinmcurr-1){	// at end of one month
     		ground.soil.layer2structmonthly(ground.fstsoill);
      		ed->endOfMonth(currmind,assigneq);

     		if (outSiteMonth) {
   				updateSiteMlyOutputBuffer_Env(currmind);
     		}

     		//Yuan: for output soil climate variables
     		if (outSoilClm) {
     			updateSclmOutputBuffer(currmind);
     		}
		}
	}
	
	if(currmind==11){ 	
	  	ed->endOfYear(assigneq);
	  	
	  	if (outSiteYear) {
  			updateSiteYlyOutputBuffer_Env();
	  	}
    }
	
};

///////////////////////////////////////////////////////////////////////////////////////////
// Biogeochemical Module Calling at monthly timestep
///////////////////////////////////////////////////////////////////////////////////////////
void Cohort::updateMonthly_Bgc(const int & yrcnt,const int &  calyr, 
			const int & currmind, const int & dinmcurr, const bool & useeq){
		 
	if(useeq){
		ed->m_atms.ta = ed->eq_ta[currmind];
		ed->m_atms.co2 = ed->eq_co2[currmind];
		ed->m_l2a.pet = ed->eq_pet[currmind];
		ed->m_l2a.eet= ed->eq_eet[currmind];
		ed->m_a2l.par = ed->eq_par[currmind];
		ed->m_soid.growpct = ed->eq_grow[currmind];
		    
		for(int il =0; il<MAX_SOI_LAY; il++){
			ed->m_sois.ts[il] = ed->eq_ts[currmind][il];
		    ed->m_sois.liq[il] = ed->eq_liq[currmind][il];
		    ed->m_sois.ice[il] = ed->eq_ice[currmind][il];
		    ed->m_soid.allvwc[il] = ed->eq_vwc[currmind][il];
		    ed->m_soid.allsws[il] = ed->eq_sws[currmind][il];
		    ed->m_soid.allaws[il] = ed->eq_aws[currmind][il];
		}
		    
		if(currmind==0){
			ed->y_l2a.pet = ed->eq_y_pet;
		 	ed->y_l2a.eet = ed->eq_y_eet;
		 	ed->y_atms.co2 = ed->eq_y_co2;
		 	ed->prvpetmx = ed->eq_prvpetmx;
		 	ed->prveetmx = ed->eq_prveetmx;		 	  
		}
	}
		 
	if(currmind==0){		
	    sb.updateKdyrly4all(yrcnt);  //since it is hard to get equilibrated if kd is changed during equilibrium run.
		bd->beginOfYear();	
	}

	sb.prepareIntegration();
	vb.prepareIntegration(equiled);
		 
	integrator.updateMonthly();
		
	//update topt and unleafmx in vegbgc
	vb.updateToptUnleafmx(currmind);
		 
	//at end of biogeochemistry processes, the layer should be changed
    //update the soil layer related variables
    sb.afterIntegration();
    vb.afterIntegration();
    bd->endOfMonth(currmind);

	if (outSiteMonth) {
		 updateSiteMlyOutputBuffer_Bgc(currmind);
	}
		 		 
	if(currmind==11){
		vb.adapt();
		bd->endOfYear(sb.bgcpar.cnsoil);

		if (outSiteYear) {
  			updateSiteYlyOutputBuffer_Bgc();
		}	  	
			
	}

};

void Cohort::getLitterFallRatio(double & deepvsshlw, double & minevsshlw){
	double shlwroot=0;
	double deeproot=0;
	double mineroot=0;
	
	double shlwltrfal=0;
	double deepltrfal=0;
	double mineltrfal=0;
 
	int numshlw=0;
	int numdeep=0;
	int nummine=0;
	for(int il = 0; il<MAX_SOI_LAY;il++){
		if(ed->m_sois.rootfrac[il]>0.01){
			if(ed->m_sois.type[il]==1){
 		 	 	shlwroot += ed->m_sois.rootfrac[il];
 		 	 	numshlw++;
			}else if(ed->m_sois.type[il] ==2){
			 	deeproot+= ed->m_sois.rootfrac[il];
 		 	 	numdeep++;
			}else if(ed->m_sois.type[il]==3){
			 	mineroot+= ed->m_sois.rootfrac[il];
 		 	 	nummine++;
			}
		}
 	}
 	
 	shlwltrfal = 0.431 +0.569*shlwroot;
 	deepltrfal = 0.569* deeproot;
 	mineltrfal = 0.569* mineroot;
    deepvsshlw = deepltrfal/shlwltrfal;
    minevsshlw = mineltrfal/shlwltrfal;
};

void Cohort::updateSiteDlyOutputBuffer_Env(const int& doy){
///////vegetation
	
	    vegod->sinterd[doy] = ed->d_vegd.sinter; 
	    vegod->rinterd[doy] = ed->d_vegd.rinter; 
	    vegod->sthfld[doy] = ed->d_v2g.sthfl; 
	    vegod->rthfld[doy] = ed->d_v2g.rthfl; 
	    vegod->sdripd[doy] = ed->d_v2g.sdrip; 
	    vegod->rdripd[doy] = ed->d_v2g.rdrip; 
	    vegod->scanopyd[doy] = ed->d_vegs.snow; 
	    vegod->rcanopyd[doy] = ed->d_vegs.rain; 
	    vegod->cansubd[doy] = ed->d_v2a.sublim; 
	    vegod->canevpd[doy] = ed->d_v2a.evapo; 
	    vegod->cantrsd[doy] = ed->d_v2a.trans; 
	        
	    vegod->racd[doy] = ed->d_vegd.rac; 
	    vegod->radrefld[doy] = ed->d_v2a.solrad; 
	    vegod->radthroud[doy] = ed->d_v2g.sw; 
	    
	    vegod->btrand[doy] = ed->d_vegd.btran; 
	  
	    vegod->m_ppfdd[doy] = ed->d_vegd.m_ppfd;
	    vegod->m_vpdd[doy] = ed->d_vegd.m_vpd;
	      
	    vegod->ccd[doy] = ed->d_vegd.cc; 

 	//atmosphere
 		atmod->tdrvd[doy] = ed->d_atms.ta; 					 	
 		atmod->raind[doy] = ed->d_a2l.rnfl; 					 	
 		atmod->snowd[doy] = ed->d_a2l.snfl; 
 		atmod->svpd[doy] = ed->d_atmd.svp; 					 	
 		atmod->dersvpd[doy] = ed->d_atmd.dersvp; 					 	
 		atmod->rhoad[doy] = ed->d_atmd.rhoa; 
 		atmod->abshdd[doy] = ed->d_atmd.abshd; 
 		atmod->dsrd[doy] = ed->d_atms.dsr; 
	
 	//snow-soil
		sslod->infild[doy] = ed->d_l2soi.perc;
		sslod->wtd[doy] = ed->d_soid.watertab;
		sslod->fsatd[doy] = ed->d_soid.frasat;
		sslod->qoverd[doy] = ed->d_soi2l.qover;
		sslod->qdraind[doy] = ed->d_soi2l.qdrain;
		sslod->growd[doy]=ed->d_soid.growpct;
		sslod->slradrefld[doy] = ed->d_soi2a.solrad;
		sslod->sevapd[doy] = ed->d_soi2a.evap;
		for(int il =0; il<MAX_OUT_SOI; il++){
			 sslod->tsd[doy][il] = ed->d_soid.tem[il];
			 sslod->tcondd[doy][il] = ed->d_soid.tcond[il];

			 sslod->liqd[doy][il] = ed->d_soid.alllwc[il];
			 sslod->iced[doy][il] = ed->d_soid.alliwc[il];
			 
			 //2D to 1D
			 sslod->tsd1D[doy*MAX_OUT_SOI+il] = ed->d_soid.tem[il];
			 sslod->tcondd1D[doy*MAX_OUT_SOI+il] = ed->d_soid.tcond[il];
			 sslod->liqd1D[doy*MAX_OUT_SOI+il] = ed->d_soid.alllwc[il];
			 sslod->iced1D[doy*MAX_OUT_SOI+il] = ed->d_soid.alliwc[il];
			 
		}
		
		sslod->aldd[doy] = ed->d_ald;

		for(int il=0;il<MAX_NUM_FNT;il++){
			 sslod->frzfnt[doy][il] = ed->d_soid.frzfnt[il];
			 sslod->thwfnt[doy][il] =ed->d_soid.thwfnt[il];
			 
			 //2D to 1D
			 sslod->frzfnt1D[doy*MAX_NUM_FNT+il] = ed->d_soid.frzfnt[il];
			 sslod->thwfnt1D[doy*MAX_NUM_FNT+il] =ed->d_soid.thwfnt[il];
			 
		}
		 sslod->numiter[doy] =ed->d_soid.itnum;
		 sslod->numiterliq[doy] =ed->d_soid.itnumliq; 

	     sslod->snowthick[doy] = ed->d_snws.thick;		
		 sslod->swed[doy] = ed->d_snws.swe;
		 sslod->smeltd[doy] = ed->d_snwd.melt;
		 sslod->ssubld[doy] = ed->d_snw2a.sublim;
	     sslod->snradrefld[doy] = ed->d_snw2a.solrad;
 	
 };

void Cohort::updateSiteMlyOutputBuffer_Env(const int & im){
 	///////////////////////////////
 	///vegetation
	   	vegod->btran[im] = ed->m_vegd.btran;
	   	vegod->rc[im] = ed->m_vegd.rc;
	   	vegod->rac[im] =ed->m_vegd.rac;
	   	vegod->trans[im]= ed->m_v2a.trans;
	   	vegod->vevap[im]= ed->m_v2a.evapo;
	   	vegod->vsubl[im]= ed->m_v2a.sublim;
	   	vegod->rinter[im]= ed->m_vegd.rinter;
	   	vegod->sinter[im]= ed->m_vegd.sinter;
	   	vegod->rthfl[im]= ed->m_v2g.rthfl;
	   	vegod->sthfl[im]= ed->m_v2g.sthfl;
	   	vegod->radthfl[im]= ed->m_v2g.sw;
	
	/// atmosphere
	
	   	atmod->ta[im] =ed->m_atms.ta;
	   	atmod->clds[im] =ed->m_atms.clds;
	   	atmod->co2[im] =ed->m_atms.co2;
	   	atmod->eet[im] =ed->m_l2a.eet;
	   	atmod->pet[im] =ed->m_l2a.pet;
	   	atmod->rnfl[im] =ed->m_a2l.rnfl;
	   	atmod->snfl[im] =ed->m_a2l.snfl;
	   	atmod->girr[im] =ed->m_a2l.girr;
	   	atmod->nirr[im] =ed->m_a2l.nirr;
	   	atmod->par[im] =ed->m_a2l.par;

 	//soil
	   	for(int il =0;il<MAX_OUT_SOI; il++){
	    	sslod->z[im][il]= ed->m_sois.z[il];
	    	sslod->type[im][il]= ed->m_sois.type[il];
	    	sslod->por[im][il]= ed->m_sois.por[il];
	    	sslod->dz[im][il] =ed->m_sois.dz[il];  
	    	sslod->ts[im][il] =ed->m_soid.tem[il];
	    	sslod->liq[im][il] =ed->m_soid.alllwc[il];
	    	sslod->vwc[im][il] =ed->m_soid.allvwc[il];
	    	sslod->ice[im][il] =ed->m_soid.alliwc[il];
	    		
	    	//2D to 1D (for java data read)
	    	sslod->z1D[im*MAX_OUT_SOI+il] =ed->m_sois.z[il];  
	    	sslod->type1D[im*MAX_OUT_SOI+il] =ed->m_sois.type[il];  
	    	sslod->por1D[im*MAX_OUT_SOI+il] =ed->m_sois.por[il];  
	    	sslod->dz1D[im*MAX_OUT_SOI+il] =ed->m_sois.dz[il];  
	    	sslod->ts1D[im*MAX_OUT_SOI+il] =ed->m_soid.tem[il];
	    	sslod->liq1D[im*MAX_OUT_SOI+il] =ed->m_soid.alllwc[il];
	    	sslod->vwc1D[im*MAX_OUT_SOI+il] =ed->m_soid.allvwc[il];
	    	sslod->ice1D[im*MAX_OUT_SOI+il] =ed->m_soid.alliwc[il];
	    }
	    sslod->ald[im] =ed->m_ald;   //Yuan:
	    
	   	sslod->ssubl[im] = ed->m_snw2a.sublim;
	   	sslod->sninfl[im] =ed->m_snw2soi.infl;
	   	sslod->sevap[im] =ed->m_soi2a.evap;
	   
	    sslod->watertab[im] =ed->m_soid.watertab;
	   
	   	sslod->mossdz[im] =ed->m_soid.mossthick;
	   	sslod->shlwdz[im] =ed->m_soid.shlwthick;
	    sslod->deepdz[im] =ed->m_soid.deepthick;
 
};
 
void Cohort::updateSiteMlyOutputBuffer_Bgc(const int & im){
 	///////////////////////////////
 	///vegetation
	   	vegod->vegc[im] =bd->m_vegs.c;
	   	vegod->strn[im] =bd->m_vegs.strn;
	   	vegod->ston[im] =bd->m_vegs.ston;
	   	vegod->ingpp[im] =bd->m_a2v.ingpp;
	   	vegod->gpp[im] =bd->m_a2v.gpp;
	   	vegod->innpp[im] =bd->m_a2v.innpp;
	   	vegod->npp[im] =bd->m_a2v.npp;
	   	vegod->rm[im] =bd->m_v2a.rm;
	   	vegod->rg[im] =bd->m_v2a.rg;
	   	vegod->ltrfalc[im] =bd->m_v2soi.ltrfalc;
	   	vegod->ltrfaln[im] =bd->m_v2soi.ltrfaln;
	   	vegod->innuptake[im] =bd->m_soi2v.innuptake;
	   	vegod->nuptake[im] =bd->m_soi2v.nuptake;
	   	vegod->luptake[im] =bd->m_soi2v.luptake;
	   	vegod->suptake[im] =bd->m_soi2v.suptake;
	   	vegod->nresorb[im] =bd->m_v2v.nresorb;
	   	vegod->nmobil[im] =bd->m_v2v.nmobil;
	   	vegod->lai[im] =bd->m_vegd.lai;
	   	vegod->fpc[im] =bd->m_vegd.fpc;
	   	vegod->unnormleaf[im] =bd->m_vegs.unnormleaf;
	   	vegod->leaf[im] =bd->m_vegd.leaf;
	   	vegod->foliage[im] =bd->m_vegd.foliage;	   	
 	 	
	    for(int il =0;il<MAX_OUT_SOI; il++){	
	   
	   	    sslod->reac[im][il]= bd->m_sois.reac[il];
			sslod->nonc[im][il]= bd->m_sois.nonc[il];			  
	   		sslod->rrh[im][il]= bd->m_soi2a.rrh[il];
	   		sslod->nrh[im][il]= bd->m_soi2a.nrh[il];
		    sslod->rhmoist[im][il]= bd->m_soid.rhmoist[il];
		    sslod->rhq10[im][il]= bd->m_soid.rhq10[il];
	   		sslod->ksoil[im][il]= bd->m_soid.ksoil[il];
	    	sslod->kdl[im][il]= bd->m_soid.kdl[il];
	    	sslod->kdr[im][il]= bd->m_soid.kdr[il];
	    	sslod->kdn[im][il]= bd->m_soid.kdn[il];
	    
	    	//2D to 1D (for Java data reading)
	    	sslod->reac1D[im*MAX_OUT_SOI+il]= bd->m_sois.reac[il];
			sslod->nonc1D[im*MAX_OUT_SOI+il]= bd->m_sois.nonc[il];			  
	   		sslod->rrh1D[im*MAX_OUT_SOI+il]= bd->m_soi2a.rrh[il];
	   		sslod->nrh1D[im*MAX_OUT_SOI+il]= bd->m_soi2a.nrh[il];
		    sslod->rhmoist1D[im*MAX_OUT_SOI+il]= bd->m_soid.rhmoist[il];
		    sslod->rhq101D[im*MAX_OUT_SOI+il]= bd->m_soid.rhq10[il];
	   		sslod->ksoil1D[im*MAX_OUT_SOI+il]= bd->m_soid.ksoil[il];
	    	sslod->kdl1D[im*MAX_OUT_SOI+il]= bd->m_soid.kdl[il];
	    	sslod->kdr1D[im*MAX_OUT_SOI+il]= bd->m_soid.kdr[il];
	    	sslod->kdn1D[im*MAX_OUT_SOI+il]= bd->m_soid.kdn[il];
	   	}	
	   	
	    sslod->ninput[im]=bd->m_a2soi.ninput;
	   	sslod->nlost[im]= bd->m_soi2l.nlost;
	   	sslod->netnmin[im]= bd->m_soi2soi.netnmin;
	   	sslod->nimmob[im]= bd->m_soi2soi.nimmob;
	    sslod->orgn[im]= bd->m_sois.orgn;
	   	sslod->avln[im]= bd->m_sois.avln;
	   	sslod->reacsum[im]= bd->m_soid.reacsum;
	   	sslod->noncsum[im]= bd->m_soid.noncsum;
   		sslod->shlwcsum[im]= bd->m_soid.shlwc;
   		sslod->deepcsum[im]= bd->m_soid.deepc;
   		sslod->minecsum[im]= bd->m_soid.minec;

	  	sslod->growpct[im] =ed->m_soid.growpct;

};
 
void Cohort::updateSiteYlyOutputBuffer_Fir(){
	sslod->yrburnthick =fd->y_soid.burnthick;
	sslod->yrburnsoilc =fd->y_soi2a.orgc;
	sslod->yrburnsoiln =fd->y_soi2a.orgn;
	sslod->yrorgnreturn =fd->y_a2soi.orgn;
	
	vegod->yrburnorgc = fd->y_v2a.orgc;
	vegod->yrburnorgn = fd->y_v2a.orgn;
};

void Cohort::updateSiteYlyOutputBuffer_Env(){
	//vegetation
	vegod->yrevapo = ed->y_v2a.evapo;
	vegod->yrsublim = ed->y_v2a.sublim;
	vegod->yrtrans =ed->y_v2a.trans;

	//atmosphere
	atmod->yrrnfl=ed->y_a2l.rnfl;
	atmod->yrsnfl=ed->y_a2l.snfl;
	atmod->yrta =ed->y_atms.ta;
	   	
	//soil
    sslod->yrsevap = ed->y_soi2a.evap;
	sslod->yrqover = ed->y_soi2l.qover;
	sslod->yrqdrain = ed->y_soi2l.qdrain;
	sslod->yrssubl = ed->y_snw2a.sublim;
	sslod->yrliqsum  = ed->y_sois.liqsum;
	sslod->yricesum  = ed->y_sois.icesum;
	sslod->yrtsave   = ed->y_sois.tsave;

	sslod->yrtshlw = 0.; sslod->yrvwcshlw= 0.;
	sslod->yrtdeep = 0.; sslod->yrvwcdeep= 0.;
	sslod->yrtmine = 0.; sslod->yrvwcmine= 0.;
	int lynum1=0;
	int lynum2=0;
	int lynum3=0;
	bool isfirstmine=true;
	for (int il=0; il<=MAX_OUT_SOI; il++){
		if(ed->y_sois.type[il]==1){
			sslod->yrtshlw+=ed->y_soid.tem[il];
			sslod->yrvwcshlw+=ed->y_soid.allvwc[il];
			lynum1+=1;
		}else if(ed->y_sois.type[il]==2){
			sslod->yrtdeep+=ed->y_soid.tem[il];
			sslod->yrvwcdeep+=ed->y_soid.allvwc[il];
			lynum2+=1;
		}else if(ed->y_sois.type[il]==3){
			sslod->yrtmine+=ed->y_soid.tem[il];
			sslod->yrvwcmine+=ed->y_soid.allvwc[il];
			if (isfirstmine) {
				sslod->yrvwcmin10=ed->y_soid.allvwc[il];
				isfirstmine = false;
			}
			lynum3+=1;
		}
	}
	if (lynum1>0) {
		sslod->yrtshlw/=lynum1;
		sslod->yrvwcshlw/=lynum1;
	} else {
		sslod->yrtshlw = -999;
		sslod->yrvwcshlw = -999;
	}
	if (lynum2>0) {
		sslod->yrtdeep/=lynum2;
		sslod->yrvwcdeep/=lynum2;
	} else {
		sslod->yrtdeep = -999;
		sslod->yrvwcdeep = -999;
	}
	if (lynum3>0) {
		sslod->yrtmine/=lynum3;
		sslod->yrvwcmine/=lynum3;
	} else {
		sslod->yrtmine = -999;
		sslod->yrvwcmine = -999;
	}
	sslod->yrtmin10 = ed->y_soid.tmineral10cm;

	sslod->yrald =ed->y_ald;
	sslod->yrperm =ed->permafrost;
	sslod->yrmossdz =ed->y_soid.mossthick;
	sslod->yrshlwdz =ed->y_soid.shlwthick;
	sslod->yrdeepdz =ed->y_soid.deepthick;
	sslod->yrwatertab=ed->y_soid.watertab;	
 	sslod->yrmossnum= ed->y_soid.mossnum;
	sslod->yrshlwnum= ed->y_soid.shlwnum;
	sslod->yrdeepnum= ed->y_soid.deepnum; 

};

void Cohort::updateSiteYlyOutputBuffer_Bgc(){
	//vegetation
	vegod->yrc2n = bd->c2n;
	
	vegod->yrnpp = bd->y_a2v.npp;
	vegod->yrrm = bd->y_v2a.rm;
	vegod->yrrg = bd->y_v2a.rg;
	vegod->yrltrfalc = bd->y_v2soi.ltrfalc;
	vegod->yrltrfaln = bd->y_v2soi.ltrfaln;
	vegod->yrvnuptake = bd->y_soi2v.nuptake;
	
	vegod->yrabvgndc = bd->y_vegd.abvgndc;	
	vegod->yrfoliage = bd->y_vegd.foliage;
	vegod->yrleaf = bd->y_vegd.leaf;
	vegod->yrlai = bd->y_vegd.lai;
	vegod->yrfpc = bd->y_vegd.fpc;
	
	vegod->yrvegc =bd->y_vegs.c;
	vegod->yrstrn =bd->y_vegs.strn;
	vegod->yrston =bd->y_vegs.ston;
    
	//snow-soil
	sslod->yrnetnmin = bd->y_soi2soi.netnmin;
    sslod->yrrrhsum =   bd->y_soid.rrhsum;
    sslod->yrnrhsum =   bd->y_soid.nrhsum;
    
    sslod->yrreacsum =bd->y_soid.reacsum;
    sslod->yrnoncsum =bd->y_soid.noncsum;
    
    sslod->yrshlwcsum =bd->y_soid.shlwc;
    sslod->yrdeepcsum =bd->y_soid.deepc;
    sslod->yrminecsum =bd->y_soid.minec;
    
    sslod->yrorgn =bd->y_sois.orgn;
    sslod->yravln =bd->y_sois.avln;
    sslod->yrsnuptake=bd->y_soi2v.nuptake;
    
    sslod->yrwdebris =bd->y_sois.wdebris;
    sslod->yrwdrh =bd->y_soi2a.wdrh;    

    sslod->yrninput =bd->y_a2soi.ninput;   //Yuan: for checking
    sslod->yrnlost  =bd->y_soi2l.nlost;     //Yuan: for checking
    
};

void Cohort::updateRegionalOutputBuffer(const int & im){
	
	if (im==0) {
		if(md->runeq) regnod->chtid = cd->eqchtid;
		if(md->runsp) regnod->chtid = cd->spchtid;
		if(md->runtr) regnod->chtid = cd->trchtid;
	}

	if (im==11) {
		regnod->status = errorid;
		regnod->ysf =fd->ysf;
	}

	//the following is always yearly
	if (regnod->outvarlist[0]>=1 && im==11) {
		regnod->burnthick = fd->y_soid.burnthick;}

	if (regnod->outvarlist[1]>=1 && im==11) {
		regnod->burnsoic = fd->y_soi2a.orgc;}

	if (regnod->outvarlist[2]>=1 && im==11) {
		regnod->burnvegc = fd->y_v2a.orgc;}

	if (regnod->outvarlist[3]>=1 && im==11) {
		if(ed->y_soid.growstart<=0){ //for seasonal frost area
			regnod->growstart= ed->y_soid.snowfree1st;
		}else{ 	//for permafrost area
			regnod->growstart= ed->y_soid.growstart;
		}
	}

	if (regnod->outvarlist[4]>=1 && im==11) {
		regnod->growend= ed->y_soid.growend;}

	if (regnod->outvarlist[5]>=1 && im==11) {
		regnod->perm =ed->permafrost;}

	if (regnod->outvarlist[6]>=1 && im==11) {
		regnod->mossdz =ed->y_soid.mossthick;}

	if (regnod->outvarlist[7]>=1 && im==11) {
		regnod->shlwdz =ed->y_soid.shlwthick;}

	if (regnod->outvarlist[8]>=1 && im==11) {
		regnod->deepdz =ed->y_soid.deepthick;}

	//The following either at yearly or monthly

	if (regnod->outvarlist[9]==1 && im==11) {
		regnod->lai[0] =bd->y_vegd.lai;       //note: the yearly was in var[0]
	} else if (regnod->outvarlist[9]==2) {
		regnod->lai[im] =bd->m_vegd.lai;
	}

	if (regnod->outvarlist[10]==1 && im==11) {
		regnod->vegc[0] = bd->y_vegs.c;
	} else if (regnod->outvarlist[10]==2) {
		regnod->vegc[im] = bd->m_vegs.c;
	}

	if (regnod->outvarlist[11]==1 && im==11) {
		regnod->vegn[0] =bd->y_vegs.strn + bd->y_vegs.ston;
	} else if (regnod->outvarlist[11]==2) {
		regnod->vegn[im] =bd->m_vegs.strn + bd->m_vegs.ston;
	}

	if (regnod->outvarlist[12]==1 && im==11) {
		regnod->gpp[0] = bd->y_a2v.gpp;
	} else if (regnod->outvarlist[12]==2) {
		regnod->gpp[im]= bd->m_a2v.gpp;
	}

	if (regnod->outvarlist[13]==1 && im==11) {
		regnod->npp[0] = bd->y_a2v.npp;
	} else if (regnod->outvarlist[13]==2) {
		regnod->npp[im]= bd->m_a2v.npp;
	}

	if (regnod->outvarlist[14]==1 && im==11) {
		regnod->rh[0]  = bd->y_soid.rrhsum + bd->y_soid.nrhsum;
	} else if (regnod->outvarlist[14]==2) {
		regnod->rh[im] = bd->m_soid.rrhsum + bd->m_soid.nrhsum;
	}

	if (regnod->outvarlist[15]==1 && im==11) {
		regnod->ltrfalc[0] =bd->y_v2soi.ltrfalc;
	} else if (regnod->outvarlist[15]==2) {
		regnod->ltrfalc[im] =bd->m_v2soi.ltrfalc;
	}

	if (regnod->outvarlist[16]==1 && im==11) {
		regnod->ltrfaln[0] =bd->y_v2soi.ltrfaln;
	} else if (regnod->outvarlist[16]==2) {
		regnod->ltrfaln[im] =bd->m_v2soi.ltrfaln;
	}

	if (regnod->outvarlist[17]==1 && im==11) {
		regnod->shlwc[0]  =bd->y_soid.shlwc;
	} else if (regnod->outvarlist[17]==2) {
		regnod->shlwc[im] =bd->m_soid.shlwc;
	}

	if (regnod->outvarlist[18]==1 && im==11) {
		regnod->deepc[0] =bd->y_soid.deepc;
	} else if (regnod->outvarlist[18]==2) {
		regnod->deepc[im] =bd->m_soid.deepc;
	}

	if (regnod->outvarlist[19]==1 && im==11) {
		regnod->minec[0] =bd->y_soid.minec;
	} else if (regnod->outvarlist[19]==2) {
		regnod->minec[im] =bd->m_soid.minec;
	}

	if (regnod->outvarlist[20]==1 && im==11) {
		regnod->orgn[0] =bd->y_sois.orgn;
	} else if (regnod->outvarlist[20]==2) {
		regnod->orgn[im] =bd->m_sois.orgn;
	}

	if (regnod->outvarlist[21]==1 && im==11) {
		regnod->avln[0] =bd->y_sois.avln;
	} else if (regnod->outvarlist[21]==2) {
		regnod->avln[im] =bd->m_sois.avln;
	}

	if (regnod->outvarlist[22]==1 && im==11) {
		regnod->netnmin[0] =bd->y_soi2soi.netnmin;
	} else if (regnod->outvarlist[22]==2) {
		regnod->netnmin[im] =bd->m_soi2soi.netnmin;
	}

	if (regnod->outvarlist[23]==1 && im==11) {
		regnod->nuptake[0] =bd->y_soi2v.nuptake;
	} else if (regnod->outvarlist[23]==2) {
		regnod->nuptake[im] =bd->m_soi2v.nuptake;
	}

	if (regnod->outvarlist[24]==1 && im==11) {
		regnod->ninput[0] = bd->y_a2soi.ninput;
	} else if (regnod->outvarlist[24]==2) {
		regnod->ninput[im] = bd->m_a2soi.ninput;
	}

	if (regnod->outvarlist[25]==1 && im==11) {
		regnod->nlost[0] = bd->y_soi2l.nlost;
	} else if (regnod->outvarlist[25]==2) {
		regnod->nlost[im] = bd->m_soi2l.nlost;
	}

	if (regnod->outvarlist[26]==1 && im==11) {
		regnod->eet[0]  = ed->y_l2a.eet;
	} else if (regnod->outvarlist[26]==2) {
		regnod->eet[im] = ed->m_l2a.eet;
	}

	if (regnod->outvarlist[27]==1 && im==11) {
		regnod->pet[0]  = ed->y_l2a.pet;
	} else if (regnod->outvarlist[27]==2) {
		regnod->pet[im] = ed->m_l2a.pet;
	}

	if (regnod->outvarlist[28]==1 && im==11) {
		regnod->qdrain[0] = ed->y_soi2l.qdrain;
	} else if (regnod->outvarlist[28]==2) {
		regnod->qdrain[im]= ed->m_soi2l.qdrain;
	}

	if (regnod->outvarlist[29]==1 && im==11) {
		regnod->qrunoff[0] = ed->y_soi2l.qover;
	} else if (regnod->outvarlist[29]==2) {
		regnod->qrunoff[im]= ed->m_soi2l.qover;
	}

	if (regnod->outvarlist[30]==1 && im==11) {
		regnod->snowthick[0] = ed->y_snws.thick;
	} else if (regnod->outvarlist[30]==2) {
		regnod->snowthick[im] = ed->m_snws.thick;
	}

	if (regnod->outvarlist[31]==1 && im==11) {
		regnod->swe[0] = ed->y_snws.swe;
	} else if (regnod->outvarlist[31]==2) {
		regnod->swe[im]= ed->m_snws.swe;
	}
	
	if (regnod->outvarlist[32]==1 && im==11) {
		regnod->wtd[0]=ed->y_soid.watertab;
	} else if (regnod->outvarlist[32]==2) {
		regnod->wtd[im]=ed->m_soid.watertab;
	}

	if (regnod->outvarlist[33]==1 && im==11) {
		regnod->ald[0] = ed->y_ald;
	} else if (regnod->outvarlist[33]==2) {
		regnod->ald[im] = ed->m_ald;
	}

	// The following soil variables have to aggregate into 4 layer classes (otherwise too much output)
	int lynum1=0; double vwc1 =0.; double t1=0.; double hk1=0.; double tc1=0.;
	int lynum2=0; double vwc2 =0.; double t2=0.; double hk2=0.; double tc2=0.;
	int lynum3=0; double vwc3 =0.; double t3=0.; double hk3=0.; double tc3=0.;
	int lynum4=0; double vwc4 =0.; double t4=0.; double hk4=0.; double tc4=0.;
	double dtop=0.;

	for (int il=0; il<ed->m_soid.actual_num_soil; il++){
			if(ed->y_sois.type[il]==1){
				lynum1+=1;
				if (regnod->outvarlist[34]==1 && im==11) {vwc1+=ed->y_soid.allvwc[il];}
				if (regnod->outvarlist[38]==1 && im==11) {t1+=ed->y_soid.tem[il];}
				if (regnod->outvarlist[42]==1 && im==11) {hk1+=ed->y_soid.hcond[il];}
				if (regnod->outvarlist[46]==1 && im==11) {tc1+=ed->y_soid.tcond[il];}

				if (regnod->outvarlist[34]==2) {vwc1+=ed->m_soid.allvwc[il];}
				if (regnod->outvarlist[38]==2) {t1+=ed->m_soid.tem[il];}
				if (regnod->outvarlist[42]==2) {hk1+=ed->m_soid.hcond[il];}
				if (regnod->outvarlist[46]==2) {tc1+=ed->m_soid.tcond[il];}

			}else if(ed->y_sois.type[il]==2){
				lynum2+=1;
				if (regnod->outvarlist[35]==1 && im==11) {vwc2+=ed->y_soid.allvwc[il];}
				if (regnod->outvarlist[39]==1 && im==11) {t2+=ed->y_soid.tem[il];}
				if (regnod->outvarlist[43]==1 && im==11) {hk2+=ed->y_soid.hcond[il];}
				if (regnod->outvarlist[47]==1 && im==11) {tc2+=ed->y_soid.tcond[il];}

				if (regnod->outvarlist[35]==2) {vwc2+=ed->m_soid.allvwc[il];}
				if (regnod->outvarlist[39]==2) {t2+=ed->m_soid.tem[il];}
				if (regnod->outvarlist[43]==2) {hk2+=ed->m_soid.hcond[il];}
				if (regnod->outvarlist[47]==2) {tc2+=ed->m_soid.tcond[il];}

			}else if(ed->y_sois.type[il]==3){
				dtop+=ed->m_sois.dz[il];
				if (dtop<=0.20) {
					lynum3+=1;
					if (regnod->outvarlist[36]==1 && im==11) {vwc3+=ed->y_soid.allvwc[il];}
					if (regnod->outvarlist[40]==1 && im==11) {t3+=ed->y_soid.tem[il];}
					if (regnod->outvarlist[44]==1 && im==11) {hk3+=ed->y_soid.hcond[il];}
					if (regnod->outvarlist[48]==1 && im==11) {tc3+=ed->y_soid.tcond[il];}

					if (regnod->outvarlist[36]==2) {vwc3+=ed->m_soid.allvwc[il];}
					if (regnod->outvarlist[40]==2) {t3+=ed->m_soid.tem[il];}
					if (regnod->outvarlist[44]==2) {hk3+=ed->m_soid.hcond[il];}
					if (regnod->outvarlist[48]==2) {tc3+=ed->m_soid.tcond[il];}

				} else {
					lynum4+=1;
					if (regnod->outvarlist[37]==1 && im==11) {vwc4+=ed->y_soid.allvwc[il];}
					if (regnod->outvarlist[41]==1 && im==11) {t4+=ed->y_soid.tem[il];}
					if (regnod->outvarlist[45]==1 && im==11) {hk4+=ed->y_soid.hcond[il];}
					if (regnod->outvarlist[49]==1 && im==11) {tc4+=ed->y_soid.tcond[il];}

					if (regnod->outvarlist[37]==2) {vwc4+=ed->m_soid.allvwc[il];}
					if (regnod->outvarlist[41]==2) {t4+=ed->m_soid.tem[il];}
					if (regnod->outvarlist[45]==2) {hk4+=ed->m_soid.hcond[il];}
					if (regnod->outvarlist[49]==2) {tc4+=ed->m_soid.tcond[il];}

				}
			}
	}

	if (lynum1>0) {
		if (regnod->outvarlist[34]==1 && im==11) {regnod->vwcshlw[0]=vwc1/lynum1;}
		if (regnod->outvarlist[38]==1 && im==11) {regnod->tshlw[0]  =t1/lynum1;}
		if (regnod->outvarlist[42]==1 && im==11) {regnod->hkshlw[0] =hk1/lynum1;}
		if (regnod->outvarlist[46]==1 && im==11) {regnod->tcshlw[0] =tc1/lynum1;}

		if (regnod->outvarlist[34]==2) {regnod->vwcshlw[im]=vwc1/lynum1;}
		if (regnod->outvarlist[38]==2) {regnod->tshlw[im]=t1/lynum1;}
		if (regnod->outvarlist[42]==2) {regnod->hkshlw[im]=hk1/lynum1;}
		if (regnod->outvarlist[46]==2) {regnod->tcshlw[im]=tc1/lynum1;}
	}

	if (lynum2>0) {
		if (regnod->outvarlist[35]==1 && im==11) {regnod->vwcdeep[0]=vwc2/lynum2;}
		if (regnod->outvarlist[39]==1 && im==11) {regnod->tdeep[0]  =t2/lynum2;}
		if (regnod->outvarlist[43]==1 && im==11) {regnod->hkdeep[0] =hk2/lynum2;}
		if (regnod->outvarlist[47]==1 && im==11) {regnod->tcdeep[0] =tc2/lynum2;}

		if (regnod->outvarlist[35]==2) {regnod->vwcdeep[im]=vwc2/lynum2;}
		if (regnod->outvarlist[39]==2) {regnod->tdeep[im]=t2/lynum2;}
		if (regnod->outvarlist[43]==2) {regnod->hkdeep[im]=hk2/lynum2;}
		if (regnod->outvarlist[47]==2) {regnod->tcdeep[im]=tc2/lynum2;}
	}
	if (lynum3>0) {
		if (regnod->outvarlist[36]==1 && im==11) {regnod->vwcminetop[0]=vwc3/lynum3;}
		if (regnod->outvarlist[40]==1 && im==11) {regnod->tminetop[0]  =t3/lynum3;}
		if (regnod->outvarlist[44]==1 && im==11) {regnod->hkminetop[0] =hk3/lynum3;}
		if (regnod->outvarlist[48]==1 && im==11) {regnod->tcminetop[0] =tc3/lynum3;}

		if (regnod->outvarlist[36]==2) {regnod->vwcminetop[im]=vwc3/lynum3;}
		if (regnod->outvarlist[40]==2) {regnod->tminetop[im]  =t3/lynum3;}
		if (regnod->outvarlist[44]==2) {regnod->hkminetop[im] =hk3/lynum3;}
		if (regnod->outvarlist[48]==2) {regnod->tcminetop[im] =tc3/lynum3;}
	}
	if (lynum4>0) {
		if (regnod->outvarlist[37]==1 && im==11) {regnod->vwcminebot[0]=vwc4/lynum4;}
		if (regnod->outvarlist[41]==1 && im==11) {regnod->tminebot[0]  =t4/lynum4;}
		if (regnod->outvarlist[45]==1 && im==11) {regnod->hkminebot[0] =hk4/lynum4;}
		if (regnod->outvarlist[49]==1 && im==11) {regnod->tcminebot[0] =tc4/lynum4;}

		if (regnod->outvarlist[37]==2) {regnod->vwcminebot[im]=vwc4/lynum4;}
		if (regnod->outvarlist[41]==2) {regnod->tminebot[im]  =t4/lynum4;}
		if (regnod->outvarlist[45]==2) {regnod->hkminebot[im] =hk4/lynum4;}
		if (regnod->outvarlist[49]==2) {regnod->tcminebot[im] =tc4/lynum4;}
	}

	if (regnod->outvarlist[50]==1 && im==11) {regnod->trock34[0] = ed->y_soid.trock34m;}
	if (regnod->outvarlist[50]==2) {regnod->trock34[im] = ed->m_soid.trock34m;}

	// some variables averaged for soil above ALD
	regnod->somcald[im] = 0.;
	regnod->vwcald[im]  = 0.;
	regnod->tald[im]    = 0.;

	if (im==11 && (regnod->outvarlist[51]==1 || regnod->outvarlist[52]==1
			|| regnod->outvarlist[53]==1)) {
		for (int il=0; il<ed->y_soid.actual_num_soil; il++){
			double ztop = ed->y_sois.z[il];
			double zbot = ed->y_sois.z[il]+ed->y_sois.dz[il];
			double dzald = min(zbot-ztop, ed->y_ald-ztop);
			if(dzald>0.){
				if (regnod->outvarlist[51]==1)
				{regnod->somcald[0]+= (bd->y_sois.nonc[il]+bd->y_sois.reac[il])*dzald;}  //thickness-weighted

				if (regnod->outvarlist[52]==1)
				{regnod->vwcald[0]+= ed->y_soid.allvwc[il]*dzald;}  //thickness-weighted

				if (regnod->outvarlist[53]==1)
				{regnod->tald[0]+= ed->y_sois.ts[il]*dzald;}  //thickness-weighted

			} else {
				break;
			}
		}
		if (regnod->outvarlist[51]==1 && ed->y_ald>0.) regnod->somcald[0] /= ed->y_ald;  //thickness-weighted
		if (regnod->outvarlist[52]==1 && ed->y_ald>0.) regnod->vwcald[0] /= ed->y_ald;  //thickness-weighted
		if (regnod->outvarlist[53]==1 && ed->y_ald>0.) regnod->tald[0] /= ed->y_ald;  //thickness-weighted

	}

	if (regnod->outvarlist[51]==2 || regnod->outvarlist[52]==2
			|| regnod->outvarlist[53]==2) {
		for (int il=0; il<ed->m_soid.actual_num_soil; il++){
			double ztop = ed->m_sois.z[il];
			double zbot = ed->m_sois.z[il]+ed->m_sois.dz[il];
			double dzald = min(zbot-ztop, ed->m_ald-ztop);
			if(dzald>0.){
				if (regnod->outvarlist[51]==2)
				{regnod->somcald[im]+= (bd->m_sois.nonc[il]+bd->m_sois.reac[il])*dzald;}  //thickness-weighted

				if (regnod->outvarlist[52]==2)
				{regnod->vwcald[im]+= ed->m_soid.allvwc[il]*dzald;}  //thickness-weighted

				if (regnod->outvarlist[53]==2)
				{regnod->tald[im]+= ed->m_sois.ts[il]*dzald;}  //thickness-weighted

			} else {
				break;
			}
		}
		if (regnod->outvarlist[51]==2 && ed->m_ald>0.) regnod->somcald[0] /= ed->m_ald;  //thickness-weighted
		if (regnod->outvarlist[52]==2 && ed->m_ald>0.) regnod->vwcald[0] /= ed->m_ald;  //thickness-weighted
		if (regnod->outvarlist[53]==2 && ed->m_ald>0.) regnod->tald[0] /= ed->m_ald;  //thickness-weighted

	}

};

void Cohort::updateRestartOutputBuffer(const int & stage){
 	Layer* currl = ground.frontl;
 	SoilLayer*sl;
 	PeatLayer* pl;

 	resod->reinitValue();
 	
 	try {
 		if(stage==1) resod->chtid = cd->eqchtid;
 		if(stage==2) resod->chtid = cd->spchtid;
 		if(stage>=3) resod->chtid = cd->trchtid;

 	int snowcount =-1;
 	int soilcount =-1;
 	int rockcount =-1;
 	int frontcount =-1;
 	while(currl!=NULL){
 		//Snow layers
 		if(currl->isSnow()){
 		  snowcount++;
 		  resod->AGEsnow[snowcount] = currl->age;
 		  resod->DZsnow[snowcount] = currl->dz;
 		  resod->TSsnow[snowcount] = currl->tem;
 		  resod->LIQsnow[snowcount] = currl->liq;
 		  resod->ICEsnow[snowcount] = currl->ice;
 		  resod->RHOsnow[snowcount] = currl->rho;
 		
 		//Soil layers
 		}else if(currl->isSoil()){
 		  soilcount++;
 		  
 		  resod->DZsoil[soilcount] = currl->dz;
 		  resod->TSsoil[soilcount] = currl->tem;
 		  resod->LIQsoil[soilcount] = currl->liq;
 		 
 		  resod->ICEsoil[soilcount] = currl->ice;
 		  resod->FROZENsoil[soilcount] = currl->frozen;
 		 
 		  sl = dynamic_cast<SoilLayer*>(currl);
 		 
 		  if(sl->isMoss()){
 			  resod->TYPEsoil[soilcount] = 0;
 		  }else if(sl->isPeat()){
 			  pl = dynamic_cast<PeatLayer*>(currl);
 		  	  if(pl->isFibric){
 		  		  resod->TYPEsoil[soilcount] =1;
 		  	  }else if(pl->isHumic){
 		  		  resod->TYPEsoil[soilcount] =2;
 		  	  }
 		  }else if(sl->isMineral()){
 		  	  resod->TYPEsoil[soilcount] = 3;
 		  }
 		  
 		  if(sl->fronts.size()>0){
 		  	  if(sl->frozen !=0 ){
 		  	      cout <<"error of soil frozne state when exist fronts\n";	
 		  	  }
   		      for(unsigned int i =0;i<sl->fronts.size();i++){
   		    	  frontcount++;
   		    	  resod->frontFT[frontcount] = sl->fronts[i]->frzing;
   		    	  resod->frontZ[frontcount] = sl->z  + sl->fronts[i]->dz;
   		      }	
   		  }
 		  
 		//rock layers
 		}else if (currl->isRock()){
 		  rockcount++;
 		  resod->DZrock[rockcount] = currl->dz;
 		  resod->TSrock[rockcount] = currl->tem;
 		}
 		
 		currl =currl->nextl;	
 	}
 	
 	for(int il =0; il<MAX_SOI_LAY ; il++){
 		if(resod->TYPEsoil[il] >=0){
 	      resod->NONCsoil[il] =bd->m_sois.nonc[il];
 		  resod->REACsoil[il] =bd->m_sois.reac[il];
 		}
 	}
 	
 	for(int il =0; il<MAX_MIN_LAY ; il++){
 		resod->TYPEmin[il] =ground.soil.mineral.type[il];
 	}
 	
 	resod->perma = ed->permafrost;

 	resod->vegc = bd->m_vegs.c;
 	resod->deadc = bd->m_vegs.deadc;
 	resod->deadn = bd->m_vegs.deadn;
 	resod->unnormleaf = bd->m_vegs.unnormleaf;
 	resod->prvunnormleafmx = bd->prvunleafmx;
 	resod->foliagemx = bd->foliagemx;
 	
 	resod->prvtopt = bd->prvtopt;
 	
 	resod->strn = bd->m_vegs.strn;
 	resod->ston = bd->m_vegs.ston;
 		
 	resod->soln = bd->m_sois.orgn;
 	resod->avln = bd->m_sois.avln;
 	resod->wdebris = bd->m_sois.wdebris;
 	
 	resod->prveetmx = ed->prveetmx;
 	resod->prvpetmx = ed->prvpetmx;
 	resod->c2n = bd->c2n;
 	resod->kdfib = bd->kdfib;
 	resod->kdhum = bd->kdhum;
 	resod->kdmin = bd->kdmin;
 	resod->kdslow = bd->kdslow;
 	
 	resod->lai = bd->m_vegd.lai;
	
 	resod->ysf = fd->ysf;
 	resod->burnedn = fd->y_a2soi.orgn;
  
 	for(unsigned int i=0; i<ed->eetmxque.size();i++){
 		if(i<10){
 			resod->eetmxA[i] = ed->eetmxque[i];
 		}	
 	}
 	
 	for(unsigned int i=0; i<ed->petmxque.size();i++){
 		if(i<10){
 			resod->petmxA[i] = ed->petmxque[i];
 		}	
 	}
 	
 	for(unsigned int i=0; i<bd->toptque.size();i++){
 		if(i<10){
 			resod->toptA[i] = bd->toptque[i];
 		}	
 	}
 	
 	for(unsigned  int i=0; i<bd->unleafmxque.size();i++){
 		if(i<10){
 			resod->unnormleafmxA[i] = bd->unleafmxque[i];
 		}	
 	}
 	
 	} catch (Exception &exception) {
  		exception.mesg();
 	}
};

void Cohort::updateSclmOutputBuffer(const int &im){ //Monthly

 	try {

 		sclmod->drg   = cd->drgtype;
 		sclmod->numsl = ed->m_sois.numsl;

	   	for(int il =0;il<MAX_SOI_LAY; il++){
	    	sclmod->type[il] = (int)ed->m_sois.type[il];
	    	sclmod->poro[il] = ed->m_sois.por[il];
	    	sclmod->dz[il]   = ed->m_sois.dz[il];
	    	sclmod->rootfrac[il] = ed->m_sois.rootfrac[il];

	    	sclmod->ts[im][il]  = ed->m_soid.tem[il];
	    	sclmod->liq[im][il] = ed->m_soid.alllwc[il];
	    	sclmod->vwc[im][il] = ed->m_soid.allvwc[il];
	    	sclmod->ice[im][il] = ed->m_soid.alliwc[il];
	   	}

 		for(int il =0; il<MAX_MIN_LAY ; il++){
 			sclmod->mintype[il] =ground.soil.mineral.type[il];
 		}

 		sclmod->ald[im] = ed->m_ald;
 		sclmod->watb[im]= ed->m_soid.watertab;

 		sclmod->pet[im] = ed->m_l2a.pet;
 		sclmod->eet[im] = ed->m_l2a.eet;

 		sclmod->yreet = ed->y_l2a.eet;
 		sclmod->yrpet = ed->y_l2a.pet;

 		sclmod->prveetmx = ed->prveetmx;
 		sclmod->prvpetmx = ed->prvpetmx;

 	} catch (Exception &exception) {
  		exception.mesg();
 	}
};

void Cohort::updateSoilLayerType(int TYPEsoil[], int TYPEmin[]){
 	Layer* currl = ground.frontl;
 	SoilLayer*sl;
 	PeatLayer* pl;
 		
 	int soilcount =-1;
  	while(currl!=NULL){
 		if(currl->isSoil()){
 		  soilcount++;
 		   		 
 		  sl = dynamic_cast<SoilLayer*>(currl);
 		 
 		  if(sl->isMoss()){
 			  TYPEsoil[soilcount] = 0;
 		  }else if(sl->isPeat()){
 			  pl = dynamic_cast<PeatLayer*>(currl);
 		  	  if(pl->isFibric){
 		  		  TYPEsoil[soilcount] =1;
 		  	  }else if(pl->isHumic){
 		  		  TYPEsoil[soilcount] =2;
 		  	  }
 		  }else if(sl->isMineral()){
 		  	  TYPEsoil[soilcount] = 3;
 		  }else {
 			  TYPEsoil[soilcount] = -999;
 		  }
 		  		   
 		}
 		
 		currl =currl->nextl;

 		for(int il =0; il<MAX_MIN_LAY ; il++){
 	 		TYPEmin[il] =ground.soil.mineral.type[il];
 	 	}

 	}
 	 	
};
