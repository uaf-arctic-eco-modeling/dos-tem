package runTEM;
/*
 * runcohort.java
 * 
 * The java version of RunCohort.cpp
 * 
 * cohort initialization, run, and output
 * 		Note: the output modules are put here, so can be flexible for outputs
 * 
*/

//java definition/method for data, inputers and outputers
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

import DATA.ConstTime;
import DATA.DataCohort;
import DATA.DataRestart;
import DATA.DataSitein;

import INPUT.CohortInputer;
import INPUT.FireInputer;
import INPUT.RestartInputer;
import INPUT.SiteinInputer;
import INPUT.CCohortDriver;

import GUI.PlotterUpdate;

//model entities (for one cohort)
import TEMJNI.Cohort;

//cohort-level model parameters for data exchange
import TEMJNI.vegpar_cal;
import TEMJNI.soipar_cal;
import TEMJNI.vegpar_bgc;
import TEMJNI.soipar_bgc;

//for initial states to be modified
import TEMJNI.SiteIn;

public class runcohort {
	
	//java inputers for cohort-level data
	public CohortInputer cinputer = new CohortInputer();
	public RestartInputer resinputer = new RestartInputer();
	public FireInputer finputer = new FireInputer();
	public SiteinInputer sinputer = new SiteinInputer();
	
	public CCohortDriver ccdriver = new CCohortDriver();
	
	//java outputers for cohort-level variables
	public runoutputs outmodes = new runoutputs();
	
	//java data definition (cohort-level)
	DataCohort jCd = new DataCohort();        // for c++ data: cd
	DataRestart jResid = new DataRestart();   // for c++ data: resid
	DataSitein jSitein = new DataSitein();    // for c++ data: Sitein
	
    //model entity - cohort
	public int cohortcount = 0;
	public Cohort cht = new Cohort();	

	//controling option for read-in calibrated parameters
 	public boolean califilein; //
 	public String califile;
 	public boolean inicali;    //use the initial C conditions in califile or not, if califile reading
 	
 	//caliration driver in/out options
 	public boolean usecalirestart; // for equlibrium-run only
 	public boolean outcalirestart; // for equlibrium-run only
 	public String ccdfile;
 	
 	public boolean assigneq;
 	public boolean useeq;

 	//calibration parameters, used to convey java-input to c++ holders
 	public vegpar_cal vbcalpar = new vegpar_cal();
 	public soipar_cal sbcalpar = new soipar_cal();

 	public vegpar_bgc vbpar = new vegpar_bgc();
 	public soipar_bgc sbpar = new soipar_bgc();

 	//initial states to be modified
 	public SiteIn initstate = new SiteIn();
 	
 	//real-time plotting for GUI
	public boolean GUIgraphic;
 	public PlotterUpdate plotting = new PlotterUpdate();

 	///////////////////////////////////////////////////////////////////////////////////////
	
	// Model Running process operations for using GUI
//	private boolean m_stop = true;
//	private Thread m_thread;
		
///////////////////////////////////////////////////////////////////////////////////////
    
