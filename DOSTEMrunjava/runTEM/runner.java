package runTEM;
/* runner.java
 * 
 * I. The initialization for TEM runs
 * (1) general initialization
 * (2) configuration data
 * (3) input data reading
 * (4) data/method initialization
 * 
 * II. outputs
 * 
 * III. The region/grid-level data
 * 
 * IV. run model
 *  (1) get cohort IDs in the input data
 *  (2) pass data for one cohort
 *  (3) run model
 *  
 * V. interrupt model run
 */

//java definition/method for data, inputers and outputers

import DATA.DataRegion;
import DATA.DataGrid;
import DATA.ConstTime;

import INPUT.RegionInputer;
import INPUT.GridInputer;

import OUTPUT.SiteOutputer;
import OUTPUT.AtmosphereOutputer;
import OUTPUT.SnowSoilOutputer;
import OUTPUT.VegetationOutputer;
import OUTPUT.RegnOutputer;

//cpp wrappers
//(1)configuration for TEM
import TEMJNI.Controller;
import TEMJNI.Timer;
import TEMJNI.ModelData;
//(2)data definition (for one cohort)
import TEMJNI.RegionData;
import TEMJNI.GridData;
import TEMJNI.EnvData;
import TEMJNI.BgcData;
import TEMJNI.FirData;
import TEMJNI.CohortData;
import TEMJNI.RestartData;
//(3)model entities
import TEMJNI.Grid;   //cohort is included in .runcohort
//(4) output data definition (for one cohort)
import TEMJNI.AtmOutData;   //for siter-run
import TEMJNI.VegOutData;   //for siter-run
import TEMJNI.SnowSoilOutData;   //for siter-run
import TEMJNI.RegnOutData;  //for regioner-run (i.e., multiple sites)

public class runner {
	//cpp configuration for model run
	public String controlfile;   //so then can be input outside
	Controller configin = new Controller();
	public ModelData md = new ModelData();

	//java inputers
	RegionInputer rinputer = new RegionInputer();
	GridInputer ginputer = new GridInputer();
	
	//java data definition from inputers: note-'in' is added to the names of cpp data definition
	DataRegion jRd = new DataRegion();
	DataGrid jGd = new DataGrid();
	
	//cpp data definition:
	public RegionData rd = new RegionData();
	public GridData gd = new GridData();
	public CohortData cd = new CohortData();
	
	EnvData ed = new EnvData();
	BgcData bd = new BgcData();
	FirData fd = new FirData();
	
	//java outputers
	SiteOutputer souter = new SiteOutputer();
	AtmosphereOutputer atmouter = new AtmosphereOutputer();
	VegetationOutputer vegouter = new VegetationOutputer();
	SnowSoilOutputer sslouter = new SnowSoilOutputer();

	RegnOutputer router = new RegnOutputer();

	//cpp output data definitions
	AtmOutData atmod = new AtmOutData();    //for site-run
	VegOutData vegod = new VegOutData();    //for site-run
	SnowSoilOutData sslod = new SnowSoilOutData();    //for site-run
	
	RegnOutData regnod = new RegnOutData();    //for regional-run
	
	RestartData resod = new RestartData();
	
	//misc.
	Timer temtimer = new Timer();

	//model-run entities
	public Grid grid = new Grid();
	public runcohort runcht = new runcohort();
	
	//cohort ids
	public int runchtid, prechtid; 
	public int grdid;
	public int clmid;
	public int eqchtid;
	public int spchtid;
	public int trchtid;	
	public int vegid;
	public int drgid;
	
	//record orders of cohorts
	public int cid;     //(sp/tr/sc cohort)
	public int eqcid;   //eq cohort
	public int rescid;  //restart cohort
	
