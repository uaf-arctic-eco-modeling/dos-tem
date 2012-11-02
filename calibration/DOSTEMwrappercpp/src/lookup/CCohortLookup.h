#ifndef CCOHORTLOOKUP_H_
	#define CCOHORTLOOKUP_H_

	#include "../inc/cohortkey.h"
	#include "../inc/cohortconst.h"
	#include <cstdlib>
	#include <string>
	#include <iostream>
	#include <fstream>
	#include <sstream>
	using namespace std;
  			  
	class CCohortLookup{
  		public:
  			CCohortLookup();	
  			~CCohortLookup();
  			
  			// for target values
  			void init(string & file);
			float fibthick[MAX_DRG_TYPE][MAX_VEG_TYPE];
			float humthick[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float npp[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float gpp[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float nppsat[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float nuptake[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float vegC[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float vegN[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float fibsoilC[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float humsoilC[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float minesoilC[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float soilC[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float availN[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float soilN[MAX_DRG_TYPE][MAX_VEG_TYPE];

  			float ini_cmax[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float ini_nmax[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float ini_krb[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float ini_nup[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float ini_cfall[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float ini_nfall[MAX_DRG_TYPE][MAX_VEG_TYPE];  			
  			float ini_kdcfib[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float ini_kdchum[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float ini_kdcminfast[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float ini_kdcminslow[MAX_DRG_TYPE][MAX_VEG_TYPE];
  
  			float order_cmax[MAX_DRG_TYPE][MAX_VEG_TYPE];
    		float order_nmax[MAX_DRG_TYPE][MAX_VEG_TYPE];
   			float order_krb[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float order_nup[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float order_cfall[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float order_nfall[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float order_kdcfib[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float order_kdchum[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float order_kdcminfast[MAX_DRG_TYPE][MAX_VEG_TYPE];
  			float order_kdcminslow[MAX_DRG_TYPE][MAX_VEG_TYPE];
  
	};
	
#endif /*CCOHORTLOOKUP_H_*/
