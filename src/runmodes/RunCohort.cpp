/*
 * RunCohort.cpp
 * 
 * Cohort initialization, run, and output
 * 		Note: the output modules are put here, so can be flexible for outputs
 * 
*/

#include "RunCohort.h"

RunCohort::RunCohort(){
 	cohortcount = 0;
	jcalifilein = true;    // switch for reading calibrated parameters; can be reset outside
	ccdriverout = false;  // switch for output calirestart.nc; can be reset outside
}

void RunCohort::setGridInputer(GridInputer * gin){
  	ginputer= gin;
};

void RunCohort::setCohortInputer(CohortInputer * cin){
  	cinputer= cin;
};

void RunCohort::setRestartInputer(RestartInputer * resin){
  	resinputer= resin;
};

void RunCohort::setSiteinInputer(SiteinInputer * sin){
  	sinputer= sin;
};

//ONLY update Calibrated Pars ONLY
void RunCohort::setCalibrationParameters(CohortLookup* chtlu, string& jtxtfile){
	
	string califile = jtxtfile; 
 
 	ifstream fctr;
 	fctr.open(califile.c_str(),ios::in );
 	bool isOpen = fctr.is_open();
    if ( !isOpen ) {
      	cout << "\nCannot open " << califile << "  \n" ;
      	exit( -1 );
    }

 	int drgtypei;
 	int vegtypei; 
 	double dummy;

 	fctr >> vegtypei;  //cht.cd->vegtype ;  //Yuan: DON'T change them to mess up with input
 	fctr >> drgtypei;  //cht.cd->drgtype ;

	fctr >> dummy; //chtlu->fibthick[drgtypei][vegtypei];
	fctr >> dummy; //chtlu->humthick[drgtypei][vegtypei];
 	fctr >> dummy; //chtlu->initvegc[drgtypei][vegtypei];
 	fctr >> dummy;
 	//chtlu->initstrn[drgtypei][vegtypei] = dummy* 0.96 ;
 	//chtlu->initston[drgtypei][vegtypei] = dummy* 0.04 ;
 	fctr >> dummy; //chtlu->initavln[drgtypei][vegtypei];
 	fctr >> dummy; //chtlu->initsoln[drgtypei][vegtypei];

  	fctr >> chtlu->cmax[drgtypei][vegtypei];
    	fctr >> chtlu->nmax[drgtypei][vegtypei];
    	fctr >> chtlu->krb[drgtypei][vegtypei];
    	fctr >> chtlu->nup[drgtypei][vegtypei];  
  	fctr >> chtlu->cfall[drgtypei][vegtypei]; 
  	fctr >> chtlu->nfall[drgtypei][vegtypei]; 
	fctr >> chtlu->kdcfib[drgtypei][vegtypei];
	fctr >> chtlu->kdchum[drgtypei][vegtypei];
	fctr >> chtlu->kdcmin[drgtypei][vegtypei];
	fctr >> chtlu->kdcslow[drgtypei][vegtypei];
	
 	fctr.close();
};

//update Initial conditions from Jcalinput.txt ONLY
void RunCohort::setCalibrationInits(CohortLookup* chtlu, string& jtxtfile){

	string califile = jtxtfile;

 	ifstream fctr;
 	fctr.open(califile.c_str(),ios::in );
 	bool isOpen = fctr.is_open();
    if ( !isOpen ) {
      	cout << "\nCannot open " << califile << "  \n" ;
      	exit( -1 );
    }

 	int drgtypei;
 	int vegtypei;
 	double dummy;

 	fctr >> vegtypei;  //cht.cd->vegtype ;  //Yuan: DON'T change them to mess up with input
 	fctr >> drgtypei;  //cht.cd->drgtype ;

	fctr >> chtlu->fibthick[drgtypei][vegtypei];
	fctr >> chtlu->humthick[drgtypei][vegtypei];
 	fctr >> chtlu->initvegc[drgtypei][vegtypei];
 	fctr >> dummy;
 	chtlu->initstrn[drgtypei][vegtypei] = dummy* 0.96 ;
 	chtlu->initston[drgtypei][vegtypei] = dummy* 0.04 ;
 	fctr >> chtlu->initavln[drgtypei][vegtypei];
 	fctr >> chtlu->initsoln[drgtypei][vegtypei];

  	fctr >> dummy; //chtlu->cmax[drgtypei][vegtypei];
    	fctr >> dummy; //chtlu->nmax[drgtypei][vegtypei];
    	fctr >> dummy; //chtlu->krb[drgtypei][vegtypei];
    	fctr >> dummy; //chtlu->nup[drgtypei][vegtypei];
  	fctr >> dummy; //chtlu->cfall[drgtypei][vegtypei];
  	fctr >> dummy; //chtlu->nfall[drgtypei][vegtypei];
	fctr >> dummy; //chtlu->kdcfib[drgtypei][vegtypei];
	fctr >> dummy; //chtlu->kdchum[drgtypei][vegtypei];
	fctr >> dummy; //chtlu->kdcminfast[drgtypei][vegtypei];
	fctr >> dummy; //chtlu->kdcminslow[drgtypei][vegtypei];

 	fctr.close();

};