 	//(eq/res)cid are record order in .nc files
    public int chtreinit(int cid, int eqcid, int rescid){

    	// initial module-calling controls, can be updated later on if NEEDED     
		cht.setFailed(false);
    	cht.setErrorid(0);
     	  	        	
    	//data from cohort input files: eq/vegetation.nc, drainage.nc, and sp,tr/fire.nc
    	try {
    		
    		jCd.vegtype=cinputer.getVegetation(eqcid);
    		cht.getCd().setVegtype(jCd.vegtype);

    		jCd.drgtype=cinputer.getDrainage(eqcid);
    		cht.getCd().setDrgtype(jCd.drgtype);
	
    		if(cht.getMd().getRuntr()){
     			
    			finputer.getTransientFireYear(jCd.trfireyear, cid);
    			cht.getCd().setTrfireyear(jCd.trfireyear);
    			finputer.getTransientFireSeason(jCd.trfireseason, cid);
    			cht.getCd().setTrseason(jCd.trfireseason);
			
    			if (cht.getFd().getUseseverity()){
        			finputer.getTransientSeverity(jCd.trseverity, cid);
    				cht.getCd().setTrseverity(jCd.trseverity);
    			}
    		}

    		if(cht.getMd().getRunsp()){
    			
    			finputer.getSpinupFireYear(jCd.spfireyear, cid);
    			cht.getCd().setSpfireyear(jCd.spfireyear);
    			finputer.getSpinupFireSeason(jCd.spfireseason, cid);
    			cht.getCd().setSpseason(jCd.spfireseason);
			
    			if (cht.getFd().getUseseverity()){
        			finputer.getSpinupSeverity(jCd.spseverity, cid);
    				cht.getCd().setSpseverity(jCd.spseverity);
    			}
    		}
    	} catch (Exception e) {
    	    return -1;
    	}
    	
    	//fire driving data
   		cht.fireDrivingData(cht.getMd().getRunsp(), cht.getMd().getRuntr(), cht.getMd().getRunsc());
	 
		//initial modes other than lookup (by which, initmode = 1)
		if (cht.getMd().getInitmode()==2) {
			//NOTE: the ids in sitein.nc must be exactly ordered as in eq/sp/tr cohort ids
			sinputer.getSiteinData(jSitein, cid, cht.getMd().getJinitialfile()); 
		
			cht.getSitein().setYsf(jSitein.ysf); 

			cht.getSitein().setLai(jSitein.lai); 
			cht.getSitein().setVegc(jSitein.vegc); 
			cht.getSitein().setVegn(jSitein.vegn); 

			cht.getSitein().setMossthick(jSitein.mossthick); 
			cht.getSitein().setFibthick(jSitein.fibthick); 
			cht.getSitein().setHumthick(jSitein.humthick); 
			cht.getSitein().setSoilc(jSitein.soilc); 
			cht.getSitein().setFibc(jSitein.fibc); 
			cht.getSitein().setHumc(jSitein.humc); 
			cht.getSitein().setOrgn(jSitein.orgn); 
			cht.getSitein().setAvln(jSitein.avln); 

			cht.getSitein().setMintype(jSitein.mintype);
			cht.getSitein().setInitz(jSitein.initz); 
			cht.getSitein().setInitst(jSitein.initst); 
			cht.getSitein().setInitsm(jSitein.initsm); 

		} else if (cht.getMd().getInitmode()==3) {
			
			resinputer.getResin(jResid, rescid);
			if (jResid.errcode!=0) return -2;
			
			cht.getResid().setDZsnow(jResid.DZsnow);
			cht.getResid().setTSsnow(jResid.TSsnow);
			cht.getResid().setICEsnow(jResid.DZsnow);
			cht.getResid().setAGEsnow(jResid.DZsnow);
			cht.getResid().setRHOsnow(jResid.DZsnow);
		 
			cht.getResid().setTYPEsoil(jResid.TYPEsoil);
			cht.getResid().setFROZENsoil(jResid.FROZENsoil);
			cht.getResid().setDZsoil(jResid.DZsoil);
			cht.getResid().setTSsoil(jResid.TSsoil);
			cht.getResid().setLIQsoil(jResid.LIQsoil);
			cht.getResid().setICEsoil(jResid.ICEsoil);
			cht.getResid().setNONCsoil(jResid.NONCsoil);
			cht.getResid().setREACsoil(jResid.REACsoil);

			cht.getResid().setTYPEmin(jResid.TYPEmin);
			cht.getResid().setDZrock(jResid.DZrock);
			cht.getResid().setTSrock(jResid.TSrock);
			cht.getResid().setFrontZ(jResid.frontZ);
			cht.getResid().setFrontFT(jResid.frontFT);

			cht.getResid().setVegc(jResid.vegc);
			cht.getResid().setDeadc(jResid.deadc);
			cht.getResid().setWdebris(jResid.wdebris);
			cht.getResid().setStrn(jResid.strn);
			cht.getResid().setSton(jResid.ston);
			cht.getResid().setDeadn(jResid.deadn);
			cht.getResid().setC2n(jResid.c2n);
			cht.getResid().setSoln(jResid.soln);
			cht.getResid().setAvln(jResid.avln);

			cht.getResid().setLai(jResid.lai);
			cht.getResid().setFoliagemx(jResid.foliagemx);
			cht.getResid().setUnnormleaf(jResid.unnormleaf);
			cht.getResid().setPrvunnormleafmx(jResid.prvunnormleafmx);
			cht.getResid().setPrveetmx(jResid.prveetmx);
			cht.getResid().setPrvpetmx(jResid.prvpetmx);
			cht.getResid().setPrvtopt(jResid.prvtopt);

			cht.getResid().setKdfib(jResid.kdfib);
			cht.getResid().setKdhum(jResid.kdfib);
			cht.getResid().setKdmin(jResid.kdmin);
			cht.getResid().setKdslow(jResid.kdslow);
		 
			cht.getResid().setYsf(jResid.ysf);
			cht.getResid().setBurnedn(jResid.burnedn);
		 
			cht.getResid().setToptA(jResid.toptA);
			cht.getResid().setEetmxA(jResid.eetmxA);
			cht.getResid().setPetmxA(jResid.petmxA);
			cht.getResid().setUnnormleafmxA(jResid.unnormleafmxA);

		}

		//the following For Calibration run ONLY, be sure that was set correctly in options.
		// read calibration cohort driving data from java if switched on
//	 	if (usecalirestart) {
//	 		setEqSoilClimate();
//	 	}

	 	//reset other initial state variables, 
	 	// basically will transfer the initial data above to model's relvant modules
	 	cht.reset();
	 	
		// reading calibrated parameters, if switched on
	 	// have to be done after .reset
    	if(califilein){
   			if (califile.compareToIgnoreCase("")==0 || califile==null) {
   				califile = cht.getMd().getJcalibrationdir()+"Jcalinput"
    			          +Integer.toString(cht.getCd().getVegtype())
    			          +Integer.toString(cht.getCd().getDrgtype())+".txt";
   			} else {
   				califile = cht.getMd().getJcalibrationdir()+califile; 				
   			}
    		System.out.println("calibrated parameters reading from:"+califile+"\n");
    		setCalPar(califile, inicali);
    	}

    	//for java info display
	 	cht.getBgcPar(vbpar, sbpar);
	 	cht.getCalPar(vbcalpar, sbcalpar);
	 	cht.getSiteStates(initstate);
    		 	
    	//default modules/process switches
	 	useeq    = false;
	 	assigneq = false;
    	
	 	cht.setEquiled(false); 
    	cht.setSpined(false); 
    	cht.setTransed(false); 
    	if (cht.getMd().getRunsp()) {
    		cht.setEquiled(true);
    	}
    	if (cht.getMd().getRuntr()) {
    		 cht.setEquiled(true);
    		 cht.setSpined(true);
    	}
    	 	 
   		cht.getBd().setBaseline(1);
   		cht.getBd().setNfeed(1);
   		cht.getBd().setAvlnflg(1);

   		cht.setDsbmodule(true);
   		cht.setEnvmodule(true);
  		cht.setEcomodule(true);
   		cht.setDslmodule(true);
     	 	
	    cht.setVeupdateLAI5Vegc(true); 
    	if (cht.getMd().getRuneq()) {
    	    cht.setVeupdateLAI5Vegc(false); 
    	}
        	    		 
 		cht.setFriderived(true);
  
    	//output options
   	 	cht.setOutSiteDay(false);
   	 	cht.setOutSiteMonth(false);
   	 	cht.setOutSiteYear(false);
   	 	cht.setOutRegn(false);
   	 	cht.setOutSoilClm(false);
   	 	if (outmodes.ODAY) cht.setOutSiteDay(true);
   	 	if (outmodes.OMONTH) cht.setOutSiteMonth(true);
   	 	if (outmodes.OYEAR) cht.setOutSiteYear(true);
   	 	if (outmodes.OREGNER) cht.setOutRegn(true);
   	 	if (outmodes.OSCLM) cht.setOutSoilClm(true);

   	 	cht.setOutputSpinup(false); 
   	 	if (cht.getMd().getRunsp() && cht.getMd().getRuntr()) 
   	 		cht.setOutputSpinup(true);
   	 	
   	 	return 0;
     };

