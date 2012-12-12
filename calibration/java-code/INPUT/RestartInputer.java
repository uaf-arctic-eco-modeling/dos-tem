package INPUT;
/*
 * 
 */
import java.io.File;
import java.io.IOException;

import ucar.ma2.Array;
import ucar.ma2.Index;
import ucar.nc2.NetcdfFile;
import ucar.nc2.Variable;

import DATA.ConstLayer;
import DATA.DataRestart;

public class RestartInputer {
 	Array chtidA;
 	Array errcodeA;
 	Array TSsnowA;
 	Array DZsnowA;
 	Array LIQsnowA;
 	Array ICEsnowA;
 	Array AGEsnowA;
 	Array RHOsnowA;

 	Array TSsoilA;
 	Array DZsoilA;
 	Array LIQsoilA;
 	Array ICEsoilA;
 	Array TYPEsoilA;
 	Array TYPEminA;
 	Array FROZENsoilA;
 	Array NONCsoilA;
 	Array REACsoilA;
 	Array TSrockA;
 	Array DZrockA;

 	Array frontZA;
 	Array frontFTA;
 	Array solnA;
 	Array avlnA;
 	Array wdebrisA;
 	Array strnA;
 	Array stonA;
 	Array vegcA;
 	Array deadcA;
 	Array deadnA;
 	Array laiA;
 	Array prveetmxA;
 	Array prvpetmxA;
 	Array foliagemxA;
 	Array unnormleafA;
 	Array prvunnormleafmxA;
 	Array prvtoptA;
 	
 	Array c2nA;
 	Array kdfibA;
 	Array kdhumA;
 	Array kdminA;
 	Array kdslowA;
 	Array ysfA;
 	Array burnednA;

 	Array toptaA;
 	Array unnormleafmxaA;
 	Array petmxaA;
 	Array eetmxaA;