//when initializing a cohort, using its record ids RATHER THAN chtids
int RunCohort::reinit(const int &cid, const int &eqcid, const int &rescid){
    // initializing module-calling controls     

cout << "cid: " << cid << "\n";
cout << "eqcid: " << eqcid << "\n";
cout << "rescid: " << rescid << "\n";
	
	cht.equiled = false;
	cht.spined = false;
	cht.transed = false;
	 
	cht.failed  = false;
	cht.errorid = 0;
	     
	cht.envmodule = false;
	cht.ecomodule = false;
	cht.dslmodule = false;
	cht.dsbmodule = false;
    	
	int errcode = 0;	
	//common static data from input files 

    	if (eqcid<0) return -1;
 	cinputer->getVegetation(cht.cd->vegtype, eqcid);
	cinputer->getDrainage( cht.cd->drgtype, eqcid);
	if (cht.cd->vegtype<0 || cht.cd->vegtype>=MAX_VEG_TYPE) return -2;
	if (cht.cd->drgtype<0 || cht.cd->drgtype>=MAX_DRG_TYPE) return -3;
	
	if(cht.md->runsp){
	    if (cid<0) return -4;
		cinputer->getSpinupFire(cht.cd->spfiredate, cht.cd->spfiremonth, cht.cd->spfireyear, cht.cd->spfirearea,cid);
//		cinputer->getSpinupFireOccur(cht.cd->spfireyear,cid);
//	  	cinputer->getSpinupFireSeason(cht.cd->spseason,cid);
//	  	if(cht.fd->useseverity){
//	  		cinputer->getSpinupSeverity(cht.cd->spseverity,cid);
//	  	}
	}

	if(cht.md->runtr){
	    if (cid<0) return -5;
		cinputer->getTransientFire(cht.cd->trfiredate, cht.cd->trfiremonth, cht.cd->trfireyear, cht.cd->trfirearea,cid);
//		cinputer->getTransientFireOccur(cht.cd->trfireyear,cid);
//	  	cinputer->getTransientFireSeason(cht.cd->trseason,cid);
//	   	if(cht.fd->useseverity){
//	  		cinputer->getTransientSeverity(cht.cd->trseverity,cid);
//	  	}
	 }

	if(cht.md->runsc){
	    if (cid<0) return -5;
		cinputer->getScenarioFire(cht.cd->scfiredate, cht.cd->scfiremonth, cht.cd->scfireyear, cht.cd->scfirearea,cid);
	 }

	 // may update the calibrated pars from Jcalinput.txt file, which from calibration run
	 if (jcalifilein) {
		 svegtype.str("");  //clear-up before use
		 svegtype<<cht.cd->vegtype;   //convert vegtype to string
		 sdrgtype.str("");
		 sdrgtype<<cht.cd->drgtype;   //convert drgtype to string
		 jcalparfile = "config/Jcalinput"
                     +svegtype.str()+sdrgtype.str()+".txt";
			
		 setCalibrationParameters(&cht.chtlu, jcalparfile);
		 if (cht.md->consoledebug) {
			 cout<<"Cohort dependend parameters reading from: "+jcalparfile+"\n";
		 }
	 }
	 //fire driving data 
	 cht.fireDrivingData(cht.md->runeq, cht.md->runsp, cht.md->runtr, cht.md->runsc);
	 
	 //initial modes other than lookup (initmode = 1)
	 if (cht.md->initmode==2) {
		 //note: the cohort order in sitein.nc must be exactly same as eq/sp/tr cohort in cruid.nc/cohortid.nc
		 int err=0;
		 err=sinputer->getSiteinData(&cht.sitein, cid);
		 if (err!=0) return -6;
		 		 
	 } else if (cht.md->initmode == 3) {
		 if (rescid<0) return -7;
		 resinputer->getERRCODE(errcode, rescid);
		 if (errcode!=0) return -8;

		 resinputer->getPERMAFROST(cht.resid.perma, rescid);
//cout<<"cht.resid.perma: "<<cht.resid.perma<<"\n";		 	 
		 resinputer->getDZsnow(cht.resid.DZsnow, rescid);
//cout<<"cht.resid.DZsnow: "<<cht.resid.DZsnow<<"\n";		 	 
		 resinputer->getTSsnow(cht.resid.TSsnow, rescid);
//cout<<"cht.resid.TSsnow: "<< cht.resid.TSsnow <<"\n";		 	 
		 resinputer->getICEsnow(cht.resid.ICEsnow, rescid);
//cout<<"cht.resid.ICEsnow: "<< cht.resid.ICEsnow <<"\n";		 	 
		 resinputer->getICEsnow(cht.resid.LIQsnow, rescid);
//cout<<"cht.resid.LIQsnow: "<< cht.resid.LIQsnow <<"\n";		 	 
		 resinputer->getAGEsnow(cht.resid.AGEsnow, rescid);
//cout<<"cht.resid.AGEsnow: "<< cht.resid.AGEsnow <<"\n";		 	 
		 resinputer->getRHOsnow(cht.resid.RHOsnow, rescid);
//cout<<"cht.resid.RHOsnow: "<< cht.resid.RHOsnow <<"\n";		 	 
		 
		 resinputer->getTSsoil(cht.resid.TSsoil, rescid);
//cout<<"cht.resid.TSsoil: "<< cht.resid.TSsoil <<"\n";		 	 
		 resinputer->getDZsoil(cht.resid.DZsoil, rescid);
//cout<<"cht.resid.DZsoil: "<< cht.resid.DZsoil <<"\n";		 	 
		 resinputer->getLIQsoil(cht.resid.LIQsoil, rescid);
//cout<<"cht.resid.LIQsoil: "<< cht.resid.LIQsoil <<"\n";		 	 
		 resinputer->getICEsoil(cht.resid.ICEsoil, rescid);
//cout<<"cht.resid.ICEsoil: "<< cht.resid.ICEsoil <<"\n";		 	 
		 resinputer->getFROZENsoil(cht.resid.FROZENsoil, rescid);
//cout<<"cht.resid.FROZENsoil: "<< cht.resid.FROZENsoil <<"\n";		 	 
		 resinputer->getNONC(cht.resid.NONCsoil, rescid);
//cout<<"cht.resid.NONCsoil: "<< cht.resid.NONCsoil <<"\n";		 	 
		 resinputer->getREAC(cht.resid.REACsoil, rescid);
//cout<<"cht.resid.REACsoil: "<< cht.resid.REACsoil <<"\n";		 	 
		 resinputer->getTYPEsoil(cht.resid.TYPEsoil, rescid);
//cout<<"cht.resid.TYPEsoil: "<< cht.resid.TYPEsoil <<"\n";		 	 
		 resinputer->getCLAYmin(cht.resid.CLAYmin, rescid);
cout<<"cht.resid.CLAYmin: "<< cht.resid.CLAYmin <<"\n";		 	 
		 resinputer->getSANDmin(cht.resid.SANDmin, rescid);
cout<<"cht.resid.SANDmin: "<< cht.resid.SANDmin <<"\n";		 	 
		 resinputer->getSILTmin(cht.resid.SILTmin, rescid);
cout<<"cht.resid.SILTmin: "<< cht.resid.SILTmin <<"\n";		 	 

		 resinputer->getDZrock(cht.resid.DZrock, rescid);
//cout<<"cht.resid.DZrock: "<< cht.resid.DZrock <<"\n";		 	 
		 resinputer->getTSrock(cht.resid.TSrock, rescid);
//cout<<"cht.resid.TSrock: "<< cht.resid.TSrock <<"\n";		 	 
		 resinputer->getFrontZ(cht.resid.frontZ, rescid);
//cout<<"cht.resid.frontZ: "<< cht.resid.frontZ <<"\n";		 	 
		 resinputer->getFrontFT(cht.resid.frontFT, rescid);
//cout<<"cht.resid.frontFT: "<< cht.resid.frontFT <<"\n";		 	 

		 resinputer->getSOLN(cht.resid.soln, rescid);
//cout<<"cht.resid.soln: "<< cht.resid.soln <<"\n";		 	 
		 resinputer->getAVLN(cht.resid.avln, rescid);
//cout<<"cht.resid.avln: "<< cht.resid.avln <<"\n";		 	 
		 resinputer->getWDEBRIS(cht.resid.wdebris, rescid);
//cout<<"cht.resid.wdebris: "<< cht.resid.wdebris <<"\n";		 	 
		 resinputer->getSTRN(cht.resid.strn, rescid);
//cout<<"cht.resid.strn: "<< cht.resid.strn <<"\n";		 	 
		 resinputer->getSTON(cht.resid.ston, rescid);
//cout<<"cht.resid.ston: "<< cht.resid.ston <<"\n";		 	 
		 resinputer->getVEGC(cht.resid.vegc, rescid);
//cout<<"cht.resid.vegc: "<< cht.resid.vegc <<"\n";		 	 
		 resinputer->getDEADC(cht.resid.deadc, rescid);
//cout<<"cht.resid.deadc: "<< cht.resid.deadc <<"\n";		 	 
		 resinputer->getDEADN(cht.resid.deadn, rescid);
//cout<<"cht.resid.deadn: "<< cht.resid.deadn <<"\n";		 	 
		 
		 resinputer->getPRVEETMX(cht.resid.prveetmx, rescid);
//cout<<"cht.resid.prveetmx: "<< cht.resid.prveetmx <<"\n";		 	 
		 resinputer->getPRVPETMX(cht.resid.prvpetmx, rescid);
//cout<<"cht.resid.prvpetmx: "<< cht.resid.prvpetmx <<"\n";		 	 
		 resinputer->getFOLIAGEMX(cht.resid.foliagemx, rescid);
//cout<<"cht.resid.foliagemx: "<< cht.resid.foliagemx <<"\n";		 	 

		 resinputer->getLAI(cht.resid.lai, rescid);
//cout<<"cht.resid.lai: "<<  cht.resid.lai <<"\n";		 	 
		 resinputer->getUNNORMLEAF(cht.resid.unnormleaf, rescid);
//cout<<"cht.resid.unnormleaf: "<< cht.resid.unnormleaf <<"\n";		 	 
		 resinputer->getPRVUNNORMLEAFMX(cht.resid.prvunnormleafmx, rescid);
//cout<<"cht.resid.prvunnormleafmx: "<< cht.resid.prvunnormleafmx <<"\n";		 	 
		 resinputer->getPRVTOPT(cht.resid.prvtopt, rescid);
//cout<<"cht.resid.prvtopt: "<< cht.resid.prvtopt <<"\n";		 	 
		 resinputer->getC2N(cht.resid.c2n, rescid);
//cout<<"cht.resid.c2n: "<< cht.resid.c2n <<"\n";		 	 
		 
		 resinputer->getKDFIB(cht.resid.kdfib, rescid);
//cout<<"cht.resid.kdfib: "<< cht.resid.kdfib <<"\n";		 	 
		 resinputer->getKDHUM(cht.resid.kdhum, rescid);
//cout<<"cht.resid.kdhum: "<< cht.resid.kdhum <<"\n";		 	 
		 resinputer->getKDMIN(cht.resid.kdmin, rescid);
//cout<<"cht.resid.kdmin: "<< cht.resid.kdmin <<"\n";		 	 
		 resinputer->getKDSLOW(cht.resid.kdslow, rescid);
//cout<<"cht.resid.kdslow: "<< cht.resid.kdslow <<"\n";		 	 

//calpar.kdcfib; //resin->getKDFIB(bd->kdfib, ed->cd->reschtid);
//calpar.kdchum;  //resin->getKDHUM(bd->kdhum, ed->cd->reschtid);
//calpar.kdcmin;  //resin->getkdmin(bd->kdmin, ed->cd->reschtid);
//calpar.kdcslow;  //resin->getkdlitter(bd->kdlitter, ed->cd->reschtid);

		 
		 resinputer->getYSF(cht.resid.ysf, rescid);
//cout<<"cht.resid.ysf: "<< cht.resid.ysf <<"\n";		 	 
		 resinputer->getBURNEDN(cht.resid.burnedn, rescid);
//cout<<"cht.resid.burnedn: "<< cht.resid.burnedn <<"\n";		 	 

		 resinputer->getTOPTA(cht.resid.toptA, rescid);
//cout<<"cht.resid.toptA: "<< cht.resid.toptA <<"\n";		 	 
		 resinputer->getEETMXA(cht.resid.eetmxA, rescid);
//cout<<"cht.resid.eetmxA: "<< cht.resid.eetmxA <<"\n";		 	 
		 resinputer->getPETMXA(cht.resid.petmxA, rescid);
//cout<<"cht.resid.petmxA: "<< cht.resid.petmxA <<"\n";		 	 
		 resinputer->getUNNORMLEAFMXA(cht.resid.unnormleafmxA, rescid);
//cout<<"cht.resid.unnormleafmxA: "<< cht.resid.unnormleafmxA <<"\n";		 	 

	 }
	 //reset other initial state variables
	 errcode = cht.reset();
	 if (errcode != 0) return -9;
	 	 
	 //output options
     	cht.outputSpinup = false;
     	if (cht.md->runsp && cht.md->runtr) cht.outputSpinup = true;

	cht.outSoilClm   = OSOILCLM;
	 
     if (SITEMODE) {
		 cht.outRegn=false;
		 if (OYEAR) cht.outSiteYear=true;
		 if (OMONTH) cht.outSiteMonth=true;
		 #ifdef ODAY
		 	cht.outSiteDay=true;
		 #endif
	 } else if (REGNMODE){
//		 if (cht.md->runeq || cht.md->runsp) {
		 if (cht.md->runeq) {
			 cht.outRegn=false;
		 } else {
			 cht.outRegn=true;
		 }
		 cht.outSiteYear=false;
		 cht.outSiteDay=false;
		 cht.outSiteMonth=false;
	 } else {
		 cht.outRegn=false;
		 cht.outSiteYear=false;
		 cht.outSiteDay=false;
		 cht.outSiteMonth=false;
	 }
  
     return 0;
};

