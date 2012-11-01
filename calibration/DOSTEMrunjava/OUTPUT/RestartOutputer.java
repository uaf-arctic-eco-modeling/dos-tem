package OUTPUT;
/*
 * 
*/

//for netcdf file operation
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import ucar.ma2.*;
import ucar.nc2.*;

import TEMJNI.ModelData;
import TEMJNI.RestartData;

import DATA.ConstLayer;

public class RestartOutputer {
	
	String restartfn="";
	RestartData resod = new RestartData();
	
	public void init(ModelData md){
	 	
		restartfn = md.getJoutputdir()+"restart-"+md.getJrunstages()+".nc";
	
		try {
			NetcdfFileWriteable resFile=NetcdfFileWriteable.createNew(restartfn, false);
		
			Dimension chtD = resFile.addUnlimitedDimension("CHTID");
			Dimension snowlayerD = resFile.addDimension("SNOWLAYER", ConstLayer.MAX_SNW_LAY);
			Dimension soillayerD = resFile.addDimension("SOILLAYER", ConstLayer.MAX_SOI_LAY);
			Dimension minlayerD  = resFile.addDimension("MINLAYER", ConstLayer.MAX_MIN_LAY);
			Dimension rocklayerD = resFile.addDimension("ROCKLAYER", ConstLayer.MAX_ROC_LAY);
			Dimension frontlayerD= resFile.addDimension("FRONTLAYER", ConstLayer.MAX_NUM_FNT);
			Dimension meanyearD  = resFile.addDimension("MEANYEAR", 10);

			ArrayList<Dimension> dimCht = new ArrayList<Dimension>();
			dimCht.add(chtD);
			ArrayList<Dimension> dimSnowL = new ArrayList<Dimension>();
			dimSnowL.add(chtD); dimSnowL.add(snowlayerD);
			ArrayList<Dimension> dimSoilL = new ArrayList<Dimension>();
			dimSoilL.add(chtD); dimSoilL.add(soillayerD);
			ArrayList<Dimension> dimMinL = new ArrayList<Dimension>();
			dimMinL.add(chtD); dimMinL.add(minlayerD);
			ArrayList<Dimension> dimRockL = new ArrayList<Dimension>();
			dimRockL.add(chtD); dimRockL.add(rocklayerD);
			ArrayList<Dimension> dimFrontL = new ArrayList<Dimension>();
			dimFrontL.add(chtD); dimFrontL.add(frontlayerD);
			ArrayList<Dimension> dimMeanY = new ArrayList<Dimension>();
			dimMeanY.add(chtD); dimMeanY.add(meanyearD);
		
		//output variables for restart of cohort(s)
			resFile.addVariable("CHTID", DataType.INT, dimCht);
			resFile.addVariable("ERRCODE", DataType.INT, dimCht);
    
			resFile.addVariable("TSsnow", DataType.DOUBLE, dimSnowL);
			resFile.addVariable("DZsnow", DataType.DOUBLE, dimSnowL);
			resFile.addVariable("LIQsnow", DataType.DOUBLE, dimSnowL);
			resFile.addVariable("ICEsnow", DataType.DOUBLE, dimSnowL);
			resFile.addVariable("AGEsnow", DataType.DOUBLE, dimSnowL);
			resFile.addVariable("RHOsnow", DataType.DOUBLE, dimSnowL);
 
			resFile.addVariable("TSsoil", DataType.DOUBLE, dimSoilL);
			resFile.addVariable("DZsoil", DataType.DOUBLE, dimSoilL);
			resFile.addVariable("LIQsoil", DataType.DOUBLE, dimSoilL);
			resFile.addVariable("ICEsoil", DataType.DOUBLE, dimSoilL);
			resFile.addVariable("FROZENsoil", DataType.INT, dimSoilL);
			resFile.addVariable("NONCsoil", DataType.DOUBLE, dimSoilL);
			resFile.addVariable("REACsoil", DataType.DOUBLE, dimSoilL);
			resFile.addVariable("TYPEsoil", DataType.INT, dimSoilL);

			resFile.addVariable("TYPEmin", DataType.INT, dimMinL);
        
			resFile.addVariable("TSrock", DataType.DOUBLE, dimRockL);
			resFile.addVariable("DZrock", DataType.DOUBLE, dimRockL);
   
			resFile.addVariable("frontZ", DataType.DOUBLE, dimFrontL);
			resFile.addVariable("frontFT", DataType.INT, dimFrontL);
    
			resFile.addVariable("SOLN", DataType.DOUBLE, dimCht);
			resFile.addVariable("AVLN", DataType.DOUBLE, dimCht);
			resFile.addVariable("WDEBRIS", DataType.DOUBLE, dimCht);
			resFile.addVariable("STRN", DataType.DOUBLE, dimCht);
			resFile.addVariable("STON", DataType.DOUBLE, dimCht);
			resFile.addVariable("VEGC", DataType.DOUBLE, dimCht);
			resFile.addVariable("DEADC", DataType.DOUBLE, dimCht);
			resFile.addVariable("DEADN", DataType.DOUBLE, dimCht);
			resFile.addVariable("PRVEETMX", DataType.DOUBLE, dimCht);
			resFile.addVariable("PRVPETMX", DataType.DOUBLE, dimCht);
			resFile.addVariable("FOLIAGEMX", DataType.DOUBLE, dimCht);
			resFile.addVariable("LAI", DataType.DOUBLE, dimCht);
   	   	
			resFile.addVariable("UNNORMLEAF", DataType.DOUBLE, dimCht);
			resFile.addVariable("PRVUNNORMLEAFMX", DataType.DOUBLE, dimCht);
			resFile.addVariable("PRVTOPT", DataType.DOUBLE, dimCht);
			resFile.addVariable("C2N", DataType.DOUBLE, dimCht);
			resFile.addVariable("KDFIB", DataType.DOUBLE, dimCht);
			resFile.addVariable("KDHUM", DataType.DOUBLE, dimCht);
			resFile.addVariable("KDMIN", DataType.DOUBLE, dimCht);
			resFile.addVariable("KDSLOW", DataType.DOUBLE, dimCht);
	
			resFile.addVariable("YSF", DataType.INT, dimCht);
			resFile.addVariable("BURNEDN", DataType.DOUBLE, dimCht);

			resFile.addVariable("TOPTA", DataType.DOUBLE, dimMeanY);
			resFile.addVariable("EETMXA", DataType.DOUBLE, dimMeanY);
			resFile.addVariable("PETMXA", DataType.DOUBLE, dimMeanY);
			resFile.addVariable("UNNORMLEAFMXA", DataType.DOUBLE, dimMeanY);

			try {
				resFile.create();
				resFile.close();
			}catch (IOException e) {
				System.err.println("Error in creating file"+resFile.getLocation()+"\n");
			}

			resod.reinitValue();
			
		} catch (Exception e) {
			System.err.println("Error in creating restart.nc file:"+e+"\n");			
		}
	};

