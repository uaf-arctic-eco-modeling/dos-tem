package GUI;

//from cpp (for getting instant data)
import TEMJNI.Cohort;

//GUI
import GUI.BioVariablePlotter;
import GUI.PhyVariablePlotter;

public class PlotterUpdate {
		
	BioVariablePlotter varplotter;
	PhyVariablePlotter var2plotter;
	
	// methods	

	public void setPlotter(BioVariablePlotter bvp){
		varplotter = bvp;
	}

	public void setPlotter2(PhyVariablePlotter pvp){
		var2plotter = pvp;
	}
	
	public void updateYlyBioGraph(int yrcnt, Cohort cht){		//update plots

		if(yrcnt%1 ==0){
			//flux variables
			varplotter.nppTP.addPoint((double) yrcnt, cht.getBd().getY_a2v().getNpp());
			varplotter.gppTP.addPoint((double) yrcnt, cht.getBd().getY_a2v().getGpp());
			varplotter.innppTP.addPoint((double) yrcnt, cht.getBd().getY_a2v().getInnpp());
			varplotter.ingppTP.addPoint((double) yrcnt, cht.getBd().getY_a2v().getGpp());
			varplotter.raTP.addPoint((double) yrcnt, cht.getBd().getY_v2a().getRg()+cht.getBd().getY_v2a().getRm());			
			double sumrh=0;
			double[] rrh = cht.getBd().getY_soi2a().getRrh();
			double[] nrh = cht.getBd().getY_soi2a().getNrh();
			for (int il=0; il<rrh.length; il++){
				sumrh=sumrh+rrh[il]+nrh[il];
			}
			varplotter.rhTP.addPoint((double) yrcnt, sumrh);
	
			varplotter.ltrfalcTP.addPoint((double) yrcnt, cht.getBd().getY_v2soi().getLtrfalc());
			varplotter.ltrfalnTP.addPoint((double) yrcnt, cht.getBd().getY_v2soi().getLtrfaln());
			varplotter.netnminTP.addPoint((double) yrcnt, cht.getBd().getY_soi2soi().getNetnmin());
			varplotter.nuptakeTP.addPoint((double) yrcnt, cht.getBd().getY_soi2v().getNuptake());
		 			
			varplotter.vegcTP.addPoint((double) yrcnt, cht.getBd().getY_vegs().getC());
			
			double fib =cht.getBd().getY_soid().getShlwc();
			double hum =cht.getBd().getY_soid().getDeepc();
			double mine=cht.getBd().getY_soid().getMinec();			
			varplotter.fibsoilcTP.addPoint((double) yrcnt, fib);
			varplotter.humsoilcTP.addPoint((double) yrcnt, hum);
			varplotter.minesoilcTP.addPoint((double) yrcnt, mine);
			varplotter.allsoilcTP.addPoint((double) yrcnt, fib+hum+mine);
			
			varplotter.vegnTP.addPoint((double) yrcnt, cht.getBd().getY_vegs().getSton() 
					                                + cht.getBd().getY_vegs().getStrn());
			varplotter.orgnTP.addPoint((double) yrcnt, cht.getBd().getY_sois().getOrgn());		
			varplotter.avlnTP.addPoint((double) yrcnt, cht.getBd().getY_sois().getAvln());
				
			varplotter.laiTP.addPoint((double) yrcnt, cht.getBd().getY_vegd().getLai());
			varplotter.fpcTP.addPoint((double) yrcnt, cht.getBd().getY_vegd().getFpc());
		
		}
		
	};
		
