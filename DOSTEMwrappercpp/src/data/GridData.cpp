#include "GridData.h"


GridData::GridData(){
	
};

GridData::~GridData(){
	
};

//for java interface
void GridData::d1tod2() {
	for (int i=0; i<MAX_ATM_DRV_YR; i++) {
		for (int j=0; j<12; j++) {
			ta[i][j]   = ta1d[i*12+j];
			prec[i][j] = prec1d[i*12+j];
			nirr[i][j] = nirr1d[i*12+j];
			vap[i][j]  = vap1d[i*12+j];
		}
	}
	
};

