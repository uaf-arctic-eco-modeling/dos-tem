/*! \define output variables for vegetation BGC
 * 
 */

#include "VegOutData.h"

VegOutData::VegOutData() {

	for (int id=0; id<DYINY; id++){
		sinterd[id]=-999;
		rinterd[id]=-999;
		sthfld[id]=-999;
		rthfld[id]=-999;
		sdripd[id]=-999;
		rdripd[id]=-999;
		scanopyd[id]=-999;
		rcanopyd[id]=-999;
		cansubd[id]=-999;
		canevpd[id]=-999;
		cantrsd[id]=-999;
   	
		racd[id]=-999;
		radrefld[id]=-999;
		radthroud[id]=-999;
   	
		btrand[id]=-999;
		m_ppfdd[id]=-999;
		m_vpdd[id]=-999;
		ccd[id]=-999;
	}
	
	for (int im=0; im<MINY; im++){
		btran[im]=-999;
		rc[im]=-999;
		rac[im]=-999;	
		trans[im]=-999;			 
   		vevap[im]=-999;
   		vsubl[im]=-999;		
   		rinter[im]=-999;
   		sinter[im]=-999;
   		rthfl[im]=-999;
   		sthfl[im]=-999;					   	   	
   		radthfl[im]=-999;	  		
		vegc[im]=-999;    
		strn[im]=-999;
		ston[im]=-999;
		ingpp[im]=-999;
		gpp[im]=-999;
		innpp[im]=-999;
		npp[im]=-999;
		rm[im]=-999;
		rg[im]=-999;	
		ltrfalc[im]=-999;	
		ltrfaln[im]=-999;	
		innuptake[im]=-999;	
		nuptake[im]=-999;	
		luptake[im]=-999;	
		suptake[im]=-999;	
		nresorb[im]=-999;	
		nmobil[im]=-999;
		lai[im]=-999;	    
		fpc[im]=-999;	    
		unnormleaf[im]=-999;	    
		leaf[im]=-999;
		foliage[im]=-999;	
	}
	
	//yearly outputs
		yrevapo=-999;
    	yrsublim=-999;
    	yrtrans=-999;

    	yrc2n=-999;

    	yrnpp=-999;
    	yrrg=-999;
    	yrrm=-999;
    	yrltrfalc=-999;
    	yrltrfaln=-999;
    	yrvnuptake=-999;

    	yrabvgndc=-999;
    	yrfoliage=-999;
    	yrleaf=-999;  //Yuan:
    	yrlai=-999;
    	yrfpc=-999; //Yuan:    
    
    	yrvegc=-999;
    	yrstrn=-999;
    	yrston=-999;

    	yrburnorgc=-999;
    	yrburnorgn=-999;

};

VegOutData::~VegOutData(){
	
}

