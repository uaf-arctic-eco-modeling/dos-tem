#include "SoilclmInputer.h"

SoilclmInputer::SoilclmInputer(){
	
};

SoilclmInputer::~SoilclmInputer(){
 	if(sclmFile!=NULL){
    	sclmFile->close();
		delete sclmFile;
 	}
	
};

//Yuan: modified to be multiple-year to be used as atm-independent drivers for "soil" process
void SoilclmInputer::init(string & outdir){
	
	string filename = outdir+ "soilclm.nc";

	sclmFile = new NcFile(filename.c_str(), NcFile::ReadOnly);
	if(!sclmFile->is_valid()){
 		string msg = filename+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_NCFILE_NOT_EXIST);
 	}

	// dimensions
	chtD = sclmFile->get_dim("CHTID");
 	if(!chtD->is_valid()){
 		string msg = "Cohort Dimension is no Valid in SoilclmInputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

	yrD = sclmFile->get_dim("YEAR");
 	if(!chtD->is_valid()){
 		string msg = "Cohort Dimension is no Valid in SoilclmInputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

	monD = sclmFile->get_dim("MON");
 	if(!chtD->is_valid()){
 		string msg = "Cohort Dimension is no Valid in SoilclmInputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

	layerD = sclmFile->get_dim("LAYER");
 	if(!chtD->is_valid()){
 		string msg = "Cohort Dimension is no Valid in SoilclmInputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCDIM_NOT_EXIST);
 	}

	mlayerD = sclmFile->get_dim("MINLAYER");
 	if(!chtD->is_valid()){
 		string msg = "Cohort Dimension is no Valid in SoilclmInputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

 	// variables
 	chtidV = sclmFile->get_var("CHTID");
 	if(chtidV==NULL){
 	   string msg = "Cannot get chtidv in SoilclmInputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	drgV = sclmFile->get_var("DRG");
 	numslV = sclmFile->get_var("NUMSL");

 	dzV = sclmFile->get_var("DZ");
 	typeV = sclmFile->get_var("TYPE");
	mintypeV = sclmFile->get_var("MINTYPE");
 	poroV = sclmFile->get_var("PORO");
 	rootfracV = sclmFile->get_var("ROOTFRAC");

 	petV = sclmFile->get_var("PET");
 	eetV = sclmFile->get_var("EET");

 	tsV  = sclmFile->get_var("TS");
 	aldV = sclmFile->get_var("ALD");
 	vwcV = sclmFile->get_var("VSM");
 	liqV = sclmFile->get_var("LIQ");
 	iceV = sclmFile->get_var("ICE");

 	yreetV = sclmFile->get_var("YREET");
 	yrpetV = sclmFile->get_var("YRPET");
 	prveetmxV = sclmFile->get_var("PRVEETMX");
 	prvpetmxV = sclmFile->get_var("PRVPETMX");

};

////////////////////////////////////////////////////////////////////////////////////////
//Yuan: chtid is the cohort id, but not exactly the record id in the .nc file
int SoilclmInputer::getRecordId(const int &chtid){

	int chtno = (int)chtD->size();
	int id;
	for (int i=0; i<chtno; i++){
		getChtId(id, i);
		if (id==chtid) return i;

	}
	cout << "cohort "<< chtid<<" NOT exists in SoilclmInputer\n";
	return -1;
}

void SoilclmInputer::getChtId(int &chtid, const int &recid){

	chtidV->set_cur(recid);
	NcBool nb1 = chtidV->get(&chtid,1);
	if(!nb1){
	 string msg = "problem in reading chtid in SoilclmInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}

///////////////////////////////////////////////////

//Yuan: read data for one cohort
void SoilclmInputer::getSoilClimate(SoilClm * sclm, const int & recid){

  	numslV->set_cur(recid);
	numslV->get(&sclm->numsl, 1);

	drgV->set_cur(recid);
	drgV->get(&sclm->drg, 1);

  	poroV->set_cur(recid);
	poroV->get(&sclm->poro[0], MAX_SOI_LAY);

  	typeV->set_cur(recid);
  	typeV->get(&sclm->type[0], MAX_SOI_LAY);

  	dzV->set_cur(recid);
  	dzV->get(&sclm->dz[0], MAX_SOI_LAY);

  	rootfracV->set_cur(recid);
	rootfracV->get(&sclm->rootfrac[0], MAX_SOI_LAY);

  	aldV->set_cur(recid);
	aldV->get(&sclm->ald[0], 12);

  	tsV->set_cur(recid);
	tsV->get(&sclm->ts[0][0], 12, MAX_SOI_LAY);

	liqV->set_cur(recid);
	liqV->get(&sclm->liq[0][0], 12, MAX_SOI_LAY);

	iceV->set_cur(recid);
	iceV->get(&sclm->ice[0][0], 12, MAX_SOI_LAY);

	vwcV->set_cur(recid);
	vwcV->get(&sclm->vwc[0][0], 12, MAX_SOI_LAY);
	
  	petV->set_cur(recid);
	petV->get(&sclm->pet[0], 12);

	eetV->set_cur(recid);
    eetV->get(&sclm->eet[0], 12);

  	yreetV->set_cur(recid);
	yreetV->get(&sclm->yreet, 1);

	yrpetV->set_cur(recid);
	yrpetV->get(&sclm->yrpet, 1);

  	prveetmxV->set_cur(recid);
	prveetmxV->get(&sclm->prveetmx, 1);

	prvpetmxV->set_cur(recid);
	prvpetmxV->get(&sclm->prvpetmx, 1);
	
};




