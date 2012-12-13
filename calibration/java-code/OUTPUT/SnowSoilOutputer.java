package OUTPUT;
/*
 * 
*/

//for netcdf file operation
import java.io.File;
import java.io.IOException;

import ucar.ma2.*;
import ucar.nc2.*;

import TEMJNI.SnowSoilOutData;
import DATA.ConstTime;
import DATA.ConstLayer;

public class SnowSoilOutputer {
		  	 
	SnowSoilOutData sslod = new SnowSoilOutData();

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
					 
					 ArrayFloat dataML  = new ArrayFloat.D3(1, ConstTime.MINY, ConstLayer.MAX_OUT_SOI);
					 Index imb = dataML.getIndex();
					 int[] mlorigin = new int[] {0, 0, 0};  		
					 mlorigin[0] = yrcnt;
			 
					 //ground (soil-snow) system outputs
					 mdata =sslod.getGrowpct();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("GROWPCT", morigin, dataM);

					 mdata =sslod.getOrgn();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("ORGN", morigin, dataM);

					 mdata =sslod.getAvln();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("AVLN", morigin, dataM);

					 mdata =sslod.getNimmob();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("NIMMOB", morigin, dataM);

					 mdata =sslod.getNetnmin();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("NETNMIN", morigin, dataM);

					 mdata =sslod.getNlost();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("NLOST", morigin, dataM);

					 mdata =sslod.getReacsum();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("REACSUM", morigin, dataM);

					 mdata =sslod.getNoncsum();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("NONCSUM", morigin, dataM);

					 mdata =sslod.getSninfl();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("SNINFL", morigin, dataM);

					 mdata =sslod.getSevap();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("SEVAP", morigin, dataM);

					 mdata =sslod.getSsubl();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("SSUBL", morigin, dataM);

					 mdata =sslod.getMossdz();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("MOSSDZ", morigin, dataM);

					 mdata =sslod.getShlwdz();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("SHLWDZ", morigin, dataM);

					 mdata =sslod.getDeepdz();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("DEEPDZ", morigin, dataM);

					 mdata =sslod.getWatertab();
					 for (int im=0; im<ConstTime.MINY; im++){
						 dataM.setFloat(ima.set(0,im),mdata[im]);
					 }
					 ncfile.write("WATERTAB", morigin, dataM);

					 //3-D data
					 mdata =sslod.getTs1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("TS", mlorigin, dataML);

					 mdata =sslod.getLiq1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("LIQVWC", mlorigin, dataML);

					 mdata =sslod.getVwc1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("VWC", mlorigin, dataML);
					 
					 mdata =sslod.getIce1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("ICEVWC", mlorigin, dataML);

					 mdata =sslod.getDz1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("DZ", mlorigin, dataML);

					 mdata =sslod.getZ1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("Z", mlorigin, dataML);

					 mdata =sslod.getPor1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("PORO", mlorigin, dataML);

					 mdata =sslod.getType1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("TYPE", mlorigin, dataML);

					 mdata =sslod.getReac1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("REAC", mlorigin, dataML);

					 mdata =sslod.getNonc1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("NONC", mlorigin, dataML);

					 mdata =sslod.getRrh1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("RRH", mlorigin, dataML);

					 mdata =sslod.getNrh1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("NRH", mlorigin, dataML);

					 mdata =sslod.getRhmoist1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("RHMOIST", mlorigin, dataML);

					 mdata =sslod.getRhq101D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("RHQ10", mlorigin, dataML);

					 mdata =sslod.getKsoil1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("KSOIL", mlorigin, dataML);

					 mdata =sslod.getKdl1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("KDL", mlorigin, dataML);
					 
					 mdata =sslod.getKdr1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("KDR", mlorigin, dataML);

					 mdata =sslod.getKdn1D();     //month-layered data
					 for (int im=0; im<ConstTime.MINY; im++){
					 	for (int il=0; il<ConstLayer.MAX_OUT_SOI; il++) {
						 dataML.setFloat(imb.set(0, im, il),mdata[im*ConstLayer.MAX_OUT_SOI+il]);
					 	}
					 }
					 ncfile.write("KDN", mlorigin, dataML);

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
					 int[] originY = new int[] {0}; originY[0] = yrcnt; 
					 float ydata = 0.0f;

