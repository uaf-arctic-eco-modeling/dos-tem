#ifndef GRID_H_
#define GRID_H_

#include <cmath>
#include <iostream>
using namespace std;

#include "../atmosphere/Atmosphere.h"

#include "../data/EnvData.h"
#include "../data/GridData.h"
#include "../data/RegionData.h"

#include "../util/Exception.h"
#include "../inc/ErrorCode.h"

class Grid{
	public :
	Grid();
	~Grid();
	
	int gid;
	
	
	int reinit(const int &gid1);
	
 	void setEnvData(EnvData * ed);
 	void setRegionData(RegionData *rd);
 	void setGridData(GridData * gd);

 	// 	protected:

 	Atmosphere atm; 	
	
    EnvData* ed;
    RegionData* rd;
    GridData* gd;

};
#endif /*GRID_H_*/
