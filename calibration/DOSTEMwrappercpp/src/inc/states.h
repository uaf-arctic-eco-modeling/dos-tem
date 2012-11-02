/*
 * \file
 * defines struct for state variables between atmosphere, vegetation, land(snow and soil)
 */
#ifndef STATES_H_
#define STATES_H_

#include "layerconst.h"

struct atmstate_env{
	double ta;
	double clds;
	double co2; //ppmv
	int dsr; // day since rain
};

struct vegstate_env{
	double snow;  // snow interception // mm (H2O)
	double rain;  // rain interception // mm (H2O)
};

struct vegstate_bgc{
	double c;
	double deadc;
	double deadn;
	double ston;
	double strn;
	double unnormleaf;
};

struct snwstate_env{
	double thick; // thickness of snowpack
	double swe;
};

struct soistate_env{
	int numsl; // number of soil layers
	int numal; // number of active soil layers

	double tsave;
	double ts[MAX_SOI_LAY];
	double liq[MAX_SOI_LAY]; // soil liquid water content kg/m2
	double ice[MAX_SOI_LAY]; // soil ice content kg/m2
	double liqsum;
	double icesum;

	double rootfrac[MAX_SOI_LAY];
	double dz[MAX_SOI_LAY]; // layer thickness
	double z[MAX_SOI_LAY]; // distance between soil surface and layer top
	double por[MAX_SOI_LAY];
	double type[MAX_SOI_LAY]; // layer type://0,1,2,moss, peat, mineral

};

struct soistate_bgc{
	double reac[MAX_SOI_LAY];
	double nonc[MAX_SOI_LAY]; //non reactive c

	double wdebris;
	double orgn ;// soil liquid water content kg/m2
	double avln ;// soil ice content kg/m2
};

#endif /*STATES_H_*/
