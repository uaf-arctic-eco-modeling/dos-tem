package DATA;
import DATA.ConstTime;
public class DataGrid {
  
    public int grdid;
    public float lat;
    public float lon;
    public float[] alldaylengths=new float[365]; 

    public int fri;
	public int[] fyear=new int[ConstTime.MAX_FSIZE_DRV_YR];
	public int[] fsize=new int[ConstTime.MAX_FSIZE_DRV_YR];
	public int[] fseason=new int[ConstTime.MAX_FSIZE_DRV_YR];

    public int topsoil;
    public int botsoil;
    
    public int act_atm_drv_yr;
    //the variables are set to 1D in order to easily pass to c++ holders
    public int clmid;
    public float[] tair=new float[ConstTime.MAX_ATM_DRV_YR*12];
    public float[] prec=new float[ConstTime.MAX_ATM_DRV_YR*12];
    public float[] nirr=new float[ConstTime.MAX_ATM_DRV_YR*12];
    public float[] vapo=new float[ConstTime.MAX_ATM_DRV_YR*12];
	
};

