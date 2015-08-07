#include "CohortInputer.h"

CohortInputer::CohortInputer(){
	useseverity =0;
};

CohortInputer::~CohortInputer(){

}

void CohortInputer::init(){
  	if(md!=NULL){
                useseverity = md->useseverity;
  		if(md->runsp){
cout << "lala4 \n";		
   			initEqChtidFile(md->eqchtinputdir);
cout << "lala5 \n";		
 			initSpChtidFile(md->spchtinputdir);
cout << "lala6 \n";		
   			initSpinupFire(md->spchtinputdir);
cout << "lala7 \n";		
	  	}
  
  		if(md->runtr){
  			initSpChtidFile(md->spchtinputdir);
    			initTransientFire(md->trchtinputdir);
    			initTrChtidFile(md->trchtinputdir);
  		}

  		if(md->runsc){
   			initSpChtidFile(md->spchtinputdir);
 			initTrChtidFile(md->trchtinputdir);
    			initScenarioFire(md->scchtinputdir);
   			initScChtidFile(md->scchtinputdir);
  		}

cout << "lala8 \n";		
  		initEqChtidFile(md->eqchtinputdir);
cout << "lala9 \n";		
 		initVegetation(md->eqchtinputdir);
cout << "lala10 \n";		
  		initDrainage(md->eqchtinputdir);
cout << "lala11 \n";		
  
  	}else{
  		string msg = "inputer in CohortInputer::init is null";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_VAR_NULL);
  	}
	
}

