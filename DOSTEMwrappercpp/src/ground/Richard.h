
/*!\file
 * Implementation of Richard's law for soil water dynamics*/
 
#ifndef RICHARD_H_
#define RICHARD_H_



#include "../inc/layerconst.h"
#include "layer/Layer.h"
#include "layer/SoilLayer.h"
#include "../util/CrankNicholson.h"
#include "../data/EnvData.h"
#include "../util/Exception.h"

class Richard{
	public :
		Richard();
		~Richard();
	
		void updateSoilStructure(Layer *fstsoill);
	
		void  update(Layer * frontl, Layer *backl, Layer *fstsoill, Layer* drainl,  
				double & drain, const double & trans, const double & evap,
				const double & infil, const double & zwt);

		void setEnvData(EnvData* edp);

		CrankNicholson cn;
		Layer * lstunfl; // the last unfrozen layer
		int itsum;
		int itsumabv;
		int itsumblw;
	

	private:
		void initializeArray();
	    void iterate(Layer *fstsoill,const double & trans, const double & evap,const double & infil);
	    int updateOneTimeStep(Layer *fstsoill,const double & trans, const double & evap,const double & infil);
	    int updateOneIteration(Layer *fstsoill,const double & trans, const double & evap,const double & infil);	 
	
		int numal;
		double amx[MAX_SOI_LAY];// index 0 is for upper boundary condition, 
							// it is above the first soil layer 
							// and index nunsoil+1 is for lower boundary condition                           
		double bmx[MAX_SOI_LAY];	
		double cmx[MAX_SOI_LAY];
		double rmx[MAX_SOI_LAY];		
		double dwat[MAX_SOI_LAY];    
		double hk[MAX_SOI_LAY];    
		double dhkdw[MAX_SOI_LAY];     
		double smp[MAX_SOI_LAY];       
		double dsmpdw[MAX_SOI_LAY];
		double rootr[MAX_SOI_LAY];    
		double rootfr[MAX_SOI_LAY];    
		double tsl[MAX_SOI_LAY];    
		double liqii[MAX_SOI_LAY];
		double liqit[MAX_SOI_LAY];
		double liqis[MAX_SOI_LAY];
		double liqid[MAX_SOI_LAY];
		double liqld[MAX_SOI_LAY];
		double liq[MAX_SOI_LAY];
		double minliq[MAX_SOI_LAY];
		double maxliq[MAX_SOI_LAY];
		double qin[MAX_SOI_LAY];
		double qout[MAX_SOI_LAY];
		double drainratio[MAX_SOI_LAY]; // the ratio of drainage  
		double ice[MAX_SOI_LAY];
 
		//the dzmm, zmm and poro will not change until disturbance happened
		//so there is no need to create it every day  
		double dzmm[MAX_SOI_LAY];   // layer thickness in mm
		double zmm[MAX_SOI_LAY];   // layer top depth in mm
		double poro[MAX_SOI_LAY];
    
    	double ttole;	/*! tolerance of difference*/    
		int ITMAX; /*! the maximum number of iteration for one time step*/      
		double tleft; /*! the amount of time left for update (day)*/     
		double tmld;    /*!the last determined time, short for time-last-determined*/    
		bool tschanged;   // whether the time step has been changed for last factional time step
		double tstep;     
		double  TSTEPMAX; /*! the original time step*/
    
		double TSTEPORG;
    
		EnvData * ed;
 
};

#endif /*RICHARD_H_*/
