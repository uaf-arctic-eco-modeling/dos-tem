/*! \file 
 */
 
#include "Grid.h"
// constructor 
Grid::Grid(){
  
}

// deconstructor
Grid::~Grid(){
  
}

// initialization
int Grid::reinit(const int &grdid){

  	gid =grdid;
  	gd->gid = gid;
   
    	double ampl;
	for (int id=0; id<365; id++){
       		ampl = exp(7.42 +0.045 *gd->lat)/3600.;
       		gd->alldaylengths[id] = ampl * (sin ((id -79) *0.01721)) +12.0;
	}

  //check for the validity of grid level data
	if(gd->fri<0|| gd->fri>5000){
	 	gd->fri =5000;
	}
// cout <<  "FRI: "<<gd->fri<<"\n";
	gd->fri =2000;

  	if(gd->topclay <0 || gd->botclay <0 || gd->topsand <0 || gd->botsand <0 || gd->topsilt <0 || gd->botsilt <0){
  	    string msg = "soil type  should be greater than 0";
 //		char* msgc = const_cast< char* > ( msg.c_str());
 //		throw Exception(msgc, I_INPUT_INVALID);

  	    return -2;
  	}
  
   	for(int iy =0; iy<gd->act_atm_drv_yr; iy++){
       	for (int im=0; im<12; im++){
        	if(gd->ta[iy][im]<=-999 || gd->prec[iy][im]<=-999
        			|| gd->nirr[iy][im]<=-999 || gd->vap[iy][im]<=-999){
        		string msg = "climate data error";
// 				char* msgc = const_cast< char* > ( msg.c_str());
// 				throw Exception(msgc, I_INPUT_INVALID);
        		return -3;
        	}
       	}	
    }
  
  	atm.prepareMonthDrivingData();
  	atm.prepareDayDrivingData();

  	return 0;

}

//environmental variables
void Grid::setEnvData(EnvData* edp){
	ed= edp;
	atm.setEnvData(ed);
}

//inputs
void Grid::setRegionData(RegionData* rdp){
	rd = rdp;
}

void Grid::setGridData(GridData* gdp){
	gd = gdp;
}








