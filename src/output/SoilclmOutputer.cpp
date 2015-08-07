#include "SoilclmOutputer.h"

SoilclmOutputer::SoilclmOutputer(){
	
};

SoilclmOutputer::~SoilclmOutputer(){
 	if(sclmFile!=NULL){
    	sclmFile->close();
		delete sclmFile;
 	}
	
};

//Yuan: modified to be multiple-year to be used as atm-independent drivers for "soil" process
void SoilclmOutputer::initSoilClimate(string & outdir){
	
	string file = outdir+ "soilclm.nc";
	sclmFile = new NcFile(file.c_str(), NcFile::Replace);

	NcDim * chtD = sclmFile->add_dim("CHTID", 1);
	NcDim * yrD  = sclmFile->add_dim("YEAR", MAX_ATM_NOM_YR);   //Yuan: orginal 1 year, now defined in timeconst.h
	NcDim * monD = sclmFile->add_dim("MON", 12);
	NcDim * layD = sclmFile->add_dim("LAYER", MAX_SOI_LAY);
	NcDim * mlayD = sclmFile->add_dim("MINLAYER", MAX_MIN_LAY);

	chtV = sclmFile->add_var("CHTID",ncInt, chtD);
	drgV = sclmFile->add_var("DRG",ncInt, chtD);
	numslV = sclmFile->add_var("NUMSL",ncInt, chtD);

	dzV = sclmFile->add_var("DZ", ncFloat, chtD, layD);
	typeV = sclmFile->add_var("TYPE", ncFloat, chtD, layD);
	minclayV = sclmFile->add_var("MINCLAY", ncFloat, chtD, mlayD);
	minsandV = sclmFile->add_var("MINSAND", ncFloat, chtD, mlayD);
	minclayV = sclmFile->add_var("MINSILT", ncFloat, chtD, mlayD);
	poroV = sclmFile->add_var("PORO", ncFloat, chtD, layD);
	rootfracV = sclmFile->add_var("ROOTFRAC", ncFloat, chtD, layD);

	petV = sclmFile->add_var("PET",ncFloat, chtD, yrD, monD);
	eetV = sclmFile->add_var("EET",ncFloat, chtD, yrD, monD);

	tsV  = sclmFile->add_var("TS", ncFloat, chtD, yrD, monD, layD);
	aldV = sclmFile->add_var("ALD",ncFloat, chtD, yrD, monD);
	vwcV = sclmFile->add_var("VSM",ncFloat, chtD, yrD, monD, layD);
	liqV = sclmFile->add_var("LIQ",ncFloat, chtD, yrD, monD, layD);
	iceV = sclmFile->add_var("ICE",ncFloat, chtD, yrD, monD, layD);

	yreetV = sclmFile->add_var("YREET",ncFloat, chtD, yrD);
	yrpetV = sclmFile->add_var("YRPET",ncFloat, chtD, yrD);
	prveetmxV = sclmFile->add_var("PRVEETMX",ncFloat, chtD, yrD);
	prvpetmxV = sclmFile->add_var("PRVPETMX",ncFloat, chtD, yrD);

};

//Yuan: write to file once a year
void SoilclmOutputer::createSoilClimate(const int &chtcnt, const int&yrcnt){

   	chtV->set_cur(chtcnt);
	chtV->put(&sclm->chtid, 1);

  	numslV->set_cur(chtcnt);
	numslV->put(&sclm->numsl, 1);

	drgV->set_cur(chtcnt);
	drgV->put(&sclm->drg, 1);

  	poroV->set_cur(chtcnt);
	poroV->put(&sclm->poro[0], MAX_SOI_LAY);

  	typeV->set_cur(chtcnt);
  	typeV->put(&sclm->type[0], MAX_SOI_LAY);

  	dzV->set_cur(chtcnt);
  	dzV->put(&sclm->dz[0], MAX_SOI_LAY);

  	rootfracV->set_cur(chtcnt);
	rootfracV->put(&sclm->rootfrac[0], MAX_SOI_LAY);

  	aldV->set_cur(chtcnt, yrcnt);
	aldV->put(&sclm->ald[0], 12);

  	tsV->set_cur(chtcnt, yrcnt);
	tsV->put(&sclm->ts[0][0], 12, MAX_SOI_LAY);

	liqV->set_cur(chtcnt, yrcnt);
	liqV->put(&sclm->liq[0][0], 12, MAX_SOI_LAY);

	iceV->set_cur(chtcnt, yrcnt);
	iceV->put(&sclm->ice[0][0], 12, MAX_SOI_LAY);

	vwcV->set_cur(chtcnt, yrcnt);
	vwcV->put(&sclm->vwc[0][0], 12, MAX_SOI_LAY);
	
  	petV->set_cur(chtcnt, yrcnt);
	petV->put(&sclm->pet[0], 12);

	eetV->set_cur(chtcnt, yrcnt);
    eetV->put(&sclm->eet[0], 12);

  	yreetV->set_cur(chtcnt);
	yreetV->put(&sclm->yreet, 1);

	yrpetV->set_cur(chtcnt);
	yrpetV->put(&sclm->yrpet, 1);

  	prveetmxV->set_cur(chtcnt);
	prveetmxV->put(&sclm->prveetmx, 1);

	prvpetmxV->set_cur(chtcnt);
	prvpetmxV->put(&sclm->prvpetmx, 1);
	
};

void SoilclmOutputer::setSoilClm(SoilClm *soilclm){
	sclm = soilclm;
};



