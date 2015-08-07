#include "ModelData.h"

ModelData::ModelData(){
	
  	runeq = false;
  	runsp = false;
  	runtr = false;
  	runsc = false;
  
  	useseverity = false;

  	initmode =-1;	
   
  	consoledebug = true;
  	
  	myid =0;
  	numprocs =1;		
};

ModelData::~ModelData(){

}

void ModelData::checking4run(){
 	
 	//run stage
 	if(runstages == "eq"){
   		runeq = true;
 	}else if(runstages == "sp"){
   		runsp = true;
 	}else if(runstages == "tr"){
   		runtr = true;	
 	}else if(runstages == "sc"){
//	  	runtr = true;       //Yuan: scenario-run is using the setting for transient-run, except for years
	  	runsc = true;
	  	useseverity = false;  //Yuan: using ALFRESCO's fire severity data, otherwise, set this as 'false'
 	}else if(runstages== "sptr"){
   		runsp = true;
   		runtr = true;	
 	}else {
 		cout <<"the run stage " << runstages << "  was not recognized  \n";
		cout <<"should be one of 'eq','sp','tr','sc', or 'sptr'";
    	exit(-1);
 	}	
 
 	//initilization modes for state variables
 	if(initmodes =="lookup"){
 		initmode =1;
 	}else if(initmodes =="sitein"){
 		initmode =2;
 	}else if(initmodes =="restart"){
 		initmode =3;
 	}else{
    	cout <<"the initialize mode " << initmodes << "  was not recognized  \n";
		cout <<"should be one of 'lookup','sitein', or 'restart'";
    	exit(-1);	
 	}

 	//model run I/O directory checking
 	if (outputdir == "") {
 		cout <<"directory for output was not recognized  \n";
    	exit(-1);
 	}
 	if (reginputdir == "") {
 		cout <<"directory for Region-level iutput was not recognized  \n";
    	exit(-1);
 	}
 	if (grdinputdir == "") {
 		cout <<"directory for Grid-level iutput was not recognized  \n";
    	exit(-1);
 	}

 	if (eqchtinputdir == "" && runeq) {
 		cout <<"directory for Equilibrium-run cohort iutput was not recognized  \n";
    	exit(-1);
 	}
 	if (spchtinputdir == "" && runsp) {
 		cout <<"directory for Spinup-run cohort iutput was not recognized  \n";
    	exit(-1);
 	}
 	if (trchtinputdir == ""  && runtr) {
 		cout <<"directory for Transient-run cohort iutput was not recognized  \n";
    	exit(-1);
 	}
 	if (scchtinputdir == ""  && runsc) {
 		cout <<"directory for Scenario-run cohort iutput was not recognized  \n";
    	exit(-1);
 	}

 	if (initialfile == "" && initmode==2) {
 		cout <<"directory for sitein file was not recognized  \n";
    	exit(-1);
 	}

 	if (initialfile == "" && initmode==3) {
 		cout <<"directory for restart file was not recognized  \n";
    	exit(-1);
 	}

};

//BELOW is for java interface
void ModelData::stringtochar (){
  	joutputdir       = const_cast< char* > (outputdir.c_str());
  	jcasename        = const_cast< char* > (casename.c_str());
  	jcctypes         = const_cast< char* > (cctypes.c_str());
  	jreginputdir     = const_cast< char* > (reginputdir.c_str());
  	jgrdinputdir     = const_cast< char* > (grdinputdir.c_str());
  	jrunchtfile      = const_cast< char* > (runchtfile.c_str());
  	jinitmodes       = const_cast< char* > (initmodes.c_str());
  	jrunstages       = const_cast< char* > (runstages.c_str()); 
  	jinitialfile     = const_cast< char* > (initialfile.c_str());
  	jeqchtinputdir   = const_cast< char* > (eqchtinputdir.c_str());
  	jspchtinputdir   = const_cast< char* > (spchtinputdir.c_str());
  	jtrchtinputdir   = const_cast< char* > (trchtinputdir.c_str());
  	jscchtinputdir   = const_cast< char* > (scchtinputdir.c_str());
  	jcalibrationdir  = const_cast< char* > (calibrationdir.c_str());

};

