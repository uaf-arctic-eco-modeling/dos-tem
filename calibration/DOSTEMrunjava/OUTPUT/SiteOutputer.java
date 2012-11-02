package OUTPUT;

/* Outputer.java
 * output directory and netcdf file definition for TEM
 *
*/

import java.io.IOException;
import java.util.ArrayList;

import ucar.ma2.*;
import ucar.nc2.*;

import DATA.ConstLayer;
import DATA.ConstTime;

import TEMJNI.ModelData;

public class SiteOutputer {

	public boolean OMONTH;
	public boolean OYEAR;
	//file names for outputs
	public String moncfn="";
	public String mongfn="";
	public String yrcfn="";
	public String yrgfn="";
	

//	ModelData md=new ModelData();
	String outputdir = "";
	String stage ="";

	public void init(ModelData md, int chtid){
		outputdir = md.getJoutputdir();
		if(md.getRunsp() && md.getRuntr()){
			stage ="";
		}else if(md.getRunsp()){
			stage ="-sp";
		}else if(md.getRuntr()){
			stage ="-tr";
		}else if (md.getRunsc()){
			stage ="-sc";
		}else if (md.getRuneq()){
			stage="-eq";
		}
	
 		createChtFile(chtid);
 		createGrdFile(chtid);

	};

