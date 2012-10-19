////////////////////////////////////////////////////////////////////////////////////////
/* 
 *  TEM.cpp
 *  main program for running DOS-TEM
 *  
 *  It runs at 2 run-mods:
 *      (1) site-specific
 * 		(2) regional (multiple sites)
 * 
 * Authors: Shuhua Yi - the original codes
 * 		    Fengming Yuan - re-coding for (1) easily code managing;
 *                                        (2) java interface developing for calibration;
 *                                        (3) stand-alone application of TEM (java-c++)
 *                                        (4) inputs/outputs using netcdf format, have to be modified
 *                                        to fix memory-leaks
 *
 * Affilation: Spatial Ecology Lab, University of Alaska Fairbanks 
 *
 * started: 10/31/2006 
 * last modified: 09/25/2009

*/
/////////////////////////////////////////////////////////////////////////////////////////         
 
//include        

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <exception>
using namespace std;
 
#include "TEMMOD.h"         // set run-mode and output option(s) for site-run 

#ifdef SITERUN
	#include "runmodes/Siter.h"
#endif

#ifdef REGNRUN
	#include "runmodes/Regioner.h"
#endif

/////////////////////////////////////////////////////////////////////////////////
       
int main(int argc, char* argv[]){
	
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	#ifdef REGNRUN
		time_t stime;
		time_t etime;
		stime=time(NULL);
		cout <<"run TEM regionally - start @"<<ctime(&stime)<<"\n";

		string controlfile="";
		if(argc==1){ //if there is no control file specified
				controlfile ="config/regncontrol.txt";
		} else if(argc ==2) {
				controlfile =argv[1];
		}

		Regioner regner;

		regner.init(controlfile);
   
		regner.run();
      
 		etime=time(NULL);
		cout <<"run TEM regionally - done @"<<ctime(&etime)<<"\n";
		cout <<"total seconds: "<<difftime(etime, stime)<<"\n";

	#endif

	#ifdef SITERUN 
		time_t stime;
		time_t etime;
		stime=time(NULL);
		cout<<"run TEM stand-alone - start @"<<ctime(&stime)<<"\n";

		string controlfile="";
		if(argc==1){ //if there is no control file specified
			controlfile ="config/sitecontrol.txt";
		} else if(argc ==2) {
			controlfile =argv[1];
		}

		Siter siter;    
 		siter.init(controlfile);     
	
 		siter.run();       
 
 		etime=time(NULL);
		cout <<"run TEM stand-alone - done @"<<ctime(&etime)<<"\n";
		cout <<"total seconds: "<<difftime(etime, stime)<<"\n";
	#endif

 	return 0;

};
