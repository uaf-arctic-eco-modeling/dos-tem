package INPUT;

import java.io.File;
import java.io.IOException;

import ucar.ma2.Array;
import ucar.ma2.Index;
import ucar.nc2.NetcdfFile;
import ucar.nc2.Variable;

import DATA.*;
import TEMJNI.ModelData;;

public class FireInputer {
	
//	ModelData md;
	
	Array spfireyearA; 
	Array spfireseasonA; 
	Array spseverityA;
	
	Array trfireyearA; 
	Array trfireseasonA;
	Array trseverityA;
	
	public void init(ModelData md){
		boolean usefs = md.getUseseverity();
 		if(md.getRunsp()){
    		initSpinupFire(usefs, md.getJspchtinputdir());
	  	}
  
  		if(md.getRuntr()){
    		initTransientFire(usefs, md.getJtrchtinputdir());
  		}
	}

	void initSpinupFire(boolean useseverity, String dir){
		String filename = dir +"fire.nc";
		
		NetcdfFile ncfile = null;
		File spfile = new File(filename);
		if (spfile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);
				Variable fyearV = ncfile.findVariable("FIRE");
				spfireyearA = fyearV.read();

				Variable fseasonV = ncfile.findVariable("SEASON");
				spfireseasonA = fseasonV.read();
				
				if (useseverity){
					Variable fsevV = ncfile.findVariable("SEVERITY");
					spseverityA = fsevV.read();

				}
			
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

	void initTransientFire(boolean useseverity, String dir){
		String filename = dir +"fire.nc";

		NetcdfFile ncfile = null;
		File spfile = new File(filename);
		if (spfile.exists()){
			try {
				ncfile = NetcdfFile.open(filename);
				Variable fyearV = ncfile.findVariable("FIRE");
				trfireyearA = fyearV.read();

				Variable fseasonV = ncfile.findVariable("SEASON");
				trfireseasonA = fseasonV.read();
				
				if (useseverity){
					Variable fsevV = ncfile.findVariable("SEVERITY");
					trseverityA = fsevV.read();
				}
			
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
	public void getSpinupFireYear(int spfireyear[], int cid){

		Index fireyri = spfireyearA.getIndex();

		for(int i=0; i<ConstTime.MAX_SP_FIR_OCR_NUM; i++){
			spfireyear[i] = spfireyearA.getInt(fireyri.set(cid,i));
		}
	
	};

	public void getSpinupFireSeason(int spfireseason[], int cid){
	
		Index fireyri = spfireseasonA.getIndex();

		for(int i=0; i<ConstTime.MAX_SP_FIR_OCR_NUM; i++){
			spfireseason[i] = spfireseasonA.getInt(fireyri.set(cid,i));
		}
	
	};

	public void getSpinupSeverity(int spfiresev[], int cid){
	
		Index severity = spseverityA.getIndex();

		for(int i=0; i<ConstTime.MAX_SP_FIR_OCR_NUM; i++){
			spfiresev[i] = spseverityA.getInt(severity.set(cid,i));
		}
	
	};
	
	public void getTransientFireYear(int trfireyear[], int cid){
		
		Index fireind = trfireyearA.getIndex();

		for(int i=0; i<ConstTime.MAX_TR_FIR_OCR_NUM; i++){
			trfireyear[i] = trfireyearA.getInt(fireind.set(cid,i));
		}
	
	};

	public void getTransientFireSeason(int trfireseason[], int cid){
	
		Index fireind = trfireseasonA.getIndex();

		for(int i=0; i<ConstTime.MAX_TR_FIR_OCR_NUM; i++){
			trfireseason[i] = trfireseasonA.getInt(fireind.set(cid,i));
		}
	
	};

	public void getTransientSeverity(int trfiresev[], int cid){
	
		Index fireind = trseverityA.getIndex();

		for(int i=0; i<ConstTime.MAX_TR_FIR_OCR_NUM; i++){
			trfiresev[i] = trseverityA.getInt(fireind.set(cid,i));
		}
	
	};
	
}