#include "CCohortdriver.h"

CCohortdriver::CCohortdriver(){
	
};

CCohortdriver::~CCohortdriver(){
	
};

void CCohortdriver::createSoilClimate(BgcData *bd, EnvData *ed, Vegetation_Env *ve,
                                    string& datadir){
	
	string file = datadir+ "calirestart.nc";
	NcFile* resFile = new NcFile(file.c_str(), NcFile::Replace);

	NcDim * chtD = resFile->add_dim("CHTID", 1);
	NcDim * monD = resFile->add_dim("MON", 12);
	NcDim * layD = resFile->add_dim("LAYER", MAX_SOI_LAY);

	NcVar* drgV = resFile->add_var("DRG",ncInt, chtD);
	NcVar* vegV = resFile->add_var("VEG",ncInt, chtD);
	NcVar* numslV = resFile->add_var("NUMSL",ncInt, chtD);

	NcVar* rsoilcV = resFile->add_var("RSOILC", ncDouble, layD);
	NcVar* nsoilcV = resFile->add_var("NSOILC", ncDouble, layD);
	NcVar* dzV = resFile->add_var("DZ", ncDouble, layD);
	NcVar* typeV = resFile->add_var("TYPE", ncDouble, layD);
	NcVar* poroV = resFile->add_var("PORO", ncDouble, layD);
	NcVar* rootfracV = resFile->add_var("ROOTFRAC", ncDouble, layD);

	NcVar* taV = resFile->add_var("TA",ncDouble, monD);
	NcVar* growV = resFile->add_var("GROW",ncDouble, monD);
	NcVar* co2V = resFile->add_var("CO2",ncDouble, monD);
	NcVar* petV = resFile->add_var("PET",ncDouble, monD);
	NcVar* eetV = resFile->add_var("EET",ncDouble, monD);
	NcVar* parV = resFile->add_var("PAR",ncDouble, monD);
	NcVar* envlaiV = resFile->add_var("ENVLAI",ncFloat, monD);

	NcVar* tsV = resFile->add_var("TS", ncDouble, monD, layD);
	NcVar* liqV = resFile->add_var("LIQ",ncDouble, monD, layD);
	NcVar* vwcV = resFile->add_var("VSM",ncDouble, monD, layD);
	NcVar* swsV = resFile->add_var("SWS",ncDouble, monD, layD);
	NcVar* iceV = resFile->add_var("ICE",ncDouble, monD, layD);

	NcVar* yreetV = resFile->add_var("YREET",ncDouble, chtD);
	NcVar* yrpetV = resFile->add_var("YRPET",ncDouble, chtD);
	NcVar* yrco2V = resFile->add_var("YRCO2",ncDouble, chtD);
	NcVar* prveetmxV = resFile->add_var("PRVEETMX",ncDouble, chtD);
	NcVar* prvpetmxV = resFile->add_var("PRVPETMX",ncDouble, chtD);
	
	numslV->put(&ed->m_soid.actual_num_soil, 1);
	drgV->put(&ed->cd->drgtype, 1);
	vegV->put(&ed->cd->vegtype, 1);

	poroV->put(&ed->m_sois.por[0], MAX_SOI_LAY);
	typeV->put(&ed->m_sois.type[0], MAX_SOI_LAY);
	dzV->put(&ed->m_sois.dz[0], MAX_SOI_LAY);
	rsoilcV->put(&bd->m_sois.reac[0], MAX_SOI_LAY);
	nsoilcV->put(&bd->m_sois.nonc[0], MAX_SOI_LAY);
	rootfracV->put(&ed->m_sois.rootfrac[0], MAX_SOI_LAY);

	tsV->put(&ed->eq_ts[0][0], 12, MAX_SOI_LAY);
	liqV->put(&ed->eq_liq[0][0], 12, MAX_SOI_LAY);
	iceV->put(&ed->eq_ice[0][0], 12, MAX_SOI_LAY);
	vwcV->put(&ed->eq_vwc[0][0], 12, MAX_SOI_LAY);
	swsV->put(&ed->eq_sws[0][0], 12, MAX_SOI_LAY);
	
	taV->put(&ed->eq_ta[0], 12);
	petV->put(&ed->eq_pet[0], 12);
    eetV->put(&ed->eq_eet[0], 12);
	co2V->put(&ed->eq_co2[0], 12);
	parV->put(&ed->eq_par[0], 12);
	growV->put(&ed->eq_grow[0], 12);
	envlaiV->put(&ve->envlaiall[0], 12);

	yreetV->put(&ed->eq_y_eet, 1);
	yrpetV->put(&ed->eq_y_pet, 1);
	yrco2V->put(&ed->eq_y_co2, 1);

	prveetmxV->put(&ed->eq_prveetmx);
	prvpetmxV->put(&ed->eq_prvpetmx);
	
	resFile->close();
	delete resFile;   //Yuan: if not, memory leaking may occur

//	exit(0);
};




