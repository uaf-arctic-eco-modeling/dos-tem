package INPUT;

import java.io.File;
import java.io.IOException;

import ucar.ma2.Array;
import ucar.ma2.Index;
import ucar.nc2.NetcdfFile;
import ucar.nc2.Variable;

import TEMJNI.ModelData;

public class CohortInputer {

	//all cohort-level data sets
	Array vegidA;
	Array drgidA;
	
	Array grdidA;
	Array clmidA;
	Array eqchtidA;
	Array spchtidA; 
	Array eqchtid5spA;
	Array trchtidA; 
	Array spchtid5trA;
	
	//ids list in java arrays
	public int[] vegidlist;
	public int[] drgidlist;
	public int[] grdidlist;
	public int[] clmidlist;
	public int[] eqchtidlist;
	public int[] spchtidlist;
	public int[] eqid5splist;
	public int[] trchtidlist;
	public int[] spid5trlist;
	
	//one cohort-level data set will be done in cohort.java, 
	// but functions are defined here.
	
	public void init(ModelData md){

   		if(md.getRunsp() || md.getRuntr()){
  			initSpChtidFile(md.getJspchtinputdir());
	  	}
  
  		if(md.getRuntr()){
    		initTrChtidFile(md.getJtrchtinputdir());
    	}
  
  		initEqChtidFile(md.getJeqchtinputdir());
  		initVegetation(md.getJeqchtinputdir());
  		initDrainage(md.getJeqchtinputdir());
  		
  		getIDLIST(md);
  
  	}; 
  	