	void createChtFile (int chtid){
		if (OMONTH) {
			moncfn =outputdir+ "mon-cht"+stage+chtid+".nc";
			
			try {
			NetcdfFileWriteable monChtFile=NetcdfFileWriteable.createNew(moncfn, false);
			Dimension mcyearD = monChtFile.addUnlimitedDimension("year");
			Dimension mcmonD = monChtFile.addDimension("month", ConstTime.MINY);
			Dimension mclayerD = monChtFile.addDimension("layer", ConstLayer.MAX_OUT_SOI);

			ArrayList<Dimension> dimYM = new ArrayList<Dimension>();
			dimYM.add(mcyearD);
			dimYM.add(mcmonD);

			ArrayList<Dimension> dimYML = new ArrayList<Dimension>();
			dimYML.add(mcyearD);
			dimYML.add(mcmonD);
			dimYML.add(mclayerD);

			//ground (snow-soil) system output variables
			monChtFile.addVariable("GROWPCT", DataType.FLOAT, dimYM);
			monChtFile.addVariable("ORGN", DataType.FLOAT, dimYM);
			monChtFile.addVariable("AVLN", DataType.FLOAT, dimYM);
			monChtFile.addVariable("NIMMOB", DataType.FLOAT, dimYM);
			monChtFile.addVariable("NETNMIN", DataType.FLOAT, dimYM);
			monChtFile.addVariable("NLOST", DataType.FLOAT, dimYM);
			monChtFile.addVariable("REACSUM", DataType.FLOAT, dimYM);
			monChtFile.addVariable("NONCSUM", DataType.FLOAT, dimYM);
			monChtFile.addVariable("SNINFL", DataType.FLOAT, dimYM);
			monChtFile.addVariable("SEVAP", DataType.FLOAT, dimYM);
			monChtFile.addVariable("SSUBL", DataType.FLOAT, dimYM);
			monChtFile.addVariable("MOSSDZ", DataType.FLOAT, dimYM);
			monChtFile.addVariable("SHLWDZ", DataType.FLOAT, dimYM);
			monChtFile.addVariable("DEEPDZ", DataType.FLOAT, dimYM);
			monChtFile.addVariable("WATERTAB", DataType.FLOAT, dimYM);

			monChtFile.addVariable("TS", DataType.FLOAT, dimYML);
			monChtFile.addVariable("LIQVWC", DataType.FLOAT, dimYML);
			monChtFile.addVariable("VWC", DataType.FLOAT, dimYML);
			monChtFile.addVariable("ICEVWC", DataType.FLOAT, dimYML);
			monChtFile.addVariable("DZ", DataType.FLOAT, dimYML);
			monChtFile.addVariable("Z", DataType.FLOAT, dimYML);
			monChtFile.addVariable("PORO", DataType.FLOAT, dimYML);
			monChtFile.addVariable("TYPE", DataType.FLOAT, dimYML);
			monChtFile.addVariable("REAC", DataType.FLOAT, dimYML);
			monChtFile.addVariable("NONC", DataType.FLOAT, dimYML);
			monChtFile.addVariable("RRH", DataType.FLOAT, dimYML);
			monChtFile.addVariable("NRH", DataType.FLOAT, dimYML);
			monChtFile.addVariable("RHMOIST", DataType.FLOAT, dimYML);
			monChtFile.addVariable("RHQ10", DataType.FLOAT, dimYML);
			monChtFile.addVariable("KSOIL", DataType.FLOAT, dimYML);
			monChtFile.addVariable("KDL", DataType.FLOAT, dimYML);
			monChtFile.addVariable("KDR", DataType.FLOAT, dimYML);
			monChtFile.addVariable("KDN", DataType.FLOAT, dimYML);

	    	//plant system output variables
			monChtFile.addVariable("VEGC", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("VEGC","units","gC/m2");
			monChtFile.addVariableAttribute("VEGC","title", "Vegetation Carbon");

			monChtFile.addVariable("STRN", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("VEGC","units","gN/m2");
			monChtFile.addVariableAttribute("VEGC","title", "Structual Nitrogen");

			monChtFile.addVariable("STON", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("VEGC","units","gN/m2");
			monChtFile.addVariableAttribute("VEGC","title", "Labile Nitrogen");

			monChtFile.addVariable("INGPP", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("INGPP","units","gC/m2day");
			monChtFile.addVariableAttribute("INGPP","title", "GPP unlimited by N");

			monChtFile.addVariable("GPP", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("GPP","units","gC/m2day");
			monChtFile.addVariableAttribute("GPP","title", "GPP");

			monChtFile.addVariable("INNPP", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("INNPP","units","gC/m2day");
			monChtFile.addVariableAttribute("INNPP","title", "NPP unlimited by N");

			monChtFile.addVariable("NPP", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("NPP","units","gC/m2day");
			monChtFile.addVariableAttribute("NPP","title", "NPP");

			monChtFile.addVariable("RM", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("RM","units","gC/m2day");
			monChtFile.addVariableAttribute("RM","title", "Maintainence Respiration");

			monChtFile.addVariable("RG", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("RG","units","gC/m2day");
			monChtFile.addVariableAttribute("RG","title", "Growth Respiration");

			monChtFile.addVariable("LTRFALC", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("LTRFALC","units","gC/m2day");
			monChtFile.addVariableAttribute("LTRFALC","title", "Literfall Carbon");

			monChtFile.addVariable("LTRFALN", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("LTRFALN","units","gN/m2day");
			monChtFile.addVariableAttribute("LTRFALN","title", "Literfall Nitrogen");

			monChtFile.addVariable("INNUPTAKE", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("INNUPTAKE","units","gN/m2day");
			monChtFile.addVariableAttribute("INNUPTAKE","title", "N uptake unlimited by N");

			monChtFile.addVariable("NUPTAKE", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("NUPTAKE","units","gN/m2day");
			monChtFile.addVariableAttribute("NUPTAKE","title", "N uptake");

			monChtFile.addVariable("SUPTAKE", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("SUPTAKE","units","gN/m2day");
	    	monChtFile.addVariableAttribute("SUPTAKE","title", "N uptake by Structual Pool");

			monChtFile.addVariable("LUPTAKE", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("LUPTAKE","units","gN/m2day");
	    	monChtFile.addVariableAttribute("LUPTAKE","title", "N uptake by Labile Pool");

			monChtFile.addVariable("NMOBIL", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("NMOBIL","units","gN/m2day");
	    	monChtFile.addVariableAttribute("NMOBIL","title", "Mobilized Nitrogen");

			monChtFile.addVariable("NRESORB", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("NRESORB","units","gN/m2day");
	    	monChtFile.addVariableAttribute("NRESORB","title", "Reabsorbed Nitrogen");

			monChtFile.addVariable("LAI", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("LAI","units","m2/m2");
	    	monChtFile.addVariableAttribute("LAI","title", "Leaf Area Index");

			monChtFile.addVariable("FPC", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("FPC","units","");
	    	monChtFile.addVariableAttribute("FPC","title", "FPC");

			monChtFile.addVariable("UNNORMLEAF", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("UNNORMLEAF","units","-");
	    	monChtFile.addVariableAttribute("UNNORMLEAF","title", "Unnormalized Leaf");

			monChtFile.addVariable("LEAF", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("LEAF","units","-");
	    	monChtFile.addVariableAttribute("LEAF","title", "ET control factor on leaf growth");

			monChtFile.addVariable("FOLIAGE", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("FOLIAGE","units","-");
	    	monChtFile.addVariableAttribute("FOLIAGE","title", "VEG C regulated leaf growth");

			monChtFile.addVariable("BTRAN", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("BTRAN","units","-");
	 	  	monChtFile.addVariableAttribute("BTRAN","title", "Factor of Soil Water on Conductance");

			monChtFile.addVariable("RAC", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("RAC","units","W/m2");
	 	    monChtFile.addVariableAttribute("RAC","title", "Absorbed Radiation in Canopy");

			monChtFile.addVariable("RC", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("RC","units","s/mm");
			monChtFile.addVariableAttribute("RC","title", "Canopy Resistence");

	    	monChtFile.addVariable("TRANS", DataType.FLOAT, dimYM);
	    	monChtFile.addVariableAttribute("TRANS","units","mm/m2day");
	 	 	monChtFile.addVariableAttribute("TRANS","title", "Transpiration");

			monChtFile.addVariable("VEVAP", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("VEVAP","units","mm/day");
	 	 	monChtFile.addVariableAttribute("VEVAP","title", "Canopy Evaporation");

			monChtFile.addVariable("VSUBL", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("VSUBL","units","mm/day");
	 	 	monChtFile.addVariableAttribute("VSUBL","title", "Sublimation from Canopy Snow");

			monChtFile.addVariable("RINTER", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("RINTER","units","mm/day");
	 	    monChtFile.addVariableAttribute("RINTER","title", "Intercepted Rain");

			monChtFile.addVariable("SINTER", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("SINTER","units","mm/day");
	 	 	monChtFile.addVariableAttribute("SINTER","title", "Intercepted Snow");

			monChtFile.addVariable("RTHFL", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("RTHFL","units","mm/day");
	 	 	monChtFile.addVariableAttribute("RTHFL","title", "Rain Throughfall");

			monChtFile.addVariable("STHFL", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("STHFL","units","mm/day");
	 	 	monChtFile.addVariableAttribute("STHFL","title", "Snow Throughfall");

	    	monChtFile.addVariable("RADTHFL", DataType.FLOAT, dimYM);
			monChtFile.addVariableAttribute("RADTHFL","units","MJ/m2day");
			monChtFile.addVariableAttribute("RADTHFL","title", "Radition Throughfall");

			try {
				monChtFile.create();
				monChtFile.close();
			}catch (IOException e) {
				System.err.println("Error in creating file"+monChtFile.getLocation()+"\n");
			}

			}catch (Exception e) {
				
			}
		}

		if (OYEAR) {
			yrcfn =outputdir+ "yr-cht"+stage+chtid+".nc";
			
			try {
			NetcdfFileWriteable yrChtFile=NetcdfFileWriteable.createNew(yrcfn, false);
	 		Dimension ycyearD = yrChtFile.addUnlimitedDimension("year");

			ArrayList<Dimension> dimY = new ArrayList<Dimension>();
			dimY.add(ycyearD);

			//ground (snow-soil) system output variables
			yrChtFile.addVariable("LIQSUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("ICESUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("REACSUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("NONCSUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("SHLWCSUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("DEEPCSUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("MINECSUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("ORGN", DataType.FLOAT, dimY);
			yrChtFile.addVariable("AVLN", DataType.FLOAT, dimY);

			yrChtFile.addVariable("TSAVE", DataType.FLOAT, dimY);
			yrChtFile.addVariable("SEVAP", DataType.FLOAT, dimY);
			yrChtFile.addVariable("QDRAIN", DataType.FLOAT, dimY);
			yrChtFile.addVariable("QOVER", DataType.FLOAT, dimY);
			yrChtFile.addVariable("SSUBL", DataType.FLOAT, dimY);
			yrChtFile.addVariable("RRHSUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("NRHSUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("NETNMIN", DataType.FLOAT, dimY);
			yrChtFile.addVariable("SNUPTAKE", DataType.FLOAT, dimY);

			yrChtFile.addVariable("PERMAFROST", DataType.FLOAT, dimY);
			yrChtFile.addVariable("ALD", DataType.FLOAT, dimY);
			yrChtFile.addVariable("WATERTAB", DataType.FLOAT, dimY);

			yrChtFile.addVariable("MOSSDZ", DataType.FLOAT, dimY);
			yrChtFile.addVariable("SHLWDZ", DataType.FLOAT, dimY);
			yrChtFile.addVariable("DEEPDZ", DataType.FLOAT, dimY);
			yrChtFile.addVariable("MOSSNUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("SHLWNUM", DataType.FLOAT, dimY);
			yrChtFile.addVariable("DEEPNUM", DataType.FLOAT, dimY);

			yrChtFile.addVariable("BURNTHICK", DataType.FLOAT, dimY);
			yrChtFile.addVariable("BURNSOILC", DataType.FLOAT, dimY);
			yrChtFile.addVariable("BURNSOILN", DataType.FLOAT, dimY);
			yrChtFile.addVariable("ORGNRETURN", DataType.FLOAT, dimY);
			yrChtFile.addVariable("WDEBRIS", DataType.FLOAT, dimY);
			yrChtFile.addVariable("WDRH", DataType.FLOAT, dimY);

			//plant system output variables
			yrChtFile.addVariable("NPP", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("RM", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("RG", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("LTRFALC", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("LTRFALN", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("VNUPTAKE", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("EVAPO", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("SUBLIM", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("TRANS", DataType.FLOAT, dimY);

	    	yrChtFile.addVariable("C2N", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("VEGC", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("STRN", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("STON", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("ABVGNDC", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("FOLIAGE", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("LEAF", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("LAI", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("FPC", DataType.FLOAT, dimY);

	    	yrChtFile.addVariable("BURNVEGC", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("BURNVEGN", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("NSOURCE", DataType.FLOAT, dimY);
	    	yrChtFile.addVariable("NLOSS", DataType.FLOAT, dimY);

	    	try {
				yrChtFile.create();
				yrChtFile.close();
			}catch (IOException e) {
				System.err.println("Error in creating file"+yrChtFile.getLocation()+"\n");
			}
			
			}catch (Exception e) {
				
			}
		}
	};
	
	void createGrdFile (int chtid){
		if (OMONTH){
			mongfn =outputdir+ "mon-grd"+stage+chtid+".nc";
			
			try {
			NetcdfFileWriteable monGrdFile=NetcdfFileWriteable.createNew(mongfn, false);
	 		Dimension mgyearD = monGrdFile.addUnlimitedDimension("year");
	  		Dimension mgmonD  = monGrdFile.addDimension("month",ConstTime.MINY);

			//atmospheric output variables
			ArrayList<Dimension> dimYM = new ArrayList<Dimension>();
			dimYM.add(mgyearD);	dimYM.add(mgmonD);
			
			monGrdFile.addVariable("EET", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("EET","units","mm/day");
			monGrdFile.addVariableAttribute("EET","title", "Actual Evapotranspiration");
			monGrdFile.addVariable("PET", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("PET","units","mm/day");
			monGrdFile.addVariableAttribute("PET","title", "Potential Evapotranspiration");
			monGrdFile.addVariable("CO2", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("CO2", "units","ppmv");
			monGrdFile.addVariableAttribute("CO2", "title", "CO2 Concentration");
			monGrdFile.addVariable("TA", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("TA", "units","degC");
			monGrdFile.addVariableAttribute("TA", "title", "Air Temperature");
			monGrdFile.addVariable("RNFL", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("RNFL", "units","mm");
			monGrdFile.addVariableAttribute("RNFL", "title", "Snowfall");
			monGrdFile.addVariable("SNFL", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("SNFL", "units","mm");
			monGrdFile.addVariableAttribute("SNFL", "title", "Snowfall");
			monGrdFile.addVariable("NIRR", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("NIRR", "units","W/m2");
			monGrdFile.addVariableAttribute("NIRR", "title", "Incident Solar Raidation at Surface");
			monGrdFile.addVariable("GIRR", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("GIRR", "units","W/m2");
			monGrdFile.addVariableAttribute("GIRR", "title", "GIRR");
			monGrdFile.addVariable("PAR", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("PAR", "units","W/m2");
			monGrdFile.addVariableAttribute("PAR", "title", "Photosynthetic Active Raditaion");
			monGrdFile.addVariable("CLDS", DataType.FLOAT, dimYM);
			monGrdFile.addVariableAttribute("CLDS", "units","percent");
			monGrdFile.addVariableAttribute("CLDS", "title", "Cloud Fraction");

			try {
				monGrdFile.create();
				monGrdFile.close();
			}catch (IOException e) {
				System.err.println("Error in creating file"+monGrdFile.getLocation()+"\n");
			}

			}catch (Exception e) {
				
			}
		}

		if (OYEAR){
			yrgfn =outputdir+ "yr-grd"+stage+chtid+".nc";
			
			try {
			NetcdfFileWriteable yrGrdFile=NetcdfFileWriteable.createNew(yrgfn, false);
			Dimension ygyearD = yrGrdFile.addUnlimitedDimension("year");

			ArrayList<Dimension> dimY = new ArrayList<Dimension>();
			dimY.add(ygyearD);

			//atmospheric output variables
			yrGrdFile.addVariable("TA", DataType.FLOAT, dimY);
			yrGrdFile.addVariableAttribute("TA", "units","degC");
			yrGrdFile.addVariable("RNFL", DataType.FLOAT, dimY);
			yrGrdFile.addVariableAttribute("RNFL", "units","mm");
			yrGrdFile.addVariable("SNFL", DataType.FLOAT, dimY);
			yrGrdFile.addVariableAttribute("SNFL", "units","mm");

			try {
				yrGrdFile.create();
				yrGrdFile.close();
			}catch (IOException e) {
				System.err.println("Error in creating file"+yrGrdFile.getLocation()+"\n");
			}

			}catch (Exception e) {
				
			}
		}

	};
}