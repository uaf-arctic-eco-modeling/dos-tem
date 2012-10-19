/*! \file 
*/

#include "VegetationOutputer.h"

VegetationOutputer::VegetationOutputer(){
	reinit();
	
};

void VegetationOutputer::reinit(){
	daycnt=-1;	
}

#ifdef ODAY

	void VegetationOutputer::outputDayCohortVars(const int & yrcnt){
	
		sinterCDV->put_rec(&vegod->sinterd[0], yrcnt);
		rinterCDV->put_rec(&vegod->rinterd[0], yrcnt);
		sthflCDV->put_rec(&vegod->sthfld[0], yrcnt);
		rthflCDV->put_rec(&vegod->rthfld[0], yrcnt);
		sdripCDV->put_rec(&vegod->sdripd[0], yrcnt);
		rdripCDV->put_rec(&vegod->rdripd[0], yrcnt);
		scanopyCDV->put_rec(&vegod->scanopyd[0], yrcnt);
		rcanopyCDV->put_rec(&vegod->rcanopyd[0], yrcnt);
		
		cansubCDV->put_rec(&vegod->cansubd[0], yrcnt);
		canevpCDV->put_rec(&vegod->canevpd[0], yrcnt);
		cantrsCDV->put_rec(&vegod->cantrsd[0], yrcnt);
		
		
		racCDV->put_rec(&vegod->racd[0], yrcnt);
		radreflCDV->put_rec(&vegod->radrefld[0], yrcnt);
		radthrouCDV->put_rec(&vegod->radthroud[0], yrcnt);
		
		
		btranCDV->put_rec(&vegod->btrand[0], yrcnt);
		m_ppfdCDV->put_rec(&vegod->m_ppfdd[0], yrcnt);
		m_vpdCDV->put_rec(&vegod->m_vpdd[0], yrcnt);
		
		ccCDV->put_rec(&vegod->ccd[0], yrcnt);
		
	};

	void VegetationOutputer::defineDayCohortVars(){
		daycf = siteoutputer->dayChtFile;
		dcyearD = daycf->get_dim("year");
 	
		dcdayD =daycf->get_dim("day");
    //// Water Pools
		scanopyCDV = daycf->add_var("SCANOPY", ncFloat, dcyearD,   dcdayD); 
	 	scanopyCDV->add_att("units","mm");
    	scanopyCDV->add_att("title", "Canopy Snow");
    	
    	rcanopyCDV = daycf->add_var("RCANOPY", ncFloat, dcyearD,   dcdayD); 
 		rcanopyCDV->add_att("units","mm");
    	rcanopyCDV->add_att("title", "Canopy Rain");
    
    //// Water Fluxes	
    	sinterCDV = daycf->add_var("SINTER", ncFloat, dcyearD,   dcdayD); 
 	  	sinterCDV->add_att("units","mm/day");
    	sinterCDV->add_att("title", "Snow Interception");
    	rinterCDV = daycf->add_var("RINTER", ncFloat, dcyearD,   dcdayD); 
 	 	rinterCDV->add_att("units","mm/day");
    	rinterCDV->add_att("title", "Rain Interception");
    	
    /// from canopy to ground 	
    	sthflCDV = daycf->add_var("STHFL", ncFloat, dcyearD,   dcdayD); 
 	 	sthflCDV->add_att("units","mm/day");
    	sthflCDV->add_att("title", "Snow Throughfall");
    	
    	rthflCDV = daycf->add_var("RTHFL", ncFloat, dcyearD,   dcdayD); 
 	 	rthflCDV->add_att("units","mm/day");
    	rthflCDV->add_att("title", "Rain Throughfall");
    	
    	sdripCDV = daycf->add_var("SDRIP", ncFloat, dcyearD,   dcdayD); 
 	 	sdripCDV->add_att("units","mm/day");
    	sdripCDV->add_att("title", "Snow Drip");
    	
    	rdripCDV = daycf->add_var("RDRIP", ncFloat, dcyearD,   dcdayD); 
 	 	rdripCDV->add_att("units","mm/day");
    	rdripCDV->add_att("title", "Rain Drip");  
    	
	/// from canopy to atmosphere
    	cansubCDV = daycf->add_var("CANSUB", ncFloat, dcyearD,   dcdayD); 
		cansubCDV->add_att("units","mm/day");
    	cansubCDV->add_att("title", "Sublimation from Canopy Snow");
    	
    	canevpCDV = daycf->add_var("CANEVP", ncFloat, dcyearD,   dcdayD); 
		canevpCDV->add_att("units","mm/day");
    	canevpCDV->add_att("title", "Evaporation from Canopy Rain");
    	
    	cantrsCDV = daycf->add_var("CANTRS", ncFloat, dcyearD,   dcdayD);
	    cantrsCDV->add_att("units","mm/day");
    	cantrsCDV->add_att("title", "Transpiration"); 	
	
	/////Radiation
	
    	racCDV = daycf->add_var("RADINCAN", ncFloat, dcyearD,   dcdayD); 
	    racCDV->add_att("units","MJ/m2day");
    	racCDV->add_att("title", "Absorbed Rad in Canopy");
    	
    	radreflCDV = daycf->add_var("RADREFL", ncFloat, dcyearD,   dcdayD); 
	    radreflCDV->add_att("units","MJ/m2day");
    	radreflCDV->add_att("title", "Rad Reflected By Canopy");
    
    	radthrouCDV = daycf->add_var("RADTHROU", ncFloat, dcyearD,   dcdayD); 
	    radthrouCDV->add_att("units","MJ/m2day");
    	radthrouCDV->add_att("title", "Rad Through Canopy"); 	 	
    	 		 	
    	btranCDV = daycf->add_var("BTRAN", ncFloat, dcyearD,   dcdayD); 
	    btranCDV->add_att("units","-");
    	btranCDV->add_att("title", "Factor of Soil Water on Conductance");

    	m_ppfdCDV = daycf->add_var("M_PPFD", ncFloat, dcyearD,   dcdayD); 
		m_ppfdCDV->add_att("units","-");
    	m_ppfdCDV->add_att("title", "Factor of Radiation on Conductance");

    	m_vpdCDV = daycf->add_var("M_VPD", ncFloat, dcyearD,   dcdayD); 
		m_vpdCDV->add_att("units","-");
    	m_vpdCDV->add_att("title", "Factor of VPD on Conductance");
    	
    	ccCDV = daycf->add_var("CANCON", ncFloat, dcyearD,   dcdayD); 
		ccCDV->add_att("units","mm/s");
    	ccCDV->add_att("title", "Canopy Conductance");
	};

