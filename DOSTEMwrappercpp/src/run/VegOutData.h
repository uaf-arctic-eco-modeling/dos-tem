/*! \define output variables for vegetation BGC
 * 
 */
#ifndef VEGOUTDATA_H_
#define VEGOUTDATA_H_

#include <iostream>
using namespace std;

#include "../inc/timeconst.h"

class VegOutData {
	public:

		VegOutData();
		~VegOutData();
		
		//daily outputs
		float sinterd[DYINY];
		float rinterd[DYINY];
		float sthfld[DYINY];
		float rthfld[DYINY];
		float sdripd[DYINY];
		float rdripd[DYINY];
		float scanopyd[DYINY];
		float rcanopyd[DYINY];
		float cansubd[DYINY];
		float canevpd[DYINY];
		float cantrsd[DYINY];
   	
		float racd[DYINY];
		float radrefld[DYINY];
		float radthroud[DYINY];
   	
		float btrand[DYINY];
		float m_ppfdd[DYINY];
		float m_vpdd[DYINY];
		float ccd[DYINY];

	//monthly outputs
	    //Vegetation - Env
		float btran[MINY];
		float rc[MINY];
		float rac[MINY];	
		float trans[MINY];			 
   		float vevap[MINY];
   		float vsubl[MINY];		
   		float rinter[MINY];
   		float sinter[MINY];
   		float rthfl[MINY];
   		float sthfl[MINY];					   	   	
   		float radthfl[MINY];	
   		
   		//Vegtation - Bgc
		float vegc[MINY];    
		float strn[MINY];
		float ston[MINY];
	/*! fluxes from atmosphere to vegetation*/
		float ingpp[MINY];
		float gpp[MINY];
		float innpp[MINY];
		float npp[MINY];
	/*! fluxes from vegatation to atmosphere*/
		float rm[MINY];
		float rg[MINY];	
	/*! fluxes from vegetation to soil*/
		float ltrfalc[MINY];	
		float ltrfaln[MINY];	
	/*! fluxes from soil to vegetation*/
		float innuptake[MINY];	
		float nuptake[MINY];	
		float luptake[MINY];	
		float suptake[MINY];	
	/*! fluxes between pools in vegeation */
		float nresorb[MINY];	
		float nmobil[MINY];
	/*! others*/
		float lai[MINY];	    
		float fpc[MINY];	    
		float unnormleaf[MINY];	    
		float leaf[MINY];
		float foliage[MINY];	
	
	//yearly outputs
    	//Vegetation - Env
		float yrevapo;
    	float yrsublim;
    	float yrtrans;

    	//Vegetation - Bgc
    	float yrc2n;

    	float yrnpp;
    	float yrrg;
    	float yrrm;
    	float yrltrfalc;
    	float yrltrfaln;
    	float yrvnuptake;

    	float yrabvgndc;
    	float yrfoliage;
    	float yrleaf;  //Yuan:
    	float yrlai;
    	float yrfpc; //Yuan:    
    
    	float yrvegc;
    	float yrstrn;
    	float yrston;

    	//disturbance - Fire 
    	float yrburnorgc;
    	float yrburnorgn;


};

#endif /*VEGOUTDATA_H_*/