   //-----------------------------------------------------------------------------
   //TEM equlibrium run	
   	public int runeq(){					

   		useeq = false;
		assigneq = false;
	 	
		cht.getBd().setBaseline(1);
		cht.getBd().setNfeed(0);
		cht.getBd().setAvlnflg(0);  		 
		
		cht.setEnvmodule(true);
		cht.setEcomodule(false);					
	 	cht.setDsbmodule(false);
 		cht.setDslmodule(false);

  		cht.setFriderived(false);
	 	cht.getFd().setYsf(1000);   //this is critical to get correct mossthick

  		int maxenvyr = 500;
		for (int iyr=0; iyr<maxenvyr; iyr++) {
   			System.out.println("TEM ENV-MODULE ONLY RUN: year "+iyr);
			if (iyr==maxenvyr-1) assigneq = true;  			
   			for (int im=0; im<12;im++){
   				int dinmcurr = ConstTime.dinm[im]; 
   				cht.updateMonthly(iyr, iyr, im, dinmcurr, assigneq, useeq);
   				cht.getTimer().advanceOneMonth();

   			}
		}

		//ENV-MODULE ONLY RUN
		useeq = true;
		assigneq = false;
		cht.getBd().setNfeed(1);
		cht.getBd().setAvlnflg(1);  		 
		cht.setEnvmodule(false);
		cht.setEcomodule(true);					
		cht.setDslmodule(false);
		cht.setDsbmodule(false);

   		int outputyrind = 0;
   		
		for (int iyr=0; iyr<5000; iyr++) { //ConstTime.MAX_EQ_YR){ 
			System.out.println("TEM ECO-MODULE ONLY RUN: year "+iyr);

			int ycnt = iyr;
   			for (int im=0; im<12;im++){
   				int dinmcurr = ConstTime.dinm[im]; 
   				cht.updateMonthly(outputyrind, ycnt, im, dinmcurr, assigneq, useeq);

   				//output to files for one cohort (monthly or yearly)
				if(outmodes.OSITER) outmodes.siteoutput(outputyrind, im);

				cht.getTimer().advanceOneMonth();

   			}
   			   			
 			//if eq reached
  			cht.testEquilibrium(); 
  			if (cht.getEquiled()) break;
  			outputyrind++;
   				
   		}

		//restart.nc output by the end of run
		cht.getResod().setChtid(cht.getCd().getEqchtid());
		cht.updateRestartOutputBuffer(1);
		outmodes.resout.outputVariables(cohortcount);

		System.out.println("eq-run is done!");
				
		return 0;
   	 };

