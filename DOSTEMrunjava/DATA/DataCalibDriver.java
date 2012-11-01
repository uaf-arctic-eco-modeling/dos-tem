package DATA;

public class DataCalibDriver{
      
    // monthly soil climate
    // note that the variables are set to 1D in order to easily pass to c++ holders
    
	public double eq_ts[]=new double [12*ConstLayer.MAX_SOI_LAY];
    public double eq_liq[]=new double [12*ConstLayer.MAX_SOI_LAY];
    public double eq_ice[]=new double [12*ConstLayer.MAX_SOI_LAY];
    public double eq_vwc[]=new double [12*ConstLayer.MAX_SOI_LAY];
    public double eq_sws[]=new double [12*ConstLayer.MAX_SOI_LAY];
    public double eq_ta[]=new double [12];
    public double eq_co2[]=new double [12];
    public double eq_eet[]=new double [12];
    public double eq_pet[]=new double [12];
    public double eq_par[]=new double [12];
    public double eq_grow[]=new double [12];
    public double eq_y_eet;
    public double eq_y_pet;
    public double eq_y_co2;
    public double eq_prveetmx;
    public double eq_prvpetmx;
     
	//variables of soil
	public int numsoil;				
	public double soildz[]=new double[ConstLayer.MAX_SOI_LAY];
	public double[] soiltype=new double[ConstLayer.MAX_SOI_LAY];
	public double soilporo[]=new double[ConstLayer.MAX_SOI_LAY];
	public double rsoilc[]=new double[ConstLayer.MAX_SOI_LAY];
	public double nsoilc[]=new double[ConstLayer.MAX_SOI_LAY];
	
	//variables of soil/vegetation
	public int vegtype;
	public double rootfrac[]=new double[ConstLayer.MAX_SOI_LAY];
	public double envlai[]=new double[12];

	//others
	public int drgtype;
	
	
    
};