int RunCohort::run(){

	int error = 0;
	try {
	
		if(cht.md->runeq){
    			error = runEquilibrium();
		    	if (error != 0) return error;
    			cht.updateRestartOutputBuffer(1);
		}
		
		if(cht.md->runsp){
    			error = runSpinup();
		    	if (error != 0) return error;
    			cht.updateRestartOutputBuffer(2);
		}
		
		if(cht.md->runtr){
			error = runTransit();
	 		if (error != 0) return error;
	 		cht.updateRestartOutputBuffer(3);
		}
/*			if (!cht.md->runsc) {
				error = runTransit();
	 		    	if (error != 0) return error;
	 		    	cht.updateRestartOutputBuffer(3);

			//Yuan: scenario run is exactly same as transient run, except for period
		    //  So, the climate/co2/fire data are put these two together
			} else {
				error = runScenario();
	 		    	if (error != 0) return error;
			}
		}
*/
		if(cht.md->runsc){
			error = runScenario();
	 		if (error != 0) return error;
	 		cht.updateRestartOutputBuffer(4);
		}


		//restart.nc always output
		resout->outputVariables(cohortcount);
	
  	} catch (Exception &exception){
  		cout <<"problem in run for cohort"<<cohortcount<<"\n";
  		cht.failed =true;
  		cht.errorid = exception.getErrorCode();
  		exception.mesg();
  	}

  	return 0;
	
}; 

