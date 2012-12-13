package INPUT;

import java.io.File;
import java.io.IOException;

import ucar.ma2.Array;
import ucar.ma2.Index;
import ucar.nc2.NetcdfFile;
import ucar.nc2.Variable;

import DATA.ConstTime;
import DATA.DataGrid;
import TEMJNI.ModelData;

public class GridInputer {
	
	//all-grids
	
	Array grdidA;
	Array latA;
	Array lonA;
	Array topsoilA;
	Array botsoilA;

	Array friA;
	Array fseasonA;
	Array fsizeA;
	Array fyearA;

	Array clmidA;
	Array tairA;
	Array nirrA;
	Array precA;
	Array vapoA;

	public void init(ModelData md){
  
		  initLatlon(md.getJgrdinputdir());

		  initSoil(md.getJgrdinputdir());

		  String clmfile ="";
		  String firefile="";
		  if (!md.getRuneq()){
			  if (md.getRunsc()){     //sc run uses the same IDs system as 'tr', but use deferent files
				  firefile =md.getJgrdinputdir()+"fire_sc.nc";
				  clmfile  =md.getJgrdinputdir()+"climate_sc.nc";
			  } else {
				  firefile =md.getJgrdinputdir()+"fire_tr.nc";
				  clmfile  =md.getJgrdinputdir()+"climate_tr.nc";
			  }

		  }	else {
			  firefile =md.getJgrdinputdir()+"fire.nc";   //eq run uses aggregated (half degree resolution) driving data
			  clmfile  =md.getJgrdinputdir()+"climate.nc";
		  }

		  initFire(firefile);
		  initClimate(clmfile);

	};
	
	void initLatlon(String dir){
		String filename = dir +"latlon.nc";
		
		NetcdfFile ncfile = null;
		File ffile = new File(filename);
		if (ffile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);

				Variable var0 = ncfile.findVariable("GRDID");
				grdidA = var0.read();

				Variable var1 = ncfile.findVariable("LAT");
				latA = var1.read();

				Variable var2 = ncfile.findVariable("LON");
				lonA = var2.read();

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

	void initClimate(String dirfile){
		String filename = dirfile;
		
		NetcdfFile ncfile = null;
		File ffile = new File(filename);
		if (ffile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);

				Variable var3 = ncfile.findVariable("CLMID");
				clmidA = var3.read();

				Variable var4 = ncfile.findVariable("TAIR");
				tairA = var4.read();

				Variable var5 = ncfile.findVariable("NIRR");
				nirrA = var5.read();

				Variable var6 = ncfile.findVariable("PREC");
				precA = var6.read();

				Variable var7 = ncfile.findVariable("VAPO");
				vapoA = var7.read();

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

	void initSoil(String dir){
		String filename = dir +"soil.nc";

		NetcdfFile ncfile = null;
		File ffile = new File(filename);
		if (ffile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);

				Variable var2 = ncfile.findVariable("TOPSOIL");
				topsoilA = var2.read();

				Variable var3 = ncfile.findVariable("BOTSOIL");
				botsoilA = var3.read();

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
			System.exit(-1);
		}

	};

	void initFire(String dirfile){
		String filename = dirfile;
		
		NetcdfFile ncfile = null;
		File ffile = new File(filename);
		if (ffile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);
				Variable var1 = ncfile.findVariable("FRI");
				friA = var1.read();

				Variable var2 = ncfile.findVariable("YEAR");
				fyearA = var2.read();

				Variable var3 = ncfile.findVariable("SEASON");
				fseasonA = var3.read();

				Variable var4 = ncfile.findVariable("SIZE");
				fsizeA = var4.read();

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
			System.exit(-1);
		}
 
	};

	public int getGRDrecid(int grdid ){    //get recid (starts from 0) from grid id (grdid)
		Index ind = grdidA.getIndex();
		for (int i=0; i<grdidA.getSize(); i++) {
			if (grdidA.getInt(ind.set(i))==grdid) return i;
		}
		return -1;

	}; 