	public boolean interactively; 

///////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////	
	//general constructor with default options (which must be reset all or partially)
	public runner() {
		try {
		//
	
		//TEM general controler
			controlfile = "";
		
			runcht.califilein     = false;  //switch to read-in calibrated parameters from Jcalinput.txt			
			runcht.inicali        = false;  //(only valid if 'califilein' above is set to true)switch to read-in initial C conditions, if read-in calpar from Jcalinput.txt
			
			runcht.usecalirestart = false;   //switch to read-in Env. driver for equilibrim-run from calirestart.nc 
			runcht.outcalirestart = false;   //only valid if 'usecalirestart' above is set to false
		
			runcht.outmodes.OSITER  = false;
			runcht.outmodes.ODAY    = false;
			runcht.outmodes.OMONTH  = false;
			runcht.outmodes.OYEAR   = false;
			runcht.outmodes.OREGNER = false;					

			runcht.GUIgraphic=false;
			interactively = false;
		
		//extra input/output files
			runcht.ccdfile ="";
			runcht.califile="";
		
		// IDs
			runchtid= -1;
			grdid   = -1;
			clmid   = -1;
			eqchtid = -1;
			spchtid = -1;
			trchtid = -1;
			vegid   = -1;
			drgid   = -1;
			
			prechtid = runchtid;
			
		// record order for IDs above
			cid    = -1;   //can be for one of spchtid/trchtid/scchtid
			eqcid  = -1;   //for extract eqchtid, grdid, clmid, vegid, and drgid
			rescid = -1;   //for extract restart chtid
			
		} catch (Exception e){
			//
		}
		
	};

	public int initInputs(int myid, int numprocs, String runmode){ 
    	System.out.println("\nTEM initializing ...");
    	try {
    	
    		//Input and processing for reading parameters and passing them to controller
    		configin.setControlfile(controlfile);     //pass the java-input file name to c++ holder (i.e., the filename in c-string)
    		
    		if (runmode.compareToIgnoreCase("siter")==0){
    			configin.ctrl4siterun(md);   //read in model configure info from "/config/sitecontrol.txt" OR input
        		md.setConsoledebug(true);
    		} else if (runmode.compareToIgnoreCase("regner")==0) {
    			configin.ctrl4regnrun(md);   //read in model configure info from "/config/regncontrol.txt" OR input
        		md.setConsoledebug(false);
    	    } else if (runmode.compareToIgnoreCase("caliber")==0) {
    			configin.ctrl4calirun(md);   //read in model configure info from "/config/calicontrol.txt" OR input
        		md.setConsoledebug(true);
    	    } else {
    	    	System.err.println("TEM control file NOT correct!");
    	    	System.exit(-1);
    	    }
    		
    		md.setMyid(myid);
    		md.setNumprocs(numprocs);
    		md.setUseseverity(false);

    		md.checking4run();
    		md.stringtochar();
    		if (runmode.compareToIgnoreCase("regner")==0)
    			md.setJcalibrationdir("config/");   //for regional-run, this directory holds JcalinputXX.txt
    			
    		fd.setUseseverity(false);
    		if (md.getUseseverity()) {
    			fd.setUseseverity(true);
    		}
 
    		//region-level input
    		rinputer.init(md);               //get the file infos, open and read them

    		//grid-level input
    		ginputer.init(md);				//read the grid-level data (maybe multiple grids)
 		 		
    		//cohort-level input : cinputer is for netcdf format file inputting
    		runcht.cinputer.init(md);       //read the cohort-level data (maybe multiple cohorts)
 		
    		//fire year/season for cohort(s)
    		runcht.finputer.init(md); //read-in data
 		
    		//if "restart" initial mode, read-in data from the "restart.nc" file
    		if(md.getInitmode()==3){
    			if(md.getRuneq()){
    				System.out.println("cannot set initmode as 'restart' for equlibrium run");
    				System.out.println("re-set initmode as 'lookup'by default");
    				md.setInitmode(1);
    			} else {
    				runcht.resinputer.init(md.getJinitialfile());
    			}
    		} 		  		
 		 		
    		//set up data connection (initialization)
    		bd.setEnvData(ed);
    		grid.setEnvData(ed);        //define data-structures for ONE common grid
    		grid.setRegionData(rd);
    		grid.setGridData(gd);

    		runcht.cht.setTime(temtimer);        //define data-structures for ONE common cohort
    		runcht.cht.setProcessData(ed, bd, fd);
    		runcht.cht.setModelData(md);
    		runcht.cht.setInputData(rd, gd, cd);
    		runcht.cht.setAtmData(grid);
 		
    		//initializing ONE common cohort 		 		 		
    		runcht.cht.init();
    		    	
    	} catch (Exception e) {
    		System.err.println("Error in 'initInputs()'");
			return -1;
    	}
     
    	return 0;
    };

