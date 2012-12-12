package INPUT;
//
// CCohortDriver.java
//   - reading soil-env-climate driver for calibration

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import ucar.ma2.*;
import ucar.nc2.*;

import DATA.ConstLayer;
import DATA.DataCalibDriver;

import TEMJNI.EnvData;
import TEMJNI.BgcData;
import TEMJNI.Cohort;

public class CCohortDriver {

	public DataCalibDriver jCcd=new DataCalibDriver();
	
	public void updateDriver(String filename) {

		NetcdfFile ncfile = null;
		File f = new File(filename);
		if (f.exists()) {
			try {
				ncfile = NetcdfFile.open(filename);

				//soil-climate driving data from DataEnv
				Variable tsV = ncfile.findVariable("TS");
				Array tsa = tsV.read();
				Index ima = tsa.getIndex();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						jCcd.eq_ts[imil] = tsa.getDouble(ima.set(im,il));
					}

				}
				
				Variable liqV = ncfile.findVariable("LIQ");
				Array liqa = liqV.read();
				Index ima1 = liqa.getIndex();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						jCcd.eq_liq[imil] = liqa.getDouble(ima1.set(im, il));
					}

				}
				
				Variable vsmV = ncfile.findVariable("VSM");
				Array vsma = vsmV.read();
				Index ima2 = vsma.getIndex();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						jCcd.eq_vwc[imil] = vsma.getDouble(ima2.set(im, il));
					}

				}
				
				Variable swV = ncfile.findVariable("SW");
				Array swa = swV.read();
				Index ima3 = swa.getIndex();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						jCcd.eq_sws[imil] = swa.getDouble(ima3.set(im, il));
					}

				}
				
				Variable iceV = ncfile.findVariable("ICE");
				Array icea = iceV.read();
				Index ima4 = icea.getIndex();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						jCcd.eq_ice[imil] = icea.getDouble(ima4.set(im, il));
					}

				}
		 
				Variable taV = ncfile.findVariable("TA");
				Array taa = taV.read();
				Index taima = taa.getIndex();
				for (int im = 0; im < 12; im++) {
					jCcd.eq_ta[im] = taa.getDouble(taima.set(im));

				}

				Variable growV = ncfile.findVariable("GROW");
				Array growa = growV.read();
				Index growima = growa.getIndex();
				for (int im = 0; im < 12; im++) {
					jCcd.eq_grow[im] = growa.getDouble(growima.set(im));

				}

				Variable petV = ncfile.findVariable("PET");
				Array peta = petV.read();
				Index petima = peta.getIndex();
				for (int im = 0; im < 12; im++) {
					jCcd.eq_pet[im] = peta.getDouble(petima.set(im));

				}

				Variable eetV = ncfile.findVariable("EET");
				Array eeta = eetV.read();
				Index eetima = eeta.getIndex();
				for (int im = 0; im < 12; im++) {
					jCcd.eq_eet[im] = eeta.getDouble(eetima.set(im));

				}

				Variable parV = ncfile.findVariable("PAR");
				Array para = parV.read();
				Index parima = para.getIndex();
				for (int im = 0; im < 12; im++) {
					jCcd.eq_par[im] = para.getDouble(parima.set(im));

				}

				Variable co2V = ncfile.findVariable("CO2");
				Array co2a = co2V.read();
				Index co2ima = co2a.getIndex();				 
				for (int im = 0; im < 12; im++) {
					jCcd.eq_co2[im] = co2a.getDouble(co2ima.set(im));

				}

				Variable yreetV = ncfile.findVariable("YREET");
				Array yreeta = yreetV.read();
				Index yreetima = yreeta.getIndex();
				jCcd.eq_y_eet = yreeta.getDouble(yreetima.set(0));

				Variable yrpetV = ncfile.findVariable("YRPET");
				Array yrpeta = yrpetV.read();
				Index yrpetima = yrpeta.getIndex();
				jCcd.eq_y_pet = yrpeta.getDouble(yrpetima.set(0));
				
				Variable yrco2V = ncfile.findVariable("YRCO2");
				Array yrco2a = yrco2V.read();
				Index yrco2ima = yrco2a.getIndex();
				jCcd.eq_y_co2 = yrco2a.getDouble(yrco2ima.set(0));
				
				Variable prveetmxV = ncfile.findVariable("PRVEETMX");
				Array prveetmxa = prveetmxV.read();
				Index prveetmxima = prveetmxa.getIndex();
				jCcd.eq_prveetmx = prveetmxa.getDouble(prveetmxima.set(0));

				Variable prvpetmxV = ncfile.findVariable("PRVPETMX");
				Array prvpetmxa = prvpetmxV.read();
				Index prvpetmxima = prvpetmxa.getIndex();
				jCcd.eq_prvpetmx = prvpetmxa.getDouble(prvpetmxima.set(0));

				Variable dzV = ncfile.findVariable("DZ");
				Array dza = dzV.read();
				Index dzima = dza.getIndex();

				//other variables of soil/vegetation
				for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
					jCcd.soildz[il] = dza.getDouble(dzima.set(il));
				}

				Variable typeV = ncfile.findVariable("TYPE");
				Array typea = typeV.read();
				Index typeima = typea.getIndex();

				for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
					jCcd.soiltype[il] = typea.getInt(typeima.set(il));
				}
				Variable porV = ncfile.findVariable("PORO");
				Array pora = porV.read();
				Index porima = pora.getIndex();

				for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
					jCcd.soilporo[il] = pora.getDouble(porima.set(il));
				}

				Variable reacV = ncfile.findVariable("RSOILC");
				Array reaca = reacV.read();
				Index reacima = reaca.getIndex();

				for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
					jCcd.rsoilc[il] = reaca.getDouble(reacima.set(il));
				}
				Variable noncV = ncfile.findVariable("NSOILC");
				Array nonca = noncV.read();
				Index noncima = nonca.getIndex();

				for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
					jCcd.nsoilc[il] = nonca.getDouble(noncima.set(il));
				}		
				
				Variable rootfracV = ncfile.findVariable("ROOTFRAC");
				Array rootfraca = rootfracV.read();
				Index rootfracima = rootfraca.getIndex();
               
				for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
					jCcd.rootfrac[il] = rootfraca.getDouble(rootfracima.set(il));
				}

				Variable envlaiV = ncfile.findVariable("ENVLAI");
				Array envlaia = envlaiV.read();
				Index envlaiima = envlaia.getIndex();
				for (int im = 0; im < 12; im++) {
					jCcd.envlai[im] = envlaia.getDouble(envlaiima.set(im));

				}
				 
				Variable drgV = ncfile.findVariable("DRG");
				Array drga = drgV.read();
				Index drgima = drga.getIndex();
				jCcd.drgtype = drga.getInt(drgima.set(0));
				
				Variable vegV = ncfile.findVariable("VEG");
				Array vega = vegV.read();
				Index vegima = vega.getIndex();
				jCcd.vegtype = vega.getInt(vegima.set(0));
				
				Variable numslV = ncfile.findVariable("NUMSL");
				Array numsla = numslV.read();
				Index numslima = numsla.getIndex();
				jCcd.numsoil = numsla.getInt(numslima.set(0));				

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
	
	public void createSoilClimate(EnvData ed_eq, BgcData bd_eq, Cohort cht, String ncfilename){
		try {
			NetcdfFileWriteable ncfile=NetcdfFileWriteable.createNew(ncfilename, false);
		
			Dimension chtD = ncfile.addDimension("CHTID", 1);	
			Dimension monD = ncfile.addDimension("MON", 12);	
			Dimension layD = ncfile.addDimension("LAYER", ConstLayer.MAX_SOI_LAY);
		
			ArrayList<Dimension> dim0 = new ArrayList<Dimension>();
			dim0.add(chtD);
			ncfile.addVariable("DRG", DataType.INT, dim0);
			ncfile.addVariable("VEG", DataType.INT, dim0);
			ncfile.addVariable("NUMSL", DataType.INT, dim0);
		
			ArrayList<Dimension> dim2 = new ArrayList<Dimension>();
			dim2.add(monD);
			dim2.add(layD);
			ncfile.addVariable("TS", DataType.DOUBLE, dim2);
			ncfile.addVariable("LIQ", DataType.DOUBLE, dim2);
			ncfile.addVariable("VSM", DataType.DOUBLE, dim2);
			ncfile.addVariable("ICE", DataType.DOUBLE, dim2);
			ncfile.addVariable("SWS", DataType.DOUBLE, dim2);
		
			ArrayList<Dimension> dimL = new ArrayList<Dimension>();
			dimL.add(layD);
			ncfile.addVariable("RSOILC", DataType.DOUBLE, dimL);
			ncfile.addVariable("NSOILC", DataType.DOUBLE, dimL);
			ncfile.addVariable("DZ", DataType.DOUBLE, dimL);
			ncfile.addVariable("TYPE", DataType.DOUBLE, dimL);
			ncfile.addVariable("PORO", DataType.DOUBLE, dimL);
			ncfile.addVariable("ROOTFRAC", DataType.DOUBLE, dimL);
		
			ArrayList<Dimension> dimM = new ArrayList<Dimension>();
			dimM.add(monD);
			ncfile.addVariable("TA", DataType.DOUBLE, dimM);
			ncfile.addVariable("GROW", DataType.DOUBLE, dimM);
			ncfile.addVariable("CO2", DataType.DOUBLE, dimM);
			ncfile.addVariable("PET", DataType.DOUBLE, dimM);
			ncfile.addVariable("EET", DataType.DOUBLE, dimM);
			ncfile.addVariable("PAR", DataType.DOUBLE, dimM);
			ncfile.addVariable("ENVLAI", DataType.FLOAT, dimM);

			ncfile.addVariable("YREET", DataType.DOUBLE, dim0);
			ncfile.addVariable("YRPET", DataType.DOUBLE, dim0);
			ncfile.addVariable("YRCO2", DataType.DOUBLE, dim0);
			ncfile.addVariable("PRVEETMX", DataType.DOUBLE, dim0);
			ncfile.addVariable("PRVPETMX", DataType.DOUBLE, dim0);
	
			try {
				ncfile.create();
			}catch (IOException e) {
				System.err.println("Error in creating file"+e+"\n");
			}		
		
		//writing to calirestart.nc file
			try {
				ArrayInt.D1 dataI=new ArrayInt.D1(chtD.getLength());
				jCcd.vegtype=ed_eq.getCd().getVegtype();
				dataI.set(dataI.getIndex().set(0),jCcd.vegtype);
				ncfile.write("VEG", dataI);
			
				jCcd.drgtype=ed_eq.getCd().getDrgtype();
				dataI.set(dataI.getIndex().set(0),jCcd.drgtype);
				ncfile.write("DRG", dataI);

				jCcd.numsoil=ed_eq.getM_soid().getActual_num_soil();
				dataI.set(dataI.getIndex().set(0),jCcd.numsoil);
				ncfile.write("NUMSL", dataI);

				//monthly-layered data writing
				int [] origin = new int[2];
				ArrayDouble.D2 data2= new ArrayDouble.D2(monD.getLength(), layD.getLength());
				Index ima=data2.getIndex();
			
				jCcd.eq_ts=ed_eq.getEq_ts1d();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						data2.setDouble(ima.set(im,il), jCcd.eq_ts[imil]);
					}
				}
				ncfile.write("TS", origin, data2);			
			
				jCcd.eq_liq=ed_eq.getEq_liq1d();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						data2.setDouble(ima.set(im,il), jCcd.eq_liq[imil]);
					}
				}
				ncfile.write("LIQ", origin, data2);			
			
				jCcd.eq_vwc=ed_eq.getEq_vwc1d();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						data2.setDouble(ima.set(im,il), jCcd.eq_vwc[imil]);
					}
				}
				ncfile.write("VSM", origin, data2);		
			
				jCcd.eq_ice=ed_eq.getEq_ice1d();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						data2.setDouble(ima.set(im,il), jCcd.eq_ice[imil]);
					}
				}
				ncfile.write("ICE", origin, data2);
			
				jCcd.eq_sws=ed_eq.getEq_sws1d();
				for (int im = 0; im < 12; im++) {
					for (int il = 0; il < ConstLayer.MAX_SOI_LAY; il++) {
						int imil=im*ConstLayer.MAX_SOI_LAY+il;
						data2.setDouble(ima.set(im,il), jCcd.eq_sws[imil]);
					}
				}
				ncfile.write("SW", origin, data2);

			//monthly data writing 
				ArrayDouble.D1 dataM= new ArrayDouble.D1(monD.getLength());
				Index imb=dataM.getIndex();
				jCcd.eq_ta=ed_eq.getEq_ta();
				for (int im=0; im<12; im++){
					dataM.setDouble(imb.set(im), jCcd.eq_ta[im]);
				}
				ncfile.write("TA", dataM);
			
				jCcd.eq_pet=ed_eq.getEq_pet();
				for (int im=0; im<12; im++){
					dataM.setDouble(imb.set(im), jCcd.eq_pet[im]);
				}
			
				ncfile.write("EET", dataM);
				jCcd.eq_eet=ed_eq.getEq_eet();
				for (int im=0; im<12; im++){
					dataM.setDouble(imb.set(im), jCcd.eq_eet[im]);
				}
				ncfile.write("EET", dataM);
			
				jCcd.eq_co2=ed_eq.getEq_co2();
				for (int im=0; im<12; im++){
					dataM.setDouble(imb.set(im), jCcd.eq_co2[im]);
				}
				ncfile.write("CO2", dataM);
			
				jCcd.eq_par=ed_eq.getEq_par();
				for (int im=0; im<12; im++){
					dataM.setDouble(imb.set(im), jCcd.eq_par[im]);
				}
				ncfile.write("PAR", dataM);
			
				jCcd.eq_grow=ed_eq.getEq_grow();
				for (int im=0; im<12; im++){
					dataM.setDouble(imb.set(im), jCcd.eq_grow[im]);
				}
				ncfile.write("GROW", dataM);

				jCcd.envlai=cht.getVeenvlai();
				for (int im=0; im<12; im++){
					dataM.setDouble(imb.set(im), jCcd.envlai[im]);
				}
				ncfile.write("ENVLAI", dataM);
			
				//layerd data writing
				ArrayDouble.D1 dataL= new ArrayDouble.D1(layD.getLength());
				Index imc=dataL.getIndex();
				jCcd.soiltype=ed_eq.getM_sois().getType();
				for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
					dataL.setDouble(imc.set(il), jCcd.soiltype[il]);
				}
				ncfile.write("TYPE", dataL);

				jCcd.soilporo=ed_eq.getM_sois().getPor();
				for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
					dataL.setDouble(imc.set(il), jCcd.soilporo[il]);
				}
				ncfile.write("PORO", dataL);
			
				jCcd.soildz=ed_eq.getM_sois().getDz();
				for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
					dataL.setDouble(imc.set(il), jCcd.soildz[il]);
				}
				ncfile.write("DZ", dataL);
			
				jCcd.rsoilc=bd_eq.getM_sois().getReac();
				for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
					dataL.setDouble(imc.set(il), jCcd.rsoilc[il]);
				}
				ncfile.write("RSOILC", dataL);
			
				jCcd.nsoilc=bd_eq.getM_sois().getNonc();
				for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
					dataL.setDouble(imc.set(il), jCcd.nsoilc[il]);
				}
				ncfile.write("NSOILC", dataL);
			
				jCcd.rootfrac=ed_eq.getM_sois().getRootfrac();
				for (int il=0; il<ConstLayer.MAX_SOI_LAY; il++){
					dataL.setDouble(imc.set(il), jCcd.rootfrac[il]);
				}
				ncfile.write("ROOTFRAC", dataL);
			
				//yearly data writing
				ArrayDouble.D1 dataY=new ArrayDouble.D1(chtD.getLength());
				jCcd.eq_y_eet=ed_eq.getEq_y_eet();
				dataY.set(dataY.getIndex().set(0),jCcd.eq_y_eet);
				ncfile.write("YREET", dataY);
			
				jCcd.eq_y_pet=ed_eq.getEq_y_pet();
				dataY.set(dataY.getIndex().set(0),jCcd.eq_y_pet);
				ncfile.write("YRPET", dataY);

				jCcd.eq_y_co2=ed_eq.getEq_y_co2();
				dataY.set(dataY.getIndex().set(0),jCcd.eq_y_co2);
				ncfile.write("YRCO2", dataY);

				jCcd.eq_prveetmx=ed_eq.getEq_prveetmx();
				dataY.set(dataY.getIndex().set(0),jCcd.eq_prveetmx);
				ncfile.write("PRVEETMX", dataY);

				jCcd.eq_prvpetmx=ed_eq.getEq_prvpetmx();
				dataY.set(dataY.getIndex().set(0),jCcd.eq_prvpetmx);
				ncfile.write("PRVPETMX", dataY);
			
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

		} catch (Exception e) {
			
		}

	};
	
}