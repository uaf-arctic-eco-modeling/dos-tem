#ifndef COHORTDATA_H_
#define COHORTDATA_H_

#include "../inc/timeconst.h"

class CohortData{
  	public:
  		CohortData();
  		~CohortData();
  
  		int grdid;   // Yuan: grid id of soil, grid-level fire data
  		int clmid;   // Yuan: used for different climate data

  		int trchtid; // transient cohortid
  		int eqchtid; // equilibrium cohort id
  		int spchtid; // spinup cohort id
  		int scchtid; // scenario cohort id
  		int reschtid;  //cohort id for restart

  		int drgtype;
  		int vegtype;
  	
		int trfireyear[MAX_TR_FIR_OCR_NUM];
		int trseason[MAX_TR_FIR_OCR_NUM];
		int trseverity[MAX_TR_FIR_OCR_NUM];   //Yuan: severity in ALFRESCO: 0 - none; //
		         //1- Low severity;
		         //2 - Moderate Severity;
		         //3 - High severity + Low Surface Severity;
                 //4 - High severity + High Surface Severity;

		int spfireyear[MAX_SP_FIR_OCR_NUM];
		int spseason[MAX_SP_FIR_OCR_NUM];

		int spseverity[MAX_SP_FIR_OCR_NUM];   //Yuan: modified
	
};

#endif /*COHORTDATA_H_*/