	//output setting-up 		
 	public int initOutputs(){
 		try {
 				
 		//site-specific OR single cohort outputs
 			if (runcht.outmodes.OSITER) {
 				if (runcht.outmodes.OMONTH) souter.OMONTH=true;
 				if (runcht.outmodes.OYEAR) souter.OYEAR=true;
 				souter.init(md, runchtid);				//creat netcdf files for output
		
 				runcht.cht.setSiteOutData(atmod, vegod, sslod); //output data sets connenction		
 				runcht.outmodes.setSiteOutputer(souter, atmouter, vegouter, sslouter);
 				atmouter.setOutdata(runcht.cht.getAtmod());   //connection of atmospheric output data from cpp to java
 				sslouter.setOutdata(runcht.cht.getSslod());   //connection of ground system output data from cpp to java
 				vegouter.setOutdata(runcht.cht.getVegod());   //connection of plant system output data from cpp to java
 			}  		
		
 		//regional OR multi-cohort outputs
 			if (runcht.outmodes.OREGNER) {
 				if (md.getRuneq()) router.init(md.getJoutputdir(), md.getJrunstages(), ConstTime.MAX_EQ_YR);				//creat netcdf files for output
 				if (md.getRunsp()) router.init(md.getJoutputdir(), md.getJrunstages(), ConstTime.MAX_SP_YR);				//creat netcdf files for output
 				if (md.getRuntr()) router.init(md.getJoutputdir(), md.getJrunstages(), ConstTime.MAX_TR_YR);				//creat netcdf files for output
 				runcht.cht.setRegnOutData(regnod);             //output data sets connenction		
 				runcht.outmodes.setRegnOutputer(router);
 				runcht.outmodes.regnout.setOutData(regnod);
 			}
 		
		//restart.nc always output
 			runcht.outmodes.resout.init(md); //define netcdf file for restart output 
			runcht.outmodes.resout.setRestartData(resod);
 			runcht.cht.setRestartOutData(resod);   //restart output data sets connenction

 		// if running at eq, and needed
 			if (runcht.usecalirestart || runcht.outcalirestart){
 				runcht.ccdfile=md.getJcalibrationdir()+"/calirestart.nc";
 			}
 			
 		}catch (Exception e) {
 			System.err.println("Error in 'initOutputs()'");
			return -2;
 		}
 		
 		return 0;
 	};
 	
 	//get region-level data AND assign to c++ holders
 	public int rd4run(){
 		try {
 			rinputer.getCO2(jRd);
 			rd.setCo2year(jRd.co2year);	  //assign the input (java array) to c++ array 
 			rd.setCo2(jRd.co2);  		  //assign the input (java array) to c++ array 
 		} catch (Exception e) {
 			System.err.println("Error in 'rd4run()'"); 			
			return -3;
 		}
 		
 		return 0;
 	};

 	//get grid-level data for one grid AND assign to c++ holders
 	public int gd4grid(int grdid, int clmid){
 	//extract one-grid-data from java inputs
 		jGd.grdid = grdid;
 		int grecid=ginputer.getGRDrecid(grdid);
 		int crecid=ginputer.getCLMrecid(clmid);
 		if (grecid>=0 && crecid>=0) {
 			ginputer.getGridData(jGd, grecid); 
 			ginputer.getClmData(jGd, crecid);
 			//pass java-data-sets to cpp data holders
 			gd.setGid(jGd.grdid);
 			gd.setLat(jGd.lat);
 			gd.setLon(jGd.lon);
 			gd.setTopsoil(jGd.topsoil);
 			gd.setBotsoil(jGd.botsoil);

 			gd.setFri(jGd.fri);
 			gd.setFireyear(jGd.fyear);
 			gd.setFireseason(jGd.fseason);
 			gd.setFiresize(jGd.fsize);
	
 			gd.setAct_atm_drv_yr(jGd.act_atm_drv_yr);
 			gd.setNirr1d(jGd.nirr);
 			gd.setPrec1d(jGd.prec);
 			gd.setTa1d(jGd.tair);
 			gd.setVap1d(jGd.vapo);
 			gd.d1tod2();   //this is needed to convert 1D climate data to 2D
							  //it will simplify array-data communication from java to c++
 		} else {
 			System.err.println("Grid "+grdid+" NOT exists!");
 			return -1;
 		}
 		
 		return 0;
 	};

