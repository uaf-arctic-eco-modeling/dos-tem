#include "GridInputer.h"

GridInputer::GridInputer(){
	
};

GridInputer::~GridInputer(){

}

void GridInputer::init(){
  if(md!=NULL){

	  initLatlon(md->grdinputdir);

	  initSoil(md->grdinputdir);

	  string clmfile ="";
	  string firefile="";
	  if (!md->runeq){
		  if (md->runsc){     //sc run uses the same IDs system as 'tr', but use deferent files
			  firefile =md->grdinputdir+"fire_sc.nc";
			  clmfile  =md->grdinputdir+"climate_sc.nc";
		  } else {
			  firefile =md->grdinputdir+"fire_tr.nc";
			  clmfile  =md->grdinputdir+"climate_tr.nc";
		  }

	  }	else {
		  firefile =md->grdinputdir+"fire.nc";   //eq run uses aggregated (half degree resolution) driving data
		  clmfile  =md->grdinputdir+"climate.nc";
	  }

	  initFire(firefile);
	  initClimate(clmfile);

  }else{
  	string msg = "GridInputer::init - ModelData is NULL";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_VAR_NULL);
  }
	
}

void GridInputer::initLatlon(string& dir){
	//netcdf error
	NcError err(NcError::silent_nonfatal);

	grdfilename = dir +"latlon.nc";
	NcFile gridFile(grdfilename.c_str(), NcFile::ReadOnly);
 	if(!gridFile.is_valid()){
 		string msg = grdfilename+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception( msgc, I_NCFILE_NOT_EXIST);
 	}

 	NcDim* grdD = gridFile.get_dim("GRDID");
 	if(!grdD->is_valid()){
 		string msg = "GRDID Dimension is not Valid in latlon data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

}

void GridInputer::initFire(string & dirfile){
	//netcdf error
	NcError err(NcError::silent_nonfatal);

	firefilename = dirfile;
	NcFile fireFile(firefilename.c_str(), NcFile::ReadOnly);
 	if(!fireFile.is_valid()){
 		string msg = firefilename+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_NCFILE_NOT_EXIST);
 	}

 	NcDim* yrD = fireFile.get_dim("YEAR");
 	if(!yrD->is_valid()){
 		string msg = "YEAR Dimension is not Valid in grid-fire data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

 	fsize_drv_yr=yrD->size();  //Yuan: actual fire-size data years in a grid

}

void GridInputer::initSoil(string& dir){
	//netcdf error
	NcError err(NcError::silent_nonfatal);

	soilfilename = dir +"soil.nc";
	NcFile soilFile(soilfilename.c_str(), NcFile::ReadOnly);
 	if(!soilFile.is_valid()){
 		string msg = soilfilename+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_NCFILE_NOT_EXIST);
 	}
 	
 	NcDim* grdD = soilFile.get_dim("GRDID");
 	if(!grdD->is_valid()){
 		string msg = "GRDID Dimension is not Valid in Soil data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

}


void GridInputer::initClimate(string& dirfile){
	//netcdf error
	NcError err(NcError::silent_nonfatal);

	clmfilename = dirfile;

	NcFile climateFile(clmfilename.c_str(), NcFile::ReadOnly);
 	if(!climateFile.is_valid()){
 		string msg = clmfilename+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception( msgc, I_NCFILE_NOT_EXIST);
 	}
 	
 	NcDim* grdD = climateFile.get_dim("CLMID");
 	if(!grdD->is_valid()){
 		string msg = "CLMID Dimension is not Valid in Climate data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 		
 	NcDim* yrD = climateFile.get_dim("YEAR");
 	if(!yrD->is_valid()){
 		string msg = "YEAR Dimension is not Valid in Climate data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

 	atm_drv_yr=yrD->size();  //Yuan: actual atm data years

 	NcDim* monD = climateFile.get_dim("MONTH");
 	if(!monD->is_valid()){
 		string msg = "MONTH Dimension is not Valid in Climate data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

}

//YUAN: recid - the order (from ZERO) in the .nc file, gid - the grid id
int GridInputer::getGridRecID(const int &gid){
	//netcdf error
	NcError err(NcError::silent_nonfatal);

	NcFile gridFile(grdfilename.c_str(), NcFile::ReadOnly);

	NcVar* grdidV = gridFile.get_var("GRDID");
	if(grdidV==NULL){
		string msg = "Cannot get GRDID in GridInputer";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCVAR_NOT_EXIST);
	}

	int id=-1;
	for (int i=0; i<(int)grdidV->num_vals(); i++){
		grdidV->set_cur(i);
		grdidV->get(&id,1);
		if(id==gid) return i;
	}
	return -1;
}

//YUAN: recid - the order (from ZERO) in the .nc file, clmid - the grid CLM id
// note that: in climate.nc file, the clm id is named as "GRDID", which may be same as grid id, may be not
//            in cohortid.nc file, this id is named as "CLMID"
// We need to hormonize this name confusion issue in the new version of model
int GridInputer::getClmRecID(const int &clmid){
	//netcdf error
	NcError err(NcError::silent_nonfatal);

	NcFile clmFile(clmfilename.c_str(), NcFile::ReadOnly);

	NcVar* clmidV = clmFile.get_var("CLMID");
	if(clmidV==NULL){
		string msg = "Cannot get CLMID in GridInputer::getClmRecID";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
	}

	int id=-1;
	for (int i=0; i<(int)clmidV->num_vals(); i++){
		clmidV->set_cur(i);
		clmidV->get(&id,1);
		if(id==clmid) return i;
	}
	return -1;
}

// read grid-level data (netcdf format) into GridData class
void GridInputer::getGridData(GridData* gd, const int &grdrecid, const int&clmrecid){

  	gd->lat = getLAT(grdrecid);
  	gd->lon = getLON(grdrecid);

  	gd->topsoil = getTOPSOIL(grdrecid);
  	gd->botsoil = getBOTSOIL(grdrecid);

  	gd->act_atm_drv_yr = atm_drv_yr;
  	getClimate(gd->ta, gd->prec, gd->nirr, gd->vap, clmrecid);

  	gd->fri = getFRI(grdrecid);
 	getFireSize(gd->fireyear, gd->fireseason, gd->firesize, 0);  //currently ONLY one fire size dataset available

};

/////////////////////////////////////////////////////////////////

float GridInputer::getLAT(const int & recid ){
	float lat=-1;

	NcError err(NcError::silent_nonfatal);

	NcFile gridFile(grdfilename.c_str(), NcFile::ReadOnly);
 	NcVar* latV = gridFile.get_var("LAT");
 	if(latV==NULL){
 	   string msg = "Cannot get LAT in GridInputer ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	   return -1;
 	}

 	latV->set_cur(recid);
	latV->get(&lat, 1);
	return lat;
} 

float GridInputer::getLON(const int & recid ){
	float lon=-1;

	NcError err(NcError::silent_nonfatal);

	NcFile gridFile(grdfilename.c_str(), NcFile::ReadOnly);
 	NcVar* lonV = gridFile.get_var("LON");
 	if(lonV==NULL){
 	    string msg="Cannot get LON in GridInputer ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

 	}
 	lonV->set_cur(recid);
	lonV->get(&lon, 1);
	return lon;
} 

int GridInputer::getTOPSOIL(const int & recid ){
	int topsoil = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile soilFile(soilfilename.c_str(), NcFile::ReadOnly);
 	NcVar* topsoilV = soilFile.get_var("TOPSOIL");
 	if(topsoilV==NULL){
 	   string msg = "Cannot get TOPSOIL in initSoil ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

 	}

 	topsoilV->set_cur(recid);
	topsoilV->get(&topsoil, 1);
	return topsoil;
} 

int GridInputer::getBOTSOIL(const int & recid ){
	int botsoil = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile soilFile(soilfilename.c_str(), NcFile::ReadOnly);
 	NcVar* botsoilV = soilFile.get_var("BOTSOIL");
 	if(botsoilV==NULL){
 	   string msg = "Cannot get BOTSOIL in initSoil ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

  	}

 	botsoilV->set_cur(recid);
	botsoilV->get(&botsoil, 1);
	return botsoil;
} 

void GridInputer::getClimate(float ta[][12], float prec[][12], float nirr[][12], float vap[][12] ,
		const int & recid){
	int numyr  = atm_drv_yr;
	int nummon = 12;

	//read the data from netcdf file
	NcError err(NcError::silent_nonfatal);

	NcFile climateFile(clmfilename.c_str(), NcFile::ReadOnly);
 	NcVar* taV = climateFile.get_var("TAIR");
 	if(taV==NULL){
 	    string msg = "Cannot get TAIR in GridInputer \n";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}

 	NcVar* nirrV = climateFile.get_var("NIRR");
 	if(nirrV==NULL){
 	    string msg = "Cannot get NIRR in GridInputer \n";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}

 	NcVar* precV = climateFile.get_var("PREC");
 	if(precV==NULL){
 	   string msg = "Cannot get PREC in GridInputer \n";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	NcVar* vapV = climateFile.get_var("VAPO");
 	if(vapV==NULL){
 	    string msg = "Cannot get VAPO in GridInputer ";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	//get the data for recid
	taV->set_cur(recid);
	NcBool nb1 = taV->get(&ta[0][0],1, numyr, nummon);
	if(!nb1){
	 	string msg = "problem in reading TA in  GridInputer::getClimate";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
	
	precV->set_cur(recid);
	NcBool nb2 = precV->get(&prec[0][0],1, numyr, nummon);
	if(!nb2){
		string msg = "problem in reading PREC in  GridInputer::getClimate ";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
	
	nirrV->set_cur(recid);
	NcBool nb3 = nirrV->get(&nirr[0][0], 1,numyr, nummon);
	if(!nb3){
		string msg = "problem in reading NIRR in  GridInputer::getClimate";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	
	vapV->set_cur(recid);
	NcBool nb4 = vapV->get(&vap[0][0],1, numyr, nummon);
	if(!nb4){
	 //cout <<"problem in reading VAPO in Inputer::getDriving Vars \n";
	 	string msg = "problem in reading VAPO in  GridInputer::getClimate";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	
} 

int GridInputer::getFRI(const int & recid ){
	int fri = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile fireFile(firefilename.c_str(), NcFile::ReadOnly);

	NcVar* friV = fireFile.get_var("FRI");
 	if(friV==NULL){
 	   string msg = "Cannot get FRI in FRI data file";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

// 	float fri= (friV->get_rec(recid))->as_float(0);
 	friV->set_cur(recid);
	friV->get(&fri, 1);

	return fri;
}

void GridInputer::getFireSize(int fyear[], int fseason[], int fsize[], const int & recid){
	int numyr = fsize_drv_yr;

	//netcdf error
	NcError err(NcError::silent_nonfatal);

	NcFile fireFile(firefilename.c_str(), NcFile::ReadOnly);

 	NcVar* fsyrV = fireFile.get_var("YEAR");
 	NcVar* fsizeV = fireFile.get_var("SIZE");
 	NcVar* fseasonV = fireFile.get_var("SEASON");
 	if(fsyrV==NULL || fsizeV==NULL || fseasonV==NULL){
 	   string msg = "Cannot get Fire size data in GridInputer::getFireSize";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	//get the data for recid
 	int rec0= 0;
	fsyrV->set_cur(rec0);
	NcBool nb1 = fsyrV->get(&fyear[0],numyr);
	if(!nb1){
	 	string msg = "problem in reading fire year in GridInputer::getFireSize";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}

	fsizeV->set_cur(recid);
	NcBool nb2 = fsizeV->get(&fsize[0],1, numyr);
	if(!nb2){
	 	string msg = "problem in reading fire size in  GridInputer::getFireSize";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}

	fseasonV->set_cur(recid);
	NcBool nb3 = fseasonV->get(&fseason[0],1, numyr);
	if(!nb3){
	 	string msg = "problem in reading fire season in  GridInputer::getFireSize";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}

};

void GridInputer::setModelData(ModelData* mdp){
	md = mdp;
};




