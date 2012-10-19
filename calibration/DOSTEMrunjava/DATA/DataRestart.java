package DATA;

public class DataRestart {

		public int chtid;
		public int errcode;
		
		public double TSsnow[] = new double[ConstLayer.MAX_SNW_LAY];
		public double DZsnow[] = new double[ConstLayer.MAX_SNW_LAY];
		public double LIQsnow[] = new double[ConstLayer.MAX_SNW_LAY];
		public double RHOsnow[] = new double[ConstLayer.MAX_SNW_LAY];
		public double ICEsnow[] = new double[ConstLayer.MAX_SNW_LAY];
		public double AGEsnow[] = new double[ConstLayer.MAX_SNW_LAY];
	    
		public int TYPEsoil[]   = new int[ConstLayer.MAX_SOI_LAY];
		public int FROZENsoil[] = new int[ConstLayer.MAX_SOI_LAY];
		public double TSsoil[] = new double[ConstLayer.MAX_SOI_LAY];
		public double DZsoil[] = new double[ConstLayer.MAX_SOI_LAY];
		public double LIQsoil[] = new double[ConstLayer.MAX_SOI_LAY];
		public double ICEsoil[] = new double[ConstLayer.MAX_SOI_LAY];
		public double NONCsoil[] = new double[ConstLayer.MAX_SOI_LAY];
		public double REACsoil[] = new double[ConstLayer.MAX_SOI_LAY];
	    
		public double toptA[]  = new double[10];
		public double eetmxA[] = new double[10];
		public double petmxA[] = new double[10];
		public double unnormleafmxA[] = new double[10];
	        
		public int TYPEmin[] = new int[ConstLayer.MAX_MIN_LAY];   
		public double TSrock[] = new double[ConstLayer.MAX_ROC_LAY];
		public double DZrock[] = new double[ConstLayer.MAX_ROC_LAY];
		public double frontZ[] = new double[ConstLayer.MAX_NUM_FNT];
		public int frontFT[] = new int[ConstLayer.MAX_NUM_FNT];
	     
		public int ysf;
		public double vegc, wdebris, deadc;
		public double strn, ston, c2n, deadn, soln, avln;
		public double prveetmx, prvpetmx;
		public double unnormleaf, prvunnormleafmx;
		public double prvtopt;
		public double kdfib,kdhum,kdmin,kdslow; 
		public double lai, foliagemx;
		public double burnedn;    
   	
};