	public void outputVariables(int chtcount){

		 String ncfilename = restartfn;
		 File f = new File(ncfilename);
		 if (f.exists()) {
			 try {
				 NetcdfFileWriteable ncfile = NetcdfFileWriteable.openExisting(ncfilename, true);
		 
				 try {			
					 Array AchtI  = Array.factory(DataType.INT, new int[] {1});
					 Array AchtD  = Array.factory(DataType.DOUBLE, new int[] {1});
					 int[] origin = new int[] {0}; origin[0] = chtcount; 
					 int datachtI = 0;
					 double datachtD = 0.0;
					 
					 int[] origin2 = new int[] {0, 0};  
					 origin2[0] = chtcount;
					 ArrayDouble ADsnow  = new ArrayDouble.D2(1, ConstLayer.MAX_SNW_LAY);
					 Index ilsnow = ADsnow.getIndex();
					 double [] dataDsnow = new double[ConstLayer.MAX_SNW_LAY];			

					 ArrayDouble ADsoil  = new ArrayDouble.D2(1, ConstLayer.MAX_SOI_LAY);
					 Index ilsoil = ADsoil.getIndex();
					 double [] dataDsoil = new double[ConstLayer.MAX_SOI_LAY];			
					 ArrayInt AIsoil  = new ArrayInt.D2(1, ConstLayer.MAX_SOI_LAY);
					 Index ilsoili = AIsoil.getIndex();
					 int [] dataIsoil = new int[ConstLayer.MAX_SOI_LAY];			
					 
					 ArrayInt ADmin  = new ArrayInt.D2(1, ConstLayer.MAX_MIN_LAY);
					 Index ilmin = ADmin.getIndex();
					 int [] dataImin = new int[ConstLayer.MAX_MIN_LAY];			

					 ArrayDouble ADrock  = new ArrayDouble.D2(1, ConstLayer.MAX_ROC_LAY);
					 Index ilrock = ADrock.getIndex();
					 double [] dataDrock = new double[ConstLayer.MAX_ROC_LAY];			

					 ArrayDouble ADfront  = new ArrayDouble.D2(1, ConstLayer.MAX_NUM_FNT);
					 Index ilfront = ADfront.getIndex();
					 double [] dataDfront = new double[ConstLayer.MAX_NUM_FNT];			
					 ArrayInt AIfront  = new ArrayInt.D2(1, ConstLayer.MAX_NUM_FNT);
					 Index ilfronti = AIfront.getIndex();
					 int [] dataIfront = new int[ConstLayer.MAX_NUM_FNT];			

					 ArrayDouble ADymean  = new ArrayDouble.D2(1, 10);
					 Index iymean = ADymean.getIndex();
					 double [] dataDymean = new double[10];			
 
					 //write values to the netcdf file
					 datachtI =resod.getChtid();
					 AchtI.setInt(AchtI.getIndex(),datachtI);
					 ncfile.write("CHTID", origin, AchtI);

					 datachtI =errorChecking();
					 AchtI.setInt(AchtI.getIndex(),datachtI);
					 ncfile.write("ERRCODE", origin, AchtI);

					 //snow variables
					 dataDsnow =resod.getTSsnow();
					 for (int il=0; il<ConstLayer.MAX_SNW_LAY; il++){
						 ADsnow.setDouble(ilsnow.set(0,il),dataDsnow[il]);
					 }
					 ncfile.write("TSsnow", origin2, ADsnow);

					 dataDsnow =resod.getDZsnow();
					 for (int il=0; il<ConstLayer.MAX_SNW_LAY; il++){
						 ADsnow.setDouble(ilsnow.set(0,il),dataDsnow[il]);
					 }
					 ncfile.write("DZsnow", origin2, ADsnow);

					 dataDsnow =resod.getLIQsnow();
					 for (int il=0; il<ConstLayer.MAX_SNW_LAY; il++){
						 ADsnow.setDouble(ilsnow.set(0,il),dataDsnow[il]);
					 }
					 ncfile.write("LIQsnow", origin2, ADsnow);

					 dataDsnow =resod.getICEsnow();
					 for (int il=0; il<ConstLayer.MAX_SNW_LAY; il++){
						 ADsnow.setDouble(ilsnow.set(0,il),dataDsnow[il]);
					 }
					 ncfile.write("ICEsnow", origin2, ADsnow);

					 dataDsnow =resod.getAGEsnow();
					 for (int il=0; il<ConstLayer.MAX_SNW_LAY; il++){
						 ADsnow.setDouble(ilsnow.set(0,il),dataDsnow[il]);
					 }
					 ncfile.write("AGEsnow", origin2, ADsnow);

					 dataDsnow =resod.getRHOsnow();
					 for (int il=0; il<ConstLayer.MAX_SNW_LAY; il++){
						 ADsnow.setDouble(ilsnow.set(0,il),dataDsnow[il]);
					 }
					 ncfile.write("RHOsnow", origin2, ADsnow);
					 
					 //soil variables
					 dataDsoil =resod.getTSsoil();
					 for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
						 ADsoil.setDouble(ilsoil.set(0,il),dataDsoil[il]);
					 }
					 ncfile.write("TSsoil", origin2, ADsoil);
				 
					 dataDsoil =resod.getDZsoil();
					 for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
						 ADsoil.setDouble(ilsoil.set(0,il),dataDsoil[il]);
					 }
					 ncfile.write("DZsoil", origin2, ADsoil);
					 
					 dataDsoil =resod.getLIQsoil();
					 for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
						 ADsoil.setDouble(ilsoil.set(0,il),dataDsoil[il]);
					 }
					 ncfile.write("LIQsoil", origin2, ADsoil);

					 dataDsoil =resod.getICEsoil();
					 for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
						 ADsoil.setDouble(ilsoil.set(0,il),dataDsoil[il]);
					 }
					 ncfile.write("ICEsoil", origin2, ADsoil);

