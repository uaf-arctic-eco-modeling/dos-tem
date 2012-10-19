/*
 * output directory and netcdf file definition for TEM 
 * for a single site run, i.e., more detailed output 
 * 
 */

#include "SiteOutputer.h"

/*! constructor */
SiteOutputer::SiteOutputer(){
 
};

SiteOutputer::~SiteOutputer(){
 	//cout<< "closing output files in SiteOutputer \n";
 	#ifdef ODAY
 		dayChtFile->close();
 		delete dayChtFile;
 		dayGrdFile->close();
 		delete dayGrdFile;
 	#endif
 	
 	if(OMONTH){
		monChtFile->close();
		delete monChtFile;
		monGrdFile->close();
		delete monGrdFile;
 	}
	
	if(OYEAR){
		yrChtFile->close();
		delete yrChtFile;
		yrGrdFile->close();
		delete yrGrdFile;
	}

};

void SiteOutputer::init(){
	
	string outputdir = md->outputdir;
 	string stage ="";
    if(md->runsp && md->runtr){
     	stage ="";
    }else if(md->runsp){
     	stage ="-sp";	
    }else if(md->runtr){
     	stage ="-tr";	
        if (md->runstages=="sc") stage ="-sc";
    }else if (md->runeq){
     	stage="-eq";	
    }

	#ifdef ODAY
    	string dayfnc =outputdir+ "day-cht"+stage+".nc";
		dayChtFile = new NcFile(dayfnc.c_str(), NcFile::Replace);
		defineDailyCohortDimension();
		string dayfng =outputdir+ "day-grd"+stage+".nc";
		dayGrdFile = new NcFile(dayfng.c_str(), NcFile::Replace);
		defineDailyGridDimension();
	#endif

	if (OMONTH){
		string moncfn =outputdir+ "mon-cht"+stage+".nc";
		monChtFile = new NcFile(moncfn.c_str(), NcFile::Replace);
		defineMonthlyCohortDimension();
		string mongfn =outputdir+ "mon-grd"+stage+".nc";
		monGrdFile = new NcFile(mongfn.c_str(), NcFile::Replace);
		defineMonthlyGridDimension();
	}

	if (OYEAR) {
		string yrcfn =outputdir+ "yr-cht"+stage+".nc";
		yrChtFile = new NcFile(yrcfn.c_str(), NcFile::Replace);
		defineYearlyCohortDimension();
		string yrgfn =outputdir+ "yr-grd"+stage+".nc";
		yrGrdFile = new NcFile(yrgfn.c_str(), NcFile::Replace);
		defineYearlyGridDimension();
	}	

};

#ifdef ODAY
 	void SiteOutputer::defineDailyCohortDimension(){
 		dcyearD = dayChtFile->add_dim("year");
  		dcdayD =  dayChtFile->add_dim("day", DYINY);
  		dcfrontD = dayChtFile->add_dim("FRONTLAYER", MAX_NUM_FNT);
  		dcsnlayD = dayChtFile->add_dim("snlayer", MAX_OUT_SNW);
  		dclayerD = dayChtFile->add_dim("dlayer", MAX_OUT_SOI);
 	};
 
 	void SiteOutputer::defineDailyGridDimension(){
 		dgyearD = dayGrdFile->add_dim("year");
  		dgdayD =  dayGrdFile->add_dim("day", DYINY);
 	};

#endif

void SiteOutputer::defineMonthlyCohortDimension(){
 	mcyearD = monChtFile->add_dim("year");
  	mcmonD = monChtFile->add_dim("month",MINY);
  	mclayerD =  monChtFile->add_dim("layer", MAX_OUT_SOI);
 
};
 
void SiteOutputer::defineMonthlyGridDimension(){
 	mgyearD = monGrdFile->add_dim("year");
  	mgmonD = monGrdFile->add_dim("month",MINY);
  	mglayerD =  monGrdFile->add_dim("layer", MAX_OUT_SOI);
};
 
void SiteOutputer::defineYearlyCohortDimension(){
	ycyearD = yrChtFile->add_dim("year");
	yclayerD =  yrChtFile->add_dim("layer", MAX_OUT_SOI);
};
  
void SiteOutputer::defineYearlyGridDimension(){
	ygyearD = yrGrdFile->add_dim("year");

};

void SiteOutputer::setModelData(ModelData* mdp){
   md = mdp;
};