     public int onerun(){					
 		int runyrcnt = 0; 		
 		cht.getTimer().reset();
 		
 		boolean done = false;
 		int err= -1;
 		while (!done){	
     		 			
     		int yrind=cht.getTimer().getYearind();
     		if (cht.getMd().getRunsp()) yrind+=cht.getTimer().getSpinbegyr();  // Calendar yr
     		if (cht.getMd().getRuntr()) yrind+=cht.getTimer().getTrsbegyr();   // Calendar yr

     		if(cht.getMd().getConsoledebug())
     			System.out.println("TEM RUN: year "+yrind+"@"+cht.getMd().getJrunstages());

 			int outputyrind= cht.timerOutputYearIndex(cht.getEquiled(),
                     cht.getSpined(), cht.getOutputSpinup());
 			 			
 			//if not Eq-run, when reaching the first-fire specified in sp/tr fire.nc, fire cycle NOT driven by FRI anymore
 			if (yrind>=cht.getFirstfireyr() && !cht.getMd().getRuneq()) cht.setFriderived(false);
 						
 			for (int im=0; im<12;im++){
 				int dinmcurr = ConstTime.dinm[im]; 
 				cht.updateMonthly(outputyrind, runyrcnt, im, dinmcurr, assigneq, useeq);

 				//output to files for one cohort (monthly or yearly)
 				if(outmodes.OSITER) outmodes.siteoutput(outputyrind, im);

 				// graphic display monthly
				if (GUIgraphic) {
					plotting.updateMlyBioGraph(runyrcnt, im, cht);
					plotting.updateMlyPhyGraph(runyrcnt, im, cht);
				}

 				cht.getTimer().advanceOneMonth();
				
 			}

 			//real-time output to plots yearly
			if (GUIgraphic) {
				plotting.updateYlyBioGraph(runyrcnt, cht);
				plotting.updateYlyPhyGraph(runyrcnt, cht);
			}
 						
 			//multiple-cohort yearly outputs
 			if (outmodes.OREGNER) {
 				outmodes.regnout.outputYearCohortVars(runyrcnt, cohortcount);
 			}
			 			
 			// end of running
 	    	if(cht.getMd().getRuneq() && (runyrcnt>10*cht.getFd().getGd().getFri()-2)) {	    				
 	    			System.out.println("Multi-Module Equilibrium running Stage is done!");

 	    			//restart.nc output all the time
 	    			cht.getResod().setChtid(cht.getCd().getEqchtid());
 	    			cht.updateRestartOutputBuffer(1);
 	    			outmodes.resout.outputVariables(cohortcount);
 	    			
 	     	    	cht.setEquiled(true); 
 	    			done= true;
 	    			err = 0;
 	    		
 			} else if(cht.getMd().getRunsp() && (runyrcnt>=ConstTime.MAX_SP_YR-1)){
     			System.out.println("Dynamical Spin-up Stage running is done!");
 	    		
 	    		//restart.nc output all the time
	    		cht.getResod().setChtid(cht.getCd().getSpchtid());
	    		cht.updateRestartOutputBuffer(2);
 				outmodes.resout.outputVariables(cohortcount);
 				
     			cht.setSpined(true);	
	   			done= true;
 	   			err = 0;
 			
 			}  else if(cht.getMd().getRuntr() && (runyrcnt>=ConstTime.MAX_TR_YR-1)){
     			System.out.println("Transit Stage running is done!");
 	    		
 	    		//restart.nc output all the time
	    		cht.getResod().setChtid(cht.getCd().getTrchtid());
	    		cht.updateRestartOutputBuffer(3);
 				outmodes.resout.outputVariables(cohortcount);

     	    	cht.setTransed(true); 
	   			done= true;
 	   			err = 0;
 			}
 	    	
 			runyrcnt++;

 		}
 		
	 	return err;

 	};

//////////////////////////////////////////////////////////////////////////////////////////
//The following are for controlling of model running process USING GUI
////////////////////////////////////////////////////////////////////////////////////////// 			
/*     int yrcnt = 0; 	 

     public void run(){					

		//GUI error message
		this.m_thread=Thread.currentThread();

		//thread status initialization
		this.m_stop = false;
				    
		while (!this.m_stop){	
    		if(cht.getMd().getConsoledebug())
    			System.out.println("TEM GUI RUN: year "+yrcnt);

			int outputyrind= cht.timerOutputYearIndex(cht.getEquiled(),
                    cht.getSpined(), cht.getOutputSpinup());
					
			for (int im=0; im<12;im++){
				int dinmcurr = ConstTime.dinm[im]; 
				cht.updateMonthly(outputyrind, yrcnt, im, dinmcurr, assigneq, useeq);

				//output to files for one cohort (monthly or yearly)
				if(outmodes.OSITER) outmodes.siteoutput(outputyrind, im);
				
				// graphic display monthly
				if (GUIgraphic) {
					plotting.updateMlyBioGraph(yrcnt, im, cht);
					plotting.updateMlyPhyGraph(yrcnt, im, cht);
				}

				cht.getTimer().advanceOneMonth();

			}
			
			//multiple-cohort yearly outputs
			if (outmodes.OREGNER) {
				outmodes.regnout.outputYearCohortVars(yrcnt, cht.getCohortcount());
			}

			//real-time output to plots yearly
			if (GUIgraphic) {
				plotting.updateYlyBioGraph(yrcnt, cht);
				plotting.updateYlyPhyGraph(yrcnt, cht);
			}

			yrcnt++;
			
			// thread control
			if (Thread.interrupted()) this.stop();
			if (yrcnt<1000) {
				if (yrcnt%100==0) {
					try {
						Thread.sleep(100);
						this.stop();
					} catch (InterruptedException e) {
						this.stop();
					}
				}
			} else {
				if (yrcnt%1000==0) {
					try {
						Thread.sleep(100);
						this.stop();
					} catch (InterruptedException e) {
						this.stop();
					}
				}
			}		
			
			// end of running
 	    	if(cht.getMd().getRuneq() && (yrcnt>=10*cht.getFd().getGd().getFri()-2)) {	    				
	    			System.out.println("Multi-Module Equilibrium running is done!");

	    			//restart.nc output all the time
	    			cht.updateRestartOutputBuffer(1);
	    			outmodes.resout.outputVariables(cht.getCohortcount());
	    			
	     	    	cht.setEquiled(true); 
	    			System.out.println("Equilibrium running is done!");

	    			//restart.nc output all the time
	    			cht.updateRestartOutputBuffer(1);
	    			outmodes.resout.outputVariables(cht.getCohortcount());
	    			
	    			return;
	    		
			} else if(cht.getMd().getRunsp() && (yrcnt>=ConstTime.MAX_SP_YR-1)){
    			System.out.println("Spin-up running is done!");
    			cht.setSpined(true);	
	    		
	    		//restart.nc output all the time
 				cht.updateRestartOutputBuffer(2);
				outmodes.resout.outputVariables(cht.getCohortcount());
				
				return;
			
			}  else if(cht.getMd().getRuntr() && (yrcnt>=ConstTime.MAX_TR_YR-1)){
    			System.out.println("Transit running is done!");
    	    	cht.setTransed(true); 
	    		
	    		//restart.nc output all the time
 				cht.updateRestartOutputBuffer(3);
				outmodes.resout.outputVariables(cht.getCohortcount());

				return;
			}
		}


	};

	public void start() {
		if (this.m_stop) {
			this.m_thread = new Thread(this);
			this.m_thread.start();
		}
	};

	public void stop() {
		this.m_stop = true;
	};

	public void reset() {
		if (!this.m_stop) this.m_stop = true;
		this.m_thread = new Thread(this);
		
		System.out.println("\n TEM RUN will be reset for a new Model Run ...");
		
	};
*/

////////////////////////////////////////////////////////////////////////////////////////
    void setCalPar(String califile, boolean init){
    	
    	File parF = new File(califile);
        
    	if(parF.exists()){
    		try {
    			BufferedReader input =  new BufferedReader(new FileReader(parF));
    			
    			String dummy="";
       		
    			dummy = input.readLine();
    			dummy = input.readLine();
    			    	  		
    			dummy = input.readLine();
    			initstate.setFibthick(Float.valueOf(dummy));
    			dummy = input.readLine();
    			initstate.setHumthick(Float.valueOf(dummy));   			
    			dummy = input.readLine();  //
    			initstate.setVegc(Float.valueOf(dummy));
    			dummy = input.readLine();  //
    			initstate.setVegn(Float.valueOf(dummy));
    			dummy = input.readLine();  //
    			initstate.setAvln(Float.valueOf(dummy));
    			dummy = input.readLine();  //
    			initstate.setOrgn(Float.valueOf(dummy));

    			if (init) cht.setSiteStates(initstate);   //use initials from califile

    			dummy = input.readLine();
    			vbcalpar.setCmax(Float.valueOf(dummy));
    			dummy = input.readLine();
    			vbcalpar.setNmax(Float.valueOf(dummy));
    			dummy = input.readLine();
    			vbcalpar.setKrb(Float.valueOf(dummy));
    			dummy = input.readLine();
    			sbcalpar.setNup(Float.valueOf(dummy));
    			dummy = input.readLine();
    			vbcalpar.setCfall(Float.valueOf(dummy));
    			dummy = input.readLine();
    			vbcalpar.setNfall(Float.valueOf(dummy));

    			dummy = input.readLine();
    			sbcalpar.setKdcfib(Float.valueOf(dummy));
    			dummy = input.readLine();
    			sbcalpar.setKdchum(Float.valueOf(dummy));
    			dummy = input.readLine();
    			sbcalpar.setKdcmin(Float.valueOf(dummy));
    			dummy = input.readLine();
    			sbcalpar.setKdcslow(Float.valueOf(dummy));
    			
    			cht.resetCalPar(vbcalpar, sbcalpar);
   			
    			input.close();
    		} catch (IOException e) {
        		System.err.println("Error in reading"+califile+e);
        	}   
			
    	} else {
    		System.err.println(califile+" NOT exists - built-in pars used!");
    	}
    };
    
