/*! \file 
 * this header provides constants for TEM Run*/
 
#ifndef TEMCONST_H_
#define TEMCONST_H_
#include "layerconst.h"

	// number of non-layered state variables
	const int NUM_NL_STATE =7;

	// number of non-layered flux or diagnostic variables
	const int NUM_NL_FLXDIAG =20;

	// number of layered state variables
	const int NUM_L_STATE =2;

	// number of layered flux or diagnostic variables
	const int NUM_L_FLXDIAG =2;

	// number of ODE equations
	const int NUMEQ = NUM_NL_STATE + NUM_NL_FLXDIAG +( NUM_L_STATE+NUM_L_FLXDIAG)*MAX_SOI_LAY;

	// number of state variables
	const int MAXSTATE = NUM_NL_STATE;

#endif /*TEMCONST_H_*/
