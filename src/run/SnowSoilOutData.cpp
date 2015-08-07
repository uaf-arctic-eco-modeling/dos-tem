/*define snow/soil variables for output*/

#include "SnowSoilOutData.h"

SnowSoilOutData::SnowSoilOutData(){
	 
	for (int id=0; id<DYINY; id++){
	// for daily
			errord = -999;

			infild[id]=-999;
			wtd[id]=-999;
			fsatd[id]=-999;
			qoverd[id]=-999; 
			qdraind[id]=-999;     
			
			growd[id]=-999;
			slradrefld[id]=-999;
			sevapd[id]=-999;

			for (int il=0; il<MAX_OUT_SOI; il++){
				liqd[id][il]=-999;
				tsd[id][il]=-999;
				iced[id][il]=-999;

				liqd1D[id*MAX_OUT_SOI+il]=-999;
				tcondd1D[id*MAX_OUT_SOI+il]=-999;
				iced1D[id*MAX_OUT_SOI+il]=-999;
				tsd1D[id*MAX_OUT_SOI+il]=-999;
			}
			
			for (int il=0; il<MAX_NUM_FNT; il++){
				frzfnt[id][il]=-999;
				thwfnt[id][il]=-999;
				frzfnt1D[id*MAX_OUT_SOI+il]=-999; 
				thwfnt1D[id*MAX_OUT_SOI+il]=-999;
			}

			numiter[id]=-999;
			numiterliq[id]=-999;

			snowthick[id]=-999; 
			swed[id]=-999; 
			smeltd[id]=-999; 
			ssubld[id]=-999;

			snradrefld[id]=-999;
	}
	
	for (int im=0; im<MINY; im++){
	// for monthly
	   		errorm=-999;
	   		
			ssubl[im]=-999;
			sninfl[im]=-999;
			sevap[im]=-999;
			watertab[im]=-999;
			mossdz[im]=-999;
			shlwdz[im]=-999;
			deepdz[im]=-999;

			for (int il=0; il<MAX_OUT_SOI; il++){
				dz[im][il]=-999;
				ts[im][il]=-999;	
				liq[im][il]=-999; 
				vwc[im][il]=-999;
				ice[im][il]=-999;
				z[im][il]=-999;
				por[im][il]=-999;
				type[im][il]=-999;
				reac[im][il]=-999;
				nonc[im][il]=-999;

				rrh[im][il]=-999;
				nrh[im][il]=-999;

				rhmoist[im][il]=-999;
				rhq10[im][il]=-999;
				ksoil[im][il]=-999;
				kdl[im][il]=-999;
				kdr[im][il]=-999;
				kdn[im][il]=-999;
			
				ts1D[im*MAX_OUT_SOI+il]=-999;
				liq1D[im*MAX_OUT_SOI+il]=-999; 
				vwc1D[im*MAX_OUT_SOI+il]=-999;
				ice1D[im*MAX_OUT_SOI+il]=-999;
				dz1D[im*MAX_OUT_SOI+il]=-999;
				z1D[im*MAX_OUT_SOI+il]=-999;
				por1D[im*MAX_OUT_SOI+il]=-999;
				type1D[im*MAX_OUT_SOI+il]=-999;
				reac1D[im*MAX_OUT_SOI+il]=-999;
				rrh1D[im*MAX_OUT_SOI+il]=-999;
				nonc1D[im*MAX_OUT_SOI+il]=-999;
				nrh1D[im*MAX_OUT_SOI+il]=-999;
				rhmoist1D[im*MAX_OUT_SOI+il]=-999;
				rhq101D[im*MAX_OUT_SOI+il]=-999;
				ksoil1D[im*MAX_OUT_SOI+il]=-999;
				kdl1D[im*MAX_OUT_SOI+il]=-999;
				kdr1D[im*MAX_OUT_SOI+il]=-999;
				kdn1D[im*MAX_OUT_SOI+il]=-999;
			}
			
			ninput[im]=-999;
			nlost[im]=-999;
			netnmin[im]=-999;
			nimmob[im]=-999;

			orgn[im]=-999;
			avln[im]=-999;
			reacsum[im]=-999;
			noncsum[im]=-999;
			shlwcsum[im]=-999;
			deepcsum[im]=-999;
			minecsum[im]=-999;

			growpct[im]=-999;

	}
	
	// for yearly
    		errory=-999;

    		yrsevap=-999;
    		yrqover=-999;
    		yrqdrain=-999;
    		yrssubl=-999;
 
       		yrtsave=-999;
    		yrliqsum=-999;
       		yricesum=-999;

       		yrvwcmin10=-999;
       		yrvwcshlw=-999;
       		yrvwcdeep=-999;
       		yrvwcmine=-999;

       		yrtmin10=-999;
       		yrtshlw=-999;
       		yrtdeep=-999;
       		yrtmine=-999;
       		
			yrald=-999;
			yrperm=-999;

			yrmossdz=-999;
			yrshlwdz=-999;
			yrdeepdz=-999;

			yrwatertab=-999;

			yrmossnum=-999;
			yrshlwnum=-999;
			yrdeepnum=-999;

    		yrnetnmin=-999;
    		yrrrhsum=-999;
    		yrnrhsum=-999;

    		yrreacsum=-999;
    		yrnoncsum=-999;

		yrshlwcsum=-999;
    		yrdeepcsum=-999;
    		yrminecsum=-999;

		yrkdfib=-999;
		yrkdhum=-999;
		yrkdmin=-999;
		yrkdslow=-999;

    		yrorgn=-999;
   		yravln=-999;
   		yrsnuptake=-999;
   		yrwdebris=-999;
		yrwdrh=-999;
						  
    		yrninput=-999;   //Yuan: for checking
    		yrnlost=-999;    //Yuan: for checking

 			yrburnthick=-999;
    		yrburnsoilc=-999;
    		yrburnsoiln=-999;
    		yrorgnreturn=-999;
    		
};

SnowSoilOutData::~SnowSoilOutData(){
	
};