#endif

void VegetationOutputer::outputMonthCohortVars(const int & yrcnt){
		
	    vegcCMV->put_rec(&vegod->vegc[0],yrcnt);
	    strnCMV->put_rec(&vegod->strn[0],yrcnt);
	    stonCMV->put_rec(&vegod->ston[0],yrcnt);
	    ingppCMV->put_rec(&vegod->ingpp[0],yrcnt);
	    gppCMV->put_rec(&vegod->gpp[0],yrcnt);
	    innppCMV->put_rec(&vegod->innpp[0],yrcnt);
	    nppCMV->put_rec(&vegod->npp[0],yrcnt);
	    rmCMV->put_rec(&vegod->rm[0],yrcnt);
	    rgCMV->put_rec(&vegod->rg[0],yrcnt);
	    ltrfalcCMV->put_rec(&vegod->ltrfalc[0],yrcnt);
	    ltrfalnCMV->put_rec(&vegod->ltrfaln[0],yrcnt);
	    innuptakeCMV->put_rec(&vegod->innuptake[0],yrcnt);
	    nuptakeCMV->put_rec(&vegod->nuptake[0],yrcnt);
	    luptakeCMV->put_rec(&vegod->luptake[0],yrcnt);
	    suptakeCMV->put_rec(&vegod->suptake[0],yrcnt);
	    nmobilCMV->put_rec(&vegod->nmobil[0],yrcnt);
	    nresorbCMV->put_rec(&vegod->nresorb[0],yrcnt);
	    laiCMV->put_rec(&vegod->lai[0],yrcnt);
	    fpcCMV->put_rec(&vegod->fpc[0],yrcnt);
	    unnormleafCMV->put_rec(&vegod->unnormleaf[0],yrcnt);
	    leafCMV->put_rec(&vegod->leaf[0],yrcnt);
	    foliageCMV->put_rec(&vegod->foliage[0],yrcnt);
	    btranCMV->put_rec(&vegod->btran[0],yrcnt);
	    rcCMV->put_rec(&vegod->rc[0],yrcnt);
	    racCMV->put_rec(&vegod->rac[0],yrcnt);
	    transCMV->put_rec(&vegod->trans[0],yrcnt);
	    vevapCMV->put_rec(&vegod->vevap[0],yrcnt);
	    vsublCMV->put_rec(&vegod->vsubl[0],yrcnt);
	    rinterCMV->put_rec(&vegod->rinter[0],yrcnt);
	    sinterCMV->put_rec(&vegod->sinter[0],yrcnt);
	    rthflCMV->put_rec(&vegod->rthfl[0],yrcnt);
	    sthflCMV->put_rec(&vegod->sthfl[0],yrcnt);
		radthflCMV->put_rec(&vegod->radthfl[0],yrcnt);

};