					 dataDsoil =resod.getNONCsoil();
					 for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
						 ADsoil.setDouble(ilsoil.set(0,il),dataDsoil[il]);
					 }
					 ncfile.write("NONCsoil", origin2, ADsoil);

					 dataDsoil =resod.getREACsoil();
					 for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
						 ADsoil.setDouble(ilsoil.set(0,il),dataDsoil[il]);
					 }
					 ncfile.write("REACsoil", origin2, ADsoil);

					 dataIsoil =resod.getFROZENsoil();             //int 
					 for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
						 AIsoil.setInt(ilsoili.set(0,il),dataIsoil[il]);
					 }
					 ncfile.write("FROZENsoil", origin2, AIsoil);

					 dataIsoil =resod.getTYPEsoil();
					 for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
						 AIsoil.setInt(ilsoili.set(0,il),dataIsoil[il]);
					 }
					 ncfile.write("TYPEsoil", origin2, AIsoil);

					 //mineral layer
					 dataImin =resod.getTYPEmin();
					 for (int il=0; il<ConstLayer.MAX_MIN_LAY; il++){
						 ADmin.setInt(ilmin.set(0,il),dataImin[il]);
					 }
					 ncfile.write("TYPEmin", origin2, ADmin);

					 //rock layer
					 dataDrock =resod.getTSrock();
					 for (int il=0; il<ConstLayer.MAX_ROC_LAY; il++){
						 ADrock.setDouble(ilrock.set(0,il),dataDrock[il]);
					 }
					 ncfile.write("TSrock", origin2, ADrock);

					 dataDrock =resod.getDZrock();
					 for (int il=0; il<ConstLayer.MAX_ROC_LAY; il++){
						 ADrock.setDouble(ilrock.set(0,il),dataDrock[il]);
					 }
					 ncfile.write("DZrock", origin2, ADrock);

				     //front
					 dataDfront =resod.getFrontZ();
					 for (int il=0; il<ConstLayer.MAX_NUM_FNT; il++){
						 ADfront.setDouble(ilfront.set(0,il),dataDfront[il]);
					 }
					 ncfile.write("frontZ", origin2, ADfront);

					 dataIfront =resod.getFrontFT();
					 for (int il=0; il<ConstLayer.MAX_NUM_FNT; il++){
						 AIfront.setInt(ilfronti.set(0,il),dataIfront[il]);
					 }
					 ncfile.write("frontFT", origin2, AIfront);
				    
					 //non-layed variables
					 datachtD =resod.getSoln();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("SOLN", origin, AchtD);

					 datachtD =resod.getAvln();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("AVLN", origin, AchtD);

					 datachtD =resod.getWdebris();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("WDEBRIS", origin, AchtD);

					 datachtD =resod.getStrn();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("STRN", origin, AchtD);

					 datachtD =resod.getSton();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("STON", origin, AchtD);

					 datachtD =resod.getVegc();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("VEGC", origin, AchtD);

					 datachtD =resod.getDeadc();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("DEADC", origin, AchtD);

					 datachtD =resod.getDeadn();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("DEADN", origin, AchtD);

					 datachtD =resod.getPrveetmx();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("PRVEETMX", origin, AchtD);

					 datachtD =resod.getPrvpetmx();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("PRVPETMX", origin, AchtD);
					 
					 datachtD =resod.getFoliagemx();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("FOLIAGEMX", origin, AchtD);

					 datachtD =resod.getLai();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("LAI", origin, AchtD);

					 datachtD =resod.getUnnormleaf();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("UNNORMLEAF", origin, AchtD);

					 datachtD =resod.getPrvunnormleafmx();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("PRVUNNORMLEAFMX", origin, AchtD);

					 datachtD =resod.getPrvtopt();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("PRVTOPT", origin, AchtD);

					 datachtD =resod.getC2n();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("C2N", origin, AchtD);

					 datachtD =resod.getKdfib();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("KDFIB", origin, AchtD);

					 datachtD =resod.getKdhum();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("KDHUM", origin, AchtD);

					 datachtD =resod.getKdmin();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("KDMIN", origin, AchtD);

					 datachtD =resod.getKdslow();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("KDSLOW", origin, AchtD);

					 datachtI =resod.getYsf();
					 AchtI.setDouble(AchtI.getIndex(),datachtI);
					 ncfile.write("YSF", origin, AchtI);

					 datachtD =resod.getBurnedn();
					 AchtD.setDouble(AchtD.getIndex(),datachtD);
					 ncfile.write("BURNEDN", origin, AchtD);

					 dataDymean =resod.getToptA();
					 for (int iy=0; iy<10; iy++){
						 ADymean.setDouble(iymean.set(0,iy),dataDymean[iy]);
					 }
					 ncfile.write("TOPTA", origin2, ADymean);
					 
					 dataDymean =resod.getEetmxA();
					 for (int iy=0; iy<10; iy++){
						 ADymean.setDouble(iymean.set(0,iy),dataDymean[iy]);
					 }
					 ncfile.write("EETMXA", origin2, ADymean);

					 dataDymean =resod.getPetmxA();
					 for (int iy=0; iy<10; iy++){
						 ADymean.setDouble(iymean.set(0,iy),dataDymean[iy]);
					 }
					 ncfile.write("PETMXA", origin2, ADymean);

					 dataDymean =resod.getUnnormleafmxA();
					 for (int iy=0; iy<10; iy++){
						 ADymean.setDouble(iymean.set(0,iy),dataDymean[iy]);
					 }
					 ncfile.write("UNNORMLEAFMXA", origin2, ADymean);

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

	private int errorChecking(){
		int errcode = 0;
/*		
		for(int il =0;il<DATA.ConstLayer.MAX_SNW_LAY; il++){
			if (isnan(resod.getTSsnow()) || isinf(resod.getTSsnow[il])) errcode = -1;	
			if (isnan(resod.getDZsnow[il]) || isinf(resod.getDZsnow[il])) errcode = -1;	
			if (isnan(resod.getLIQsnow[il]) || isinf(resod.getLIQsnow[il])) errcode = -1;	
			if (isnan(resod.getICEsnow[il]) || isinf(resod.getICEsnow[il])) errcode = -1;	
			if (isnan(resod.getAGEsnow[il]) || isinf(resod.getAGEsnow[il])) errcode = -1;	
			if (isnan(resod.getRHOsnow[il]) || isinf(resod.getRHOsnow[il])) errcode = -1;	
		}
		
		for(int il =0;il<DATA.ConstLayer.MAX_SOI_LAY; il++){
			if (isnan(resod.getTSsoil[il]) || isinf(resod.getTSsoil[il])) errcode = -1;	
			if (isnan(resod.getDZsoil[il]) || isinf(resod.getDZsoil[il])) errcode = -1;	
			if (isnan(resod.getLIQsoil[il]) || isinf(resod.getLIQsoil[il])) errcode = -1;	
			if (isnan(resod.getICEsoil[il]) || isinf(resod.getICEsoil[il])) errcode = -1;	
			if (isnan(resod.getFROZENsoil[il]) || isinf(resod.getFROZENsoil[il])) errcode = -1;	
			if (isnan(resod.getTYPEsoil[il]) || isinf(resod.getTYPEsoil[il])) errcode = -1;	
			if (isnan(resod.getNONCsoil[il]) || isinf(resod.getNONCsoil[il])) errcode = -1;	
			if (isnan(resod.getREACsoil[il]) || isinf(resod.getREACsoil[il])) errcode = -1;	
		}
		
		for(int il =0;il<DATA.ConstLayer.MAX_MIN_LAY; il++){
			if (isnan(resod.getTYPEmin[il]) || isinf(resod.getTYPEmin[il])) errcode = -1;	
		}
	   
		for(int il =0;il<DATA.ConstLayer.MAX_ROC_LAY; il++){
			if (isnan(resod.getTSrock[il]) || isinf(resod.getTSrock[il])) errcode = -1;	
			if (isnan(resod.getDZrock[il]) || isinf(resod.getDZrock[il])) errcode = -1;	
		}

		for(int il =0;il<DATA.ConstLayer.MAX_NUM_FNT; il++){
			if (isnan(resod.getfrontZ[il]) || isinf(resod.getfrontZ[il])) errcode = -1;	
			if (isnan(resod.getfrontFT[il]) || isinf(resod.getfrontFT[il])) errcode = -1;	
		}
	     
	    for(int i=0; i<10; i++){
			if (isnan(resod.gettoptA[i]) || isinf(resod.gettoptA[i])) errcode = -1;	
			if (isnan(resod.geteetmxA[i]) || isinf(resod.geteetmxA[i])) errcode = -1;	
			if (isnan(resod.getpetmxA[i]) || isinf(resod.getpetmxA[i])) errcode = -1;	
			if (isnan(resod.getunnormleafmxA[i]) || isinf(resod.getunnormleafmxA[i])) errcode = -1;	
	    }
	     
		if (isnan(resod.getsoln) || isinf(resod.getsoln)) errcode = -1;	
		if (isnan(resod.getavln) || isinf(resod.getavln)) errcode = -1;	
		if (isnan(resod.getwdebris) || isinf(resod.getwdebris)) errcode = -1;	
		if (isnan(resod.getstrn) || isinf(resod.getstrn)) errcode = -1;	
		if (isnan(resod.getston) || isinf(resod.getston)) errcode = -1;	
		if (isnan(resod.getvegc) || isinf(resod.getvegc)) errcode = -1;	
		if (isnan(resod.getdeadc) || isinf(resod.getdeadc)) errcode = -1;	
		if (isnan(resod.getdeadn) || isinf(resod.getdeadn)) errcode = -1;	
		if (isnan(resod.getprveetmx) || isinf(resod.getprveetmx)) errcode = -1;	
		if (isnan(resod.getprvpetmx) || isinf(resod.getprvpetmx)) errcode = -1;	
		if (isnan(resod.getunnormleaf) || isinf(resod.getunnormleaf)) errcode = -1;	
		if (isnan(resod.getprvunnormleafmx) || isinf(resod.getprvunnormleafmx)) errcode = -1;	
		if (isnan(resod.getprvtopt) || isinf(resod.getprvtopt)) errcode = -1;	
		if (isnan(resod.getc2n) || isinf(resod.getc2n)) errcode = -1;	
		if (isnan(resod.getkdfib) || isinf(resod.getkdfib)) errcode = -1;	
		if (isnan(resod.getkdhum) || isinf(resod.getkdhum)) errcode = -1;	
		if (isnan(resod.getkdmin) || isinf(resod.getkdmin)) errcode = -1;	
		if (isnan(resod.getkdlitter) || isinf(resod.getkdlitter)) errcode = -1;	
		if (isnan(resod.getfoliagemx) || isinf(resod.getfoliagemx)) errcode = -1;	
		if (isnan(resod.getysf) || isinf(resod.getysf)) errcode = -1;	
		if (isnan(resod.getburnedn) || isinf(resod.getburnedn)) errcode = -1;
		if (isnan(resod.getlai) || isinf(resod.getlai)) errcode = -1;	
*/
		return errcode;
	};

	public void setRestartData(RestartData resodp){
		resod = resodp;
	};

}
