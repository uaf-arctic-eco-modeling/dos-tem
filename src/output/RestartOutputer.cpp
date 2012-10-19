#include "RestartOutputer.h"

/*! constructor */
 RestartOutputer::RestartOutputer(){
 
};

RestartOutputer::~RestartOutputer(){
	if (restartFile!=NULL) {
		restartFile->close();
		delete restartFile;
	}

};

inline string itos (int n) {stringstream ss; ss<<n; return ss.str();}

void RestartOutputer::init(string& outputdir,string& stage, const int & numprocs, const int & myid){
	
 	NcError err(NcError::verbose_nonfatal);
 	
	restartfname ="";
	if(numprocs==1){
		restartfname = outputdir+"restart"+stage+".nc";
	}else{
		restartfname = outputdir+itos(myid)+"/restart.nc";
	}

	restartFile=new NcFile(restartfname.c_str(), NcFile::Replace);

	//dimension definition
	chtD = restartFile->add_dim("CHTID");
	snowlayerD = restartFile->add_dim("SNOWLAYER", MAX_SNW_LAY);
	soillayerD = restartFile->add_dim("SOILLAYER", MAX_SOI_LAY);
	minlayerD  = restartFile->add_dim("MINLAYER", MAX_MIN_LAY);
	rocklayerD = restartFile->add_dim("ROCKLAYER", MAX_ROC_LAY);
	frontD     = restartFile->add_dim("FRONTLAYER", MAX_NUM_FNT);
	meanyearD  = restartFile->add_dim("MEANYEAR", 10);
	
	//variable definition
    chtidV   =restartFile->add_var("CHTID", ncInt,chtD);
    errcodeV =restartFile->add_var("ERRCODE", ncInt,chtD);
    
    permaV   =restartFile->add_var("PERMAFROST", ncInt,chtD);
    TSsnowV  =restartFile->add_var("TSsnow", ncDouble,chtD, snowlayerD);
    DZsnowV  =restartFile->add_var("DZsnow", ncDouble,chtD, snowlayerD);
    LIQsnowV =restartFile->add_var("LIQsnow", ncDouble,chtD, snowlayerD);
    ICEsnowV =restartFile->add_var("ICEsnow", ncDouble,chtD, snowlayerD);
 	AGEsnowV =restartFile->add_var("AGEsnow", ncDouble,chtD, snowlayerD);
    RHOsnowV =restartFile->add_var("RHOsnow", ncDouble,chtD, snowlayerD);
 
	TSsoilV  =restartFile->add_var("TSsoil", ncDouble,chtD, soillayerD);
    DZsoilV  =restartFile->add_var("DZsoil", ncDouble,chtD, soillayerD);
    LIQsoilV =restartFile->add_var("LIQsoil", ncDouble,chtD, soillayerD);
    
    ICEsoilV  =restartFile->add_var("ICEsoil", ncDouble,chtD, soillayerD);
    FROZENsoilV =restartFile->add_var("FROZENsoil", ncInt,chtD, soillayerD);
    NONCsoilV =restartFile->add_var("NONCsoil", ncDouble,chtD, soillayerD);
    REACsoilV =restartFile->add_var("REACsoil", ncDouble,chtD, soillayerD);
    TYPEsoilV =restartFile->add_var("TYPEsoil", ncInt,chtD, soillayerD);
    TYPEminV  =restartFile->add_var("TYPEmin", ncInt,chtD, minlayerD);
        
    TSrockV =restartFile->add_var("TSrock", ncDouble,chtD, rocklayerD);
    DZrockV =restartFile->add_var("DZrock", ncDouble,chtD, rocklayerD);
   
	frontZV =restartFile->add_var("frontZ", ncDouble,chtD, frontD);
    frontFTV=restartFile->add_var("frontFT", ncInt,chtD, frontD);
    
    solnV   =restartFile->add_var("SOLN", ncDouble,chtD);
    avlnV   =restartFile->add_var("AVLN", ncDouble,chtD);
    wdebrisV=restartFile->add_var("WDEBRIS", ncDouble,chtD);
    
    strnV   =restartFile->add_var("STRN", ncDouble,chtD);
    stonV   =restartFile->add_var("STON", ncDouble,chtD);
    vegcV   =restartFile->add_var("VEGC", ncDouble,chtD);
    deadcV  =restartFile->add_var("DEADC", ncDouble,chtD);
    deadnV  =restartFile->add_var("DEADN", ncDouble,chtD);
    prveetmxV =restartFile->add_var("PRVEETMX", ncDouble,chtD);
   	prvpetmxV =restartFile->add_var("PRVPETMX", ncDouble,chtD);
   	foliagemxV=restartFile->add_var("FOLIAGEMX", ncDouble,chtD);
   	   	
	laiV =restartFile->add_var("LAI", ncDouble,chtD);
   	
   	unnormleafV      =restartFile->add_var("UNNORMLEAF", ncDouble,chtD);
	prvunnormleafmxV =restartFile->add_var("PRVUNNORMLEAFMX", ncDouble,chtD);
	prvtoptV         =restartFile->add_var("PRVTOPT", ncDouble,chtD);
	c2nV             =restartFile->add_var("C2N", ncDouble,chtD);
	kdfibV           =restartFile->add_var("KDFIB", ncDouble,chtD);
	kdhumV           =restartFile->add_var("KDHUM", ncDouble,chtD);
	kdminV           =restartFile->add_var("KDMIN", ncDouble,chtD);
	kdslowV        =restartFile->add_var("KDSLOW", ncDouble,chtD);
	
	ysfV     =restartFile->add_var("YSF", ncInt,chtD);
	burnednV =restartFile->add_var("BURNEDN", ncDouble,chtD);
 	toptAV   =restartFile->add_var("TOPTA", ncDouble,  chtD,meanyearD);
	eetmxAV  =restartFile->add_var("EETMXA", ncDouble, chtD,meanyearD);
	petmxAV  =restartFile->add_var("PETMXA", ncDouble, chtD,meanyearD);
	unnormleafmxAV =restartFile->add_var("UNNORMLEAFMXA", ncDouble,  chtD,meanyearD);

}

