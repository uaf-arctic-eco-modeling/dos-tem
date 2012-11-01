#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

/* \file 
 * This class is used to implement
 * Runge-Kutta Method for integration of TEM equations
 * (see ATPress42005a, Numerical Recipes in C++, The art of scientific computing, 2nd edition
 *  W.H. Press, S.A. Teukolsky, W.T. Vetterling and B.P. Flannery, 2005, Cambridge University Press)
 * Page 712-727
 * 
 * Low-order classical Runge-Kutta Formulas with step size control and their application
 * to some heat transfer problems
 * by Erwin Feblberg
 * NASA TR R-315, 1969
 * REPORT TL 521 A3312 no.315 in GI-IARC 1st floor
 * see also http://www.ece.uwaterloo.ca/~ece204/TheBook/14IVPs/rkf45/
 */
#include "../inc/temconst.h"
 
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

#include "../ground/Soil_Bgc.h"
#include "../vegetation/Vegetation_Bgc.h"
#include "../data/BgcData.h"
#include "../data/EnvData.h"

class Integrator{
	public :
		Integrator();
        enum temkey { I_VEGC,  I_STRN, I_STON, I_SOLN, I_AVLN, I_UNNORMLEAF,I_WDEBRIS, //7,  start from zero, index
        	
				   I_INGPP,    I_GPP,      I_INNPP,    I_NPP,      I_RM,
				   I_RG,       I_LTRC,     I_RH_WD,                     //8

                   I_NINP,     I_INNUP,    I_VNUP,     I_VSUP,
                   I_VLUP,     I_VNMBL,    I_VNRSRB,   I_LTRN,  
                   I_NMIN,     I_MNUP,     I_NLST,    I_SNUP,  //4+8
                  
                   I_L_REAC =NUM_NL_STATE + NUM_NL_FLXDIAG,
                   I_L_NONC =NUM_NL_STATE + NUM_NL_FLXDIAG + MAX_SOI_LAY,
                   I_L_RRH   =NUM_NL_STATE + NUM_NL_FLXDIAG + 2* MAX_SOI_LAY,//reactive rh
                   I_L_NRH   =NUM_NL_STATE + NUM_NL_FLXDIAG + 3* MAX_SOI_LAY //non-reactive rh
                
                  };  
        // after change the keys here , remember to update the NUMEQ and MAXSTATE in  TEMCONST         

       char predstr[NUMEQ][11];
                    
       void setSoil_Bgc(Soil_Bgc * soib);
       void setVegetation_Bgc( Vegetation_Bgc * vegb);
       void setBgcData(BgcData* bdp);
       void setEnvData(EnvData* edp);
       
       void updateMonthly();
    
  	   int NUMSL; //actual number of soil layers
  
  private:
       int nfeed;
       int adapt(float pstate[]);

       bool rkf45( const int& numeq, float pstate[], float& pdt);
       int boundcon( float ptstate[], float err[], 
                            float& ptol ) ;
       void delta(  float pstate[], 
                          float pdstate[] );

       int blackhol;
       float inittol;
       int maxit;
       int maxitmon;
       int retry;

       int syint;
       int test;
      
       float y[NUMEQ];
       float dum4[NUMEQ];
       float error[NUMEQ];

       void step( const int& numeq, float pstate[], float pdstate[], 
                 float ptstate[], float& pdt );

      float dum5[NUMEQ];
      float dumy[NUMEQ];

      float ydum[NUMEQ];
      float dy[NUMEQ];
      float yprime[NUMEQ];
      float rk45[NUMEQ];

      float f11[NUMEQ];
      float f2[NUMEQ];
      float f13[NUMEQ];
      float f3[NUMEQ];
      float f14[NUMEQ];
      float f4[NUMEQ];
      float f15[NUMEQ];
      float f5[NUMEQ];
      float f16[NUMEQ];
      float f6[NUMEQ];


      static float  a1, a3, a31, a32;
      static float      a4, a41, a42, a43;
      static float      a5, a51, a52, a53, a54;
      static float  b1,  b3, b4, b5;
      static float  b6, b61, b62, b63, b64, b65;

      float dummy;
	
	  void y2cstate(float dy[]);
	  void c2ystate(float dy[]);
	  void y2cflux(float dy[]);
	  void c2yflux(float dy[]);
	  void dc2yflux(float pdstate[]);
	  void dc2ystate(float pdstate[]);
	  void y2tcstate(float pdstate[]);// t stands for temporary
	 
	  bool checkPools();
	 
      Soil_Bgc * ssl;
	  Vegetation_Bgc * veg;
	  BgcData * bd;
	  EnvData * ed;
	  
	  
};
#endif /*INTEGRATOR_H_*/


