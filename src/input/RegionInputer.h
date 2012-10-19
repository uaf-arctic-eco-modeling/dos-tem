#ifndef REGIONINPUTER_H_
#define REGIONINPUTER_H_
/*! this class is used to readin input of parameters, forcings for TEM
 * \file
 */

 
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

#include "netcdfcpp.h"

#include "../data/RegionData.h"
#include "../inc/ErrorCode.h"
#include "../util/Exception.h"

#include "../run/ModelData.h"

class RegionInputer{
	public:
		RegionInputer();
		~RegionInputer();

    // regional-level data
		void getCO2year(RegionData * rd);  //Yuan: modified
		void getCO2(RegionData * rd);        //Yuan: modified
	
		void setModelData(ModelData* mdp);
	
	private:
		ModelData* md;
	
};

#endif /*REGIONINPUTER_H_*/
