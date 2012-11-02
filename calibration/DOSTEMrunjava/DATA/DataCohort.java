package DATA;
import DATA.ConstTime;
public class DataCohort{
  
	public int cruid;
	public int trchtid; // transient cohortid
  	public int eqchtid; //equilibrium cohort id
  	public int spchtid; //spinup cohort id
  	public int scchtid; //scenario cohort id 
  	public int reschtid;  //cohort id for restart

  	public int drgtype;
  	public int vegtype;   	
  	
  	public int trfireyear[]=new int[ConstTime.MAX_TR_FIR_OCR_NUM];
  	public int trfireseason[]=new int[ConstTime.MAX_TR_FIR_OCR_NUM];
  	public int trseverity[]=new int[ConstTime.MAX_TR_FIR_OCR_NUM];

  	public int spfireyear[]=new int[ConstTime.MAX_SP_FIR_OCR_NUM];
  	public int spfireseason[]=new int[ConstTime.MAX_SP_FIR_OCR_NUM];
  	public int spseverity[]=new int[ConstTime.MAX_SP_FIR_OCR_NUM];
	
};

