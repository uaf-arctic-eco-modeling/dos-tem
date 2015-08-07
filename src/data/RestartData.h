#ifndef RESTARTDATA_H_
#define RESTARTDATA_H_

#include "../inc/layerconst.h"
#include "../inc/timeconst.h"

class RestartData {
	public :
		RestartData();
		~RestartData();
		void reinitValue();
		
		int chtid;
		
		int perma;
	    double TSsnow[MAX_SNW_LAY];
	    double DZsnow[MAX_SNW_LAY]; 
	    double LIQsnow[MAX_SNW_LAY];
	    double RHOsnow[MAX_SNW_LAY]; 
	    double ICEsnow[MAX_SNW_LAY]; 
	    double AGEsnow[MAX_SNW_LAY];
	    double TSsoil[MAX_SOI_LAY]; 
	    double DZsoil[MAX_SOI_LAY]; 
	    double LIQsoil[MAX_SOI_LAY]; 
	    double ICEsoil[MAX_SOI_LAY];
	    int FROZENsoil[MAX_SOI_LAY]; 
	    int TYPEsoil[MAX_SOI_LAY];
	    double NONCsoil[MAX_SOI_LAY]; 
	    double REACsoil[MAX_SOI_LAY];
	    
	    double toptA[10];
	    double eetmxA[10];
	    double petmxA[10];
	    double unnormleafmxA[10];
	        
	    int CLAYmin[MAX_MIN_LAY];   
	    int SANDmin[MAX_MIN_LAY];
	    int SILTmin[MAX_MIN_LAY];
	    double TSrock[MAX_ROC_LAY]; 
	    double DZrock[MAX_ROC_LAY];
	    double frontZ[MAX_NUM_FNT];
	    int frontFT[MAX_NUM_FNT];
	     
	    double soln;
	    double avln;
	    double wdebris;
	    double strn; 
	    double ston; 
	    double vegc; 
	    double deadc; 
	    double deadn;
	    double prveetmx; 
	    double prvpetmx; 
	    double unnormleaf; 
	    double prvunnormleafmx;
	    double prvtopt; 
	    double c2n; 
	    double kdfib; 
	    double kdhum; 
	    double kdmin; 
	    double kdslow;
	    double foliagemx;
	    int ysf;
	    double burnedn; 
	    double lai;    
   	
};

#endif /*RESTARTDATA_H_*/