void CohortInputer::initEqChtidFile(string & dir){

	eqidfname = dir +"cohortid.nc";

	NcError err(NcError::silent_nonfatal);
	NcFile eqidFile(eqidfname.c_str(), NcFile::ReadOnly);
 	if(!eqidFile.is_valid()){
 		string msg = eqidfname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception( msgc, I_NCFILE_NOT_EXIST);
 	}

 	NcDim* eqchtD = eqidFile.get_dim("EQCHTID");
  	if(!eqchtD->is_valid()){
  		string msg = "CHTD Dimension is not Valid in EqChtidFile";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

}
void CohortInputer::initVegetation(string & dir){
	vegidfname = dir +"vegetation.nc";

	NcError err(NcError::silent_nonfatal);
	NcFile vegetationFile(vegidfname.c_str(), NcFile::ReadOnly);
 	if(!vegetationFile.is_valid()){
 		string msg = vegidfname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception( msgc, I_NCFILE_NOT_EXIST);
 	}
 	
 	NcDim* chtD = vegetationFile.get_dim("EQCHTID");
 	if(!chtD->is_valid()){
 		string msg = "CHTD Dimension is not Valid in Vegetation file";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 	
}

void CohortInputer::initDrainage(string& dir){
	drgidfname = dir +"drainage.nc";

	NcError err(NcError::silent_nonfatal);
	NcFile drainageFile(drgidfname.c_str(), NcFile::ReadOnly);
 	if(!drainageFile.is_valid()){
 		string msg = drgidfname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception( msgc, I_NCFILE_NOT_EXIST);
 	}
 	
 	NcDim* chtD = drainageFile.get_dim("EQCHTID");
 	if(!chtD->is_valid()){
 		string msg = "CHTD Dimension is not Valid in Drainage file";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 	
}

void CohortInputer::initSpChtidFile(string& dir){
	spidfname = dir +"cohortid.nc";

	NcError err(NcError::silent_nonfatal);
	NcFile spchtidFile(spidfname.c_str(), NcFile::ReadOnly);
 	if(!spchtidFile.is_valid()){
 		string msg = spidfname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception( msgc, I_NCFILE_NOT_EXIST);
 	}
 	
 	NcDim* spchtD = spchtidFile.get_dim("SPCHTID");
 	if(!spchtD->is_valid()){
 		string msg = "CHTD Dimension is no Valid in SpChtidFile";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 	
}


void CohortInputer::initTrChtidFile(string& dir){
	tridfname = dir +"cohortid.nc";

	NcError err(NcError::silent_nonfatal);
	NcFile trchtidFile(tridfname.c_str(), NcFile::ReadOnly);
 	if(!trchtidFile.is_valid()){
 		string msg = tridfname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception( msgc, I_NCFILE_NOT_EXIST);
 	}

 	NcDim* trchtD=trchtidFile.get_dim("TRCHTID");
 	if(!trchtD->is_valid()){
 		string msg = "CHTD Dimension is not Valid in TrChtidFile";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

 
}

void CohortInputer::initScChtidFile(string& dir){
	scidfname = dir +"cohortid.nc";

	NcError err(NcError::silent_nonfatal);
	NcFile scchtidFile(scidfname.c_str(), NcFile::ReadOnly);
 	if(!scchtidFile.is_valid()){
 		string msg = scidfname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception( msgc, I_NCFILE_NOT_EXIST);
 	}

 	NcDim* scchtD=scchtidFile.get_dim("SCCHTID");
 	if(!scchtD->is_valid()){
 		string msg = "CHTD Dimension is not Valid in ScChtidFile";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

}

void CohortInputer::initSpinupFire(string& dir){
	spffname = dir +"fire.nc";

	NcError err(NcError::silent_nonfatal);
	NcFile spfireFile(spffname.c_str(), NcFile::ReadOnly);
 	
	if(!spfireFile.is_valid()){
 		string msg = spffname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_NCFILE_NOT_EXIST);
 	}

 	NcDim* chtD = spfireFile.get_dim("SPCHTID");
 	if(!chtD->is_valid()){
 		string msg = "CHTD Dimension is not Valid in spFIRE";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCDIM_NOT_EXIST);
 	}

 	NcDim* yrD = spfireFile.get_dim("YEAR");
 	if(!yrD->is_valid()){
 		string msg = "YEAR Dimension is not Valid in spFIRE";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCDIM_NOT_EXIST);
 	}

 	firesp_drv_yr=yrD->size();  //Yuan: actual atm data years

}

void CohortInputer::initTransientFire(string& dir){
	trffname = dir +"fire.nc";

	NcError err(NcError::silent_nonfatal);
	NcFile trfireFile(trffname.c_str(), NcFile::ReadOnly);
 	if(!trfireFile.is_valid()){
 		string msg = trffname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_NCFILE_NOT_EXIST);
 	}

 	NcDim* chtD = trfireFile.get_dim("TRCHTID");
 	if(!chtD->is_valid()){
 		string msg = "CHTD Dimension is not Valid in trFIRE";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
/*
 	NcDim* numfireD = trfireFile.get_dim("NUMFIRE");
 	if(!numfireD->is_valid()){
  		string msg = "NUMFIRE Dimension is no Valid in initFIRE";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
*/

 	NcDim* yrD = trfireFile.get_dim("YEAR");
 	if(!yrD->is_valid()){
 		string msg = "YEAR Dimension is not Valid in trFIRE";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCDIM_NOT_EXIST);
 	}

 	firetr_drv_yr=yrD->size();  //Yuan: actual atm data years

}

void CohortInputer::initScenarioFire(string& dir){
	scffname = dir +"fire.nc";

	NcError err(NcError::silent_nonfatal);
	NcFile scfireFile(scffname.c_str(), NcFile::ReadOnly);
 	if(!scfireFile.is_valid()){
 		string msg = scffname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_NCFILE_NOT_EXIST);
 	}

 	NcDim* chtD = scfireFile.get_dim("SCCHTID");
 	if(!chtD->is_valid()){
 		string msg = "CHTD Dimension is not valid in scFIRE";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

  	NcDim* yrD = scfireFile.get_dim("YEAR");
 	if(!yrD->is_valid()){
 		string msg = "YEAR Dimension is not Valid in scFIRE";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCDIM_NOT_EXIST);
 	}

 	firesc_drv_yr=yrD->size();  //Yuan: actual atm data years

}


///////////////////////////////////////////////////////////////////////
//YUAN: recid - the order (from ZERO) in the .nc file, chtid - the cohort id
int CohortInputer::getEqRecID(const int &chtid){
	NcError err(NcError::silent_nonfatal);

	NcFile eqidFile(eqidfname.c_str(), NcFile::ReadOnly);
 	NcVar* eqchtidV = eqidFile.get_var("EQCHTID");
 	if(eqchtidV==NULL){
 	   string msg = "Cannot get eqchtid  in initcruididFile ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	int id = -1;
	for (int i=0; i<(int)eqchtidV->num_vals(); i++){
		eqchtidV->set_cur(i);
		eqchtidV->get(&id, 1);
		if(id==chtid) return i;
	}
	return -1;
}

void CohortInputer::getGrdID(int & grdid, const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile idFile(eqidfname.c_str(), NcFile::ReadOnly);
 	NcVar* grdidV = idFile.get_var("GRDID");
 	if(grdidV==NULL){
  	   string msg = "Cannot get GRDID in eq cohortid file";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	grdidV->set_cur(recid);
	grdidV->get(&grdid, 1);

}

void CohortInputer::getVegetation(int & vtype,  const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile vegetationFile(vegidfname.c_str(), NcFile::ReadOnly);
 	NcVar* vegV = vegetationFile.get_var("VEGID");
 	if(vegV==NULL){
  	   string msg = "Cannot get vegetation  in initVeg ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	vegV->set_cur(recid);
	vegV->get(&vtype, 1);

}

void CohortInputer::getDrainage(int & dtype, const int & recid){
	NcError err(NcError::silent_nonfatal);

	NcFile drainageFile(drgidfname.c_str(), NcFile::ReadOnly);
 	NcVar* drainV = drainageFile.get_var("DRAINID");
 	if(drainV==NULL){
  	   string msg = "Cannot get drainage  in initDrainage ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	drainV->set_cur(recid);
	drainV->get(&dtype, 1);

}

int CohortInputer::getSpRecID(const int &chtid){
	NcError err(NcError::silent_nonfatal);


	NcFile spchtidFile(spidfname.c_str(), NcFile::ReadOnly);
 	NcVar* spchtidV = spchtidFile.get_var("SPCHTID");
 	if(spchtidV==NULL){
 	   string msg = "Cannot get spchtid  in SpChtidFile ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	int id=-1;
	for (int i=0; i<(int)spchtidV->num_vals(); i++){
		spchtidV->set_cur(i);
		spchtidV->get(&id, 1);
		if(id==chtid) return i;
	}

	return -1;
}

int CohortInputer::getTrRecID(const int &chtid){
	NcError err(NcError::silent_nonfatal);

	NcFile trchtidFile(tridfname.c_str(), NcFile::ReadOnly);
 	NcVar* trchtidV = trchtidFile.get_var("TRCHTID");
 	if(trchtidV==NULL){
 	   string msg = "Cannot get trchtid  in TrChtidFile ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	int id=-1;
	for (int i=0; i<(int)trchtidV->num_vals(); i++){
		trchtidV->set_cur(i);
		trchtidV->get(&id, 1);
		if(id==chtid) return i;
	}

	return -1;
}

int CohortInputer::getScRecID(const int &chtid){
	NcError err(NcError::silent_nonfatal);

	NcFile scchtidFile(scidfname.c_str(), NcFile::ReadOnly);
 	NcVar* scchtidV = scchtidFile.get_var("SCCHTID");
 	if(scchtidV==NULL){
 	   string msg = "Cannot get scchtid  in ScChtidFile ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	int id=-1;
	for (int i=0; i<(int)scchtidV->num_vals(); i++){
		scchtidV->set_cur(i);
		scchtidV->get(&id, 1);
		if(id==chtid) return i;
	}

	return -1;
}

void CohortInputer::getEqchtid5SpFile(int & eqchtid,  const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile spchtidFile(spidfname.c_str(), NcFile::ReadOnly);
 	NcVar* eqchtid5spV = spchtidFile.get_var("EQCHTID");
 	if(eqchtid5spV==NULL){
 	   string msg = "Cannot get eqchtid in SpChtidFile ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	eqchtid5spV->set_cur(recid);
	eqchtid5spV->get(&eqchtid, 1);

}

void CohortInputer::getSpchtid5TrFile(int & spchtid,  const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile trchtidFile(tridfname.c_str(), NcFile::ReadOnly);
 	NcVar* spchtid5trV = trchtidFile.get_var("SPCHTID");
 	if(spchtid5trV==NULL){
 	   string msg = "Cannot get spchtid  in TrChtidFile ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

    spchtid5trV->set_cur(recid);
    spchtid5trV->get(&spchtid, 1);

}


void CohortInputer::getTrchtid5ScFile(int & trchtid,  const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile scchtidFile(scidfname.c_str(), NcFile::ReadOnly);
 	NcVar* trchtid5scV = scchtidFile.get_var("TRCHTID");
 	if(trchtid5scV==NULL){
 	   string msg = "Cannot get trchtid  in ScChtidFile ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

    trchtid5scV->set_cur(recid);
    trchtid5scV->get(&trchtid, 1);

}

//////////////////////////////////Fire Occur////////////////////////////


void CohortInputer::getSpinupFire(int firedate[MAX_SP_YR], int firemonth[MAX_SP_YR],int fireyear[MAX_SP_YR],int firearea[MAX_SP_YR], const int &recid){


	int numyr = firesp_drv_yr;
	NcError err(NcError::silent_nonfatal);
	NcFile spfireFile(spffname.c_str(), NcFile::ReadOnly);


  	NcVar* firedateV = spfireFile.get_var("DOB");
 	NcVar* firemonthV = spfireFile.get_var("MOB");
 	NcVar* fireyearV = spfireFile.get_var("YOB");
 	NcVar* fireareaV = spfireFile.get_var("AOB");

	if(firedateV==NULL || firemonthV==NULL || fireyearV==NULL || fireareaV==NULL){ 
 	   string msg = "Cannot get Fire in getSpinupFire";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

//cout <<"numyr"<<numyr<<"\n";
	firedateV->set_cur(recid);
	NcBool nb1 = firedateV->get(&firedate[0],1, numyr);
	if(!nb1){
	 	string msg = "problem in reading fire date in getSpinupFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	firemonthV->set_cur(recid);
	NcBool nb2 = firemonthV->get(&firemonth[0],1, numyr);
	if(!nb2){
	 	string msg = "problem in reading fire month in getSpinupFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	fireyearV->set_cur(recid);
	NcBool nb3 = fireyearV->get(&fireyear[0],1, numyr);
	if(!nb3){
	 	string msg = "problem in reading fire year in getSpinupFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	fireareaV->set_cur(recid);
	NcBool nb4 = fireareaV->get(&firearea[0],1, numyr);
	if(!nb4){
	 	string msg = "problem in reading fire area in getSpinupFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	
}

void CohortInputer::getTransientFire(int firedate[MAX_TR_YR], int firemonth[MAX_TR_YR],int fireyear[MAX_TR_YR],int firearea[MAX_TR_YR], const int &recid){


	int numyr = firetr_drv_yr;
	NcError err(NcError::silent_nonfatal);
	NcFile trfireFile(trffname.c_str(), NcFile::ReadOnly);

  	NcVar* firedateV = trfireFile.get_var("DOB");
 	NcVar* firemonthV = trfireFile.get_var("MOB");
 	NcVar* fireyearV = trfireFile.get_var("YOB");
 	NcVar* fireareaV = trfireFile.get_var("AOB");

	if(firedateV==NULL || firemonthV==NULL || fireyearV==NULL || fireareaV==NULL){ 
 	   string msg = "Cannot get Fire in getTransientFire";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	firedateV->set_cur(recid);
	NcBool nb1 = firedateV->get(&firedate[0],1, numyr);
	if(!nb1){
	 	string msg = "problem in reading fire date in  getTransientFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}

	firemonthV->set_cur(recid);
	NcBool nb2 = firemonthV->get(&firemonth[0],1, numyr);
	if(!nb2){
	 	string msg = "problem in reading fire month in getTransientFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}

	fireyearV->set_cur(recid);
	NcBool nb3 = fireyearV->get(&fireyear[0],1, numyr);
	if(!nb3){
	 	string msg = "problem in reading fire year in getTransientFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}

	fireareaV->set_cur(recid);
	NcBool nb4 = fireareaV->get(&firearea[0],1, numyr);
	if(!nb4){
	 	string msg = "problem in reading fire area in getTransientFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	
}

void CohortInputer::getScenarioFire(int firedate[MAX_SC_YR], int firemonth[MAX_SC_YR],int fireyear[MAX_SC_YR],int firearea[MAX_SC_YR], const int &recid){


	int numyr = firesc_drv_yr;
	NcError err(NcError::silent_nonfatal);
	NcFile scfireFile(scffname.c_str(), NcFile::ReadOnly);


  	NcVar* firedateV = scfireFile.get_var("DOB");
 	NcVar* firemonthV = scfireFile.get_var("MOB");
 	NcVar* fireyearV = scfireFile.get_var("YOB");
 	NcVar* fireareaV = scfireFile.get_var("AOB");

	if(firedateV==NULL || firemonthV==NULL || fireyearV==NULL || fireareaV==NULL){ 
 	   string msg = "Cannot get Fire in getScenarioFire";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	firedateV->set_cur(recid);
	NcBool nb1 = firedateV->get(&firedate[0],1, numyr);
	if(!nb1){
	 	string msg = "problem in reading fire date in  getScenarioFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	firemonthV->set_cur(recid);
	NcBool nb2 = firemonthV->get(&firemonth[0],1, numyr);
	if(!nb2){
	 	string msg = "problem in reading fire month in  getScenarioFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	fireyearV->set_cur(recid);
	NcBool nb3 = fireyearV->get(&fireyear[0],1, numyr);
	if(!nb3){
	 	string msg = "problem in reading fire year in  getScenarioFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	fireareaV->set_cur(recid);
	NcBool nb4 = fireareaV->get(&firearea[0],1, numyr);
	if(!nb4){
	 	string msg = "problem in reading fire area in  getScenarioFire";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
	
}


/*
void CohortInputer::getSpinupFireOccur(int spoccur[MAX_SP_FIR_OCR_NUM], const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile spfireFile(spffname.c_str(), NcFile::ReadOnly);
 	NcVar* spoccurV = spfireFile.get_var("FIRE");
 	if(spoccurV==NULL){
 	   string msg = "Cannot get Fire in spFire ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	spoccurV->set_cur(recid);
	NcBool nb1 = spoccurV->get(&spoccur[0],1, MAX_SP_FIR_OCR_NUM);
	if(!nb1){
	    string msg = "problem in reading spfire year data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCVAR_NOT_EXIST);
	}
	
}

void CohortInputer::getSpinupFireSeason(int spseason[MAX_SP_FIR_OCR_NUM], const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile spfireFile(spffname.c_str(), NcFile::ReadOnly);
 	NcVar* spseasonV = spfireFile.get_var("SEASON");
 	if(spseasonV==NULL){
 	   string msg = "Cannot get Fire Season in spFire ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
  	}
	
	spseasonV->set_cur(recid);
	NcBool nb1 = spseasonV->get(&spseason[0],1, MAX_SP_FIR_OCR_NUM);
	if(!nb1){
	    string msg = "problem in reading fire data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCVAR_NOT_EXIST);
	}
}

void CohortInputer::getSpinupSeverity(int spsev[MAX_SP_FIR_OCR_NUM], const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile spfireFile(spffname.c_str(), NcFile::ReadOnly);
	NcVar* spsevV = spfireFile.get_var("SEVERITY");
	if(spsevV==NULL){
   		string msg = "Cannot get severity in spFire ";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
	}

	spsevV->set_cur(recid);
	NcBool nb1 = spsevV->get(&spsev[0],1, MAX_SP_FIR_OCR_NUM);
	if(!nb1){
	    string msg = "problem in reading spfire severity data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCVAR_NOT_EXIST);
	}
	
}


void CohortInputer::getTransientFireOccur(int troccur[MAX_TR_FIR_OCR_NUM], const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile trfireFile(trffname.c_str(), NcFile::ReadOnly);
 	NcVar* troccurV = trfireFile.get_var("FIRE");
 	if(troccurV==NULL){
 	   string msg = "Cannot get Fire Occur in trFire ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	troccurV->set_cur(recid);
	NcBool nb1 = troccurV->get(&troccur[0],1, MAX_TR_FIR_OCR_NUM);
	if(!nb1){
	    string msg = "problem in reading fire data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCVAR_NOT_EXIST);
	}

}

void CohortInputer::getTransientFireSeason(int trseason[MAX_TR_FIR_OCR_NUM], const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile trfireFile(trffname.c_str(), NcFile::ReadOnly);
 	NcVar* trseasonV = trfireFile.get_var("SEASON");
 	if(trseasonV==NULL){
 	   string msg = "Cannot get Fire Season in trFire ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	trseasonV->set_cur(recid);
	NcBool nb1 = trseasonV->get(&trseason[0],1, MAX_TR_FIR_OCR_NUM);
	if(!nb1){
	    string msg = "problem in reading fire season data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCVAR_NOT_EXIST);
	}

}

void CohortInputer::getTransientSeverity(int trsev[MAX_TR_FIR_OCR_NUM], const int &recid){
	NcError err(NcError::silent_nonfatal);

	NcFile trfireFile(trffname.c_str(), NcFile::ReadOnly);
	NcVar* trsevV = trfireFile.get_var("SEVERITY");
		if(trsevV==NULL){
	   		string msg = "Cannot get trFire severity";
	 		char* msgc = const_cast<char*> (msg.c_str());
	 		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
		}
	
	trsevV->set_cur(recid);
	NcBool nb1 = trsevV->get(&trsev[0],1, MAX_TR_FIR_OCR_NUM);
	if(!nb1){
	    string msg = "problem in reading transient fire severity data";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc, I_NCVAR_NOT_EXIST);
	}
	
}
*/







void CohortInputer::getChtID(int & chtid,  const int & recid){
	NcError err(NcError::silent_nonfatal);
	string idFilename="";
	string idVarname="";
	if (md->runeq) {
		idFilename=eqidfname;
		idVarname="EQCHTID";
	} else if (md->runsp) {
		idFilename=spidfname;
		idVarname="SPCHTID";
	} else if (md->runtr) {
		idFilename=tridfname;
		idVarname="TRCHTID";
	} else if (md->runsc) {
		idFilename=scidfname;
		idVarname="SCCHTID";
	}

	NcFile cohortidFile(idFilename.c_str(), NcFile::ReadOnly);

 	NcVar* chtidV = cohortidFile.get_var(idVarname.c_str());
 	if(chtidV==NULL){
 	   string msg = "Cannot get eq/sp/trchtid in cohortid File ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	chtidV->set_cur(recid);
	chtidV->get(&chtid, 1);

}

void CohortInputer::getClmID(int & clmid,  const int & recid){
	NcError err(NcError::silent_nonfatal);
	string idFilename="";
	if (md->runeq) {
		idFilename=eqidfname;
	} else if (md->runsp) {
		idFilename=spidfname;
	} else if (md->runtr) {
		idFilename=tridfname;
	} else if (md->runsc) {
		idFilename=scidfname;
	}

	NcFile cohortidFile(idFilename.c_str(), NcFile::ReadOnly);

 	NcVar* clmidV = cohortidFile.get_var("CLMID");
 	if(clmidV==NULL){
 	   string msg = "Cannot get clmid in cohortid File ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	clmidV->set_cur(recid);
	clmidV->get(&clmid, 1);

}

void CohortInputer::setModelData(ModelData* mdp){
   md = mdp;
};
