package INPUT;

import java.io.File;
import java.io.IOException;

import ucar.ma2.Array;
import ucar.ma2.Index;
import ucar.nc2.NetcdfFile;
import ucar.nc2.Variable;

import DATA.ConstLayer;
import DATA.DataSitein;

public class SiteinInputer {

	//(multiple) sitein data arrays
	Array ysfA;
	Array laiA;
	Array vegcA;
	Array vegnA;
	Array mossthickA;
	Array fibthickA;
	Array humthickA;
	Array soilcA;
	Array fibcA;
	Array humcA;
	Array orgnA;
	Array avlnA;
	Array mintypeA;
	Array initzA;
	Array initstA;
	Array initsmA;
	
	public void getSiteinData(DataSitein siteindata, int cid, String siteinfile){
		
		try {
			String filename = siteinfile;
			
			siteinread(filename);
		
			siteindata.ysf       = getYSF(cid);
			getLAI(siteindata.lai, cid);
			siteindata.vegc      = getVEGC(cid);
			siteindata.vegn      = getVEGN(cid);
		
			siteindata.mossthick = getMOSSTHICK(cid);
			siteindata.fibthick  = getFIBTHICK(cid);
			siteindata.humthick  = getHUMTHICK(cid);
			siteindata.soilc     = getSOILC(cid);
			siteindata.fibc      = getFIBC(cid);
			siteindata.humc      = getHUMC(cid);
			siteindata.orgn      = getORGN(cid);
			siteindata.avln      = getAVLN(cid);

			getMINTYPE(siteindata.mintype,cid);
			getINITZ(siteindata.initz, cid);
			getINITST(siteindata.initst, cid);
			getINITSM(siteindata.initsm, cid);
		} catch (Exception e) {
			System.err.println("sitein.nc reading NOT correct");
		}
	
	};


	void siteinread(String filename){
  		
		NetcdfFile ncfile = null;
		File ffile = new File(filename);
		if (ffile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);

				Variable var1 = ncfile.findVariable("YSF");
				ysfA = var1.read();
				
				Variable var2 = ncfile.findVariable("LAI");
				laiA = var2.read();
				Variable var3 = ncfile.findVariable("VEGC");
				vegcA = var3.read();
				Variable var4 = ncfile.findVariable("VEGN");
				vegnA = var4.read();

				Variable var5 = ncfile.findVariable("MOSSTHICK");
				mossthickA = var5.read();
				Variable var6 = ncfile.findVariable("FIBTHICK");
				fibthickA = var6.read();
				Variable var7 = ncfile.findVariable("HUMTHICK");
				humthickA = var7.read();

				Variable var8 = ncfile.findVariable("SOILC");
				soilcA = var8.read();
				Variable var9 = ncfile.findVariable("FIBC");
				fibcA = var9.read();
				Variable var10 = ncfile.findVariable("HUMC");
				humcA = var10.read();

				Variable var11 = ncfile.findVariable("ORGN");
				orgnA = var11.read();
				Variable var12 = ncfile.findVariable("AVLN");
				avlnA = var12.read();

				Variable var13 = ncfile.findVariable("MINTYPE");
				mintypeA = var13.read();

				Variable var14 = ncfile.findVariable("ZOUT");
				initzA = var14.read();
				Variable var15 = ncfile.findVariable("STOUT");
				initstA = var15.read();
				Variable var16 = ncfile.findVariable("SMOUT");
				initsmA = var16.read();

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
			System.err.println("Input file: "+filename+" NOT existed");
		}
	 
	};

	int getYSF(int cid){
		Index i = ysfA.getIndex();
		int ysf = ysfA.getInt(i.set(cid));
		return ysf;
	};

	void getLAI(float lai[], int cid){
		Index i = laiA.getIndex();
		for(int j=0; j<12; j++){
			lai[j] = laiA.getFloat(i.set(cid, j));
		}
	};

	float getVEGC(int cid){
		Index i = vegcA.getIndex();
		float vegc = vegcA.getInt(i.set(cid));
		return vegc;
	};

	float getVEGN(int cid){
		Index i = vegnA.getIndex();
		float vegn = vegnA.getInt(i.set(cid));
		return vegn;
	};

	float getMOSSTHICK(int cid){
		Index i = mossthickA.getIndex();
		float mossthick = mossthickA.getInt(i.set(cid));
		return mossthick;
	};

	float getFIBTHICK(int cid){
		Index i = fibthickA.getIndex();
		float fibthick = fibthickA.getInt(i.set(cid));
		return fibthick;
	};

	float getHUMTHICK(int cid){
		Index i = humthickA.getIndex();
		float humthick = humthickA.getInt(i.set(cid));
		return humthick;
	};

	float getSOILC(int cid){
		Index i = soilcA.getIndex();
		float soilc = soilcA.getInt(i.set(cid));
		return soilc;
	};

	float getFIBC(int cid){
		Index i = fibcA.getIndex();
		float fibc = fibcA.getInt(i.set(cid));
		return fibc;
	};

	float getHUMC(int cid){
		Index i = humcA.getIndex();
		float humc = humcA.getInt(i.set(cid));
		return humc;
	};

	float getORGN(int cid){
		Index i = orgnA.getIndex();
		float orgn = orgnA.getInt(i.set(cid));
		return orgn;
	};

	float getAVLN(int cid){
		Index i = avlnA.getIndex();
		float avln = avlnA.getInt(i.set(cid));
		return avln;
	};

	void getMINTYPE(int mintype[], int cid){
		Index i = mintypeA.getIndex();
		for(int j=0; j<ConstLayer.MAX_MIN_LAY; j++){
			mintype[j] = mintypeA.getInt(i.set(cid, j));
		}
	};


	void getINITZ(float initz[], int cid){
		Index i = initzA.getIndex();
		for(int j=0; j<ConstLayer.MAX_SOI_LAY; j++){
			initz[j] = initzA.getFloat(i.set(cid, j));
		}
	};
	
	void getINITST(float initst[], int cid){
		Index i = initstA.getIndex();
		for(int j=0; j<ConstLayer.MAX_SOI_LAY; j++){
			initst[j] = initstA.getFloat(i.set(cid, j));
		}
	};

	void getINITSM(float initsm[], int cid){
		Index i = initsmA.getIndex();
		for(int j=0; j<ConstLayer.MAX_SOI_LAY; j++){
			initsm[j] = initsmA.getFloat(i.set(cid, j));
		}
	};

}
