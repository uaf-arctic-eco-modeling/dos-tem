#include "GridInputer.h"

GridInputer::GridInputer(){
	
};

GridInputer::~GridInputer(){

}

void GridInputer::init(){
  if(md!=NULL){

	  initLatlon(md->grdinputdir);
	  initSoil(md->grdinputdir);
	  initTopo(md->grdinputdir);

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

	  } else {
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

void GridInputer::initTopo(string& dir){
	//netcdf error
	NcError err(NcError::silent_nonfatal);

	topofilename = dir +"topo.nc";
	NcFile topoFile(topofilename.c_str(), NcFile::ReadOnly);
 	if(!topoFile.is_valid()){
 		string msg = topofilename+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_NCFILE_NOT_EXIST);
 	}
 	
 	NcDim* grdD = topoFile.get_dim("GRDID");
 	if(!grdD->is_valid()){
 		string msg = "GRDID Dimension is not Valid in Topo data";
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
		if(id==clmid) {
			return i;
		}
	}
	return -1;
}

// read grid-level data (netcdf format) into GridData class
void GridInputer::getGridData(GridData* gd, const int &grdrecid, const int&clmrecid){

  	gd->lat = getLAT(grdrecid);
  	gd->lon = getLON(grdrecid);
		//cout<<"lat :"<<gd->lat<<"\n";
  	gd->topclay = getTOPCLAY(grdrecid);
 	gd->botclay = getBOTCLAY(grdrecid);
  	gd->topsand = getTOPSAND(grdrecid);
  	gd->botsand = getBOTSAND(grdrecid);
  	gd->topsilt = getTOPSILT(grdrecid);
  	gd->botsilt = getBOTSILT(grdrecid);
  	gd->elevation = getELEVATION(grdrecid);
  	gd->slope = getSLOPE(grdrecid);
  	gd->aspect = getASPECT(grdrecid);
  	gd->flowacc = getFLOWACC(grdrecid);

  	gd->act_atm_drv_yr = atm_drv_yr;
  	getClimate(gd->ta, gd->prec, gd->nirr, gd->vap, clmrecid);
 	gd->fri = getFRI(grdrecid);
		//cout<<"fri :"<<gd->fri<<"\n";
  	getFireSize(gd->fireyear, gd->fireseason, gd->fireDOB, gd->firesize, gd->fireAOB, 0);  //currently ONLY one fire size dataset available

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

int GridInputer::getTOPCLAY(const int & recid ){
	int topclay = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile soilFile(soilfilename.c_str(), NcFile::ReadOnly);
 	NcVar* topclayV = soilFile.get_var("CLAYTOP");
 	if(topclayV==NULL){
 	   string msg = "Cannot get CLAYTOP in initSoil ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

 	}

 	topclayV->set_cur(recid);
	topclayV->get(&topclay, 1);
	return topclay;
} 
int GridInputer::getTOPSAND(const int & recid ){
	int topsand = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile soilFile(soilfilename.c_str(), NcFile::ReadOnly);
 	NcVar* topsandV = soilFile.get_var("SANDTOP");
 	if(topsandV==NULL){
 	   string msg = "Cannot get SANDTOP in initSoil ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

 	}

 	topsandV->set_cur(recid);
	topsandV->get(&topsand, 1);
	return topsand;
} 
int GridInputer::getTOPSILT(const int & recid ){
	int topsilt = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile soilFile(soilfilename.c_str(), NcFile::ReadOnly);
 	NcVar* topsiltV = soilFile.get_var("SILTTOP");
 	if(topsiltV==NULL){
 	   string msg = "Cannot get SILTTOP in initSoil ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

 	}

 	topsiltV->set_cur(recid);
	topsiltV->get(&topsilt, 1);
	return topsilt;
} 

int GridInputer::getBOTCLAY(const int & recid ){
	int botclay = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile soilFile(soilfilename.c_str(), NcFile::ReadOnly);
 	NcVar* botclayV = soilFile.get_var("CLAYBOT");
 	if(botclayV==NULL){
 	   string msg = "Cannot get CLAYBOT in initSoil ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

  	}

 	botclayV->set_cur(recid);
	botclayV->get(&botclay, 1);
	return botclay;
} 
int GridInputer::getBOTSAND(const int & recid ){
	int botsand = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile soilFile(soilfilename.c_str(), NcFile::ReadOnly);
 	NcVar* botsandV = soilFile.get_var("SANDBOT");
 	if(botsandV==NULL){
 	   string msg = "Cannot get SANDBOT in initSoil ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

  	}

 	botsandV->set_cur(recid);
	botsandV->get(&botsand, 1);
	return botsand;
} 
int GridInputer::getBOTSILT(const int & recid ){
	int botsilt = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile soilFile(soilfilename.c_str(), NcFile::ReadOnly);
 	NcVar* botsiltV = soilFile.get_var("SILTBOT");
 	if(botsiltV==NULL){
 	   string msg = "Cannot get SILTBOT in initSoil ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

  	}

 	botsiltV->set_cur(recid);
	botsiltV->get(&botsilt, 1);
	return botsilt;
} 

float GridInputer::getELEVATION(const int & recid ){
	float elev = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile topoFile(topofilename.c_str(), NcFile::ReadOnly);
 	NcVar* elevV = topoFile.get_var("ELEV");
 	if(elevV==NULL){
 	   string msg = "Cannot get ELEVATION (ELEV) in initTopo ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

  	}
 	elevV->set_cur(recid);
	elevV->get(&elev, 1);
	return elev;
} 

float GridInputer::getSLOPE(const int & recid ){
	float slope = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile topoFile(topofilename.c_str(), NcFile::ReadOnly);
 	NcVar* slopeV = topoFile.get_var("SLOPE");
 	if(slopeV==NULL){
 	   string msg = "Cannot get SLOPE in initTopo ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

  	}
 	slopeV->set_cur(recid);
	slopeV->get(&slope, 1);
	return slope;
} 

float GridInputer::getASPECT(const int & recid ){
	float asp = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile topoFile(topofilename.c_str(), NcFile::ReadOnly);
 	NcVar* aspV = topoFile.get_var("ASP");
 	if(aspV==NULL){
 	   string msg = "Cannot get ASPECT (ASP) in initTopo ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

  	}
 	aspV->set_cur(recid);
	aspV->get(&asp, 1);
	return asp;
} 

float GridInputer::getFLOWACC(const int & recid ){
	float flowacc = -1;
	NcError err(NcError::silent_nonfatal);

	NcFile topoFile(topofilename.c_str(), NcFile::ReadOnly);
 	NcVar* flowaccV = topoFile.get_var("FA");
 	if(flowaccV==NULL){
 	   string msg = "Cannot get FLOW ACCUMULATION (FA) in initTopo ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);

  	}
 	flowaccV->set_cur(recid);
	flowaccV->get(&flowacc, 1);
	return flowacc;
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

void GridInputer::getFireSize(int fyear[], int fseason[], int fDOB[], int fsize[], int fAOB[], const int & recid){
	int numyr = fsize_drv_yr;

	//netcdf error
	NcError err(NcError::silent_nonfatal);

	NcFile fireFile(firefilename.c_str(), NcFile::ReadOnly);

 	NcVar* fsyrV = fireFile.get_var("YEAR");
 	NcVar* fsizeV = fireFile.get_var("SIZE");
 	NcVar* fAOBV = fireFile.get_var("AOB");
 	NcVar* fseasonV = fireFile.get_var("SEASON");
 	NcVar* fDOBV = fireFile.get_var("DOB");

 	if(fsyrV==NULL || fsizeV==NULL || fAOBV==NULL || fseasonV==NULL || fDOBV==NULL){ 
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
	NcBool nb2 = fsizeV->get(&fsize[0], numyr);
	if(!nb2){
	 	string msg = "problem in reading fire size in  GridInputer::getFireSize";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
	fAOBV->set_cur(recid);
	NcBool nb3 = fAOBV->get(&fAOB[0], numyr);
	if(!nb3){
	 	string msg = "problem in reading area of burn (AOB) in  GridInputer::getFireSize";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}

	fseasonV->set_cur(recid);
	NcBool nb4 = fseasonV->get(&fseason[0],1, numyr);
	if(!nb4){
	 	string msg = "problem in reading fire season in  GridInputer::getFireSize";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	fDOBV->set_cur(recid);
	NcBool nb5 = fDOBV->get(&fDOB[0],1, numyr);
	if(!nb5){
	 	string msg = "problem in reading date of burn (DOB) in  GridInputer::getFireSize";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}

};

void GridInputer::setModelData(ModelData* mdp){
	md = mdp;
};




