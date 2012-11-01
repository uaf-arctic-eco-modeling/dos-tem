package GUI;

public class GUIconfigurer{
	
	public String controlfile;
	
	public String outputdir;
  	public String reginputdir;
  	public String grdinputdir;
  	public String eqchtinputdir;
  	public String spchtinputdir;
  	public String trchtinputdir;
  	public String restartinputdir;
  	public String calibrationdir;
  	public String runstage;
  	public String initmode;
  	public String climatemode;
  	public String co2mode;
  	
  	public String casename;
  	//other I/O options
  	public boolean califilein;   //read-in calibrated pars from text file: 'califile'
  	public String califile;
  	
  	public boolean ccdfilein; //read-in soil climate driver from netcdf file: 'ccdfile'
  	public String ccdfile;

  	public boolean OSITE;     //for Single-site run (i.e., TEMsiter)
  	public boolean OREGN;     //for multi-sites run (i.e., TEMregioner)
  	public boolean OSDLY;     //only for Single-site run
  	public boolean OSMLY;     //only for Single-site run
  	public boolean OSYLY;     //only for Single-site run
  	
  	public boolean OGRAPH;    //only if no file output
  	public boolean OBGRAPH;   //showing bio. var. graphs only if no file output
  	public boolean OPGRAPH;   //showing phy. var. graphs only if no file output
	
	//fixed states
	public static int I_VEGETATION =0;
	public static int I_DRAINAGE =1;
	public static int I_GRD=2;
	public static int I_EQCHT=3;
	public static int I_SPCHT=4;
	public static int I_TRCHT=5;

	//fixed Parameters
	public static int I_m1 =0;
	public static int I_m2 =1;
	public static int I_m3 =2;
	public static int I_m4 =3;
	public static int I_fsoma =4;
	public static int I_fsompr=5;
	public static int I_fsomcr =6;
	public static int I_som2co2 =7;

	//calibrated Parameters
	public static int I_CMAX =0;
	public static int I_NMAX =1;
	public static int I_KRB =2;
	public static int I_NUP =3;
	public static int I_CFALL =4;
	public static int I_NFALL=5;
	public static int I_KDCFIB =6;
	public static int I_KDCHUM =7;
	public static int I_KDCMIN =8;
	public static int I_KDCSLOW =9;
 
	//initial conditions
	public static int I_MOSSTHICK =0;
	public static int I_FIBTHICK =1;
	public static int I_HUMTHICK =2;
	public static int I_VEGC =3;
	public static int I_VEGN =4;
	public static int I_SOILC =5;
	public static int I_FIBSOILC =6;
	public static int I_HUMSOILC =7;
	public static int I_MINESOILC =8;
	public static int I_AVAILN=9;
	public static int I_SOILN =10;

	public GUIconfigurer(){
		 
	}	
	
}