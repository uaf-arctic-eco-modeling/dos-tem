#ifndef COHORTLOOKUP_H_
	#define COHORTLOOKUP_H_

	#include "../inc/cohortkey.h"
	#include "../inc/cohortconst.h"
	#include "../inc/timeconst.h"	
	#include "../inc/layerconst.h"

	const int MAX_SOC_DEP =7; // seven layers for soc
	const int MAX_FR_INT =10; // 10 intervals for fine root production

	class CohortLookup {
  		public:
  			CohortLookup();
  			~CohortLookup();

  			void init();

  			// for vegetation			  
  			float kc[MAX_VEG_TYPE];
  			float ki[MAX_VEG_TYPE];
  			float gva[MAX_VEG_TYPE];
  			float tmin[MAX_VEG_TYPE];
  			float toptmin[MAX_VEG_TYPE];
  			float toptmax[MAX_VEG_TYPE];
  			float tmax[MAX_VEG_TYPE];
  			float raq10a0[MAX_VEG_TYPE];
  			float raq10a1[MAX_VEG_TYPE];
  			float raq10a2[MAX_VEG_TYPE];
  			float raq10a3[MAX_VEG_TYPE];
  			float kn1[MAX_VEG_TYPE];
  			float labncon[MAX_VEG_TYPE];
  			float leafmxc[MAX_VEG_TYPE];
  			float kleafc[MAX_VEG_TYPE];
  			float sla[MAX_VEG_TYPE];
  			float cov[MAX_VEG_TYPE];
  			float fpcmax[MAX_VEG_TYPE];
  			float abv2totmass[MAX_VEG_TYPE];
  
  			float maturefoliagemin[MAX_VEG_TYPE];
  
      		// calib
 
  			float initleafmx[MAX_VEG_TYPE]; 
  			float c2nmin[MAX_VEG_TYPE];
  			float cnmin[MAX_VEG_TYPE];
  			float c2na[MAX_VEG_TYPE];
  			float c2nb[MAX_VEG_TYPE];
  			float initcneven[MAX_VEG_TYPE]; 
  
  			// for leaf
  			float minleaf[MAX_VEG_TYPE];
  			float aleaf[MAX_VEG_TYPE];
  			float bleaf[MAX_VEG_TYPE];  	
  			float cleaf[MAX_VEG_TYPE];

  			float m1[MAX_VEG_TYPE];
  			float m2[MAX_VEG_TYPE];
  			float m3[MAX_VEG_TYPE];
  			float m4[MAX_VEG_TYPE];

  			float albvisnir[MAX_VEG_TYPE];
  			float gl_bl[MAX_VEG_TYPE];
  			float gl_c[MAX_VEG_TYPE];
  			float glmax[MAX_VEG_TYPE];
  			float er[MAX_VEG_TYPE]; // canopy light extinction coefficient
  			float ircoef[MAX_VEG_TYPE]; //canopy interception coeff for rain
  			float iscoef[MAX_VEG_TYPE]; //canopy interception coeff for rain
  
  			float vpd_open[MAX_VEG_TYPE]; //vpd: start of conductance reduction
  			float vpd_close[MAX_VEG_TYPE]; //vpd: complete conductance reduction
  
  			//from biomebgc
  			float lwp_open[MAX_VEG_TYPE];
  			float lwp_close[MAX_VEG_TYPE];
  			float all2prj[MAX_VEG_TYPE];
  			float ppfd50[MAX_VEG_TYPE];
  
  			// for mcrobe
    		float rhq10[MAX_VEG_TYPE];
    		float kn2[MAX_VEG_TYPE];
    		float moistmin[MAX_VEG_TYPE];
    		float moistopt[MAX_VEG_TYPE];
    		float moistmax[MAX_VEG_TYPE];
    
    		float propftos[MAX_VEG_TYPE];
    		float nloss[MAX_VEG_TYPE];

    		float lcclnc[MAX_VEG_TYPE];

    		float cnsoil[MAX_VEG_TYPE];  
    	
    		///calibration related
 			float kdcfib[MAX_DRG_TYPE][MAX_VEG_TYPE];
 			float kdchum[MAX_DRG_TYPE][MAX_VEG_TYPE];
 			float kdcmin[MAX_DRG_TYPE][MAX_VEG_TYPE];
 			float kdcslow[MAX_DRG_TYPE][MAX_VEG_TYPE];
 			float nup[MAX_DRG_TYPE][MAX_VEG_TYPE];
     
  			float cmax[MAX_DRG_TYPE][MAX_VEG_TYPE];        
  			float nmax[MAX_DRG_TYPE][MAX_VEG_TYPE];
 
  			float cfall[MAX_DRG_TYPE][MAX_VEG_TYPE];     
  			float nfall[MAX_DRG_TYPE][MAX_VEG_TYPE];
  
  			float kra[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float krb[MAX_DRG_TYPE][MAX_VEG_TYPE];
  
  			//init value
  			float initvegc[MAX_DRG_TYPE][MAX_VEG_TYPE];     //target value
  			float initstrn[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float initston[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float initsolc[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float initsoln[MAX_DRG_TYPE][MAX_VEG_TYPE]; 
  			float initavln[MAX_DRG_TYPE][MAX_VEG_TYPE];
   
  			// for root
    		float frprod_frac[MAX_VEG_TYPE][MAX_FR_INT];
    		float rootza[MAX_VEG_TYPE];
    		float rootzb[MAX_VEG_TYPE];
    		float rootzc[MAX_VEG_TYPE];
    		float minrootz[MAX_VEG_TYPE];
    		float rootmass[MAX_VEG_TYPE];
    		float rootbeta[MAX_VEG_TYPE];
    		float rootdp4infil[MAX_VEG_TYPE];
    		float richardl[MAX_VEG_TYPE];
    
    		float rootdp4gpp[MAX_VEG_TYPE];
  
  			// for SOC
    		//float fracsoc[MAX_VEG_TYPE][MAX_SOC_DEP];  // should be from site specific data
    		float maxmossthick[MAX_VEG_TYPE];
    		float abvltrr2t[MAX_VEG_TYPE];//above ground litter fall ratio of reactive to total 
    		float blwltrr2t[MAX_VEG_TYPE];//below ground litter fall ratio of reactive to total 

  			//monthly LAI
    		float envlai[MAX_VEG_TYPE][MINY];
    
  			/// SOIL LAYER  
    		float mossthick[MAX_DRG_TYPE][MAX_VEG_TYPE];
    		float fibthick[MAX_DRG_TYPE][MAX_VEG_TYPE];
    		float humthick[MAX_DRG_TYPE][MAX_VEG_TYPE];
    
    		float coefshlwa[MAX_DRG_TYPE][MAX_VEG_TYPE];//carbon vs thick
    		float coefshlwb[MAX_DRG_TYPE][MAX_VEG_TYPE];//carbon vs thick
    
    		float coefdeepa[MAX_DRG_TYPE][MAX_VEG_TYPE];//carbon vs thick
    		float coefdeepb[MAX_DRG_TYPE][MAX_VEG_TYPE];//carbon vs thick
    
    		float coefminea[MAX_DRG_TYPE][MAX_VEG_TYPE];//carbon density vs ham
    		float coefmineb[MAX_DRG_TYPE][MAX_VEG_TYPE];//carbon density vs ham
    
			float ltrfalratiom2f[MAX_DRG_TYPE][MAX_VEG_TYPE]; 
			float ltrfalratioh2f[MAX_DRG_TYPE][MAX_VEG_TYPE];
    
     		float fsoma[MAX_DRG_TYPE][MAX_VEG_TYPE];    //after decomposition, fraction of active SOM-C
     		float fsompr[MAX_DRG_TYPE][MAX_VEG_TYPE];   //after decomposition, fraction of physically-resistant SOM-C
     		float fsomcr[MAX_DRG_TYPE][MAX_VEG_TYPE];   //after decomposition, fraction of chemically-resistant SOM-C
     		float som2co2[MAX_DRG_TYPE][MAX_VEG_TYPE];  //after decomposition, ratio of SOM-Cs to CO2-C released
     
    		float minthick[MAX_MIN_LAY];
    		int minclay[MAX_MIN_LAY];
    		int minsand[MAX_MIN_LAY];
    		int minsilt[MAX_MIN_LAY];
    
  			// hydrological related

    		float psimax[MAX_VEG_TYPE];
     		float evapmin[MAX_VEG_TYPE];
    
   			// for VIC
   			float Ds[MAX_DRG_TYPE];
   			float Ws[MAX_DRG_TYPE];
   			float Dsmax[MAX_DRG_TYPE];
   			float b_infilt[MAX_DRG_TYPE];
 			float drainmax[MAX_DRG_TYPE];
   			float wfact[MAX_DRG_TYPE];

   			// snow related
    		float snwdenmax[MAX_VEG_TYPE];
    		float snwalbmax[MAX_VEG_TYPE];
    		float snwalbmin[MAX_VEG_TYPE];
    		float snwdennew[MAX_VEG_TYPE];
    
   			//fire related
    		float burnthick_max[MAX_VEG_TYPE];// maximum burn thickness[m]
    		float vegcombust[MAX_VEG_TYPE];// vegetation combustion rate
    		float vegslash[MAX_VEG_TYPE]; // vegetation slash
    		float matureage[MAX_VEG_TYPE];
  	  		
  		private:
   			void assignVegetationParams();	
   			void assignLeafParams();		
   			void assignMicrobeParams();	
   			void assignRootParams();	
   			void assignSoilTextureParams();	
   			void assignSOCParams();	
   			void assignHydroPara();	
   			void assignSnowPara();
   			void assignFirePara();
   
   			void setEnvLAI(); 
	};

#endif /*COHORTLOOKUP_H_*/