	public void updateMlyBioGraph(int yrcnt, int im, Cohort cht){		//update plots
		    double mcnt = yrcnt+im/12.0; 
			
		    varplotter.mgppTP.addPoint((double) mcnt, cht.getBd().getM_a2v().getGpp());
			varplotter.mnppTP.addPoint((double) mcnt, cht.getBd().getM_a2v().getNpp());

			double ra =cht.getBd().getM_v2a().getRm()+cht.getBd().getM_v2a().getRg();
			double rh=0;
			double[] rrh = cht.getBd().getM_soi2a().getRrh();
			double[] nrh = cht.getBd().getM_soi2a().getNrh();
			for (int il=0; il<rrh.length; il++){
				rh=rh+rrh[il]+nrh[il];
			}
			varplotter.mrespTP.addPoint((double) mcnt, ra+rh);
			
			varplotter.mltrfalcTP.addPoint((double) mcnt, cht.getBd().getM_v2soi().getLtrfalc());
			varplotter.mltrfalnTP.addPoint((double) mcnt, cht.getBd().getM_v2soi().getLtrfaln());
			varplotter.mnetnminTP.addPoint((double) mcnt,  cht.getBd().getM_soi2soi().getNetnmin());
			varplotter.mlaiTP.addPoint((double) mcnt, cht.getBd().getM_vegd().getLai());
			varplotter.mvegcTP.addPoint((double) mcnt,cht.getBd().getM_vegs().getC());
			varplotter.mvegnTP.addPoint((double) mcnt, cht.getBd().getM_vegs().getSton()+
					                                cht.getBd().getM_vegs().getStrn());
			varplotter.mavlnTP.addPoint((double) mcnt, cht.getBd().getM_sois().getAvln());
					
	};

	public void updateYlyPhyGraph(int ycnt, Cohort cht){		//update plots
		
		if (ycnt%1==0){
			// at yearly time-step
			double[] ts=cht.getEd().getY_soid().getTem();
			double[] vwc=cht.getEd().getY_soid().getAllvwc();
			double[] type=cht.getEd().getY_sois().getType();
			double[] dz=cht.getEd().getY_sois().getDz();

			double dz1=0., dz2=0., dz3=0.;
			int imx = 0;
			for (int il=0; il<type.length; il++){
				if (type[il]==1) {dz1+=dz[il];}
				if (type[il]==2) {dz2+=dz[il];}
				if (type[il]==3 && dz3<=0.50) {dz3+=dz[il]; imx=il;}  //the mineral soil within 0.5 m
			}
			double ts1=0., ts2=0., ts3=0.;
			double vwc1=0., vwc2=0., vwc3=0.;
			for (int il=0; il<type.length; il++){
				if (type[il]==1) {
					ts1+=ts[il]*dz[il]/dz1; 
					vwc1+=vwc[il]*dz[il]/dz1;
				} else if (type[il]==2) {
					ts2+=ts[il]*dz[il]/dz2; 
					vwc2+=vwc[il]*dz[il]/dz2;
				} else if (type[il]==3 && il<=imx) {  //the mineral soil within 0.5 m
					ts3+=ts[il]*dz[il]/dz3; 
					vwc3+=vwc[il]*dz[il]/dz3;
				}
			}

			var2plotter.ts1TP.addPoint((double) ycnt, cht.getEd().getY_atms().getTa(),
					cht.getEd().getY_sois().getTsave());
			
			double thickness =0.;
			for (int il=0; il<dz.length; il++){
				if (dz[il]>0.0) thickness+=dz[il];				
			}
			double vwcLiq=cht.getEd().getY_sois().getLiqsum()*0.001/thickness;
			double vwcIce=cht.getEd().getY_sois().getIcesum()*0.0009/thickness;
			var2plotter.vwc1TP.addPoint((double) ycnt, vwcLiq, vwcIce);

			var2plotter.ts2TP.addPoint((double) ycnt, ts1, ts2, ts3,
					cht.getEd().getY_atms().getTa());

			var2plotter.vwc2TP.addPoint((double) ycnt, vwc1, vwc2, vwc3);

			var2plotter.etTP.addPoint((double) ycnt, cht.getEd().getY_l2a().getPet(),
			                                         cht.getEd().getY_l2a().getEet());

			var2plotter.qoutTP.addPoint((double) ycnt, cht.getEd().getY_a2l().getRnfl(),
                                                       cht.getEd().getY_a2l().getSnfl(),
                                                       cht.getEd().getY_soi2l().getQover(),
                                                       cht.getEd().getY_soi2l().getQdrain());
						
			var2plotter.watertabTP.addPoint((double) ycnt, cht.getEd().getY_soid().getWatertab());
			var2plotter.mossthickTP.addPoint((double) ycnt, cht.getEd().getY_soid().getMossthick());
			var2plotter.peatthickTP.addPoint((double) ycnt, cht.getEd().getY_soid().getShlwthick()
			                                              , cht.getEd().getY_soid().getDeepthick());

			var2plotter.aldTP.addPoint((double) ycnt, cht.getEd().getY_ald()
                                                    , cht.getEd().getY_ald());

		}
	};
	