void RestartOutputer::outputVariables(const int & chtcount){
 	NcError err(NcError::verbose_nonfatal);

	int errcode=errorChecking();
	errcodeV->put_rec(&errcode, chtcount);

	chtidV->put_rec(&resod->chtid, chtcount);
	permaV->put_rec(&resod->perma, chtcount);
	TSsnowV->put_rec(&resod->TSsnow[0], chtcount);
	DZsnowV->put_rec(&resod->DZsnow[0], chtcount);
	LIQsnowV->put_rec(&resod->LIQsnow[0], chtcount);
	ICEsnowV->put_rec(&resod->ICEsnow[0], chtcount);
	AGEsnowV->put_rec(&resod->AGEsnow[0], chtcount);
	RHOsnowV->put_rec(&resod->RHOsnow[0], chtcount);
	
	TSsoilV->put_rec(&resod->TSsoil[0], chtcount);
	DZsoilV->put_rec(&resod->DZsoil[0], chtcount);
	LIQsoilV->put_rec(&resod->LIQsoil[0], chtcount);
		
	ICEsoilV->put_rec(&resod->ICEsoil[0], chtcount);
	FROZENsoilV->put_rec(&resod->FROZENsoil[0], chtcount);
	NONCsoilV->put_rec(&resod->NONCsoil[0], chtcount);
	REACsoilV->put_rec(&resod->REACsoil[0], chtcount);
	TYPEsoilV->put_rec(&resod->TYPEsoil[0], chtcount);
	TYPEminV->put_rec(&resod->TYPEmin[0], chtcount);

	TSrockV->put_rec(&resod->TSrock[0], chtcount);
	DZrockV->put_rec(&resod->DZrock[0], chtcount);
	
	frontZV->put_rec(&resod->frontZ[0], chtcount);
	frontFTV->put_rec(&resod->frontFT[0], chtcount);
	
	solnV->put_rec(&resod->soln, chtcount);
	avlnV->put_rec(&resod->avln, chtcount);
	wdebrisV->put_rec(&resod->wdebris, chtcount);
		
	strnV->put_rec(&resod->strn, chtcount);
	
	stonV->put_rec(&resod->ston, chtcount);
	deadcV->put_rec(&resod->deadc, chtcount);
	deadnV->put_rec(&resod->deadn, chtcount);
	vegcV->put_rec(&resod->vegc, chtcount);
	prveetmxV->put_rec(&resod->prveetmx, chtcount);
	prvpetmxV->put_rec(&resod->prvpetmx, chtcount);
	foliagemxV->put_rec(&resod->foliagemx, chtcount);
		
	laiV->put_rec(&resod->lai, chtcount);
	
	unnormleafV->put_rec(&resod->unnormleaf, chtcount);
	prvunnormleafmxV->put_rec(&resod->prvunnormleafmx, chtcount);
	prvtoptV->put_rec(&resod->prvtopt, chtcount);
	
	c2nV->put_rec(&resod->c2n, chtcount);
	kdfibV->put_rec(&resod->kdfib, chtcount);
	kdhumV->put_rec(&resod->kdhum, chtcount);
	kdminV->put_rec(&resod->kdmin, chtcount);
	kdslowV->put_rec(&resod->kdslow, chtcount);
	
	ysfV->put_rec(&resod->ysf, chtcount);
	burnednV->put_rec(&resod->burnedn, chtcount);
    
    toptAV->put_rec(&resod->toptA[0], chtcount);
	eetmxAV->put_rec(&resod->eetmxA[0], chtcount);
	petmxAV->put_rec(&resod->petmxA[0], chtcount);
	unnormleafmxAV->put_rec(&resod->unnormleafmxA[0], chtcount);

}