void VegetationOutputer::defineMonthCohortVars(){

		moncf = siteoutputer->monChtFile;
  
		mcyearD = moncf->get_dim("year");
		mcmonD = moncf->get_dim("month");

		vegcCMV = moncf->add_var("VEGC", ncFloat, mcyearD,  mcmonD); 
    	vegcCMV->add_att("units","gC/m2");
    	vegcCMV->add_att("title", "Vegetation Carbon");
    	strnCMV = moncf->add_var("STRN", ncFloat, mcyearD,  mcmonD); 
    	strnCMV->add_att("units","gN/m2");
    	strnCMV->add_att("title", "Structual Nitrogen");
    	  
    	stonCMV = moncf->add_var("STON", ncFloat, mcyearD,  mcmonD);
    	stonCMV->add_att("units","gN/m2");
    	stonCMV->add_att("title", "Labile Nitrogen");
    	  
    	ingppCMV = moncf->add_var("INGPP", ncFloat, mcyearD,  mcmonD); 
    	ingppCMV->add_att("units","gC/m2day");
    	ingppCMV->add_att("title", "GPP unlimited by N");
    	  
    	gppCMV = moncf->add_var("GPP", ncFloat, mcyearD,  mcmonD);
    	gppCMV->add_att("units","gC/m2day");
    	gppCMV->add_att("title", "GPP");
    	  
    	innppCMV = moncf->add_var("INNPP", ncFloat, mcyearD,  mcmonD);
    	innppCMV->add_att("units","gC/m2day");
    	innppCMV->add_att("title", "NPP unlimited by N");
    	  
    	nppCMV = moncf->add_var("NPP", ncFloat, mcyearD,  mcmonD);
    	nppCMV->add_att("units","gC/m2day");
    	nppCMV->add_att("title", "NPP");
    	  
    	rmCMV = moncf->add_var("RM", ncFloat, mcyearD,  mcmonD); 
    	rmCMV->add_att("units","gC/m2day");
    	rmCMV->add_att("title", "Maintainence Respiration");
    	  
    	rgCMV = moncf->add_var("RG", ncFloat, mcyearD,  mcmonD);
    	rgCMV->add_att("units","gC/m2day");
    	rgCMV->add_att("title", "Growth Respiration");
    	  
    	ltrfalcCMV = moncf->add_var("LTRFALC", ncFloat, mcyearD,  mcmonD);
    	ltrfalcCMV->add_att("units","gC/m2day");
    	ltrfalcCMV->add_att("title", "Literfall Carbon");
    	  
    	ltrfalnCMV = moncf->add_var("LTRFALN", ncFloat, mcyearD,  mcmonD);
    	ltrfalnCMV->add_att("units","gN/m2day");
    	ltrfalnCMV->add_att("title", "Literfall Nitrogen");
    	  
    	innuptakeCMV = moncf->add_var("INNUPTAKE", ncFloat, mcyearD,  mcmonD); 
    	innuptakeCMV->add_att("units","gN/m2day");
    	innuptakeCMV->add_att("title", "N uptake unlimited by N");
    	  
    	nuptakeCMV = moncf->add_var("NUPTAKE", ncFloat, mcyearD,  mcmonD);
    	nuptakeCMV->add_att("units","gN/m2day");
    	nuptakeCMV->add_att("title", "N uptake"); 
    	  
    	suptakeCMV = moncf->add_var("SUPTAKE", ncFloat, mcyearD,  mcmonD);
    	suptakeCMV->add_att("units","gN/m2day");
    	suptakeCMV->add_att("title", "N uptake by Structual Pool");
    	  
    	luptakeCMV = moncf->add_var("LUPTAKE", ncFloat, mcyearD,  mcmonD);
    	luptakeCMV->add_att("units","gN/m2day");
    	luptakeCMV->add_att("title", "N uptake by Labile Pool");
    	
    	nmobilCMV = moncf->add_var("NMOBIL", ncFloat, mcyearD,  mcmonD);
    	nmobilCMV->add_att("units","gN/m2day");
    	nmobilCMV->add_att("title", "Mobilized Nitrogen");
    	 
    	nresorbCMV = moncf->add_var("NRESORB", ncFloat, mcyearD,  mcmonD);
   	  	nresorbCMV->add_att("units","gN/m2day");
    	nresorbCMV->add_att("title", "Reabsorbed Nitrogen");
    	
    	laiCMV = moncf->add_var("LAI", ncFloat, mcyearD,  mcmonD);
    	laiCMV->add_att("units","m2/m2");
    	laiCMV->add_att("title", "Leaf Area Index");
    	
    	fpcCMV = moncf->add_var("FPC", ncFloat, mcyearD,  mcmonD);
    	fpcCMV->add_att("units","");
    	fpcCMV->add_att("title", "FPC");
    	
    	unnormleafCMV = moncf->add_var("UNNORMLEAF", ncFloat, mcyearD,  mcmonD);
    	unnormleafCMV->add_att("units","-");
    	unnormleafCMV->add_att("title", "Unnormalized Leaf");
    	
    	leafCMV = moncf->add_var("LEAF", ncFloat, mcyearD,  mcmonD);	
    	leafCMV->add_att("units","-");
    	leafCMV->add_att("title", "ET control factor on leaf growth");
    	
    	foliageCMV = moncf->add_var("FOLIAGE", ncFloat, mcyearD,  mcmonD);	
    	foliageCMV->add_att("units","-");
    	foliageCMV->add_att("title", "VEG C regulated leaf growth");
    	
 		btranCMV = moncf->add_var("BTRAN", ncFloat, mcyearD,  mcmonD);	
 	  	btranCMV->add_att("units","-");
    	btranCMV->add_att("title", "Factor of Soil Water on Conductance");
    	btranCMV->add_att("valid_min", 0);
    	btranCMV->add_att("valid_max", 1);
    	
    	racCMV = moncf->add_var("RAC", ncFloat, mcyearD,  mcmonD);	
 	    racCMV->add_att("units","W/m2");
    	racCMV->add_att("title", "Absorbed Rad in Canopy");
    	
    	rcCMV = moncf->add_var("RC", ncFloat, mcyearD,  mcmonD);	
		rcCMV->add_att("units","s/mm");
    	rcCMV->add_att("title", "Canopy Resistence");
    	
    	transCMV = moncf->add_var("TRANS", ncFloat, mcyearD,  mcmonD);	
 	 	transCMV->add_att("units","mm/m2day");
    	transCMV->add_att("title", "Transpiration");
    	
    	vevapCMV = moncf->add_var("VEVAP", ncFloat, mcyearD,  mcmonD);
 	 	vevapCMV->add_att("units","mm/day");
    	vevapCMV->add_att("title", "Canopy Evaporation");
    		
    	vsublCMV = moncf->add_var("VSUBL", ncFloat, mcyearD,  mcmonD);	
 	 	vsublCMV->add_att("units","mm/day");
    	vsublCMV->add_att("title", "Sublimation from Canopy Snow");
    	
    	rinterCMV = moncf->add_var("RINTER", ncFloat, mcyearD,  mcmonD);	
 	    rinterCMV->add_att("units","mm/day");
    	rinterCMV->add_att("title", "Intercepted Rain");
    	
    	sinterCMV = moncf->add_var("SINTER", ncFloat, mcyearD,  mcmonD);	
 	 	sinterCMV->add_att("units","mm/day");
    	sinterCMV->add_att("title", "Intercepted Snow");
    	
    	rthflCMV = moncf->add_var("RTHFL", ncFloat, mcyearD,  mcmonD);	
 	 	rthflCMV->add_att("units","mm/day");
    	rthflCMV->add_att("title", "Rain Throughfall");
    	
    	sthflCMV = moncf->add_var("STHFL", ncFloat, mcyearD,  mcmonD);	
 	 	sthflCMV->add_att("units","mm/day");
    	sthflCMV->add_att("title", "Snow Throughfall");
    	
    	radthflCMV = moncf->add_var("RADTHFL", ncFloat, mcyearD,  mcmonD);	
		radthflCMV->add_att("units","MJ/m2day");
    	radthflCMV->add_att("title", "Radition Throughfall");
};