int RunCohort::runEquilibrium(){

	int error = 0;

	cht.timer->reset();

	/*
	cht.bd->baseline=1;
    cht.bd->nfeed   =0;
	cht.bd->avlnflg =0;
 
	cht.equiled =false;
  	cht.spined  =false;
  	cht.transed =false;
     	 
//	int outputyrind= cht.timer->getOutputYearIndex(cht.equiled, cht.spined, cht.outputSpinup);
	
	//at first run TEM 500 years, with only env module is on
	 cht.envmodule =true;
         cht.ecomodule =false;
         cht.dsbmodule =false;
         cht.dslmodule= false;
         cht.veupdateLAI5Vegc =false;
   	 cht.friderived = false;
         cht.fd->ysf =1000;
         bool assigneq =false;
         bool useeq=false;
	 for (int iy=0; iy<500; iy++){
	   int yrcnt =iy;
	   if(iy==499)assigneq =true;
	   for (int im=0; im<12;im++){
	  
		   int currmind=  im;
		   int dinmcurr = cht.timer->getDaysInMonth(im);;
	   
		   cht.updateMonthly(iy, yrcnt, currmind, dinmcurr, assigneq, useeq);
	   }

	   if(cht.md->consoledebug) {
		   cout <<" ENV module ONLY run: year "<<iy <<" @cohort "<<cht.cd->eqchtid<<"\n";
	   }

	} 

	 //Then, use equilibrium environment to run eco module only
	 cht.envmodule =false;
     cht.ecomodule =true;
     cht.dsbmodule =false;
     cht.dslmodule =false;

     cht.bd->baseline=1;
     cht.bd->nfeed   =1;
	 cht.bd->avlnflg =1;
     useeq =true;
	 int outputyrind =0;
	 for (int iy=0; iy<MAX_EQ_YR; iy++){
	     cht.fd->ysf =1000;

	     int yrcnt =iy;
		 for (int im=0; im<12;im++){
	   		int currmind=  im;
	   		int dinmcurr = cht.timer->getDaysInMonth(im);;
	   		cht.updateMonthly(outputyrind, yrcnt, currmind, dinmcurr, false, useeq);

	   		if (SITEMODE) {
	   			siteoutput(outputyrind, currmind);
	   		}

	   		cht.timer->advanceOneMonth();
		 }

		 if (cht.outRegn){
			rout->outputYearCohortVars(outputyrind, cht.cohortcount);
		 }

  	   	cht.equiled = cht.testEquilibrium();

 		if(cht.md->consoledebug) {
 			cout <<" ECO module ONLY run: year "<<iy <<" @cohort "<<cht.cd->eqchtid<<"\n";
 		}
		if(cht.equiled )break;

		outputyrind++;
	}
*/
	 //Finally, run all modules for 20 fire-cycles (FRI) to prepare spin-up run (Yuan)
	cht.equiled   = true;

	cht.envmodule = true;
     	cht.ecomodule = true;
        cht.dslmodule = true;
       	cht.dsbmodule = true;
 
     	cht.bd->baseline =1;
     	cht.bd->nfeed    =1;
	cht.bd->avlnflg  =1;

  	 cht.friderived = true;    //When call DSB module (fire), using FRI to determine fire year
  	                  // and the fire season/size use the FIRST one in the gd.season[]/gd.size[]
  	 int outputyrind = 0;
  	 int nfri = min((int)(MAX_EQ_YR/cht.fd->gd->fri), 15);   //max. 10000+1FRI yrs or 10 FRI
	 for (int iy=0; iy<(nfri+1)*cht.fd->gd->fri-5; iy++){   //Yuan: -2 will make the final restart.nc not the fire year, but two years ago
//	 for (int iy=0; iy<MAX_EQ_YR; iy++){   //Yuan: -2 will make the final restart.nc not the fire year, but two years ago
		 int yrcnt =iy;
		 for (int im=0; im<12;im++){
	   		int currmind=  im;
	   		int dinmcurr = cht.timer->getDaysInMonth(im);
	   		error = cht.updateMonthly(outputyrind, yrcnt, currmind, dinmcurr, false, false);
			if (error != 0) return error;
	   		if (SITEMODE) {
	   			siteoutput(outputyrind, currmind);
	   		}
    		cht.updateRestartOutputBuffer(1);
	   		cht.timer->advanceOneMonth();
		 }

		if (cht.outRegn){
			rout->outputYearCohortVars(outputyrind, cohortcount);
		}

 		if(cht.md->consoledebug) {
 			cout <<"Equilibrium run: year "<<iy <<" @cohort "<<cht.cd->eqchtid<<"\n";
 		}

 		outputyrind++;
	}

	 return 0;

};

