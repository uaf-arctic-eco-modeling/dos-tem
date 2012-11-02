package OUTPUT;

//for netcdf file operation
import java.io.File;
import java.io.IOException;

import ucar.ma2.*;
import ucar.nc2.*;

import TEMJNI.VegOutData;
import DATA.ConstTime;

public class VegetationOutputer {
		  	 
	VegOutData vegod = new VegOutData();

	public void outputMonthCohortVars(String moncfn, int yrcnt){

		 String ncfilename = moncfn;
		 File f = new File(ncfilename);
		 if (f.exists()) {
			 try {
				 NetcdfFileWriteable ncfile = NetcdfFileWriteable.openExisting(ncfilename, true);
		 
				 try {			
				
					 ArrayFloat dataM  = new ArrayFloat.D2(1, ConstTime.MINY);
					 Index ima = dataM.getIndex();
					 int[] morigin = new int[] {0, 0};  
					 float[] mdata = new float[ConstTime.MINY];			
					 morigin[0] = yrcnt;
					 			 
					 //plant system outputs
					 mdata =vegod.getVegc();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("VEGC", morigin, dataM);

					 mdata =vegod.getStrn();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("STRN", morigin, dataM);

					 mdata =vegod.getSton();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("STON", morigin, dataM);

					 mdata =vegod.getIngpp();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("INGPP", morigin, dataM);

					 mdata =vegod.getGpp();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("GPP", morigin, dataM);

					 mdata =vegod.getInnpp();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("INNPP", morigin, dataM);

					 mdata =vegod.getNpp();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("NPP", morigin, dataM);

					 mdata =vegod.getRm();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("RM", morigin, dataM);

					 mdata =vegod.getRg();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("RG", morigin, dataM);

					 mdata =vegod.getLtrfalc();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("LTRFALC", morigin, dataM);

					 mdata =vegod.getLtrfaln();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("LTRFALN", morigin, dataM);

					 mdata =vegod.getInnuptake();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("INNUPTAKE", morigin, dataM);

					 mdata =vegod.getNuptake();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("NUPTAKE", morigin, dataM);

					 mdata =vegod.getSuptake();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("SUPTAKE", morigin, dataM);

					 mdata =vegod.getLuptake();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("LUPTAKE", morigin, dataM);

					 mdata =vegod.getNmobil();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("NMOBIL", morigin, dataM);

					 mdata =vegod.getNresorb();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("NRESORB", morigin, dataM);

					 mdata =vegod.getLai();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("LAI", morigin, dataM);

					 mdata =vegod.getFpc();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("FPC", morigin, dataM);

					 mdata =vegod.getUnnormleaf();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("UNNORMLEAF", morigin, dataM);

					 mdata =vegod.getLeaf();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("LEAF", morigin, dataM);

					 mdata =vegod.getFoliage();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("FOLIAGE", morigin, dataM);

					 mdata =vegod.getBtran();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("BTRAN", morigin, dataM);

					 mdata =vegod.getRac();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("RAC", morigin, dataM);

					 mdata =vegod.getRc();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("RC", morigin, dataM);

					 mdata =vegod.getTrans();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("TRANS", morigin, dataM);

					 mdata =vegod.getVevap();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("VEVAP", morigin, dataM);

					 mdata =vegod.getVsubl();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("VSUBL", morigin, dataM);

					 mdata =vegod.getRinter();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("RINTER", morigin, dataM);

					 mdata =vegod.getSinter();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("SINTER", morigin, dataM);

					 mdata =vegod.getRthfl();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("RTHFL", morigin, dataM);

					 mdata =vegod.getSthfl();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("STHFL", morigin, dataM);

					 mdata =vegod.getRadthfl();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("RADTHFL", morigin, dataM);
					 
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

	public void outputYearCohortVars(String yrcfn, int yrcnt){

		 String ncfilename = yrcfn;
		 File f = new File(ncfilename);
		 if (f.exists()) {
			 try {
				 NetcdfFileWriteable ncfile = NetcdfFileWriteable.openExisting(ncfilename, true);
		 
				 try {			
				
					 Array dataY  = Array.factory(DataType.FLOAT, new int[] {1});
					 int[] origin = new int[] {0}; origin[0] = yrcnt; 
					 float yrdata = 0.0f;
			
					 //plant system outputs
					 yrdata =vegod.getYrnpp();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("NPP", origin, dataY);
					 
					 yrdata =vegod.getYrrm();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("RM", origin, dataY);

					 yrdata =vegod.getYrrg();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("RG", origin, dataY);

					 yrdata =vegod.getYrltrfalc();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("LTRFALC", origin, dataY);

					 yrdata =vegod.getYrltrfaln();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("LTRFALN", origin, dataY);

					 yrdata =vegod.getYrvnuptake();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("VNUPTAKE", origin, dataY);

					 yrdata =vegod.getYrevapo();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("EVAPO", origin, dataY);

					 yrdata =vegod.getYrsublim();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("SUBLIM", origin, dataY);

					 yrdata =vegod.getYrtrans();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("TRANS", origin, dataY);
					 
					 yrdata =vegod.getYrc2n();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("C2N", origin, dataY);

					 yrdata =vegod.getYrvegc();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("VEGC", origin, dataY);

					 yrdata =vegod.getYrstrn();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("STRN", origin, dataY);

					 yrdata =vegod.getYrston();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("STON", origin, dataY);

					 yrdata =vegod.getYrabvgndc();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("ABVGNDC", origin, dataY);

					 yrdata =vegod.getYrfoliage();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("FOLIAGE", origin, dataY);

					 yrdata =vegod.getYrleaf();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("LEAF", origin, dataY);

					 yrdata =vegod.getYrlai();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("LAI", origin, dataY);

					 yrdata =vegod.getYrfpc();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("FPC", origin, dataY);

					 yrdata =vegod.getYrburnorgc();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("BURNVEGC", origin, dataY);

					 yrdata =vegod.getYrburnorgn();
					 dataY.setFloat(dataY.getIndex(),yrdata);
					 ncfile.write("BURNVEGN", origin, dataY);

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

	public void setOutdata(VegOutData outdata){
		vegod = outdata;
	};

}
