#ifndef LAYERCONST_H_
	#define LAYERCONST_H_
	
	const int MAX_SNW_LAY =6; //maximum number of Snow Layer
	
	const int MAX_ROC_LAY =5; // maximum number of rock Layer (
	const int MAX_MOS_LAY =2; // maximum number of moss Layer
	const int MAX_SLW_LAY =3; // maximum number of shallow organic Layer
	const int MAX_DEP_LAY =3; // maximum number of deep organic Layer
	const int MAX_MIN_LAY =13; // maximum number of mineral Layer (0.1,0.1,0.1,0.1, 0.2,0.2,0.2,0.3,0.3,0.3, 0.5, 1, 2)
	const float MINETHICK[MAX_MIN_LAY] = {0.1,0.1,0.1,0.1, 0.2,0.2,0.2,0.3,0.3,0.3, 0.5, 1.0, 2.0}; //total 5.40 m
	
	const int MAX_SOI_LAY =MAX_MOS_LAY+ MAX_SLW_LAY+MAX_DEP_LAY+MAX_MIN_LAY; // maximum number of soil layer
	const int MAX_DYN_LAY =MAX_SOI_LAY+ MAX_SNW_LAY; // maximum number of (snow + soil) layer
	const int MAX_GRN_LAY =MAX_SOI_LAY+ MAX_SNW_LAY + MAX_ROC_LAY; //maximumum number of Ground (soil+rock+snow) Layer
	
	const int MAX_NUM_FNT =10; // maximum number of fronts in ground
	const int MAX_OUT_SOI =15; //maximum number of soil layer for output
	const int MAX_OUT_SNW =6;  //maximum number of snow layer for output
    	 
#endif /*LAYERCONST_H_*/