	public void initEqChtidFile(String dir){
		String filename = dir +"cohortid.nc";
		NetcdfFile ncfile = null;
		File spchtidfile = new File(filename);
		if (spchtidfile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);
				Variable eqchtidV = ncfile.findVariable("EQCHTID");
				eqchtidA = eqchtidV.read();

				Variable grdidV = ncfile.findVariable("GRDID");
				grdidA = grdidV.read();

				Variable clmidV = ncfile.findVariable("CLMID");
				clmidA = clmidV.read();

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
		} else {   //file not exist
			System.out.println("Input file: "+filename+" NOT existed");
			System.exit(-1);
		}
 	 
	};
  	
  	
	public void initVegetation(String dir){
		String filename = dir +"vegetation.nc";

		NetcdfFile ncfile = null;
		File vegfile = new File(filename);
		if (vegfile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);
				Variable vegidV = ncfile.findVariable("VEGID");
				vegidA = vegidV.read();

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
		} else {   //file not exist
			System.out.println("Input file: "+filename+" NOT existed");
		}
		 	 	
	};

	public void initDrainage(String dir){
		String filename = dir +"drainage.nc";
 	
		NetcdfFile ncfile = null;
		File drgfile = new File(filename);
		if (drgfile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);
				Variable drgidV = ncfile.findVariable("DRAINID");
				drgidA = drgidV.read();

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
		} else {   //file not exist
			System.out.println("Input file: "+filename+" NOT existed");
		}
 
	};

	public void initSpChtidFile(String dir){
		String filename = dir +"cohortid.nc";
		NetcdfFile ncfile = null;
		File spchtidfile = new File(filename);
		if (spchtidfile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);
				Variable spchtidV = ncfile.findVariable("SPCHTID");
				spchtidA = spchtidV.read();
				Variable eqchtidV = ncfile.findVariable("EQCHTID");
				eqchtid5spA = eqchtidV.read();
				
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
		} else {   //file not exist
			System.out.println("Input file: "+filename+" NOT existed");
			System.exit(-1);
		}
 	 
	};

	public void initTrChtidFile(String dir){
		String filename = dir +"cohortid.nc";

		NetcdfFile ncfile = null;
		File trchtidfile = new File(filename);
		if (trchtidfile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);
				Variable trchtidV = ncfile.findVariable("TRCHTID");
				trchtidA = trchtidV.read();
				Variable spchtidV = ncfile.findVariable("SPCHTID");
				spchtid5trA = spchtidV.read();
				
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
		} else {   //file not exist
			System.out.println("Input file: "+filename+" NOT existed");
			System.exit(-1);
		}
 	
 	};

 	//cid - record id (starting from 0), NOT chtid (starting from 1)
	public int getEqRecid(int chtid){
		for (int i=0; i<eqchtidlist.length; i++) {
			if (eqchtidlist[i]==chtid) return i;
		}
		return -1;
	};

	public int getSpRecid(int chtid){
		for (int i=0; i<spchtidlist.length; i++) {
			if (spchtidlist[i]==chtid) return i;
		}
		return -1;
	};

	public int getTrRecid(int chtid){
		for (int i=0; i<trchtidlist.length; i++) {
			if (trchtidlist[i]==chtid) return i;
		}
		return -1;
	};

	//note: the cid is the record id in the following
	public int getGRDID(int cid){
		Index grdidi = grdidA.getIndex();
		int grdid = grdidA.getInt(grdidi.set(cid));
		return grdid;
	};

	public int getCLMID(int cid){
		Index clmidi = clmidA.getIndex();
		int clmid = clmidA.getInt(clmidi.set(cid));
		return clmid;
	};

	public int getVegetation(int cid){
		Index vegidi = vegidA.getIndex();
		int vegtype = vegidA.getInt(vegidi.set(cid));
		return vegtype;
	};

	public int getDrainage(int cid){
		Index drgidi = drgidA.getIndex();
		int drgtype = drgidA.getInt(drgidi.set(cid));
		return drgtype;
	};

	public int getEqchtid5SpFile(int spcid){
		Index eqchtidi = eqchtid5spA.getIndex();
		int eqchtid = eqchtid5spA.getInt(eqchtidi.set(spcid));
		return eqchtid;
	};

	public int getSpchtid5TrFile(int trcid){
		Index spchtidi = spchtid5trA.getIndex();
		int spchtid = spchtid5trA.getInt(spchtidi.set(trcid));
		return spchtid;
	};
	
	private void getIDLIST(ModelData md){
		
		Index grdidi = grdidA.getIndex();
		grdidlist = new int[(int)grdidi.getSize()];
		for (int i=0; i<grdidi.getSize(); i++) {
			grdidlist[i] = grdidA.getInt(grdidi.set(i));
		}
		Index clmidi = clmidA.getIndex();
		clmidlist = new int[(int)clmidi.getSize()];
		for (int i=0; i<clmidi.getSize(); i++) {
			clmidlist[i] = clmidA.getInt(clmidi.set(i));
		}
		Index eqidi = eqchtidA.getIndex();
		eqchtidlist = new int[(int)eqidi.getSize()];
		for (int i=0; i<eqidi.getSize(); i++) {
			eqchtidlist[i] = eqchtidA.getInt(eqidi.set(i));
		}
		Index vegidi = vegidA.getIndex();
		vegidlist = new int[(int)vegidi.getSize()];
		for (int i=0; i<vegidi.getSize(); i++) {
			vegidlist[i] = vegidA.getInt(vegidi.set(i));
		}
		Index drgidi = drgidA.getIndex();
		drgidlist = new int[(int)drgidi.getSize()];
		for (int i=0; i<drgidi.getSize(); i++) {
			drgidlist[i] = drgidA.getInt(drgidi.set(i));
		}

   		if(md.getRunsp() || md.getRuntr()){		
   			Index spidi = spchtidA.getIndex();
   			spchtidlist = new int[(int)spidi.getSize()];
   			for (int i=0; i<spidi.getSize(); i++) {
   				spchtidlist[i] = spchtidA.getInt(spidi.set(i));
   			}
   			Index eqid5spi = eqchtid5spA.getIndex();
   			eqid5splist = new int[(int)eqid5spi.getSize()];
   			for (int i=0; i<eqid5spi.getSize(); i++) {
   				eqid5splist[i] = eqchtid5spA.getInt(eqid5spi.set(i));
   			}
   		}

   		if(md.getRuntr()){
   			Index tridi = trchtidA.getIndex();
   			trchtidlist = new int[(int)tridi.getSize()];
   			for (int i=0; i<tridi.getSize(); i++) {
   				trchtidlist[i] = trchtidA.getInt(tridi.set(i));
   			}
   			Index spid5tri = spchtid5trA.getIndex();
   			spid5trlist = new int[(int)spid5tri.getSize()];
   			for (int i=0; i<spid5tri.getSize(); i++) {
   				spid5trlist[i] = spchtid5trA.getInt(spid5tri.set(i));
   			}
   		}
	};

}