	void getEqSoilClimate(){					
		//
		cht.getTimer().reset();
		
		cht.setEquiled(false);
		cht.setSpined(false);
		cht.setTransed(false); 
		cht.setOutputSpinup(false); 
     	 		 	
		//Turn Env-Module only on
		cht.setEnvmodule(true);
		cht.setEcomodule(false);
		cht.setDsbmodule(false);
		cht.setDslmodule(false);

		//reset calibration parameters
		cht.resetCalPar(vbcalpar, sbcalpar);

		boolean assigneq =false;		
		System.out.println("TEM Env-Module only RUN for calirestart.nc ... ");
		for (int iyr=0; iyr<100; iyr++) {

			if(iyr==99) assigneq =true;
			for (int im=0; im<12;im++){  
				int dinmcurr = ConstTime.dinm[im];
	   
				cht.updateMonthly(iyr, iyr, im, dinmcurr, assigneq, false);
				cht.getEd().d2tod1(); //this is for java output of ccdriver
				
				plotting.updateMlyPhyGraph(iyr, im, cht);

			}
			plotting.updateYlyPhyGraph(iyr, cht);
								
			//write the driver file: calirestart.nc
			ccdriver.createSoilClimate(
					cht.getEd(), 
					cht.getBd(), 
					cht, 
					ccdfile);
				
		}		
		
		System.out.println("Done!");

		Thread.currentThread().interrupt();
	};
	
