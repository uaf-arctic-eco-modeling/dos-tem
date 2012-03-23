#ifndef GRIDINPUTER_H_
#define GRIDINPUTER_H_

/*! this class is used to readin input of parameters, forcings for TEM
 * \file
 *
 * Modified by F-M Yuan, due to memory-leaking
 *
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;

#include "netcdfcpp.h"

//from TEMcore/..
#include "../util/Exception.h"
#include "../inc/layerconst.h"
#include "../inc/timeconst.h"
#include "../inc/ErrorCode.h"
#include "../data/GridData.h"

//local header
#include "../run/ModelData.h"

class GridInputer{
	public:
		GridInputer();
		~GridInputer();

		int atm_drv_yr;
		int fsize_drv_yr;

    	void init();
    	void initLatlon(string& dir);
    	void initClimate(string& dir);
    	void initFire(string& dir);
    	void initSoil(string& dir);
     
    /// grid data
    	int getGridRecID(const int & gid);
    	int getClmRecID(const int & clmid);
		void getGridData(GridData* gd, const int &grdrecid, const int &clmrecid);  //Yuan: grd's recid may or may not be same as clm's recid

    	void setModelData(ModelData* mdp);

		
	private:

		float getLAT(const int & recid );
		float getLON(const int & recid );

		void getClimate(float ta[][12], float prec[][12], float nirr[][12], float vap[][12] ,
				const int & recid);

    	int getBOTSOIL(const int & recid );
		int getTOPSOIL(const int & recid );

		int getFRI(const int & recid);
		void getFireSize(int fyear[], int fseason[], int fsize[], const int & recid);  //Yuan: moved from RegionInputer

		string grdfilename;
		string clmfilename;
		string soilfilename;
		string firefilename;
/*
	 	NcFile* friFile;
//	 	NcVar* grdfriV;
	 	NcVar* friV;
	
	 	NcFile* climateFile;
	 	NcDim* grdD;
	 	NcDim* yrD;
	 	NcDim* monD;
	 	NcVar* grdidV;  //Yuan: grid id, not the order in the climate.nc
	 	NcVar* taV;
	 	NcVar* precV;
	 	NcVar* nirrV;
	 	NcVar* vapV;
	 	NcVar* latV;
	 	NcVar* lonV;  //the soil lat lon are the same as lat lon of climate, checked when create climateFile
	 
	 
     	NcFile* soilFile;
//     	NcVar* grdsoilV;
     	NcVar* topsoilV;
     	NcVar* botsoilV;
*/
     	ModelData* md;

};


#endif /*GRIDINPUTER_H_*/
