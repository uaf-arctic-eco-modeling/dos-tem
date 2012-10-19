#include "RestartData.h"

RestartData::RestartData(){
	reinitValue();
};

RestartData::~RestartData(){

};

void RestartData::reinitValue(){
	
	chtid=-999;
	perma = -999;

	for(int il =0;il<MAX_SNW_LAY; il++){
		TSsnow[il] = -999;	
		DZsnow[il] = -999;	
		LIQsnow[il] = -999;	
		ICEsnow[il] = -999;	
		AGEsnow[il] = -999;
		RHOsnow[il] = -999;	
	}
	
	for(int il =0;il<MAX_SOI_LAY; il++){
		TSsoil[il] = -999;	
		DZsoil[il] = -999;	
		LIQsoil[il] = -999;	
		ICEsoil[il] = -999;	
		FROZENsoil[il] = -999;	
		TYPEsoil[il] = -999;	
		NONCsoil[il] = -999;	
		REACsoil[il] = -999;	
	}
	
	for(int il =0;il<MAX_MIN_LAY; il++){
		TYPEmin[il] = -999;	
	}
   
	for(int il =0;il<MAX_ROC_LAY; il++){
		TSrock[il] = -999;	
		DZrock[il] = -999;	
	}

	for(int il =0;il<MAX_NUM_FNT; il++){
		frontZ[il] = -999;	
		frontFT[il] = -999;	
	}
     
    for(int i=0; i<10; i++){
    	toptA[i] =-999;
    	eetmxA[i] =-999;
    	petmxA[i] =-999;
    	unnormleafmxA[i] =-999;     	
    }
     
    soln = -999;
    avln = -999;
    wdebris = -999;
    strn = -999;
    ston = -999;
    vegc = -999;
    deadc = -999;
    deadn=-999;
    prveetmx= -999;
    prvpetmx= -999;
    foliagemx= -999;
	lai = -999;
    unnormleaf= -999;
    prvunnormleafmx= -999;
    prvtopt= -999;
    c2n= -999;
    kdfib= -999;
    kdhum= -999;
    kdmin= -999;
    kdslow= -999;
	ysf =-999;
	burnedn =-999;
};

