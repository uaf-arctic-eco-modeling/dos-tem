package runTEM;
/*
 * outputs.java
 * 
 * The java version of RunCohort.cpp
 * 
 * for output as needed
 * 
*/

//java definition/method for data, inputers and outputers

import OUTPUT.SiteOutputer;
import OUTPUT.AtmosphereOutputer;
import OUTPUT.RestartOutputer;
import OUTPUT.SnowSoilOutputer;
import OUTPUT.VegetationOutputer;
import OUTPUT.RegnOutputer;

public class runoutputs {
	
	//java outputers for cohort-level variables
	public boolean OSITER;  //should be set in main[]
	public boolean OREGNER;
	public boolean ODAY;
	public boolean OMONTH;
	public boolean OYEAR;
	public boolean OSCLM;

	public SiteOutputer souter = new SiteOutputer();
	public AtmosphereOutputer atmouter = new AtmosphereOutputer();
	public SnowSoilOutputer sslouter = new SnowSoilOutputer();
	public VegetationOutputer vegouter = new VegetationOutputer();
	
	public RestartOutputer resout = new RestartOutputer();
	
	public RegnOutputer regnout = new RegnOutputer();

//////////////////////////////////////////////////////////////////////////////////////

 	void siteoutput(int outputyrind, int currmind){

		if(currmind==11){//end ofyear
	  	
    		if (OMONTH){
  				vegouter.outputMonthCohortVars(souter.moncfn, outputyrind);
  				sslouter.outputMonthCohortVars(souter.moncfn, outputyrind);
  				atmouter.outputMonthGridVars(souter.mongfn, outputyrind);
  			}
  	
  			if (OYEAR){
 				vegouter.outputYearCohortVars(souter.yrcfn, outputyrind);
 				sslouter.outputYearCohortVars(souter.yrcfn, outputyrind);
				atmouter.outputYearGridVars(souter.yrgfn, outputyrind);
  			}
  	
    	}
  
    };

    public void setSiteOutputer(SiteOutputer soutp, AtmosphereOutputer satmoutp,
  				VegetationOutputer svegoutp, SnowSoilOutputer sssloutp){
    	souter   = soutp;
    	atmouter = satmoutp;
    	vegouter = svegoutp;
    	sslouter = sssloutp; 
    	
    };

	public void setRegnOutputer(RegnOutputer regnoutp){
	  	
		regnout = regnoutp;
 	
	};

	public void setRestartOutputer(RestartOutputer resoutp){
  	
		resout = resoutp;
 	
	};
  
}