int RestartOutputer::errorChecking(){
	int errcode = 0;
	
	for(int il =0;il<MAX_SNW_LAY; il++){
		if (isnan(resod->TSsnow[il]) || isinf(resod->TSsnow[il])) errcode = -1;	
		if (isnan(resod->DZsnow[il]) || isinf(resod->DZsnow[il])) errcode = -1;	
		if (isnan(resod->LIQsnow[il]) || isinf(resod->LIQsnow[il])) errcode = -1;	
		if (isnan(resod->ICEsnow[il]) || isinf(resod->ICEsnow[il])) errcode = -1;	
		if (isnan(resod->AGEsnow[il]) || isinf(resod->AGEsnow[il])) errcode = -1;	
		if (isnan(resod->RHOsnow[il]) || isinf(resod->RHOsnow[il])) errcode = -1;	
	}
	
	for(int il =0;il<MAX_SOI_LAY; il++){
		if (isnan(resod->TSsoil[il]) || isinf(resod->TSsoil[il])) errcode = -1;	
		if (isnan(resod->DZsoil[il]) || isinf(resod->DZsoil[il])) errcode = -1;	
		if (isnan(resod->LIQsoil[il]) || isinf(resod->LIQsoil[il])) errcode = -1;	
		if (isnan(resod->ICEsoil[il]) || isinf(resod->ICEsoil[il])) errcode = -1;	
		if (isnan(resod->FROZENsoil[il]) || isinf(resod->FROZENsoil[il])) errcode = -1;	
		if (isnan(resod->TYPEsoil[il]) || isinf(resod->TYPEsoil[il])) errcode = -1;	
		if (isnan(resod->NONCsoil[il]) || isinf(resod->NONCsoil[il])) errcode = -1;	
		if (isnan(resod->REACsoil[il]) || isinf(resod->REACsoil[il])) errcode = -1;	
	}
	
	for(int il =0;il<MAX_MIN_LAY; il++){
		if (isnan(resod->TYPEmin[il]) || isinf(resod->TYPEmin[il])) errcode = -1;	
	}
   
	for(int il =0;il<MAX_ROC_LAY; il++){
		if (isnan(resod->TSrock[il]) || isinf(resod->TSrock[il])) errcode = -1;	
		if (isnan(resod->DZrock[il]) || isinf(resod->DZrock[il])) errcode = -1;	
	}

	for(int il =0;il<MAX_NUM_FNT; il++){
		if (isnan(resod->frontZ[il]) || isinf(resod->frontZ[il])) errcode = -1;	
		if (isnan(resod->frontFT[il]) || isinf(resod->frontFT[il])) errcode = -1;	
	}
     
    for(int i=0; i<10; i++){
		if (isnan(resod->toptA[i]) || isinf(resod->toptA[i])) errcode = -1;	
		if (isnan(resod->eetmxA[i]) || isinf(resod->eetmxA[i])) errcode = -1;	
		if (isnan(resod->petmxA[i]) || isinf(resod->petmxA[i])) errcode = -1;	
		if (isnan(resod->unnormleafmxA[i]) || isinf(resod->unnormleafmxA[i])) errcode = -1;	
    }
     
	if (isnan(resod->soln) || isinf(resod->soln)) errcode = -1;	
	if (isnan(resod->avln) || isinf(resod->avln)) errcode = -1;	
	if (isnan(resod->wdebris) || isinf(resod->wdebris)) errcode = -1;	
	if (isnan(resod->strn) || isinf(resod->strn)) errcode = -1;	
	if (isnan(resod->ston) || isinf(resod->ston)) errcode = -1;	
	if (isnan(resod->vegc) || isinf(resod->vegc)) errcode = -1;	
	if (isnan(resod->deadc) || isinf(resod->deadc)) errcode = -1;	
	if (isnan(resod->deadn) || isinf(resod->deadn)) errcode = -1;	
	if (isnan(resod->prveetmx) || isinf(resod->prveetmx)) errcode = -1;	
	if (isnan(resod->prvpetmx) || isinf(resod->prvpetmx)) errcode = -1;	
	if (isnan(resod->unnormleaf) || isinf(resod->unnormleaf)) errcode = -1;	
	if (isnan(resod->prvunnormleafmx) || isinf(resod->prvunnormleafmx)) errcode = -1;	
	if (isnan(resod->prvtopt) || isinf(resod->prvtopt)) errcode = -1;	
	if (isnan(resod->c2n) || isinf(resod->c2n)) errcode = -1;	
	if (isnan(resod->kdfib) || isinf(resod->kdfib)) errcode = -1;	
	if (isnan(resod->kdhum) || isinf(resod->kdhum)) errcode = -1;	
	if (isnan(resod->kdmin) || isinf(resod->kdmin)) errcode = -1;
	if (isnan(resod->kdslow) || isinf(resod->kdslow)) errcode = -1;
	if (isnan(resod->foliagemx) || isinf(resod->foliagemx)) errcode = -1;	
	if (isnan(resod->ysf) || isinf(resod->ysf)) errcode = -1;	
	if (isnan(resod->burnedn) || isinf(resod->burnedn)) errcode = -1;
	if (isnan(resod->lai) || isinf(resod->lai)) errcode = -1;	

	return errcode;
}

void RestartOutputer::setRestartOutData(RestartData * resodp){
	resod = resodp;
}