int RunCohort::runSpinup(){

	int error = 0;

	cht.timer->reset();

	cht.bd->baseline=1;
   	cht.bd->nfeed 	=1;	//
	cht.bd->avlnflg	=1;	//

	cht.envmodule =true;
    	cht.ecomodule =true;	//
	cht.dsbmodule =true;
    	cht.dslmodule =true;	//
	 
    	cht.veupdateLAI5Vegc =true;
	cht.equiled          =true;
    	cht.friderived       =true;  //Yuan: will change after reaching the first fire year

	 
	for(int iy=cht.timer->spinbegyr; iy<=cht.timer->spinendyr; iy++){
//		if (iy>=cht.firstfireyr) cht.friderived = false;    //prior to the first fire, model spin-up with fire occurrence at FRI
		if (iy>= BEG_SP_YR +1) cht.friderived = false;    //prior to the first fire, model runs with fire occurrence at FRI
//cout <<"friderived: "<<cht.friderived<<"\n";
	    	int outputyrind= cht.timer->getOutputYearIndex(cht.equiled, cht.spined , cht.outputSpinup);
	    	int yrcnt = cht.timer->getCurrentYearIndex();
	    	for(int im=0; im<12;im++){
	        	int currmind=  im;
	        	int dinmcurr = cht.timer->getDaysInMonth(im);;
	   		error = cht.updateMonthly(outputyrind, yrcnt, currmind, dinmcurr , false,false);
  	       		if (error != 0) return error;
	   		if (SITEMODE) {
	   			siteoutput(outputyrind, currmind);
	   		}
	   		cht.timer->advanceOneMonth();
	    	}
		if (cht.outRegn){
			rout->outputYearCohortVars(outputyrind, cohortcount);
		}
		if(cht.md->consoledebug){	
			cout <<"Spinup run: year " <<cht.timer->getCalendarYear(cht.equiled, cht.spined)-1
	    	     	<<" @cohort "<<cht.cd->spchtid<<"\n";
		}
	}
	
cht.spined =true;
return 0;
	 
};

