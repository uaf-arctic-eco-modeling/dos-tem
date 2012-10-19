#include "FileChecking.h"

FileChecking::FileChecking(){
	
};

FileChecking::~FileChecking(){
	
};

bool FileChecking::FileExists(string& filename) {
 	struct stat stFileInfo;
  	bool blnReturn;
  	int intStat;

  	intStat = stat(filename.c_str(),&stFileInfo);
  	if(intStat == 0) {
    	blnReturn = true;
  	} else {
    	blnReturn = false;
  	}
  
  	return(blnReturn);
};