	public void init(String restartfile){
 	
		NetcdfFile ncfile = null;
		File vegfile = new File(restartfile);
		if (vegfile.exists()){
			try {
				ncfile = NetcdfFile.open(restartfile);

				Variable chtidV = ncfile.findVariable("CHTID");
				chtidA = chtidV.read();

				Variable errcodeV = ncfile.findVariable("ERRCODE");
				errcodeA = errcodeV.read();

				Variable TSsnowV = ncfile.findVariable("TSsnow");
				TSsnowA = TSsnowV.read();

				Variable DZsnowV = ncfile.findVariable("DZsnow");
				DZsnowA = DZsnowV.read();

				Variable LIQsnowV = ncfile.findVariable("LIQsnow");
				LIQsnowA = LIQsnowV.read();

				Variable ICEsnowV = ncfile.findVariable("ICEsnow");
				ICEsnowA = ICEsnowV.read();

				Variable AGEsnowV = ncfile.findVariable("AGEsnow");
				AGEsnowA = AGEsnowV.read();

				Variable RHOsnowV = ncfile.findVariable("RHOsnow");
				RHOsnowA = RHOsnowV.read();

				Variable TSsoilV = ncfile.findVariable("TSsoil");
				TSsoilA = TSsoilV.read();

				Variable DZsoilV = ncfile.findVariable("DZsoil");
				DZsoilA = DZsoilV.read();

				Variable LIQsoilV = ncfile.findVariable("LIQsoil");
				LIQsoilA = LIQsoilV.read();

				Variable ICEsoilV = ncfile.findVariable("ICEsoil");
				ICEsoilA = ICEsoilV.read();

				Variable TYPEsoilV = ncfile.findVariable("TYPEsoil");
				TYPEsoilA = TYPEsoilV.read();

				Variable TYPEminV = ncfile.findVariable("TYPEmin");
				TYPEminA = TYPEminV.read();

				Variable FROZENsoilV = ncfile.findVariable("FROZENsoil");
				FROZENsoilA = FROZENsoilV.read();

				Variable NONCsoilV = ncfile.findVariable("NONCsoil");
				NONCsoilA = NONCsoilV.read();

				Variable REACsoilV = ncfile.findVariable("REACsoil");
				REACsoilA = REACsoilV.read();

				Variable TSrockV = ncfile.findVariable("TSrock");
				TSrockA = TSrockV.read();

				Variable DZrockV = ncfile.findVariable("DZrock");
				DZrockA = DZrockV.read();

				Variable frontZV = ncfile.findVariable("frontZ");
				frontZA = frontZV.read();

				Variable frontFTV = ncfile.findVariable("frontFT");
				frontFTA = frontFTV.read();

				Variable solnV = ncfile.findVariable("SOLN");
				solnA = solnV.read();

				Variable avlnV = ncfile.findVariable("AVLN");
				avlnA = avlnV.read();

				Variable wdebrisV = ncfile.findVariable("WDEBRIS");
				wdebrisA = wdebrisV.read();

				Variable strnV = ncfile.findVariable("STRN");
				strnA = strnV.read();

				Variable stonV = ncfile.findVariable("STON");
				stonA = stonV.read();

				Variable vegcV = ncfile.findVariable("VEGC");
				vegcA = vegcV.read();

				Variable deadcV = ncfile.findVariable("DEADC");
				deadcA = deadcV.read();

				Variable deadnV = ncfile.findVariable("DEADN");
				deadnA = deadnV.read();

				Variable laiV = ncfile.findVariable("LAI");
				laiA = laiV.read();

				Variable prveetmxV = ncfile.findVariable("PRVEETMX");
				prveetmxA = prveetmxV.read();

				Variable prvpetmxV = ncfile.findVariable("PRVPETMX");
				prvpetmxA = prvpetmxV.read();

				Variable foliagemxV = ncfile.findVariable("FOLIAGEMX");
				foliagemxA = foliagemxV.read();

				Variable unnormleafV = ncfile.findVariable("UNNORMLEAF");
				unnormleafA = unnormleafV.read();

				Variable prvunnormleafmxV = ncfile.findVariable("PRVUNNORMLEAFMX");
				prvunnormleafmxA = prvunnormleafmxV.read();

				Variable prvtoptV = ncfile.findVariable("PRVTOPT");
				prvtoptA = prvtoptV.read();
 	
				Variable c2nV = ncfile.findVariable("C2N");
				c2nA = c2nV.read();

				Variable kdfibV = ncfile.findVariable("KDFIB");
				kdfibA = kdfibV.read();

				Variable kdhumV = ncfile.findVariable("KDHUM");
				kdhumA = kdhumV.read();

				Variable kdminfastV = ncfile.findVariable("KDMIN");
				kdminA = kdminfastV.read();

				Variable kdminslowV = ncfile.findVariable("KDSLOW");
				kdslowA = kdminslowV.read();

				Variable ysfV = ncfile.findVariable("YSF");
				ysfA = ysfV.read();

				Variable burnednV = ncfile.findVariable("BURNEDN");
				burnednA = burnednV.read();

				Variable toptaV = ncfile.findVariable("TOPTA");
				toptaA = toptaV.read();

				Variable unnormleafmxaV = ncfile.findVariable("UNNORMLEAFMXA");
				unnormleafmxaA = unnormleafmxaV.read();

				Variable petmxaV = ncfile.findVariable("PETMXA");
				petmxaA = petmxaV.read();

				Variable eetmxaV = ncfile.findVariable("EETMXA");
				eetmxaA = eetmxaV.read();
		
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
			System.out.println("Input file: "+restartfile+" NOT existed");
		}

	};

	public void getResin(DataRestart resid, int cid) { 
		
	 	resid.errcode = getERRCODE(cid);

	 	getDZsnow(resid.DZsnow, cid);
		getTSsnow(resid.TSsnow, cid);
	 	getICEsnow(resid.ICEsnow, cid);
	 	getAGEsnow(resid.AGEsnow, cid);
	 	getRHOsnow(resid.RHOsnow, cid);
	 
	 	getTYPEsoil(resid.TYPEsoil, cid);
	 	getFROZENsoil(resid.FROZENsoil, cid);
	 	getDZsoil(resid.DZsoil, cid);
	 	getTSsoil(resid.TSsoil, cid);
	 	getLIQsoil(resid.LIQsoil, cid);
	 	getICEsoil(resid.ICEsoil, cid);
	 	getNONCsoil(resid.NONCsoil, cid);
	 	getREACsoil(resid.REACsoil, cid);
	 
	 	getTYPEmin(resid.TYPEmin,  cid);
	 	getDZrock(resid.DZrock,  cid);
	 	getTSrock(resid.TSrock,  cid);
	 	getFrontZ(resid.frontZ,  cid);
	 	getFrontFT(resid.frontFT,  cid);

	 	resid.vegc = getVEGC(cid);
	 	resid.deadc = getDEADC(cid);
	 	resid.wdebris = getWDEBRIS(cid);
	 	resid.strn = getSTRN(cid);
	 	resid.ston = getSTON(cid);
	 	resid.deadn = getDEADN(cid);
	 	resid.c2n = getC2N(cid);
	 	resid.soln = getSOLN(cid);
	 	resid.avln = getAVLN(cid);
	 
	 	resid.lai = getLAI(cid);
	 	resid.foliagemx = getFOLIAGEMX(cid);
	 	resid.unnormleaf = getUNNORMLEAF(cid);
	 	resid.prvunnormleafmx = getPRVUNNORMLEAFMX(cid);
	 	resid.prveetmx = getPRVEETMX(cid);
	 	resid.prvpetmx = getPRVPETMX(cid);
	 	resid.prvtopt = getPRVTOPT(cid);
	 
	 	resid.kdfib = getKDFIB(cid); 
	 	resid.kdhum = getKDHUM(cid);
	 	resid.kdmin = getKDMIN(cid);
	 	resid.kdslow = getKDSLOW(cid);
	 
	 	resid.ysf = getYSF(cid);
	 	resid.burnedn = getBURNEDN(cid);

	 	getTOPTA(resid.toptA, cid);
	 	getEETMXA(resid.eetmxA, cid);
	 	getPETMXA(resid.petmxA, cid);
	 	getUNNORMLEAFMXA(resid.unnormleafmxA, cid);
	 	
	};
	
	//Yuan: cid is the record id (starting from ZERO), but not cohort id (chtid) in the .nc file
	public int getRecordId(int reschtid){

		Index ind = chtidA.getIndex();
		for (int i=0; i<(int)ind.getSize(); i++){
			int chtid = chtidA.getInt(ind.set(i));
			if (chtid == reschtid) return i;
		}	
			 
		return -1;
	}

	//1-D data
	int getERRCODE(int cid){	
		Index ind = errcodeA.getIndex();
		return errcodeA.getInt(ind.set(cid));
	};

	int getYSF(int cid){	
		Index ind = ysfA.getIndex();
		return ysfA.getInt(ind.set(cid));
	};

	double getBURNEDN(int cid){
		Index ind = burnednA.getIndex();
		return burnednA.getDouble(ind.set(cid));
	};

	double getVEGC(int cid){
		Index ind = vegcA.getIndex();
		return vegcA.getDouble(ind.set(cid));
	};

	double getSTRN(int cid){
		Index ind = strnA.getIndex();
		return strnA.getDouble(ind.set(cid));
	};

	double getUNNORMLEAF(int cid){	
		Index ind = unnormleafA.getIndex();
		return unnormleafA.getDouble(ind.set(cid));
	};

	double getLAI(int cid){
		Index ind = laiA.getIndex();
		return laiA.getDouble(ind.set(cid));
	};

	double getPRVPETMX(int cid){
		Index ind = prvpetmxA.getIndex();
		return prvpetmxA.getDouble(ind.set(cid));
	};

	double getPRVEETMX(int cid){	
		Index ind = prveetmxA.getIndex();
		return prveetmxA.getDouble(ind.set(cid));
	};

	double getFOLIAGEMX(int cid){	
		Index ind = foliagemxA.getIndex();
		return foliagemxA.getDouble(ind.set(cid));
	};

	double getPRVTOPT(int cid){
		Index ind = prvtoptA.getIndex();
		return prvtoptA.getDouble(ind.set(cid));
	};

	double getC2N(int cid){
		Index ind = c2nA.getIndex();
		return c2nA.getDouble(ind.set(cid));
	};

	double getKDFIB(int cid){
		Index ind = kdfibA.getIndex();
		return kdfibA.getDouble(ind.set(cid));
	};

	double getKDHUM(int cid){
		Index ind = kdhumA.getIndex();
		return kdhumA.getDouble(ind.set(cid));
	};

	double getKDMIN(int cid){
		Index ind = kdminA.getIndex();
		return kdminA.getDouble(ind.set(cid));
	};

	double getKDSLOW(int cid){
		Index ind = kdslowA.getIndex();
		return kdslowA.getDouble(ind.set(cid));
	};

	double getPRVUNNORMLEAFMX(int cid){
		Index ind = prvunnormleafmxA.getIndex();
		return prvunnormleafmxA.getDouble(ind.set(cid));
	};

	double getSTON(int cid){
		Index ind = stonA.getIndex();
		return stonA.getDouble(ind.set(cid));
	};

	double getWDEBRIS(int cid){
		Index ind = wdebrisA.getIndex();
		return wdebrisA.getDouble(ind.set(cid));
	};

	double getSOLN(int cid){
		Index ind = solnA.getIndex();
		return solnA.getDouble(ind.set(cid));
	};

	double getAVLN(int cid){
		Index ind = avlnA.getIndex();
		return avlnA.getDouble(ind.set(cid));
	};

	double getDEADC(int cid){
		Index ind = deadcA.getIndex();
		return deadcA.getDouble(ind.set(cid));
	};

	double getDEADN(int cid){
		Index ind = deadnA.getIndex();
		return deadnA.getDouble(ind.set(cid));
	};
	
	//2-D data
	void  getDZsnow(double DZsnow[], int cid){
		Index ind = DZsnowA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SNW_LAY; il++) {
			DZsnow[il] = DZsnowA.getDouble(ind.set(cid,il));
		}
	};