int RunCohort::runTransit(){

	int error = 0;

	cht.timer->reset();

  	cht.dsbmodule =true; 
 	cht.envmodule =true;
   	cht.ecomodule =true;
   	cht.dslmodule =true;
   
	cht.bd->baseline =0;
	cht.bd->nfeed    =1;
	cht.bd->avlnflg  =1;

   	cht.equiled = true;
   	cht.spined  = true;
   	
   	cht.veupdateLAI5Vegc = true;
	cht.friderived       = true;

	for(int iy=cht.timer->trsbegyr; iy<=cht.timer->trsendyr; iy++){

//		if (iy>=cht.firstfireyr) cht.friderived = false;    //prior to the first fire, model runs with fire occurrence at FRI
		if (iy>= BEG_TR_YR +1) cht.friderived = false;    //prior to the first fire, model runs with fire occurrence at FRI

		int outputyrind= cht.timerOutputYearIndex
		                 (cht.equiled, cht.spined, cht.outputSpinup);

		int yrcnt = cht.timer->getCurrentYearIndex();
	    for(int im=0; im<12;im++){
	        int currmind=  im;
	        int dinmcurr = cht.timer->getDaysInMonth(im);

	        error = cht.updateMonthly(outputyrind, yrcnt, currmind, dinmcurr,false, false);
		    if (error != 0) return error;

	        if (SITEMODE){
	        	siteoutput(outputyrind, currmind);
	        }

	        cht.timer->advanceOneMonth();
	    }
	    
		if (cht.outRegn){
			rout->outputYearCohortVars(outputyrind, cohortcount);
		}

	    if(cht.md->consoledebug){
	    	cout <<"Transient run: year " 
	    	<<cht.timer->getCalendarYear(cht.equiled, cht.spined)-1
	    	<<" @cohort "<<cht.cd->trchtid<<"\n";
	    }
	}
	 
	cht.transed =true;	
	
	return 0;

};

