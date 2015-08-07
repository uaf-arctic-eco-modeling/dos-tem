#ifndef COHORTINPUTER_H_
#define COHORTINPUTER_H_

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

//local header
#include "../run/ModelData.h"

//from TEMcore.dll
#include "../util/Exception.h"
#include "../inc/layerconst.h"
#include "../inc/timeconst.h"
#include "../inc/ErrorCode.h"

class CohortInputer{
	public:
		CohortInputer();
		~CohortInputer();
		
		int firesp_drv_yr;
		int firetr_drv_yr;
		int firesc_drv_yr;

		void init( );

		int  getEqRecID(const int &chtid);
		void getGrdID(int &grdid, const int &recid);   //Yuan: this id is for grid-level data, like soil, FRI, fire size
		void getVegetation(int & vtype,  const int & eqcid);
		void getDrainage(  int & dtype,  const int & eqcid);
	
		int  getSpRecID(const int &chtid);
		void getEqchtid5SpFile(int & eqchtid,  const int &recid);
  
		int  getTrRecID(const int &chtid);
		void getSpchtid5TrFile( int & spchtid,  const int &recid);

		int  getScRecID(const int &chtid);
		void getTrchtid5ScFile( int & trchtid,  const int &recid);

		void getChtID(int &chtid, const int &recid);   //Yuan: this is used for all run stages
		void getClmID(int &clmid, const int &recid);   //Yuan: this is used for all run stages
/*
		void getSpinupFireOccur(int year[MAX_SP_FIR_OCR_NUM], const int &spcid);
		void getSpinupFireSeason(int season[MAX_SP_FIR_OCR_NUM], const int &spcid);
		void getSpinupSeverity(int severity[MAX_SP_FIR_OCR_NUM], const int &spcid);  //Yuan:
		void getTransientFireOccur(int year[MAX_TR_FIR_OCR_NUM], const int &trcid);
		void getTransientFireSeason(int season[MAX_TR_FIR_OCR_NUM], const int &trcid);
		void getTransientSeverity(int severity[MAX_TR_FIR_OCR_NUM], const int &trcid);  //Yuan:
*/
		void getSpinupFire(int firedate[MAX_SP_YR], int firemonth[MAX_SP_YR],int fireyear[MAX_SP_YR],int firearea[MAX_SP_YR], const int &recid);
		void getTransientFire(int firedate[MAX_TR_YR], int firemonth[MAX_TR_YR],int fireyear[MAX_TR_YR],int firearea[MAX_TR_YR], const int &recid);
		void getScenarioFire(int firedate[MAX_SC_YR], int firemonth[MAX_SC_YR],int fireyear[MAX_SC_YR],int firearea[MAX_SC_YR], const int &recid);

		void setModelData(ModelData* mdp);

	private:
	 
		 int useseverity;
		 string eqidfname;
		 string vegidfname;
		 string drgidfname;
		 string spidfname;
		 string spffname;
		 string tridfname;
		 string trffname;
		 string scidfname;
		 string scffname;

		 void initEqChtidFile(string& dir);
		 void initVegetation(string& dir);
		 void initDrainage(string& dir);

		 void initSpChtidFile(string& dir);
		 void initTrChtidFile(string& dir);
		 void initScChtidFile(string& dir);

		 void initSpinupFire(string& dir);
		 void initTransientFire(string& dir);
		 void initScenarioFire(string& dir);

		 ModelData* md;
	
};


#endif /*COHORTINPUTER_H_*/