	void  getTSsnow(double  TSsnow[], int cid){
		Index ind = TSsnowA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SNW_LAY; il++) {
			TSsnow[il] = TSsnowA.getDouble(ind.set(cid,il));
		}
	};

	void  getAGEsnow(double  AGEsnow[], int cid){
		Index ind = AGEsnowA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SNW_LAY; il++) {
			AGEsnow[il] = AGEsnowA.getDouble(ind.set(cid,il));
		}
	};

 	void  getICEsnow(double  ICEsnow[], int cid){
		Index ind = ICEsnowA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SNW_LAY; il++) {
			ICEsnow[il] = ICEsnowA.getDouble(ind.set(cid,il));
		}
	};

 	void  getRHOsnow(double  RHOsnow[], int cid){
		Index ind = RHOsnowA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SNW_LAY; il++) {
			RHOsnow[il] = RHOsnowA.getDouble(ind.set(cid,il));
		}
	};

 	void  getDZrock(double  DZrock[], int cid){
		Index ind = DZrockA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_ROC_LAY; il++) {
			DZrock[il] = DZrockA.getDouble(ind.set(cid,il));
		}
	};

 	void  getTSrock(double  TSrock[], int cid){	
		Index ind = TSrockA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_ROC_LAY; il++) {
			TSrock[il] = TSrockA.getDouble(ind.set(cid,il));
		}
	};

 	void  getDZsoil(double  DZsoil[], int cid){	
		Index ind = DZsoilA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
			DZsoil[il] = DZsoilA.getDouble(ind.set(cid,il));
		}
	};

 	void  getTSsoil(double  TSsoil[], int cid){
		Index ind = TSsoilA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
			TSsoil[il] = TSsoilA.getDouble(ind.set(cid,il));
		}
	};

 	void  getLIQsoil(double  LIQsoil[], int cid){
		Index ind = LIQsoilA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
			LIQsoil[il] = LIQsoilA.getDouble(ind.set(cid,il));
		}
	};

 	void  getICEsoil(double  ICEsoil[], int cid){
		Index ind = ICEsoilA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
			ICEsoil[il] = ICEsoilA.getDouble(ind.set(cid,il));
		}
	};

	void  getNONCsoil(double NONCsoil[], int cid){
		Index ind = NONCsoilA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
			NONCsoil[il] = NONCsoilA.getDouble(ind.set(cid,il));
		}
	};

 	void  getREACsoil(double REACsoil[], int cid){
		Index ind = REACsoilA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
			REACsoil[il] = REACsoilA.getDouble(ind.set(cid,il));
		}
	};

 	void  getFROZENsoil(int FROZENsoil[], int cid){
		Index ind = FROZENsoilA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
			FROZENsoil[il] = FROZENsoilA.getInt(ind.set(cid,il));
		}
	};

 	void  getTYPEsoil(int TYPEsoil[], int cid){
		Index ind = TYPEsoilA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
			TYPEsoil[il] = TYPEsoilA.getInt(ind.set(cid,il));
		}
	};

 	void  getTYPEmin(int TYPEmin[], int cid){
		Index ind = TYPEminA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_MIN_LAY; il++) {
			TYPEmin[il] = TYPEminA.getInt(ind.set(cid,il));
		}
	};

 	void  getFrontFT(int frontFT[], int cid){
		Index ind = frontFTA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_NUM_FNT; il++) {
			frontFT[il] = frontFTA.getInt(ind.set(cid,il));
		}
	};

 	void  getFrontZ(double frontZ[], int cid){
		Index ind = frontZA.getIndex();
		for (int il = 0; il < ConstLayer.MAX_NUM_FNT; il++) {
			frontZ[il] = frontZA.getDouble(ind.set(cid,il));
		}
	};

 	void  getTOPTA(double topta[], int cid){	
		Index ind = toptaA.getIndex();
		for (int il = 0; il < 10; il++) {
			topta[il] = toptaA.getDouble(ind.set(cid,il));
		}
	};

	void  getUNNORMLEAFMXA(double unnormleafmxa[], int cid){
		Index ind = unnormleafmxaA.getIndex();
		for (int il = 0; il < 10; il++) {
			unnormleafmxa[il] = unnormleafmxaA.getDouble(ind.set(cid,il));
		}
	};

	void  getPETMXA(double petmxa[], int cid){	
		Index ind = petmxaA.getIndex();
		for (int il = 0; il < 10; il++) {
			petmxa[il] = petmxaA.getDouble(ind.set(cid,il));
		}
	};

	void  getEETMXA(double eetmxa[], int cid){
		Index ind = eetmxaA.getIndex();
		for (int il = 0; il < 10; il++) {
			eetmxa[il] = eetmxaA.getDouble(ind.set(cid,il));
		}

	};

}