package DATA;

import TEMJNI.temcore;

public class ConstLayer {
	
	public final static int MAX_SNW_LAY =temcore.getMAX_SNW_LAY(); //maximum number of Snow Layer
	
	public final static int MAX_ROC_LAY =temcore.getMAX_ROC_LAY(); // maximum number of rock Layer (
	public final static int MAX_MOS_LAY =temcore.getMAX_MOS_LAY(); // maximum number of moss Layer
	public final static int MAX_SLW_LAY =temcore.getMAX_SLW_LAY(); // maximum number of shallow organic Layer
	public final static int MAX_DEP_LAY =temcore.getMAX_DEP_LAY(); // maximum number of deep organic Layer
	public final static int MAX_MIN_LAY =temcore.getMAX_MIN_LAY(); // maximum number of mineral Layer (0.1, 0.2, 0.5, 1, 2)
	
	public final static int MAX_SOI_LAY =temcore.getMAX_SOI_LAY(); // maximum number of Soil Layer
	public final static int MAX_DYN_LAY =temcore.getMAX_DYN_LAY(); // maximum number of snow(6) + moss (2) + shlw org(3) + deep org (3)
	public final static int MAX_GRN_LAY =temcore.getMAX_GRN_LAY(); //maximumum number of Ground Layer
	
	public final static int MAX_NUM_FNT =temcore.getMAX_NUM_FNT(); // maximum number of fronts in ground
	public final static int MAX_OUT_SOI =temcore.getMAX_OUT_SOI(); //maximum number of soil layer for output
	public final static int MAX_OUT_SNW =temcore.getMAX_OUT_SNW(); //maximum number of snow layer for output
    	
}

