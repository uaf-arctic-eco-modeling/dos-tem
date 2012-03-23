/*
 * \file
 * defines struct for diagnostic variables between atmosphere, vegetation, land(snow and soil)
 */
#ifndef DIAGNOSTICS_H_
	#define DIAGNOSTICS_H_
	#include "layerconst.h"

// Diagnostic Variables
struct atmdiag_env{
  	double rhoa;	
  	double vpd;
  	double abshd; //absolute humidity deficit
  	double dersvp;
  	double vp;    //Pa, Nov. 4, 2007
  	double svp; 	//Pa, Nov. 4, 2007
};

struct soidiag_fir{
  	double burnthick;	
};

struct vegdiag_env{
  	double envlai;
  	double btran;
  	double m_ppfd;
  	double m_vpd;
  
  	double rc;
  	double cc; //canopy conductance m/s
  	double rac; // radiation in canopy // MJ/(m2d)
  	double rinter; //rain interception
  	double sinter; //snow interception
  	double parabsorb; //absorbed PAR
  	double ppfdabsorb; //absorbed PAR
  	double vegfrac; //fraction of vegetation
};

struct vegdiag_bgc{
  	double abvgndc;
  	double lai;
  	double fpc;
  	double leaf; 
  	double foliage;
  	double raq10;
  	double ftemp; /*! temperature factor for gpp*/
  	double gv;
  	double kr;  // is related to kra, krb, and vegetation carbon  pool 
  	double fna; // effect of nitrogen availability on gpp
  	double fca; // effect of carbon availability on nuptake
};

struct snwdiag_env{
  	double dense;
  	double melt;
};

struct soidiag_env{
	double growpct;
	double watertab;
	double frasat;
	double itnum;// interation number
	double itnumliq;// interation number
	  
	double btran;
	double degday10;
	double nfactor;
	int permafrost;
	int growstart;
	int snowfree1st;
	int growend;
	double tmineral10cm;
	double trock34m;
	double  unfrzcolumn;
	  
	double allvwc[MAX_SOI_LAY];  // Yuan: soil water content: volume fraction of all water/total soil volume (Theta)
	double alliwc[MAX_SOI_LAY];  // Yuan: ice water content: volume fraction of ice water/total soil volume (Theta)
	double alllwc[MAX_SOI_LAY];  // Yuan: liquid water content: volume fraction of liquid water/total soil volume (Theta)
	double allsws[MAX_SOI_LAY];  // soil liquid water saturation (liq vwc/total porosity) for use in Soil_Bgcfor use in Soil_Bgc
	double allaws[MAX_SOI_LAY];  // adjusted soil liquid water saturation (liq vwc/(porosity-ice vwc)) for use in Soil_Bgc

	double hcond[MAX_SOI_LAY];   // Yuan: actual soil hydraulic conductivity

	double minliq[MAX_SOI_LAY]; 
	  
	double tem[MAX_SOI_LAY];
	double tcond[MAX_SOI_LAY];

	double frzfnt[MAX_NUM_FNT];
	double thwfnt[MAX_NUM_FNT];
	
	int actual_num_soil;
	double mossthick;
 	double shlwthick;
 	double deepthick;
 	double minethick;
	double mossnum;
	double shlwnum;
	double deepnum;
 
 	double maxrootratio;
 	int maxrootind;
};

struct soidiag_bgc{
  	double ksoil[MAX_SOI_LAY];
  	double rhmoist[MAX_SOI_LAY];
  	double rhq10[MAX_SOI_LAY];
  	double frprod_frac[MAX_SOI_LAY];
  	double totc[MAX_SOI_LAY];
   	double reacsum; 
   	double noncsum;
    double rrhsum; 
    double nrhsum; 
    double shlwc;
    double deepc;
    double minec;
    
  	double kdl[MAX_SOI_LAY];
  	double kdr[MAX_SOI_LAY];
  	double kdn[MAX_SOI_LAY];
};


#endif /*DIAGNOSTICS_H_*/
