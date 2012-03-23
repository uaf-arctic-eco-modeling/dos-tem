#include "SiteinInputer.h"

SiteinInputer::SiteinInputer(){
	
};

SiteinInputer::~SiteinInputer(){
	
};

void SiteinInputer::initSiteinFile(string & dirfile){

	siteinfname = dirfile;

	NcError err(NcError::silent_nonfatal);
	NcFile siteFile(siteinfname.c_str(), NcFile::ReadOnly);
 	if(!siteFile.is_valid()){
 		string msg = siteinfname+" is not valid";
 		char* msgc = const_cast< char* > ( msg.c_str());
 		throw Exception( msgc, I_NCFILE_NOT_EXIST);
 	}

 	NcDim* siteD = siteFile.get_dim("CHTID");
  	if(!siteD->is_valid()){
  		string msg = "SITED Dimension is not Valid in siteinFile";
 		char* msgc = const_cast<char*> (msg.c_str());
 		throw Exception(msgc,  I_NCDIM_NOT_EXIST);
 	}

}

//YUAN: recid - the order (from ZERO) in the .nc file, chtid - the cohort id
int SiteinInputer::getRecID(const int &siteid){
	NcError err(NcError::silent_nonfatal);

	NcFile siteFile(siteinfname.c_str(), NcFile::ReadOnly);
 	NcVar* siteidV = siteFile.get_var("CHTID");

 	int id = -1;
	for (int i=0; i<(int)siteidV->num_vals(); i++){
		siteidV->set_cur(i);
		siteidV->get(&id, 1);
		if(id==siteid) return i;
	}
	return -1;
}

int SiteinInputer::getSiteinData(SiteIn* sid, const int & recid){
	if (recid==-1) return -1;     //CID not exists in sitein.nc, so back to calling
 
	NcFile siteFile(siteinfname.c_str(), NcFile::ReadOnly);
 		
	NcVar* ysfV = siteFile.get_var("YSF");
	if(ysfV==NULL){
	  cout <<"cannot get ysf\n"; 
	}
	ysfV->set_cur(recid);
	ysfV->get(&sid->ysf, 1);
	 
	NcVar* envlaiV = siteFile.get_var("LAI");
	if(envlaiV==NULL){
	  cout <<"cannot get lai \n";
	}
	envlaiV->set_cur(recid);
	envlaiV->get(sid->lai,1, 12);

	NcVar* vegcV = siteFile.get_var("VEGC");
	if(vegcV==NULL){
	  cout <<"cannot get vegc \n";
	}
	vegcV->set_cur(recid);
	vegcV->get(&sid->vegc, 1);

	NcVar* vegnV = siteFile.get_var("VEGN");
	if(vegcV==NULL){
	  cout <<"cannot get vegn \n"; 
	}
	vegnV->set_cur(recid);
	vegnV->get(&sid->vegn, 1);

	NcVar* mossthickV = siteFile.get_var("MOSSTHICK");
	if(mossthickV==NULL){
	  cout <<"cannot get mossthick \n";	 
	}
	mossthickV->set_cur(recid);
	mossthickV->get(&sid->mossthick, 1);
	 
	NcVar* fibthickV = siteFile.get_var("FIBTHICK");
	if(fibthickV==NULL){
	  cout <<"cannot get fibthick \n";  
	}
	fibthickV->set_cur(recid);
	fibthickV->get(&sid->fibthick, 1);
	 
	NcVar* humthickV = siteFile.get_var("HUMTHICK");
	if(humthickV==NULL){
	  cout <<"cannot get humthick \n";  
	}
	humthickV->set_cur(recid);
	humthickV->get(&sid->humthick, 1);

	NcVar* soilcV = siteFile.get_var("SOILC");
	if(soilcV==NULL){
	  cout <<"cannot get soilc \n";
	}
	soilcV->set_cur(recid);
	soilcV->get(&sid->soilc, 1);

	NcVar* fibcV = siteFile.get_var("FIBC");
	if(fibcV==NULL){
	  cout <<"cannot get fibc \n";
	}
	fibcV->set_cur(recid);
	fibcV->get(&sid->fibc, 1);

	NcVar* humcV = siteFile.get_var("HUMC");
	if(humcV==NULL){
	  cout <<"cannot get humc \n";
	}
	humcV->set_cur(recid);
	humcV->get(&sid->humc, 1);

	NcVar* mincV = siteFile.get_var("MINC");
	if(mincV==NULL){
	  cout <<"cannot get minc \n";
	}
	mincV->set_cur(recid);
	mincV->get(&sid->minc, 1);

	NcVar* orgnV = siteFile.get_var("ORGN");
	if(orgnV==NULL){
	  cout <<"cannot get orgn \n";
	}
	orgnV->set_cur(recid);
	orgnV->get(&sid->orgn, 1);

	NcVar* avlnV = siteFile.get_var("AVLN");
	if(avlnV==NULL){
	  cout <<"cannot get avln \n";
	}
	avlnV->set_cur(recid);
	avlnV->get(&sid->avln, 1);

	NcVar* mintypeV = siteFile.get_var("MINTYPE");
	if(mintypeV==NULL){
	  cout <<"cannot get mineral type \n"; 
	}
	mintypeV->set_cur(recid);
	mintypeV->get(sid->mintype, 1, MAX_MIN_LAY); 
			
	NcVar* zoutV = siteFile.get_var("ZOUT");
	if(zoutV==NULL){
	  cout <<"cannot get soil depth \n"; 
	}
	zoutV->set_cur(recid);
	zoutV->get(sid->initz, 1, MAX_SOI_LAY);

	NcVar* stoutV = siteFile.get_var("STOUT");
	if(stoutV==NULL){
	  cout <<"cannot get soil temperature \n"; 
	}
	stoutV->set_cur(recid);
	stoutV->get(sid->initst, 1, MAX_SOI_LAY);

	NcVar* smoutV = siteFile.get_var("SMOUT");
	if(smoutV==NULL){
	  cout <<"cannot get soil moisture \n"; 
	}
	smoutV->set_cur(recid);
	smoutV->get(sid->initsm, 1, MAX_SOI_LAY);
	
	return 0;
};


