package DATA;

/* This is a java definition same as /run/SiteIn.h
 * So that, java read-in can exactly match with c++ data structure
 */

public class DataSitein {
		
	    public int chtid;
	    public int ysf; 

	    public float lai[]= new float[12];
	    public float vegc;
	    public float vegn;
	    
	    public float mossthick;
	    public float fibthick;
	    public float humthick;
	    
	    public float soilc;
	    public float fibc;
	    public float humc;
	    public float minc;
	    public float orgn;
	    public float avln;
	    
	    public int mintype[] = new int[ConstLayer.MAX_MIN_LAY];
	     		
	    public float initz[]= new float[ConstLayer.MAX_SOI_LAY];
	    public float initst[]= new float[ConstLayer.MAX_SOI_LAY];
	    public float initsm[]= new float[ConstLayer.MAX_SOI_LAY];
   	
};

