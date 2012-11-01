/*! \file 
 */
 
#include "SiteIn.h"
// constructor 
SiteIn::SiteIn(){
	siteid = -999;
	ysf = -999;
	for (int im=0; im<12; im++) {
		lai[im]= -999;	             
	}
	vegc= -999;
	vegn= -999;
	
	mossthick= -999;
	fibthick= -999;
	humthick= -999;
	
	soilc= -999;
	fibc= -999;
	humc= -999;
	minc= -999;
	orgn= -999;
	avln= -999;
	
	for (int i=0; i<MAX_MIN_LAY; i++){
		mintype[i]=-999;
	}
	
	for (int i=0; i<MAX_SOI_LAY; i++){
		initz[i]=-999;
		initst[i]=-999;
		initsm[i]=-999;
	}

}

// deconstructor
SiteIn::~SiteIn(){
  
}
