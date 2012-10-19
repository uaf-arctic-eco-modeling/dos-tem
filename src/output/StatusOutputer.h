/*! this class is used to output the state in the netcdf format
 */
#ifndef STATUSOUTPUTER_H_
	#define STATUSOUTPUTER_H_
	
    #include <netcdfcpp.h>
    #include <ncvalues.h>

	#include <iostream>
	#include <string>
	#include <sstream>
	#include <ctime>
	#include <cstdlib>
	
	using namespace std;
	using std::string;
 
	#include "../inc/timeconst.h"

	class StatusOutputer {
		public :
			StatusOutputer();
			void init(string& dir, const int & myid, string& stage);
			~StatusOutputer();

			NcFile* statusFile;
	 
			void  outputVariables(const int & chtcount);

    		bool runeq;
    		bool runsp;
    		bool runtr;
    
    		int chtid;
    		int errorid;
     
   	private:
   			NcDim * chtD;
			NcVar* chtidV;
			NcVar* erroridV;  	
	};

#endif /*STATUSOUTPUTER_H_*/