					 //ground (soil-snow) system outputs
					 ydata =sslod.getYrliqsum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("LIQSUM", originY, dataY);
					 
					 ydata =sslod.getYricesum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("ICESUM", originY, dataY);

					 ydata =sslod.getYrreacsum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("REACSUM", originY, dataY);

					 ydata =sslod.getYrnoncsum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("NONCSUM", originY, dataY);

					 ydata =sslod.getYrshlwcsum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("SHLWCSUM", originY, dataY);

					 ydata =sslod.getYrdeepcsum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("DEEPCSUM", originY, dataY);

					 ydata =sslod.getYrminecsum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("MINECSUM", originY, dataY);

					 ydata =sslod.getYrorgn();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("ORGN", originY, dataY);

					 ydata =sslod.getYravln();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("AVLN", originY, dataY);

					 ydata =sslod.getYrtsave();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("TSAVE", originY, dataY);

					 ydata =sslod.getYrsevap();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("SEVAP", originY, dataY);

					 ydata =sslod.getYrqdrain();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("QDRAIN", originY, dataY);

					 ydata =sslod.getYrqover();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("QOVER", originY, dataY);

					 ydata =sslod.getYrssubl();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("SSUBL", originY, dataY);

					 ydata =sslod.getYrrrhsum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("RRHSUM", originY, dataY);

					 ydata =sslod.getYrnrhsum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("NRHSUM", originY, dataY);

					 ydata =sslod.getYrnetnmin();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("NETNMIN", originY, dataY);

					 ydata =sslod.getYrsnuptake();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("SNUPTAKE", originY, dataY);

					 ydata =sslod.getYrperm();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("PERMAFROST", originY, dataY);

					 ydata =sslod.getYrald();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("ALD", originY, dataY);

					 ydata =sslod.getYrwatertab();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("WATERTAB", originY, dataY);

					 ydata =sslod.getYrmossdz();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("MOSSDZ", originY, dataY);

					 ydata =sslod.getYrshlwdz();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("SHLWDZ", originY, dataY);

					 ydata =sslod.getYrdeepdz();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("DEEPDZ", originY, dataY);

					 ydata =sslod.getYrmossnum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("MOSSNUM", originY, dataY);
					 
					 ydata =sslod.getYrshlwnum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("SHLWNUM", originY, dataY);

					 ydata =sslod.getYrdeepnum();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("DEEPNUM", originY, dataY);

					 ydata =sslod.getYrburnthick();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("BURNTHICK", originY, dataY);

					 ydata =sslod.getYrburnsoilc();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("BURNSOILC", originY, dataY);
					 
					 ydata =sslod.getYrburnsoiln();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("BURNSOILN", originY, dataY);
					 
					 ydata =sslod.getYrorgnreturn();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("ORGNRETURN", originY, dataY);
					 
					 ydata =sslod.getYrwdebris();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("WDEBRIS", originY, dataY);
					 
					 ydata =sslod.getYrwdrh();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("WDRH", originY, dataY);
					 
					 ydata =sslod.getYrninput();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("NSOURCE", originY, dataY);

					 ydata =sslod.getYrnlost();
					 dataY.setFloat(dataY.getIndex(),ydata);
					 ncfile.write("NLOSS", originY, dataY);
					 
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
   
		sslod.setYrliqsum(0); //yrliqsum =0.;
		sslod.setYricesum(0); //sslod->yricesum=0.;
		sslod.setYrreacsum(0); //sslod->yrreacsum =0.;
		sslod.setYrnoncsum(0); //sslod->yrnoncsum =0.;	
		sslod.setYrtsave(0); //sslod->yrtsave =0.;  
	}
	
	 public void setOutdata(SnowSoilOutData outdata){
		 sslod = outdata;
	 };	

}