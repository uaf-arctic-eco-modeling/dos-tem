/*define snow/soil variables for output*/


#ifndef SNOWSOILOUTDATA_H_
#define SNOWSOILOUTDATA_H_

#include <iostream>
using namespace std;

#include "../inc/timeconst.h"
#include "../inc/layerconst.h"

class SnowSoilOutData{
	public:

		SnowSoilOutData();
		~SnowSoilOutData();
		
	 // for daily
			int errord;

			float infild[DYINY];
			float wtd[DYINY];
			float fsatd[DYINY];
			float qoverd[DYINY]; 
			float qdraind[DYINY];     
			
			float growd[DYINY];            /*! the start of growing season julian day*/
			float slradrefld[DYINY];
			float sevapd[DYINY];           /*! soil surface evaporation */

			float tsd[DYINY][MAX_OUT_SOI];
			float tcondd[DYINY][MAX_OUT_SOI];

			float liqd[DYINY][MAX_OUT_SOI];
			float iced[DYINY][MAX_OUT_SOI];

			float frzfnt[DYINY][MAX_NUM_FNT];   /*! freezing fronts, even there are three fronts in one layer, only 2 in maximum can be assigned to one attribute*/
			float thwfnt[DYINY][MAX_NUM_FNT];

			float numiter[DYINY];
			float numiterliq[DYINY];

			float snowthick[DYINY]; /*! the snow pack thickness */
			float swed[DYINY]; /*! snow water equivalent mm*/
			float smeltd[DYINY]; /*! snow melt mm/day*/
			float ssubld[DYINY]; /*! snow sublimation mm/day*/

			float snradrefld[DYINY];
			float aldd[DYINY];    //Yuan: daily active layer depth

	// for monthly
	   		int errorm;
	   		
	   		//SnowSoil -Env	   		
			float dz[MINY][MAX_OUT_SOI];
			float ts[MINY][MAX_OUT_SOI];	
			float liq[MINY][MAX_OUT_SOI]; 
			float vwc[MINY][MAX_OUT_SOI];
			float ice[MINY][MAX_OUT_SOI];
       		float ald[MINY];   //Yuan: monthly max. active layer depth

			float ssubl[MINY];
			float sninfl[MINY];
			float sevap[MINY];
			float watertab[MINY];
			float mossdz[MINY];
			float shlwdz[MINY];
			float deepdz[MINY];

			float z[MINY][MAX_OUT_SOI];
			float por[MINY][MAX_OUT_SOI];
			float type[MINY][MAX_OUT_SOI];

			//SnowSoil - Bgc	
		
			float reac[MINY][MAX_OUT_SOI];
			float nonc[MINY][MAX_OUT_SOI];

			float rrh[MINY][MAX_OUT_SOI];
			float nrh[MINY][MAX_OUT_SOI];

			float rhmoist[MINY][MAX_OUT_SOI];
			float rhq10[MINY][MAX_OUT_SOI];
			float ksoil[MINY][MAX_OUT_SOI];
			float kdl[MINY][MAX_OUT_SOI];
			float kdr[MINY][MAX_OUT_SOI];
			float kdn[MINY][MAX_OUT_SOI];

			float ninput[MINY];
			float nlost[MINY];
			float netnmin[MINY];
			float nimmob[MINY];

			float orgn[MINY];
			float avln[MINY];
			float reacsum[MINY];
			float noncsum[MINY];
			float shlwcsum[MINY];
			float deepcsum[MINY];
			float minecsum[MINY];

			float growpct[MINY]; /*! grow percent in one month*/
	
	// for yearly
    		int errory;

    		//soil - Env
    		float yrsevap;
    		float yrqover;
    		float yrqdrain;
    		float yrssubl;

    		float yrliqsum;
       		float yricesum;
       		float yrtsave;
       		
       		float yrvwcmin10;
       		float yrvwcshlw;
       		float yrvwcdeep;
       		float yrvwcmine;

       		float yrtmin10;
       		float yrtshlw;
       		float yrtdeep;
       		float yrtmine;

       		float yrald;
			float yrperm;

			float yrmossdz;
			float yrshlwdz;
			float yrdeepdz;

			float yrwatertab;

			float yrmossnum;
			float yrshlwnum;
			float yrdeepnum;

       		//soil - Bgc
    		float yrnetnmin;
    		float yrrrhsum;
    		float yrnrhsum;

    		float yrreacsum;
    		float yrnoncsum;

			float yrshlwcsum;
    		float yrdeepcsum;
    		float yrminecsum;

    		float yrorgn;
   		 	float yravln;
   		 	float yrsnuptake;
   		 	float yrwdebris;
			float yrwdrh;
						  
    		float yrninput;   //Yuan: for checking
    		float yrnlost;    //Yuan: for checking

    		//soil - fire disturbance
			float yrburnthick;
    		float yrburnsoilc;
    		float yrburnsoiln;
    		float yrorgnreturn;
    		
//2D to 1D for easy Java reading (mainly soil variables)
			float ts1D[MINY*MAX_OUT_SOI]; //monthly variables	
			float liq1D[MINY*MAX_OUT_SOI]; 
			float vwc1D[MINY*MAX_OUT_SOI];
			float ice1D[MINY*MAX_OUT_SOI];
			float dz1D[MINY*MAX_OUT_SOI];
			float z1D[MINY*MAX_OUT_SOI];
			float por1D[MINY*MAX_OUT_SOI];
			float type1D[MINY*MAX_OUT_SOI];
			float reac1D[MINY*MAX_OUT_SOI];
			float rrh1D[MINY*MAX_OUT_SOI];
			float nonc1D[MINY*MAX_OUT_SOI];
			float nrh1D[MINY*MAX_OUT_SOI];
			float rhmoist1D[MINY*MAX_OUT_SOI];
			float rhq101D[MINY*MAX_OUT_SOI];
			float ksoil1D[MINY*MAX_OUT_SOI];
			float kdl1D[MINY*MAX_OUT_SOI];
			float kdr1D[MINY*MAX_OUT_SOI];
			float kdn1D[MINY*MAX_OUT_SOI];

			float snz1D[DYINY*MAX_OUT_SNW];  //daily variables
			float frzfnt1D[DYINY*MAX_NUM_FNT]; 
			float thwfnt1D[DYINY*MAX_NUM_FNT];
			float liqd1D[DYINY*MAX_OUT_SOI];
			float tcondd1D[DYINY*MAX_OUT_SOI];
			float iced1D[DYINY*MAX_OUT_SOI];
			float tsd1D[DYINY*MAX_OUT_SOI];

};

#endif /*SNOWSOILOUTDATA_H_*/