    void setEqSoilClimate(){
		if (!ccdfile.isEmpty()) {
			ccdriver.updateDriver(ccdfile);  				
 		if(ccdriver.jCcd.eq_y_pet<ccdriver.jCcd.eq_y_eet ){
 			ccdriver.jCcd.eq_y_pet=ccdriver.jCcd.eq_y_eet;
 		}	
 		if(ccdriver.jCcd.eq_prvpetmx<ccdriver.jCcd.eq_prveetmx ){
 			ccdriver.jCcd.eq_prvpetmx=ccdriver.jCcd.eq_prveetmx;
 		}	
 		for(int im =0; im<12; im++){
 			if(ccdriver.jCcd.eq_pet[im]<ccdriver.jCcd.eq_eet[im] ){
 				ccdriver.jCcd.eq_pet[im]=ccdriver.jCcd.eq_eet[im] ;
 			}
 		}
	  	
 		//  assign calibration cohort driving data to c++ holders
 		cht.getEd().setEq_ts1d(ccdriver.jCcd.eq_ts);
 		cht.getEd().setEq_liq1d(ccdriver.jCcd.eq_liq);
 		cht.getEd().setEq_vwc1d(ccdriver.jCcd.eq_vwc);
 		cht.getEd().setEq_sws1d(ccdriver.jCcd.eq_sws);
 		cht.getEd().setEq_ice1d(ccdriver.jCcd.eq_ice);
 		cht.getEd().d1tod2();               //call to transfer 1D to 2D for the variables above
	  	
 		cht.getEd().setEq_ta(ccdriver.jCcd.eq_ta);
 		cht.getEd().setEq_co2(ccdriver.jCcd.eq_co2);
 		cht.getEd().setEq_eet(ccdriver.jCcd.eq_eet);
 		cht.getEd().setEq_pet(ccdriver.jCcd.eq_pet);
 		cht.getEd().setEq_par(ccdriver.jCcd.eq_par);
 		cht.getEd().setEq_y_eet(ccdriver.jCcd.eq_y_eet);
 		cht.getEd().setEq_y_pet(ccdriver.jCcd.eq_y_pet);
 		cht.getEd().setEq_y_co2(ccdriver.jCcd.eq_y_co2);
 		cht.getEd().setEq_prveetmx(ccdriver.jCcd.eq_prveetmx);
 		cht.getEd().setEq_prvpetmx(ccdriver.jCcd.eq_prvpetmx);
 		cht.getEd().setEq_grow(ccdriver.jCcd.eq_grow);
 
		} else {
    		System.err.println(ccdfile+" NOT exists!");
    	}
    };

}
