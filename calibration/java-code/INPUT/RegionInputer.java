package INPUT;

import java.io.File;
import java.io.IOException;

import ucar.ma2.Array;
import ucar.ma2.Index;
import ucar.nc2.NetcdfFile;
import ucar.nc2.Variable;

import DATA.ConstTime;
import DATA.DataRegion;
import TEMJNI.ModelData;

public class RegionInputer {
	
	Array co2yearA;
	Array co2A;
			
	public void init(ModelData md){
	  	initCO2(md.getJreginputdir());
	};

	public void initCO2(String dir){
		String filename = dir +"co2.nc";
	  	
		NetcdfFile ncfile = null;
		File co2file = new File(filename);
		if (co2file.exists()){
			try {
				ncfile = NetcdfFile.open(filename);

				Variable var1 = ncfile.findVariable("YEAR");
				co2yearA = var1.read();

				Variable var2 = ncfile.findVariable("CO2");
				co2A = var2.read();
			
			} catch (IOException ioe) {
				System.out.println(ioe.getMessage());
			} finally {
				if (ncfile != null) {
					try {
						ncfile.close();
					} catch (IOException ioee) {
						System.out.println(ioee.getMessage());
					}
				}
			}
		}else {   //file not exist
			System.out.println("Input file: "+filename+" NOT existed");
		}
 	
	};

	public void getCO2(DataRegion rd){
		Index ind = co2A.getIndex();
		for (int iy = 0; iy < ConstTime.MAX_CO2_DRV_YR; iy++) {
			rd.co2year[iy] = co2yearA.getInt(ind.set(iy));
			rd.co2[iy] = co2A.getFloat(ind.set(iy));
		}
		
	};

}