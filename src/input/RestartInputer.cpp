#include "RestartInputer.h"

/*! constructor */
 RestartInputer::RestartInputer(){
 
};

 RestartInputer::~RestartInputer(){
 	//cout<< "closing output files in RestartInputer \n";
   
    if(restartFile!=NULL){
    	restartFile->close();
	delete restartFile;
    }

};

void RestartInputer::init(string & dirfile){
 	
//	string filename =outputdir+ "restart.nc";
	string filename =dirfile;    //Yuan: input file name with dir 

	restartFile = new NcFile(filename.c_str(), NcFile::ReadOnly);
	if(!restartFile->is_valid()){
 		string msg = filename+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception(msgc, I_NCFILE_NOT_EXIST);
 	}
	
	chtD = restartFile->get_dim("CHTID");
 	if(!chtD->is_valid()){
 		string msg = "Cohort Dimension is no Valid in RestartInputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 	
 	snowlayerD = restartFile->get_dim("SNOWLAYER");
 	if(!snowlayerD->is_valid()){
 		string msg = "snowlayer Dimension is no Valid in reaterinputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 	
    soillayerD = restartFile->get_dim("SOILLAYER");
 	if(!soillayerD->is_valid()){
 		string msg = "soillayer Dimension is no Valid in reaterinputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 	
 	rocklayerD = restartFile->get_dim("ROCKLAYER");
 	if(!rocklayerD->is_valid()){
  		string msg = "rocklayer Dimension is no Valid in reaterinputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 	
    frontD = restartFile->get_dim("FRONTLAYER");
 	if(!frontD->is_valid()){
 		string msg = " front Dimension is no Valid in reaterinputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 	
 	meanyearD = restartFile->get_dim("MEANYEAR");
 	if(!meanyearD->is_valid()){
  		string msg = " mean yearDimension is no Valid in reaterinputer::init";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}
 	
 	chtidV = restartFile->get_var("CHTID");
 	if(chtidV==NULL){
 	   string msg = "Cannot get chtidv in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	errcodeV = restartFile->get_var("ERRCODE");
 	if(errcodeV==NULL){
 	   string msg = "Cannot get errcodev in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	permaV = restartFile->get_var("PERMAFROST");
 	if(permaV==NULL){
 	   string msg = "Cannot get permav in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	TSsnowV = restartFile->get_var("TSsnow");
 	if(TSsnowV==NULL){
 	   string msg = "Cannot get TSsnow in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	DZsnowV = restartFile->get_var("DZsnow");
 	if(DZsnowV==NULL){
 	   string msg = "Cannot get DZsnow in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	LIQsnowV = restartFile->get_var("LIQsnow");
 	if(LIQsnowV==NULL){
 	   string msg = "Cannot get LIQsnow in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	ICEsnowV = restartFile->get_var("ICEsnow");
 	if(ICEsnowV==NULL){
 	   string msg = "Cannot get ICEsnow in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	AGEsnowV = restartFile->get_var("AGEsnow");
 	if(AGEsnowV==NULL){
 	   string msg = "Cannot get AGEsnow in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	RHOsnowV = restartFile->get_var("RHOsnow");
 	if(RHOsnowV==NULL){
 	   string msg = "Cannot get RHOsnow in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	TSsoilV = restartFile->get_var("TSsoil");
 	if(TSsoilV==NULL){
 	   string msg = "Cannot get TSsoil in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	DZsoilV = restartFile->get_var("DZsoil");
 	if(DZsoilV==NULL){
 	   string msg = "Cannot get DZsoil in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	LIQsoilV = restartFile->get_var("LIQsoil");
 	if(LIQsoilV==NULL){
 	   string msg = "Cannot get LIQsoil in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	frontFTV = restartFile->get_var("frontFT");
 	if(frontFTV==NULL){
 	   string msg = "Cannot get frontFT in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	frontZV = restartFile->get_var("frontZ");
 	if(frontZV==NULL){
 	   string msg = "Cannot get frontZ in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	ICEsoilV = restartFile->get_var("ICEsoil");
 	if(ICEsoilV==NULL){
 	   string msg = "Cannot get ICEsoil in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	TYPEsoilV = restartFile->get_var("TYPEsoil");
 	if(TYPEsoilV==NULL){
 	   string msg = "Cannot get TYPEsoil in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}
 	
 	TYPEminV = restartFile->get_var("TYPEmin");
 	if(TYPEminV==NULL){
 	   string msg = "Cannot get TYPEmin in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	FROZENsoilV = restartFile->get_var("FROZENsoil");
 	if(FROZENsoilV==NULL){
 	   string msg = "Cannot get FROZENsoil in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	NONCsoilV = restartFile->get_var("NONCsoil");
 	if(NONCsoilV==NULL){
 	   string msg = "Cannot get NONCsoil in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	REACsoilV = restartFile->get_var("REACsoil");
 	if(REACsoilV==NULL){
 	   string msg = "Cannot get REACsoil in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	TSrockV = restartFile->get_var("TSrock");
 	if(TSrockV==NULL){
 	   string msg = "Cannot get TSrock in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}
 	
 	DZrockV = restartFile->get_var("DZrock");
 	if(DZrockV==NULL){
 	   string msg = "Cannot get DZrock in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
	frontZV = restartFile->get_var("frontZ");
 	if(frontZV==NULL){
 	   string msg = "Cannot get frontZ in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	frontFTV = restartFile->get_var("frontFT");
 	if(frontFTV==NULL){
 	   string msg = "Cannot get frontFT in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
	
	solnV = restartFile->get_var("SOLN");
 	if(solnV==NULL){
 	   string msg = "Cannot get soln in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	avlnV = restartFile->get_var("AVLN");
 	if(avlnV==NULL){
 	   string msg = "Cannot get avln in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	wdebrisV = restartFile->get_var("WDEBRIS");
 	if(wdebrisV==NULL){
 	   string msg = "Cannot get wdebris in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}
	
	strnV = restartFile->get_var("STRN");
 	if(strnV==NULL){
 	   string msg = "Cannot get strn in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}
 	
 	stonV = restartFile->get_var("STON");
 	if(stonV==NULL){
 	   string msg = "Cannot get ston in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	vegcV = restartFile->get_var("VEGC");
 	if(vegcV==NULL){
 	   string msg = "Cannot get vegc in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	deadcV = restartFile->get_var("DEADC");
 	if(deadcV==NULL){
 	   string msg = "Cannot get deadc in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	deadnV = restartFile->get_var("DEADN");
 	if(deadnV==NULL){
 	   string msg = "Cannot get deadn in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

 	laiV = restartFile->get_var("LAI");
 	if(laiV==NULL){
 	   string msg = "Cannot get lai in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
	prveetmxV = restartFile->get_var("PRVEETMX");
 	if(prveetmxV==NULL){
 	   string msg = "Cannot get prveetmx in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	prvpetmxV = restartFile->get_var("PRVPETMX");
 	if(prvpetmxV==NULL){
 	   string msg = "Cannot get prvpetmx in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	foliagemxV = restartFile->get_var("FOLIAGEMX");
 	if(foliagemxV==NULL){
 	   string msg = "Cannot get foliage in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}
 	
 	unnormleafV = restartFile->get_var("UNNORMLEAF");
 	if(unnormleafV==NULL){
 	   string msg = "Cannot get unnormleaf in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 		prvunnormleafmxV = restartFile->get_var("PRVUNNORMLEAFMX");
 	if(prvunnormleafmxV==NULL){
 	   string msg = "Cannot get prvunnormleafmx in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 		prvtoptV = restartFile->get_var("PRVTOPT");
 	if(prvtoptV==NULL){
 	   string msg = "Cannot get prvtopt in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	c2nV = restartFile->get_var("C2N");
 	if(c2nV==NULL){
 	   string msg = "Cannot get c2n in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	 kdfibV = restartFile->get_var("KDFIB");
 	if(kdfibV==NULL){
 	   string msg = "Cannot get kdfib in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	 kdhumV = restartFile->get_var("KDHUM");
 	if(kdhumV==NULL){
 	   string msg = "Cannot get kdhum in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}
 	 kdminV = restartFile->get_var("KDMIN");
 	if(kdminV==NULL){
 	   string msg = "Cannot get kdmin in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	 kdslowV = restartFile->get_var("KDSLOW");
 	if(kdslowV==NULL){
 	   string msg = "Cannot get kdslow in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}

	ysfV = restartFile->get_var("YSF");
 	if(ysfV==NULL){
 	   string msg = "Cannot get ysf in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}
 	
	burnednV = restartFile->get_var("BURNEDN");
 	if(burnednV==NULL){
 	   string msg = "Cannot get burnedn in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_NOT_EXIST);
 	}
 	
  
 	toptAV = restartFile->get_var("TOPTA");
 	if(toptAV==NULL){
 	   string msg = "Cannot get toptA in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	unnormleafmxAV = restartFile->get_var("UNNORMLEAFMXA");
 	if(unnormleafmxAV==NULL){
 	   string msg = "Cannot get unnormleafmxA in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	petmxAV = restartFile->get_var("PETMXA");
 	if(petmxAV==NULL){
 	   string msg = "Cannot get petmxA in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
 	
 	eetmxAV = restartFile->get_var("EETMXA");
 	if(eetmxAV==NULL){
 	   string msg = "Cannot get eetmxA in restartinputer::init ";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_NOT_EXIST);
 	}
  
 	
};

////////////////////////////////////////////////////////////////////////////////////////
//Yuan: cid is the cohort id, but not exactly the record id in the .nc file
int RestartInputer::getRecordId(const int &chtid){

	int chtno = (int)chtD->size();
	int id;
	for (int i=0; i<chtno; i++){
		getChtId(id, i);
		if (id==chtid) return i;
		
	}
	cout << "cohort "<< chtid<<" NOT exists in RestartInputer\n";	
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////
//Yuan: the cid in the following is actually the record id

void RestartInputer::getChtId(int &chtid, const int &cid){       
	
	chtidV->set_cur(cid);
	NcBool nb1 = chtidV->get(&chtid,1);
	if(!nb1){	 
	 string msg = "problem in reading chtid in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getERRCODE(int & errcode, const int &cid){       
	
	errcodeV->set_cur(cid);
	NcBool nb1 = errcodeV->get(&errcode,1);
	if(!nb1){	 
	 string msg = "problem in reading errcode in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getPERMAFROST(int & perma, const int &cid){

	permaV->set_cur(cid);
	NcBool nb1 = permaV->get(&perma,1);
	if(!nb1){
	 string msg = "problem in reading permafrost in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getYSF(int & ysf, const int &cid){
	
	ysfV->set_cur(cid);
	NcBool nb1 = ysfV->get(&ysf,1);
	if(!nb1){	 
	 string msg = "problem in reading ysf in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getBURNEDN(double & burnedn, const int &cid){
	
	burnednV->set_cur(cid);
	NcBool nb1 = burnednV->get(&burnedn,1);
	if(!nb1){
	 
	 string msg = "problem in reading burnedn in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}


void RestartInputer::getVEGC(double & vegc, const int &cid){
	
	vegcV->set_cur(cid);
	NcBool nb1 = vegcV->get(&vegc,1);
	if(!nb1){
	 string msg = "problem in reading vegc in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getSTRN(double & strn, const int &cid){
	
	strnV->set_cur(cid);
	NcBool nb1 = strnV->get(&strn,1);
	if(!nb1){
	 string msg = "problem in reading strn in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}


void RestartInputer::getUNNORMLEAF(double & unnormleaf, const int &cid){
	
	unnormleafV->set_cur(cid);
	NcBool nb1 = unnormleafV->get(&unnormleaf,1);
	if(!nb1){
	 
	 string msg = "problem in reading unnormleaf in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getLAI(double & lai, const int &cid){
	
	laiV->set_cur(cid);
	NcBool nb1 = laiV->get(&lai,1);
	if(!nb1){
	 
	 string msg = "problem in reading lai in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getPRVPETMX(double & prvpetmx, const int &cid){
	
	prvpetmxV->set_cur(cid);
	NcBool nb1 = prvpetmxV->get(&prvpetmx,1);
	if(!nb1){
	 
	 string msg = "problem in reading prvpetmx in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getPRVEETMX(double & prveetmx, const int &cid){
	
	prveetmxV->set_cur(cid);
	NcBool nb1 = prveetmxV->get(&prveetmx,1);
	if(!nb1){
	 
	 string msg = "problem in reading prveetmx in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getFOLIAGEMX(double & foliagemx, const int &cid){
	
	foliagemxV->set_cur(cid);
	NcBool nb1 = foliagemxV->get(&foliagemx,1);
	if(!nb1){
	 
	 string msg = "problem in reading foliagemx in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}
void RestartInputer::getPRVTOPT(double & prvtopt, const int &cid){
	
	prvtoptV->set_cur(cid);
	NcBool nb1 = prvtoptV->get(&prvtopt,1);
	if(!nb1){
	 
	 string msg = "problem in reading prvtopt in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getC2N(double & c2n, const int &cid){
	
	c2nV->set_cur(cid);
	NcBool nb1 = c2nV->get(&c2n,1);
	if(!nb1){
	 
	 string msg = "problem in reading c2n in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}


void RestartInputer::getKDFIB(double & kdfib, const int &cid){
	
	kdfibV->set_cur(cid);
	NcBool nb1 = kdfibV->get(&kdfib,1);
	if(!nb1){
	 
	 string msg = "problem in reading kdfib in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}


void RestartInputer::getKDHUM(double & kdhum, const int &cid){
	
	kdhumV->set_cur(cid);
	NcBool nb1 = kdhumV->get(&kdhum,1);
	if(!nb1){
	 
	 string msg = "problem in reading kdhum in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getKDMIN(double & kdmin, const int &cid){
	
	kdminV->set_cur(cid);
	NcBool nb1 = kdminV->get(&kdmin,1);
	if(!nb1){
	 
	 string msg = "problem in reading kdmin in RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}


void RestartInputer::getKDSLOW(double & kdslow, const int &cid){
	
	kdslowV->set_cur(cid);
	NcBool nb1 = kdslowV->get(&kdslow,1);
	if(!nb1){
	 
	 string msg = "problem in reading kdslow in RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getPRVUNNORMLEAFMX(double & prvunnormleafmx, const int &cid){
	
	prvunnormleafmxV->set_cur(cid);
	NcBool nb1 = prvunnormleafmxV->get(&prvunnormleafmx,1);
	if(!nb1){
	 
	 string msg = "problem in reading prvunnormleafmx in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}
void RestartInputer::getSTON(double & ston, const int &cid){
	
	stonV->set_cur(cid);
	NcBool nb1 = stonV->get(&ston,1);
	if(!nb1){
	 
	 string msg = "problem in reading ston in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getWDEBRIS(double & wdebris, const int &cid){
	
	wdebrisV->set_cur(cid);
	NcBool nb1 = wdebrisV->get(&wdebris,1);
	if(!nb1){
	 
	 string msg = "problem in reading wdebris in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getSOLN(double & soln, const int &cid){
	
	solnV->set_cur(cid);
	NcBool nb1 = solnV->get(&soln,1);
	if(!nb1){
	 
	 string msg = "problem in reading soln in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getAVLN(double & avln, const int &cid){
	
	avlnV->set_cur(cid);
	NcBool nb1 = avlnV->get(&avln,1);
	if(!nb1){
	 
	 string msg = "problem in reading avln in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_GET_ERROR);
	}
}
void RestartInputer::getDEADC(double & deadc, const int &cid){
	
	deadcV->set_cur(cid);
	NcBool nb1 = deadcV->get(&deadc,1);
	if(!nb1){
	 
	 string msg = "problem in reading deadc in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getDEADN(double & deadn, const int &cid){
	
	deadnV->set_cur(cid);
	NcBool nb1 = deadnV->get(&deadn,1);
	if(!nb1){
	 
	 string msg = "problem in reading deadn in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getDZsnow(double  DZsnow[], const int &cid){

	DZsnowV->set_cur(cid);
	
	NcBool nb1 = DZsnowV->get(&DZsnow[0],1, MAX_SNW_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading DZsnow in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}


void RestartInputer::getTSsnow(double  TSsnow[], const int &cid){
	TSsnowV->set_cur(cid);
	
	NcBool nb1 = TSsnowV->get(&TSsnow[0],1, MAX_SNW_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading TSsnow in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}


void RestartInputer::getAGEsnow(double  AGEsnow[], const int &cid){
	AGEsnowV->set_cur(cid);
	NcBool nb1 = AGEsnowV->get(&AGEsnow[0],1, MAX_SNW_LAY);
	if(!nb1){
	 string msg = "problem in reading AGEsnow in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getICEsnow(double  ICEsnow[], const int &cid){
	ICEsnowV->set_cur(cid);
	NcBool nb1 = ICEsnowV->get(&ICEsnow[0],1, MAX_SNW_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading ICEsnow in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getRHOsnow(double  RHOsnow[], const int &cid){
	RHOsnowV->set_cur(cid);
	NcBool nb1 = RHOsnowV->get(&RHOsnow[0],1, MAX_SNW_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading RHOsnow in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getDZrock(double  DZrock[], const int &cid){
	
	DZrockV->set_cur(cid);
	NcBool nb1 = DZrockV->get(&DZrock[0],1, MAX_ROC_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading DZrock in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getTSrock(double  TSrock[], const int &cid){
	
	TSrockV->set_cur(cid);
	NcBool nb1 = TSrockV->get(&TSrock[0],1, MAX_ROC_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading TSrock in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getDZsoil(double  DZsoil[], const int &cid){
	
	DZsoilV->set_cur(cid);
	NcBool nb1 = DZsoilV->get(&DZsoil[0],1, MAX_SOI_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading DZsoil in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getTSsoil(double  TSsoil[], const int &cid){
	
	TSsoilV->set_cur(cid);
	NcBool nb1 = TSsoilV->get(&TSsoil[0],1, MAX_SOI_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading TSsoil in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getLIQsoil(double  LIQsoil[], const int &cid){
	
	LIQsoilV->set_cur(cid);
	NcBool nb1 = LIQsoilV->get(&LIQsoil[0],1, MAX_SOI_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading LIQsoil in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getICEsoil(double  ICEsoil[], const int &cid){
	
	ICEsoilV->set_cur(cid);
	NcBool nb1 = ICEsoilV->get(&ICEsoil[0],1, MAX_SOI_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading ICEsoil in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}
void RestartInputer::getNONC(double  NONC[], const int &cid){
	
	NONCsoilV->set_cur(cid);
	NcBool nb1 = NONCsoilV->get(&NONC[0],1, MAX_SOI_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading NONC in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getREAC(double  REAC[], const int &cid){
	
	REACsoilV->set_cur(cid);
	NcBool nb1 = REACsoilV->get(&REAC[0],1, MAX_SOI_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading REAC in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,  I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getFROZENsoil(int  FROZENsoil[], const int &cid){
	
	FROZENsoilV->set_cur(cid);
	NcBool nb1 = FROZENsoilV->get(&FROZENsoil[0],1, MAX_SOI_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading FROZENsoil in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getTYPEsoil(int  TYPEsoil[], const int &cid){
	
	TYPEsoilV->set_cur(cid);
	NcBool nb1 = TYPEsoilV->get(&TYPEsoil[0],1, MAX_SOI_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading TYPEsoil in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getTYPEmin(int  TYPEmin[], const int &cid){
	
	TYPEminV->set_cur(cid);
	NcBool nb1 = TYPEminV->get(&TYPEmin[0],1, MAX_MIN_LAY);
	if(!nb1){
	 
	 string msg = "problem in reading TYPEmin in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getFrontFT(int  frontFT[], const int &cid){
	
	frontFTV->set_cur(cid);
	NcBool nb1 = frontFTV->get(&frontFT[0],1, MAX_NUM_FNT);
	if(!nb1){
	 
	 string msg = "problem in reading frontFT in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}


void RestartInputer::getFrontZ(double  frontZ[], const int &cid){
	
	frontZV->set_cur(cid);
	NcBool nb1 = frontZV->get(&frontZ[0],1, MAX_NUM_FNT);
	if(!nb1){
	 
	 string msg = "problem in reading frontZ in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}

void RestartInputer::getTOPTA(double  frontFT[], const int &cid){
	
	toptAV->set_cur(cid);
	NcBool nb1 = toptAV->get(&frontFT[0],1,10);
	if(!nb1){
	 
	 string msg = "problem in reading topta in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}
void RestartInputer::getUNNORMLEAFMXA(double  frontFT[], const int &cid){
	
	unnormleafmxAV->set_cur(cid);
	NcBool nb1 = unnormleafmxAV->get(&frontFT[0],1,10);
	if(!nb1){
	 
	 string msg = "problem in reading unnormleafmxa in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}
void RestartInputer::getPETMXA(double  frontFT[], const int &cid){
	
	petmxAV->set_cur(cid);
	NcBool nb1 = petmxAV->get(&frontFT[0],1,10);
	if(!nb1){
	 
	 string msg = "problem in reading petmxa in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc,   I_NCVAR_GET_ERROR);
	}
}
void RestartInputer::getEETMXA(double frontFT[], const int &cid){
	
	eetmxAV->set_cur(cid);
	NcBool nb1 = eetmxAV->get(&frontFT[0],1,10);
	if(!nb1){
	 
	 string msg = "problem in reading eetmxa in  RestartInputer";
		char* msgc = const_cast<char*> (msg.c_str());
		throw Exception(msgc, I_NCVAR_GET_ERROR);
	}
}