	//cohort IDs and cruID, for runchtid
	//Important Note: these IDs are the real identification numbers for a cohort or a grid.
	public int setids() {

		try {
			if (runchtid >0) {
				if (md.getRuneq()) {
					cd.setEqchtid(runchtid);
					cd.setSpchtid(-1);
					cd.setTrchtid(-1);
				} else {
					if (md.getRunsp()){
						cd.setSpchtid(runchtid);
			
						spchtid = cd.getSpchtid();
						cid = runcht.cinputer.getSpRecid(spchtid);
						cd.setEqchtid(runcht.cinputer.getEqchtid5SpFile(cid));		
						
						cd.setTrchtid(-1);
						
						if (md.getInitmode()==3){
							cd.setReschtid(cd.getEqchtid());   //restart id should be eqchtid
							rescid = runcht.resinputer.getRecordId(cd.getReschtid());
						}
					} 
			
					if (md.getRuntr()){
						cd.setTrchtid(runchtid);
			
						trchtid = cd.getTrchtid();
						cid = runcht.cinputer.getSpRecid(trchtid);
						cd.setSpchtid(runcht.cinputer.getSpchtid5TrFile(cid));

						spchtid = cd.getSpchtid();
						int spcid = runcht.cinputer.getSpRecid(spchtid);
						cd.setEqchtid(runcht.cinputer.getEqchtid5SpFile(spcid));

						if (md.getInitmode()==3){
							cd.setReschtid(cd.getSpchtid());   //restart id should be spchtid
							rescid = runcht.resinputer.getRecordId(cd.getReschtid());
						}
					}
				}
				eqchtid = cd.getEqchtid();
				eqcid = runcht.cinputer.getEqRecid(eqchtid);
				grdid = runcht.cinputer.getGRDID(eqcid);
				clmid = runcht.cinputer.getCLMID(eqcid);
				vegid = runcht.cinputer.getVegetation(eqcid);
				drgid = runcht.cinputer.getDrainage(eqcid);
				cd.setClmid(clmid);
			
			} else {
				System.err.println("'runchtid' should be positive interger: "+runchtid);
				return -5;
			}
		
		} catch (Exception e) {
			System.err.println("Error in 'setids()' for cohort: "+runchtid);
			return -5;
		}

		return 0;
	};

	public int chtdata() {
		
		try {
		//TEM region-level data pass into c++ holder
			int err=rd4run();
			if (err<0) return err;
			
		//TEM grid-level data pass and initialization for individual grid - cruid
			err=gd4grid(grdid, clmid);
			if (err<0) return err;
			grid.reinit(grdid);			

		//TEM cohort-level data pass and re-initialization for individula cohort - cid
			err=runcht.chtreinit(cid, eqcid, rescid);
			if (err<0) return err;
		} catch (Exception e) {
			System.err.println("Error in 'chtdata()' for cohort: "+runchtid);
			return -6;
		}
		
		return 0;
	};

 	public int chtrun() {
		try {
		//TEM run for a cohort
//			int err= runcht.runeq();

//			if (interactively) {
//				runcht.runeq();
//			} else { 
				int err= runcht.onerun();
				if (err<0) return err;
//			}
			
			int i = runcht.cohortcount;

			if (runchtid != prechtid) {
				runcht.cohortcount=i+1;
			}
			
		} catch (Exception e) {
			System.err.println("Error in 'chtrun()' for cohort: "+runchtid);
			return -7;
		}
	
		return 0;
	};

}