	public int getCLMrecid(int clmid ){    //get recid (starts from 0) from clm id (clmid)
		Index ind = clmidA.getIndex();
		for (int i=0; i<clmidA.getSize(); i++) {
			if (clmidA.getInt(ind.set(i))==clmid) return i;
		}
		return -1;

	}; 

	public void getGridData(DataGrid grd, int recid){
	  
	  	grd.lat = getLAT(recid);
	  	grd.lon = getLON(recid);
	  	grd.topsoil = getTOPSOIL(recid);
	  	grd.botsoil = getBOTSOIL(recid);
	    	
	  	grd.fri     = getFRI(recid);
	  	getFireSize(grd.fyear, grd.fseason, grd.fsize, recid);

	};

	public void getClmData(DataGrid grd, int recid){
		    
	  	grd.act_atm_drv_yr = tairA.getShape()[1];
	  	getClimate(grd.tair, grd.prec, grd.nirr, grd.vapo, recid);
	  	
	};

	float getLAT(int recid ){    //recid starts from 0
		Index ind = latA.getIndex();
		float lat = latA.getFloat(ind.set(recid));
		return lat;
	}; 

	float getLON(int recid){     //recid starts from 0
		Index ind = lonA.getIndex();
		float lon = lonA.getFloat(ind.set(recid));
		return lon;
	}; 

	int getTOPSOIL(int recid){   //recid starts from 0
		Index ind = topsoilA.getIndex();
		int topsoil = topsoilA.getInt(ind.set(recid));
		return topsoil;
	}; 


	int getBOTSOIL(int recid){   //recid starts from 0
		Index ind = botsoilA.getIndex();
		int botsoil = botsoilA.getInt(ind.set(recid));
		return botsoil;
	}; 

	void getClimate(float tair[], float prec[], float nirr[], 
			               float vapo[], int recid){     //recid starts from 0
			
		Index ind1 = tairA.getIndex();
		for (int iy = 0; iy < ConstTime.MAX_ATM_DRV_YR; iy++) {
			for (int im = 0; im < 12; im++) {
				int iyim =iy*12+im;
				tair[iyim] = tairA.getFloat(ind1.set(recid,iy,im));
			}
		}


		Index ind2 = nirrA.getIndex();
		for (int iy = 0; iy < ConstTime.MAX_ATM_DRV_YR; iy++) {
			for (int im = 0; im < 12; im++) {
				int iyim =iy*12+im;
				nirr[iyim] = nirrA.getFloat(ind2.set(recid,iy,im));
			}
		}

		Index ind3 = precA.getIndex();
		for (int iy = 0; iy < ConstTime.MAX_ATM_DRV_YR; iy++) {
			for (int im = 0; im < 12; im++) {
				int iyim =iy*12+im;
				prec[iyim] = precA.getFloat(ind3.set(recid,iy,im));
			}
		}

		Index ind4 = vapoA.getIndex();
		for (int iy = 0; iy < ConstTime.MAX_ATM_DRV_YR; iy++) {
			for (int im = 0; im < 12; im++) {
				int iyim =iy*12+im;
				vapo[iyim] = vapoA.getFloat(ind4.set(recid,iy,im));
			}
		}
	
	}; 

	int getFRI(int recid ){
		Index ind = friA.getIndex();
		return friA.getInt(ind.set(recid));
		
	}; 

	void getFireSize(int fyear[], int fseason[], int fsize[], int recid){     //recid starts from 0

		Index ind1 = fyearA.getIndex();
		for (int iy = 0; iy < ConstTime.MAX_FSIZE_DRV_YR; iy++) {
			fyear[iy] = fyearA.getInt(ind1.set(iy));
		}
			
		Index ind2 = fseasonA.getIndex();
		for (int iy = 0; iy < ConstTime.MAX_FSIZE_DRV_YR; iy++) {
			fseason[iy] = fseasonA.getInt(ind2.set(recid,iy));
		}

		Index ind3 = fsizeA.getIndex();
		for (int iy = 0; iy < ConstTime.MAX_FSIZE_DRV_YR; iy++) {
			fsize[iy] = fsizeA.getInt(ind3.set(recid,iy));
		}

	}; 

}
