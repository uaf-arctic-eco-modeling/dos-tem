#include "Controller.h"

Controller::Controller(){

};

Controller::~Controller(){

};

void Controller::ctrl4calirun(ModelData *md){
 
 	ifstream fctr;
 	fctr.open(controlfile.c_str(),ios::in );
 	bool isOpen = fctr.is_open();
    if ( !isOpen ) {
      	cout << "\nCannot open " << controlfile << " in controller\n" ;
      	exit( -1 );
    }

  	fctr >> md->outputdir;
  	fctr >> md->reginputdir;
  	fctr >> md->grdinputdir;
  	fctr >> md->eqchtinputdir;
  	md->spchtinputdir="";
  	md->trchtinputdir="";
  	md->initialfile="";
    md->calibrationdir=md->eqchtinputdir;
  	
    fctr >> md->runstages;
  	fctr >> md->initmodes;  
  	fctr >> md->casename;

  	fctr.close();
	
 	md->changeco2 =false;
 	md->changeclimate =false;
 	md->consoledebug=true;
};

void Controller::ctrl4siterun(ModelData *md){
 
 	ifstream fctr;
 	fctr.open(controlfile.c_str(),ios::in );
 	bool isOpen = fctr.is_open();
    if ( !isOpen ) {
      	cout << "\nCannot open " << controlfile << " in controller\n" ;
      	exit( -1 );
    }

	fctr >> md->outputdir;
  	fctr >> md->reginputdir;
  	fctr >> md->grdinputdir;
  	fctr >> md->eqchtinputdir;
  	fctr >> md->spchtinputdir;
  	fctr >> md->trchtinputdir;
  	fctr >> md->scchtinputdir;
  	fctr >> md->initialfile;
  	fctr >> md->calibrationdir;
  
  	fctr >> md->runstages;
  	fctr >> md->initmodes;  

	string climatename;
	string co2name;

   	fctr >> climatename;
	fctr >> co2name;

	fctr >> md->casename;

	if(climatename =="dynamic"){
	  	md->changeclimate =true;
	} else	{
		md->changeclimate =false;
	}

	if(co2name =="dynamic"){
	  	md->changeco2 =true;
	} else{
  	md->changeco2 =false;
	}

  	fctr.close();

 	md->consoledebug=true;

};

void Controller::ctrl4regnrun(ModelData *md){
 

 		ifstream fctr;
 		fctr.open(controlfile.c_str(),ios::in );
 
 		bool isOpen = fctr.is_open();
    	if ( !isOpen )  {
      		cout << "\nCannot open " << controlfile << " in controller\n" ;
      		exit( -1 );
    	}

  		fctr >> md->outputdir;
  		fctr >> md->reginputdir;
  		fctr >> md->grdinputdir;
  		fctr >> md->eqchtinputdir;
  		fctr >> md->spchtinputdir;
  		fctr >> md->trchtinputdir;
    		fctr >> md->scchtinputdir;
		fctr >> md->runchtfile;
  		fctr >> md->initialfile;
  		fctr >> md->runstages;
  		fctr >> md->initmodes;

  		string climatename;
  	   	string co2name;

  	   	fctr >> climatename;
  		fctr >> co2name;

  		fctr >> md->casename;

  	if(climatename =="dynamic"){
  	  	md->changeclimate =true;
  	} else	{
      	md->changeclimate =false;
  	}
 
 	if(co2name =="dynamic"){
  	  	md->changeco2 =true;
  	} else{
      	md->changeco2 =false;
  	}

 	md->consoledebug=true;

 	fctr.close();
 
};

//BELOW is for java interface
void Controller::setControlfile (char* jcontrolfile){
  	controlfile =string(jcontrolfile);
};

