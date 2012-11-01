#ifndef CONTROLLER_H_
	#define CONTROLLER_H_
	#include <cstdlib>
	#include <string>
	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <list> // list class-template definition

	using namespace std;

	#include "../util/Exception.h"

	#include "ModelData.h"

	class Controller {
 		public:
 
    		Controller();
    		~Controller();
    		
    		string controlfile;
  			void ctrl4calirun(ModelData *md);
  			void ctrl4siterun(ModelData *md);
   			void ctrl4regnrun(ModelData *md);
 			
 			//this is for java interface
  			void setControlfile(char* jcontrolfile);
 				
	};

#endif /*CONTROLLER_H_*/
