package OUTPUT;

/*
 * 
*/

// for netcdf file operation
import java.io.File;
import java.io.IOException;

import ucar.ma2.*;
import ucar.nc2.*;

import TEMJNI.AtmOutData;
import DATA.ConstTime;

public class AtmosphereOutputer {
		  	 
	AtmOutData atmod = new AtmOutData();

	public void outputMonthGridVars(String mongfn, int yrcnt){
		 String ncfilename = mongfn;
		 File f = new File(ncfilename);
		 if (f.exists()) {
			 try {
				 NetcdfFileWriteable ncfile = NetcdfFileWriteable.openExisting(ncfilename, true);
		 
				 try {			
				
					 ArrayFloat dataM  = new ArrayFloat.D2(1, ConstTime.MINY);
					 Index ima = dataM.getIndex();
					 int[] origin = new int[] {0, 0};  
					 float[] mdata = new float[ConstTime.MINY];
			
					 origin[0] = yrcnt;
					 
					 mdata =atmod.getTa();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("TA", origin, dataM);

					 mdata =atmod.getEet();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("EET", origin, dataM);

					 mdata =atmod.getPet();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("PET", origin, dataM);

					 mdata =atmod.getCo2();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("CO2", origin, dataM);

					 mdata =atmod.getRnfl();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("RNFL", origin, dataM);

					 mdata =atmod.getSnfl();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("SNFL", origin, dataM);

					 mdata =atmod.getNirr();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("NIRR", origin, dataM);

					 mdata =atmod.getGirr();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("GIRR", origin, dataM);

					 mdata =atmod.getPar();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("PAR", origin, dataM);

					 mdata =atmod.getClds();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("CLDS", origin, dataM);

				 } catch (IOException e){
					 System.err.println("Error in writing file"+ncfile.getLocation()+"\n");
				 } catch (InvalidRangeException e){
					 e.printStackTrace();
				 }

				 try {
					ncfile.close();
				 } catch (IOException ioee) {
					System.out.println(ioee.getMessage());
				 }
		
			} catch (IOException ioe) {
				System.out.println(ioe.getMessage());
			}
		 }
	 };

	 public void outputYearGridVars(String yrgfn, int yrcnt){
		 String ncfilename = yrgfn;
		 File f = new File(ncfilename);
		 if (f.exists()) {
			 try {
				 NetcdfFileWriteable ncfile = NetcdfFileWriteable.openExisting(ncfilename, true);
		 
				 try {			
				
					 Array dataY  = Array.factory(DataType.FLOAT, new int[] {1});
					 int[] origin = new int[] {0}; origin[0] = yrcnt; 
					 float yrdata = 0.0f;
			
					 yrdata =atmod.getYrta();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("TA", origin, dataY);
				
					 yrdata=atmod.getYrrnfl();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("RNFL", origin, dataY);

					 yrdata=atmod.getYrsnfl();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("SNFL", origin, dataY);

				 } catch (IOException e){
					 System.err.println("Error in writing file"+ncfile.getLocation()+"\n");
				 } catch (InvalidRangeException e){
					 e.printStackTrace();
				 }

				 try {
					ncfile.close();
				 } catch (IOException ioee) {
					System.out.println(ioee.getMessage());
				 }
		
			} catch (IOException ioe) {
				System.out.println(ioe.getMessage());
			}
		 }
	 };

	 public void setOutdata(AtmOutData outdata){
		 atmod = outdata;
	 };	

}

