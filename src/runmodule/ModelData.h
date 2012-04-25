#ifndef MODELDATA_H_
	#define MODELDATA_H_
	#include <string>
	#include <iostream>
	#include <fstream>
	#include <sstream>
    #include <cstdlib>

	using namespace std;
	
	class ModelData{
 		public:
 
    		ModelData();
    		~ModelData();

    		int myid;            // these two are for parallel model run (NOT USED)
    		int numprocs;

    		int runmode;  //1: site; 2: region - time-series; 3: region - spatially
    		bool consoledebug;   // more info will display when running

    		// the following 5 switches will allow modules on/off -
    		bool envmodule;   //(Bio)physical module on/off
			bool bgcmodule;   //BGC module on/off

			bool dvmmodule;   //dynamic vegetation module on/off
			bool dslmodule;   //dynamic soil layer module on/off

			bool dsbmodule;   //disturbance module on/off
			bool friderived;  // option for switching Grid-level fire occurrence (upon FRI)

			// the following 3 switches will control N modules in BGC
	     	bool baseline;   //=true allowing ninput and nlost to be used for adjusting c/n of soil
	     	bool nfeed;      //=true allowing N uptake limited by soil conditions, which then controls plant growth,
	     	                 //   basically it's a switch for soil-plant N process modules
   		    bool avlnflg;    // inorganic N in/out module on (true) or not (false) - partial open N cycle

			// the following are from Controller.cpp (reading from '????control.txt')
    		bool runeq;
    		bool runsp;
    		bool runtr;
    		bool runsc;
     		int initmode;

   			string casename;
  			string configdir;
  			string runchtfile;       //must be *.nc format file
 			string outputdir;
  			string reginputdir;
  			string grdinputdir;
  			string chtinputdir;
 			string runstages;

  			string initmodes;
  			string initialfile;      //either the restart.nc, or sitein.nc file, upon initmodes

    		int changeclimate;      // 0: default (up to run stage); 1: dynamical; -1: static
     		int changeco2;          // 0: default (up to run stage); 1: dynamical; -1: static
    		bool updatelai;         // dynamical LAI in model or static LAI (from 'chtlu')
    		bool useseverity;       // using fire severity inputs

    		int  outstartyr;        // output starting calendar year (-9999 is for model starting year)
   			bool outSiteDay;
   			bool outSiteMonth;
   			bool outSiteYear;
   			bool outRegn;
   			bool outSoilClm;
 
    		//
    		void checking4run();

		//this is for java interface
  			char* joutputdir;
  			char* jcasename;
  			char* jcctypes;
  			char* jreginputdir;
  			char* jgrdinputdir;
  			char* jrunchtfile;       
  			char* jinitmodes;
  			char* jrunstages; 
  			char* jinitialfile;
  			char* jchtinputdir;

			void stringtochar();

 		private:
	
	};

#endif /*MODELDATA_H_*/