int RunCohort::runScenario(){

	int error = 0;

	cht.timer->reset();

 	cht.dsbmodule =true;
 	cht.envmodule =true;
   	cht.ecomodule =true;
   	cht.dslmodule =true;

	cht.bd->baseline =0;
	cht.bd->nfeed    =1;
	cht.bd->avlnflg  =1;

   	cht.equiled = true;
   	cht.spined  = true;

   	cht.veupdateLAI5Vegc = true;
	cht.friderived       = true;

	for(int iy=cht.timer->scbegyr; iy<=cht.timer->scendyr; iy++){

//		if (iy>=cht.firstfireyr) cht.friderived = false;    //prior to the first fire, model runs with fire occurrence at FRI
		if (iy>= BEG_SC_YR +1) cht.friderived = false;    //prior to the first fire, model runs with fire occurrence at FRI


		int outputyrind= cht.timerOutputYearIndex(cht.equiled, cht.spined, cht.outputSpinup);

		int yrcnt = cht.timer->yearind;

	    for(int im=0; im<12;im++){
	        int currmind=  im;
	        int dinmcurr = cht.timer->getDaysInMonth(im);

	        error = cht.updateMonthly(outputyrind, yrcnt, currmind, dinmcurr,false, false);
		    if (error != 0) return error;

	        if (SITEMODE){
	        	siteoutput(outputyrind, currmind);
	        }

	        cht.timer->advanceOneMonth();
	    }

		if (cht.outRegn){
			rout->outputYearCohortVars(outputyrind, cohortcount);
		}

	    if(cht.md->consoledebug){
	    	cout <<"Scenario run: year "
	    	<<iy
	    	<<" @cohort "<<cht.cd->trchtid<<"\n";
	    }
	}

	cht.transed =true;

	return 0;
};