	public void updateMlyPhyGraph(int ycnt, int im, Cohort cht){		//update plots
		
		double ymcnt = ycnt+im/12.0;
		
		//left
		var2plotter.mpptTP.addPoint((double) ymcnt, cht.getEd().getM_a2l().getRnfl()
				                            ,cht.getEd().getM_a2l().getSnfl());
		var2plotter.mppfdTP.addPoint((double) ymcnt, cht.getEd().getM_vegd().getM_ppfd());
		var2plotter.mtaTP.addPoint((double) ymcnt, cht.getEd().getM_atms().getTa());
		var2plotter.metTP.addPoint((double) ymcnt, cht.getEd().getM_l2a().getPet()
                                                  ,cht.getEd().getM_l2a().getEet());	
		var2plotter.mqoutTP.addPoint((double) ymcnt, cht.getEd().getM_soi2l().getQover()
                                                  ,cht.getEd().getM_soi2l().getQdrain());	
		
		//right
		var2plotter.maldTP.addPoint((double) ymcnt, cht.getEd().getY_ald());

		double[] ts=cht.getEd().getM_soid().getTem();
		double[] vwc=cht.getEd().getM_soid().getAllvwc();
		double[] type=cht.getEd().getM_sois().getType();
		double[] dz=cht.getEd().getM_sois().getDz();

		double dz1=0., dz2=0., dz3=0., dz4= 0.;
		int imx = 0;
		for (int il=0; il<type.length; il++){
			if (type[il]==1) {dz1+=dz[il];}
			if (type[il]==2) {dz2+=dz[il];}
			if (type[il]==3 && dz3<=0.20) {dz3+=dz[il]; imx=il;}  //the mineral soil within 0.2 m
			if (type[il]==3) {dz4+=dz[il];}  //the whole mineral soil column
		}

		double ts1 =0.; double ts2=0.; double ts3=0.; double ts4=0.;
		double vwc1 =0.; double vwc2=0.; double vwc3=0.; double vwc4=0.;
		for (int il=0; il<type.length; il++){
			if (type[il]==1) {
				ts1+=ts[il]*dz[il]/dz1; 
				vwc1+=vwc[il]*dz[il]/dz1;
			} else if (type[il]==2) {
				ts2+=ts[il]*dz[il]/dz2; 
				vwc2+=vwc[il]*dz[il]/dz2;
			} else if (type[il]==3) {
				if (il<=imx) {
					ts3+=ts[il]*dz[il]/dz3; 
					vwc3+=vwc[il]*dz[il]/dz3;
				}

				ts4+=ts[il]*dz[il]/dz4; 
				vwc4+=vwc[il]*dz[il]/dz4;
				
			}
		}
				
		var2plotter.mts1TP.addPoint((double) ymcnt, ts1,ts2);
		var2plotter.mts2TP.addPoint((double) ymcnt, ts3,ts4);
		
		var2plotter.mvwc1TP.addPoint((double) ymcnt, vwc1,vwc2);
		var2plotter.mvwc2TP.addPoint((double) ymcnt, vwc3,vwc4);

	};
	
}