void VegetationOutputer::outputYearCohortVars(const int &yrcnt){

	    nppCYV->put_rec(&vegod->yrnpp,yrcnt);
	    rmCYV->put_rec(&vegod->yrrm,yrcnt);
	    rgCYV->put_rec(&vegod->yrrg,yrcnt);
	    ltrfalcCYV->put_rec(&vegod->yrltrfalc,yrcnt);
	    ltrfalnCYV->put_rec(&vegod->yrltrfaln,yrcnt);
	    vnuptakeCYV->put_rec(&vegod->yrvnuptake,yrcnt);
	    evapoCYV->put_rec(&vegod->yrevapo,yrcnt);
	    sublimCYV->put_rec(&vegod->yrsublim,yrcnt);
	    transCYV->put_rec(&vegod->yrtrans,yrcnt);
	     
	    c2nCYV->put_rec(&vegod->yrc2n,yrcnt);
	    vegcCYV->put_rec(&vegod->yrvegc,yrcnt);
	    strnCYV->put_rec(&vegod->yrstrn,yrcnt);
	    stonCYV->put_rec(&vegod->yrston,yrcnt);
	     
	    abvgndcCYV->put_rec(&vegod->yrabvgndc,yrcnt);
	    foliageCYV->put_rec(&vegod->yrfoliage,yrcnt); 
	    leafCYV->put_rec(&vegod->yrleaf,yrcnt); 
	    laiCYV->put_rec(&vegod->yrlai,yrcnt); 
	    fpcCYV->put_rec(&vegod->yrfpc,yrcnt); 
	    
	    burnorgcCYV->put_rec(&vegod->yrburnorgc,yrcnt); 
	    burnorgnCYV->put_rec(&vegod->yrburnorgn,yrcnt);
	    	    
};

