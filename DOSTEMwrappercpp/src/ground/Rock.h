#ifndef ROCK_H_
#define ROCK_H_
#include "layer/Layer.h"

/*! \file
 */
#include "../inc/layerconst.h"
#include "../data/EnvData.h"
#include "../data/RestartData.h"

class Rock{
	public:
	Rock();
	
	
	/*! number of mineral layer*/
	int num;
	
	double dza[MAX_ROC_LAY];
	
	EnvData* ed;
	/*! total thickness of all rock layers (m) */
	double thick;
	
    void updateThicknesses(const double & thickness1);
	
	void initializeState( Layer* backl);
	void initializeState5restart( Layer* lstsoill, RestartData* resin);
	
	void  setEnvData(EnvData* ed);
};

#endif /*ROCK_H_*/
