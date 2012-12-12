package OUTPUT;
/*
 * This class is for output variables in TEM multiple-cohort run
 * in netcdf format
 * 
*/

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import ucar.ma2.*;
import ucar.nc2.*;

import TEMJNI.RegnOutData;;

public class RegnOutputer {

	RegnOutData regnod = new RegnOutData();
    public String regnfn = "";

	public void init(String outputdir, String stage, int max_drv_yr){
 	
		regnfn =outputdir+"output-"+stage+".nc";

		try {
		NetcdfFileWriteable ncfile=NetcdfFileWriteable.createNew(regnfn, false);
		Dimension chtD = ncfile.addUnlimitedDimension("CHTID");
		Dimension yearD = ncfile.addDimension("YEAR", max_drv_yr);

		ArrayList<Dimension> dimCht = new ArrayList<Dimension>();
		dimCht.add(chtD);
		ArrayList<Dimension> dimChtY = new ArrayList<Dimension>();
		dimChtY.add(chtD);
		dimChtY.add(yearD);

		ncfile.addVariable("CHTID", DataType.INT, dimCht);
		ncfile.addVariable("STATUS", DataType.INT, dimCht);
 
		ncfile.addVariable("GPP", DataType.FLOAT, dimChtY);
		ncfile.addVariable("NPP", DataType.FLOAT, dimChtY);
		ncfile.addVariable("RH", DataType.FLOAT, dimChtY);

	   	ncfile.addVariable("LAI", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("VEGC", DataType.FLOAT, dimChtY);
		ncfile.addVariable("VEGN", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("NUPTAKE", DataType.FLOAT, dimChtY);

		ncfile.addVariable("MOSSDZ", DataType.FLOAT, dimChtY);
		ncfile.addVariable("SHLWDZ", DataType.FLOAT, dimChtY);
		ncfile.addVariable("DEEPDZ", DataType.FLOAT, dimChtY);

		ncfile.addVariable("SHLWC", DataType.FLOAT, dimChtY);
		ncfile.addVariable("DEEPC", DataType.FLOAT, dimChtY);
		ncfile.addVariable("MINEC", DataType.FLOAT, dimChtY);
        
		ncfile.addVariable("LTRFALC", DataType.FLOAT, dimChtY);
		ncfile.addVariable("LTRFALN", DataType.FLOAT, dimChtY);
		
		ncfile.addVariable("ORGN", DataType.FLOAT, dimChtY);
		ncfile.addVariable("AVLN", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("NETNMIN", DataType.FLOAT, dimChtY);

	   	ncfile.addVariable("GROWSTART", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("GROWEND", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("EET", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("PET", DataType.FLOAT, dimChtY);
	   
	   	ncfile.addVariable("ALD", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("PERMAFROST", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("WATERTAB", DataType.FLOAT, dimChtY);
	   	
	   	ncfile.addVariable("TROCK34M", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("TSHLW", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("TDEEP", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("TMINETOP", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("TMINEBOT", DataType.FLOAT, dimChtY);

	   	ncfile.addVariable("VWCSHLW", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("VWCDEEP", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("VWCMINETOP", DataType.FLOAT, dimChtY);
	   	ncfile.addVariable("VWCMINEBOT", DataType.FLOAT, dimChtY);

		ncfile.addVariable("DRAINAGE", DataType.FLOAT, dimChtY);
		ncfile.addVariable("RUNOFF", DataType.FLOAT, dimChtY);
		ncfile.addVariable("NINPUT", DataType.FLOAT, dimChtY);
		ncfile.addVariable("NLOST", DataType.FLOAT, dimChtY);

		ncfile.addVariable("YSF", DataType.FLOAT, dimChtY);
		ncfile.addVariable("BURNVEGC", DataType.FLOAT, dimChtY);
		ncfile.addVariable("BURNSOIC", DataType.FLOAT, dimChtY);
		ncfile.addVariable("BURNTHICK", DataType.FLOAT, dimChtY);   	
	 
		try {
			ncfile.create();
			ncfile.close();
		}catch (IOException e) {
			System.err.println("Error in creating file"+ncfile.getLocation()+"\n");
		}

		} catch (Exception e) {
			
		}
	};

	public void outputYearCohortVars(int yrind, int chtcount){
		 String ncfilename = regnfn;
		 File f = new File(ncfilename);
		 if (f.exists()) {
			 try {
				 NetcdfFileWriteable ncfile = NetcdfFileWriteable.openExisting(ncfilename, true);
		 
				 try {			
				
					 Array dataInt   = Array.factory(DataType.INT, new int[] {1});
					 int[] origin = new int[] {0}; 
					 origin[0] = chtcount; 
					 int chtint = -999;

					 ArrayFloat dataFloat = new ArrayFloat.D2(1,1);
					 int[] originY = new int[] {0, 0}; 
					 originY[0] = chtcount; 
					 originY[1] = yrind; 
					 float chtfloat = -999;

					 chtint =regnod.getChtid();
					 dataInt.setInt(dataInt.getIndex(),chtint);
					 ncfile.write("CHTID", origin, dataInt);
					 
					 chtint =regnod.getStatus();
					 dataInt.setInt(dataInt.getIndex(),chtint);
					 ncfile.write("STATUS", origin, dataInt);

					 chtfloat =regnod.getGpp()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("GPP", originY, dataFloat);

					 chtfloat =regnod.getNpp()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("NPP", originY, dataFloat);

					 chtfloat =regnod.getRh()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("RH", originY, dataFloat);

					 chtfloat =regnod.getLai()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("LAI", originY, dataFloat);

					 chtfloat =regnod.getVegc()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("VEGC", originY, dataFloat);

					 chtfloat =regnod.getVegn()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("VEGN", originY, dataFloat);
					 
					 chtfloat =regnod.getNuptake()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("NUPTAKE", originY, dataFloat);

					 chtfloat =regnod.getMossdz();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("MOSSDZ", originY, dataFloat);

					 chtfloat =regnod.getShlwdz();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("SHLWDZ", originY, dataFloat);

					 chtfloat =regnod.getDeepdz();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("DEEPDZ", originY, dataFloat);

					 chtfloat =regnod.getShlwc()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("SHLWC", originY, dataFloat);

					 chtfloat =regnod.getDeepc()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("DEEPC", originY, dataFloat);

					 chtfloat =regnod.getMinec()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("MINEC", originY, dataFloat);

					 chtfloat =regnod.getLtrfalc()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("LTRFALC", originY, dataFloat);

					 chtfloat =regnod.getLtrfaln()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("LTRFALN", originY, dataFloat);

					 chtfloat =regnod.getOrgn()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("ORGN", originY, dataFloat);

					 chtfloat =regnod.getAvln()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("AVLN", originY, dataFloat);

					 chtfloat =regnod.getNetnmin()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("NETNMIN", originY, dataFloat);

					 chtfloat =regnod.getGrowstart();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("GROWSTART", originY, dataFloat);

					 chtfloat =regnod.getGrowend();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("GROWEND", originY, dataFloat);

					 chtfloat =regnod.getEet()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("EET", originY, dataFloat);

					 chtfloat =regnod.getPet()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("PET", originY, dataFloat);

					 chtfloat =regnod.getQdrain()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("DRAINAGE", originY, dataFloat);

					 chtfloat =regnod.getQrunoff()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("RUNOFF", originY, dataFloat);

					 chtfloat =regnod.getAld()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("ALD", originY, dataFloat);

					 chtfloat =regnod.getPerm();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("PERMAFROST", originY, dataFloat);

					 chtfloat =regnod.getWtd()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("WATERTAB", originY, dataFloat);

					 chtfloat =regnod.getTrock34()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("TROCK34M", originY, dataFloat);

					 chtfloat =regnod.getTminetop()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("TMINETOP", originY, dataFloat);

					 chtfloat =regnod.getTminebot()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("TMINEBOT", originY, dataFloat);

					 chtfloat =regnod.getTshlw()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("TSHLW", originY, dataFloat);

					 chtfloat =regnod.getTdeep()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("TDEEP", originY, dataFloat);
					 
					 chtfloat =regnod.getTminetop()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("TMINETOP", originY, dataFloat);

					 chtfloat =regnod.getTminebot()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("TMINEBOT", originY, dataFloat);

					 chtfloat =regnod.getVwcshlw()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("VWCSHLW", originY, dataFloat);
					 
					 chtfloat =regnod.getVwcdeep()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("VWCDEEP", originY, dataFloat);
					 
					 chtfloat =regnod.getVwcminetop()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("VWCMINETOP", originY, dataFloat);
					 
					 chtfloat =regnod.getVwcminebot()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("VWCMINEBOT", originY, dataFloat);

					 chtfloat =regnod.getYsf();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("YSF", originY, dataFloat);

					 chtfloat =regnod.getBurnvegc();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("BURNVEGC", originY, dataFloat);

					 chtfloat =regnod.getBurnsoic();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("BURNSOIC", originY, dataFloat);

					 chtfloat =regnod.getNinput()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("NINPUT", originY, dataFloat);

					 chtfloat =regnod.getNlost()[0];
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("NLOST", originY, dataFloat);

					 chtfloat =regnod.getBurnthick();
					 dataFloat.setFloat(dataFloat.getIndex(),chtfloat);
					 ncfile.write("BURNTHICK", originY, dataFloat);

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

	public void setOutData(RegnOutData regnodp) {
		regnod = regnodp;
	};
	
}