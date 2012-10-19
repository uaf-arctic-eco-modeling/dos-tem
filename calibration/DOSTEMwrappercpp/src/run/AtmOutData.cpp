/*
 * 
 */
 
#include "AtmOutData.h"

AtmOutData::AtmOutData() {
	  
	for (int id=0; id<DYINY; id++){  
	//daily
	 	tdrvd[id]=-999;
	 	raind[id]=-999;
	 	snowd[id]=-999;
	 	svpd[id]=-999;
	 	dersvpd[id]=-999;
	 	rhoad[id]=-999;
		abshdd[id]=-999;
	 	dsrd[id]=-999;
	}
	
	for (int im=0; im<MINY; im++) {
	 	// 	monthly
		ta[im]=-999;
		clds[im]=-999;	
		co2[im]=-999;	
		eet[im]=-999;	
		pet[im]=-999;	
		rnfl[im]=-999;	
		snfl[im]=-999;	
		girr[im]=-999;		    
		nirr[im]=-999;
		par[im]=-999;	
	}
		// yearly

		yrrnfl=-999;
		yrsnfl=-999;	
		yrta=-999;	 

};

AtmOutData::~AtmOutData(){
	
};
