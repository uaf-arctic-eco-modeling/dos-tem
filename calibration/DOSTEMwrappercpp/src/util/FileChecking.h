#ifndef FILECHECKING_H_
	#define FILECHECKING_H_

	#include <sys/stat.h>
	#include <string>
    using namespace std;
	
	class FileChecking {
		public:
			FileChecking();
			~FileChecking();
	
    		bool FileExists(string &filename);
    		

	};

#endif /*FILECHECKING_H_*/