void VegetationOutputer::defineYearCohortVars(){

  		yrcf = siteoutputer->yrChtFile;
  
  		ycyearD = yrcf->get_dim("year");
    	nppCYV = yrcf->add_var("NPP", ncFloat, ycyearD);
    	nppCYV->add_att("units","gC/m2day");
    	nppCYV->add_att("title", "NPP");
    	  
    	rmCYV = yrcf->add_var("RM", ncFloat, ycyearD); 
    	rmCYV->add_att("units","gC/m2day");
    	rmCYV->add_att("title", "Maintainence Respiration");
    	  
    	rgCYV = yrcf->add_var("RG", ncFloat, ycyearD);
    	rgCYV->add_att("units","gC/m2day");
    	rgCYV->add_att("title", "Growth Respiration");
    	  
    	ltrfalcCYV = yrcf->add_var("LTRFALC", ncFloat, ycyearD);
    	ltrfalcCYV->add_att("units","gC/m2day");
    	ltrfalcCYV->add_att("title", "Literfall Carbon");
    	  
    	ltrfalnCYV = yrcf->add_var("LTRFALN", ncFloat, ycyearD);
    	ltrfalnCYV->add_att("units","gN/m2day");
    	ltrfalnCYV->add_att("title", "Literfall Nitrogen");
    	  
    	vnuptakeCYV = yrcf->add_var("VNUPTAKE", ncFloat, ycyearD);
    	vnuptakeCYV->add_att("units","gN/m2day");
    	vnuptakeCYV->add_att("title", "N uptake");
    	  
    	evapoCYV = yrcf->add_var("EVAPO", ncFloat, ycyearD);  
    	sublimCYV = yrcf->add_var("SUBLIM", ncFloat, ycyearD);  
    	transCYV = yrcf->add_var("TRANS", ncFloat, ycyearD);  
    	
    	c2nCYV = yrcf->add_var("C2N", ncFloat, ycyearD);  
    	
    	vegcCYV = yrcf->add_var("VEGC", ncFloat, ycyearD);  
    	strnCYV = yrcf->add_var("STRN", ncFloat, ycyearD);  
    	stonCYV = yrcf->add_var("STON", ncFloat, ycyearD);  
    	
    	abvgndcCYV = yrcf->add_var("ABVGNDC", ncFloat, ycyearD);  
    	foliageCYV = yrcf->add_var("FOLIAGE", ncFloat, ycyearD);  
    	leafCYV = yrcf->add_var("LEAF", ncFloat, ycyearD);  
    	laiCYV = yrcf->add_var("LAI", ncFloat, ycyearD);  
    	fpcCYV = yrcf->add_var("FPC", ncFloat, ycyearD);  
    	
    	burnorgcCYV = yrcf->add_var("BURNVEGC", ncFloat, ycyearD);  
    	burnorgnCYV = yrcf->add_var("BURNVEGN", ncFloat, ycyearD);  
    	
};

void VegetationOutputer::setOutputer(SiteOutputer * outputerp){
   	siteoutputer = outputerp;
   	
	#ifdef ODAY
   		defineDayCohortVars();
	#endif

	if (OMONTH) {   	
   		defineMonthCohortVars();
	}

	if (OYEAR) {   	
   		defineYearCohortVars();
	}

};	

void VegetationOutputer::setOutdata( VegOutData* outdata){
   vegod = outdata;
};	
