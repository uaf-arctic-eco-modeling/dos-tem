/*
 * \file
 * defines struct for fluxes between atmosphere, vegetation, land(snow and soil)
 */
#ifndef FLUXES_H_
	#define FLUXES_H_
	#include "layerconst.h"

	// for water
	struct lnd2atm_env{
  		double eet;
  		double pet;
  		double ineet;	

	};

	struct lnd2atm_bgc{
		// carbon
  		double nep;

	};

	struct atm2lnd_env{
		// water	
  		double prec;  // mm/month
  		double snfl;  // mm/month
  		double rnfl;  // mm/month
		// energy
  		double girr;  
  		double nirr;  // W/m2
  		double par;	
  
	};

	struct atm2veg_env{
		// water
  		double rnfl;
  		double snfl;	
	};

	struct atm2veg_bgc{
		// carbon	
  		double ingpp; // gpp not limited by nitrogen availability
  		double gpp;
  		double innpp;
  		double npp;
  
	};

	struct veg2atm_env{
  		//water
  		double trans; // mm/day
  		double evapo; // mm/day
  		double trans_pet; // mm/day
  		double evapo_pet; // mm/day
  
  		double sublim; // mm/day	
  		// radiation
  		double solrad; // MJ/day
	};

	struct veg2atm_bgc{
  		//carbon
 		double rm;// maintainance respiration
  		double rg; // growth respiration;
	};

	struct veg2gnd_env{
  		// water
  		double rthfl; // rain throughfall
  		double sthfl; // snow throughfall	
  		double rdrip; // rain drip
  		double sdrip; // snow drip	
  
  		// radiation
  		double sw;// shortwave MJ/(m2d)
	};

	struct veg2soi_bgc{
  		// carbon	
  		double ltrfalc;
  
  		// nitrogen
  		double ltrfaln;
	};

	struct soi2veg_bgc{
  		// nitrogen	
  		double innuptake;	
  		double nuptake;
  		double suptake;
  		double luptake;
	};

	struct veg2veg_bgc{
  		//nitrogen
  		double nmobil;	
  		double nresorb;	

	};

	struct lnd2soi_env{
		// water	

 		double rperc;
 		double sperc;
 		double perc;
	};

	struct soi2lnd_env{
 		double qover;
 		double qdrain;
	};

	struct soi2lnd_bgc{
		// nitrogen
 		double nlost;

	};


	struct soi2atm_env{
  		double evap;
  		double trans;
  		double solrad;
	};

	struct soi2atm_bgc{
  		double rrh[MAX_SOI_LAY];
  		double nrh[MAX_SOI_LAY];
  		double wdrh; //rh from wood debris

	};

	struct snw2atm_env{
  		double sublim;	
  		double solrad;
	};

	struct snw2soi_env{
 		double infl;
	};

	struct atm2soi_bgc{
  		double ninput;
	};

	struct soi2soi_bgc{
  		double netnmin;
  		double nimmob;
	};

	struct atm2soi_fir{
 		double orgn;	
	};

	struct soi2atm_fir{
  		double orgc;
  		double orgn;	
	};

	struct veg2atm_fir{
  		double orgc;
  		double orgn;
	};

	struct veg2soi_fir{
  		double abvc;
  		double abvn;
  		double blwc;
  		double blwn;
  	
	};
#endif /*FLUXES_H_*/

