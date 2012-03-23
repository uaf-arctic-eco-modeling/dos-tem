#include "CCohortLookup.h"

CCohortLookup::CCohortLookup(){
	
};

CCohortLookup::~CCohortLookup(){
	
};

void CCohortLookup::init(string & inicalifile){
 	string targetfile =inicalifile;   //Yuan: modified according to Jinicali.txt
  
 	ifstream fctr;
 	fctr.open(targetfile.c_str(),ios::in );
 	bool isOpen = fctr.is_open();
    if ( !isOpen ) {
      	cout << "\nCannot open " << targetfile << "  \n" ;
      	exit( -1 );
    }

	int vegtypei, drgtypei;

	fctr >> vegtypei; 
  	fctr >> drgtypei; 
  	fctr >> fibthick[drgtypei][vegtypei];
  	fctr >> humthick[drgtypei][vegtypei]; 
  	//targetted/initial values of variables for calibration
  	fctr >> npp[drgtypei][vegtypei];
  	fctr >> gpp[drgtypei][vegtypei];
  	fctr >> nppsat[drgtypei][vegtypei];
  	fctr >> nuptake[drgtypei][vegtypei];
  	fctr >> vegC[drgtypei][vegtypei];
  	fctr >> vegN[drgtypei][vegtypei];
  	fctr >> soilC[drgtypei][vegtypei];
  	fctr >> fibsoilC[drgtypei][vegtypei];
  	fctr >> humsoilC[drgtypei][vegtypei];
  	fctr >> minesoilC[drgtypei][vegtypei];
  	fctr >> availN[drgtypei][vegtypei];
   	fctr >> soilN[drgtypei][vegtypei];
  	
   	//variables to be calibrated
   	string comma;
  	fctr >> ini_cmax[drgtypei][vegtypei]  >> comma >> order_cmax[drgtypei][vegtypei];
  	fctr >> ini_nmax[drgtypei][vegtypei]  >> comma >>  order_nmax[drgtypei][vegtypei];
  	fctr >> ini_krb[drgtypei][vegtypei]   >> comma >>  order_krb[drgtypei][vegtypei];
  	fctr >> ini_nup[drgtypei][vegtypei]   >> comma >>  order_nup[drgtypei][vegtypei];
  	fctr >> ini_cfall[drgtypei][vegtypei] >> comma >> order_cfall[drgtypei][vegtypei];
  	fctr >> ini_nfall[drgtypei][vegtypei] >> comma >> order_nfall[drgtypei][vegtypei];
  	fctr >> ini_kdcfib[drgtypei][vegtypei] >> comma >> order_kdcfib[drgtypei][vegtypei];
  	fctr >> ini_kdchum[drgtypei][vegtypei] >> comma >> order_kdchum[drgtypei][vegtypei];
  	fctr >> ini_kdcminfast[drgtypei][vegtypei] >> comma >> order_kdcminfast[drgtypei][vegtypei];
  	fctr >> ini_kdcminslow[drgtypei][vegtypei] >> comma >> order_kdcminslow[drgtypei][vegtypei];
  	                                                                      
 	fctr.close();
		
};
