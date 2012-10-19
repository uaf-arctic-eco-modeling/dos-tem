#ifndef REGIONER_H_
	#define REGIONER_H_

	//iutput

	#include "../input/RegionInputer.h"
	#include "../run/Controller.h"
    #include "../output/StatusOutputer.h"
	
	#include "RunCohort.h"

	#include <algorithm> // copy algorithm
	#include <iterator> // ostream_iterator
	#include <list>
	using namespace std;
	
	class Regioner {
		public:
			Regioner();
			~Regioner();
	
			void init(string& controlfile);
    		void run();

    		void createCohorList4Run();
    		list<int> runchtlist;

    		void createOutvarList(string & txtfile);

		private:

    		//Inptuer
   	    	Controller configin;
   	    	RegionInputer rin;
    		GridInputer gin;
    		CohortInputer cin;
    		RestartInputer resin;
    		SiteinInputer sitein;

     		//Outputer    
    		RestartOutputer resout;
    		RegnOutputer rout;
    		StatusOutputer errout;

    		int MAX_OREGN_YR;
    
    		//data
    		EnvData  ed;
    		BgcData  bd;
    		FirData  fd;
    		ModelData md;
    
    		RegionData rd;    
    		GridData gd;
    		CohortData cd;
    		
    		RestartData resod;
    		
    		RegnOutData regnod;
			
			//util
			Timer timer;

   			//
			Grid rgrid;
			RunCohort runcht;

	};

#endif /*REGIONER_H_*/
