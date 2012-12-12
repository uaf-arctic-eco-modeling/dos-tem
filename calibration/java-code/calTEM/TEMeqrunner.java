package calTEM;

//from java
import runTEM.runner;
import DATA.ConstTime;

//data embedded in TEM (can be updated!!!)
import TEMJNI.vegpar_cal;
import TEMJNI.soipar_cal;

//GUI
import GUI.PlotterUpdate;

public class TEMeqrunner implements Runnable{

	//calibration parameters
	public vegpar_cal vbcalpar = new vegpar_cal();
	public soipar_cal sbcalpar = new soipar_cal();
		
	// model-run entities
	public runner eqrunner; // = new runner();
	
	// model options
	public boolean useeq    = false;		
	public boolean friderived = false;
	
///////////////////////////////////////////////////////////////////////////////////////
	
	// Model Running process operations for calibration using GUI
	private boolean m_stop = true;
	private Thread m_thread;
	
	public PlotterUpdate plotting = new PlotterUpdate();
	
//////////////////////////////////////////////////////////////////////////////////////////
//The following TEM run is for calibration in TCGUI
/////////////////////////////////////////////////////////////////////////////////////////

	int yrcnt =0;
	
	public void init(){
		
		eqrunner.runchtid = 1;    //for calibration, only ONE run-cohort exists,AND must be "eq" run

		//general initialization, including input reading
		eqrunner.initInputs(0, 1, "caliber");
		eqrunner.initOutputs();

		//cohort IDs and cruID
		eqrunner.setids();
		
	    //cohort data
		eqrunner.chtdata();
		
		//control options will NOT set by GUI controller OR run module below

		eqrunner.runcht.cht.setEquiled(false);
		eqrunner.runcht.cht.setSpined(false);
		eqrunner.runcht.cht.setTransed(false); 

		//misc. 
		eqrunner.runcht.cht.setVeupdateLAI5Vegc(false);
		eqrunner.runcht.cht.getFd().setYsf(1000);

		//don't need to output for Calibration Run of TEM
   	 	eqrunner.runcht.cht.setOutSiteDay(false);
   	 	eqrunner.runcht.cht.setOutSiteMonth(false);
   	 	eqrunner.runcht.cht.setOutSiteYear(false);
   	 	eqrunner.runcht.cht.setOutRegn(false);
   	 	eqrunner.runcht.cht.setOutSoilClm(false);
   	 	
   	 	if (!eqrunner.runcht.usecalirestart){
   	 		updatedriver();
   	 	}
   	 	
   	 	yrcnt = 0;
	        
	};

//--------------------------------------------------------------------------------------			
	//TEM run for updating calibration driver
	public void updatedriver(){					
		//
		eqrunner.runcht.cht.getTimer().reset();
		
		eqrunner.runcht.cht.setEquiled(false);
		eqrunner.runcht.cht.setSpined(false);
		eqrunner.runcht.cht.setTransed(false); 
		eqrunner.runcht.cht.setOutputSpinup(false); 
     	 		 	
		//Turn Env-Module only on
		eqrunner.runcht.cht.setEnvmodule(true);
		eqrunner.runcht.cht.setEcomodule(false);
		eqrunner.runcht.cht.setDsbmodule(false);
		eqrunner.runcht.cht.setDslmodule(false);

		//reset calibration parameters
		eqrunner.runcht.cht.resetCalPar(vbcalpar, sbcalpar);
		
		//option of dynamic soil organic layer thickness for testing code
		boolean dsl = false;
		float moss = 0.001f;
		float fib  = 0.02f;
		float hum  = 0.02f;

		boolean assigneq =false;		
		System.out.println("TEM Env-Module only RUN for calirestart.nc ... ");
		for (int iyr=0; iyr<100; iyr++) {
			
			//reset soil organic layer thickness as desired
			if (dsl) {
				moss+=0.001;
//				fib+=0.005;
//				hum+=0.005;
				resetOMthickness(moss, fib, hum);
			}

			if(iyr==99) assigneq =true;
			for (int im=0; im<12;im++){  
				int dinmcurr = ConstTime.dinm[im];
	   
				eqrunner.runcht.cht.updateMonthly(iyr, iyr, im, dinmcurr, assigneq, false);
				eqrunner.runcht.cht.getEd().d2tod1(); //this is for java output of ccdriver
				
				plotting.updateMlyPhyGraph(iyr, im, eqrunner.runcht.cht);

			}
			plotting.updateYlyPhyGraph(iyr, eqrunner.runcht.cht);
								
			//write the driver file: calirestart.nc
			eqrunner.runcht.ccdriver.createSoilClimate(
					eqrunner.runcht.cht.getEd(), 
					eqrunner.runcht.cht.getBd(), 
					eqrunner.runcht.cht, 
					eqrunner.runcht.ccdfile);
				
		}		
		
		System.out.println("Done!");

		Thread.currentThread().interrupt();
	};

	//the following will reset soil organic layer thickness when called
	private void resetOMthickness(float mossthick, float fibthick, float humthick){
	
      eqrunner.runcht.initstate.setMossthick(mossthick);
      eqrunner.runcht.initstate.setFibthick(fibthick);
      eqrunner.runcht.initstate.setHumthick(humthick);
      
      eqrunner.runcht.cht.setSiteStates
                  (eqrunner.runcht.initstate);
      
	};
	
//-----------------------------------------------------------------------------
//TEM calibration run	
	public void run(){					
			
		//GUI error message
		if (Thread.currentThread() != this.m_thread) {
			throw new IllegalStateException(
			"you cannot start an own thread for running TEM");
		}

		//thread status initialization
		this.m_stop = false;
				    
		while (!this.m_stop){	
			System.out.println("TEM CALIBRATION RUN: year "+yrcnt);

			//reset calibration parameters
			eqrunner.runcht.cht.resetCalPar(vbcalpar, sbcalpar);

   	 		//reset disturbance options
			eqrunner.runcht.cht.setFriderived(friderived);
			if (!friderived) eqrunner.runcht.cht.getFd().setYsf(1000);			
			if (eqrunner.runcht.cht.getGd().getFri()<=0) eqrunner.runcht.cht.getFd().setYsf(1000);			
			
			for (int im=0; im<12;im++){
				int dinmcurr = ConstTime.dinm[im]; 
				eqrunner.runcht.cht.updateMonthly(yrcnt, yrcnt, im, dinmcurr, false, useeq);
				eqrunner.runcht.cht.getTimer().advanceOneMonth();

				plotting.updateMlyBioGraph(yrcnt, im, eqrunner.runcht.cht);
				plotting.updateMlyPhyGraph(yrcnt, im, eqrunner.runcht.cht);
			}
			yrcnt++;
			plotting.updateYlyBioGraph(yrcnt, eqrunner.runcht.cht);
			plotting.updateYlyPhyGraph(yrcnt, eqrunner.runcht.cht);
			
			if (Thread.interrupted()) this.stop();
			if (yrcnt<500) {
				if (yrcnt%100==0) {
					try {
						Thread.sleep(100);
						this.stop();
					} catch (InterruptedException e) {
						this.stop();
					}
				}
			} else {
				if (yrcnt%500==0) {
					try {
						Thread.sleep(100);
						this.stop();
					} catch (InterruptedException e) {
						this.stop();
					}
				}
			}		
			
		}

	};

//////////////////////////////////////////////////////////////////////////////////////////
//The following are for controlling of model running process USING GUI
//////////////////////////////////////////////////////////////////////////////////////////		

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
	
}
