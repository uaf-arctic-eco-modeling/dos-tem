#ifndef WILDFIRE_H_
#define WILDFIRE_H_

#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

#include "../data/EnvData.h"
#include "../data/FirData.h"
#include "../data/BgcData.h"
#include "../data/RestartData.h"

#include "../inc/timeconst.h"
#include "../inc/parameters.h"
#include "../util/Exception.h"
#include "../lookup/CohortLookup.h"

class WildFire{
	public:
		WildFire();
		~WildFire();
	

    	float VSMburn;
    
    	double cemitted;
    	double nemitted;
    	double nadd; //added nitrogen every month

    	int firstfireyr;

     	void setEnvData(EnvData* edp);
     	void setFirData(FirData* fdp);
     	void setBgcData(BgcData* bdp);  
    	void setCohortLookup(CohortLookup* chtlup);
    
    	void initializeParameter(const int & drgtypep,const int & vegtypep);
    	void initializeState(); 
    	void initializeState5restart(RestartData *resin);
    	void prepareDrivingData(const bool runsp, const bool runtr, const bool runsc);  //Yuan: modified
    	
		int getOccur(const int & yrind, const int & mind, const bool & fridrived);  	//Yuan: modified;
		void burn(const int & yrind, const bool & fridrived);  	//Yuan: modified

	private:
     	int drgtype;
     	int vegtype;
     
    	//Yuan: the following 4 variables
     	int onesize;
     	int oneseason;
     	int oneseverity;  //Yuan: fire severity category by ALFRESCO
     
     	fire_par firpar;
     
     /////////////////ratios////////////////////////
     	double r_ag2tot_cn; //above-ground C to total
     	double r_bg2tot_cn; //above-ground C to total
     
     	double r_live2ag_cn; //live C of ag C
     	double r_dead2ag_cn; //dead C of ag C
     	double r_burn2ag_cn;
     
     	double r_retain_n;
     
     	double r_live2bg_cn;
     	double r_burn2bg_cn;//burned 2 bg C
     	double r_dead2bg_cn;
         
//Yuan: the following if using years will result in huge memory needs, if spin-up is long
		int occur[MAX_FIR_OCR_NUM];
		int season[MAX_FIR_OCR_NUM];
		int month[MAX_FIR_OCR_NUM];
		int size[MAX_FIR_OCR_NUM];
		int severity[MAX_FIR_OCR_NUM];

     	CohortLookup * chtlu;
   	 	EnvData* ed;
    	FirData * fd;
    	BgcData * bd;

    	void updateBurnThickness();
    	double getBurnThick();
    	void getBurnVegetation();

};

#endif /*WILDFIRE_H_*/
