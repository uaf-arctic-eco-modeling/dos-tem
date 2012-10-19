#ifndef RESTARTOUTPUTER_H_
#define RESTARTOUTPUTER_H_

/*! this class is used to output the state in the netcdf format

 */

#include <netcdfcpp.h>
#include <ncvalues.h>

#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;
#include <string>
using std::string;

#include "../inc/layerconst.h"
#include "../inc/timeconst.h"
#include "../data/RestartData.h"

class RestartOutputer {
	public :
		RestartOutputer();
		~RestartOutputer();

		void init(string& dir, string& stage, const int& numproc, const int & myid);
		int errorChecking();

		void defineRestartDimensions();
		void defineRestartVariables();
		void outputVariables(const int & chtcount);
		void setRestartOutData(RestartData * resodp);

		RestartData * resod;

		string restartfname;

	private:

		NcFile* restartFile;
	   
   		NcDim * chtD;
   		NcDim * snowlayerD;
   		NcDim * soillayerD;
   		NcDim * rocklayerD;
   		NcDim * frontD;
   		NcDim * minlayerD ;
   		NcDim * monD ;
   		NcDim * meanyearD ;
	
	
   		NcVar* chtidV;
   		NcVar* errcodeV;

   		NcVar* permaV;
   		NcVar* TSsnowV;
   		NcVar* DZsnowV;
   		NcVar* LIQsnowV;
   		NcVar* ICEsnowV;
   		NcVar* RHOsnowV;
	

   		NcVar* AGEsnowV;
	
   		NcVar* TSsoilV;
   		NcVar* DZsoilV;
   		NcVar* LIQsoilV;
   		NcVar* ICEsoilV;
   		NcVar* FROZENsoilV;
   		NcVar* NONCsoilV;
   		NcVar* REACsoilV;

   		NcVar* TYPEsoilV;
	
   		NcVar* TYPEminV;
	
   		NcVar* TSrockV;
   		NcVar* DZrockV;
	
   		NcVar* frontZV;
   		NcVar* frontFTV;
	
   		NcVar* solnV;
   		NcVar* avlnV;
   		NcVar* wdebrisV;
	
	
   		NcVar* strnV;
   		NcVar* stonV;
   		NcVar* vegcV;
   		NcVar* deadcV;
   		NcVar* deadnV;
	
   		NcVar* prveetmxV;
   		NcVar* prvpetmxV;
   		NcVar* foliagemxV;
	
		NcVar* laiV;
	
		NcVar* unnormleafV;
		NcVar* prvunnormleafmxV;
		NcVar* prvtoptV;
	
		NcVar* toptAV;
		NcVar* eetmxAV;
		NcVar* petmxAV;
		NcVar* unnormleafmxAV;
	 
		NcVar* c2nV;
		NcVar* kdfibV;
		NcVar* kdhumV;
		NcVar* kdminV;
		NcVar* kdslowV;
	
		NcVar* ysfV;
		NcVar* burnednV;
		
};


#endif /*RESTARTOUTPUTER_H_*/