void RunCohort::siteoutput(const int & outputyrind, const int & currmind){

  	if(currmind==11){//end ofyear
  	
   		#ifdef ODAY	
  			if(cht.outSiteDay){
  				svegout->outputDayCohortVars(outputyrind);
  				ssslout->outputDayCohortVars(outputyrind);
  				satmout->outputDayGridVars(outputyrind);
  			}
  		#endif
  	
  		if(cht.outSiteMonth){
  			svegout->outputMonthCohortVars(outputyrind);
  			ssslout->outputMonthCohortVars(outputyrind);
  			satmout->outputMonthGridVars(outputyrind);
  		}
  	
  		if(cht.outSiteYear) {
  			svegout->outputYearCohortVars(outputyrind);
  			ssslout->outputYearCohortVars(outputyrind);
  			satmout->outputYearGridVars(outputyrind);
  		}
  	
  	}
  
};

void RunCohort::setOutputer(SiteOutputer *soutp, AtmosphereOutputer *satmoutp,
  				VegetationOutputer * svegoutp, SnowSoilOutputer * sssloutp){
    sout = soutp;
    satmout= satmoutp;
    svegout = svegoutp;
    ssslout = sssloutp; 
    	
    satmout->atmod = cht.atmod;
    svegout->vegod = cht.vegod;
    ssslout->sslod = cht.sslod; 	

};

void RunCohort::setRegionalOutputer(RegnOutputer* routp){
 	 rout = routp;
};

void RunCohort::setRestartOutputer(RestartOutputer * resoutp){
  	
	resout = resoutp;
  	
};
