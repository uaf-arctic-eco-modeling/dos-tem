
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.SpringLayout;

import calTEM.*;
import GUI.*;
import runTEM.runner; // not sure why not all symbols from this dir??

public class TEMCalibrator {
	
	// using GUI or not to run Calibration mode   
	static boolean GUI = true;

	public static void main(String[] args) throws Exception{	
		System.loadLibrary("temcore");
		
		//message box for information
		try {
			JFrame f = new JFrame("TEM Run Info");
			f.setLayout(new BorderLayout());
			f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
			JTextArea teminfoTA = new JTextArea();
			teminfoTA.append(null);
			
			SpringLayout slayout = new SpringLayout();
			slayout.putConstraint(SpringLayout.NORTH, teminfoTA, 5,SpringLayout.NORTH, f);
			slayout.putConstraint(SpringLayout.WEST,teminfoTA, 0,SpringLayout.WEST, f);

			f.add(teminfoTA, BorderLayout.CENTER);
			
			f.setLocation(500,1);
			f.setPreferredSize(new Dimension(500, 800));
			f.setSize(300, 600);
			f.setVisible(true);
	    
			MessageConsole mc = new MessageConsole(teminfoTA);
			mc.redirectOut(null, System.out);
			mc.redirectErr(Color.RED, null);
			mc.setMessageLines(30);

		} catch (Exception e){	  	
			System.out.println(e.getMessage());
		} finally {
			//System.out.println("In final");
		}

		System.out.println("TEM Calibrator - Java Version 1.0");
		System.out.println("F.-M. YUAN");
		System.out.println("The Spatial Ecological Laboratory");
		System.out.println("University of Alaska Fairbanks");
		
		//logger
		//org.apache.log4j.BasicConfigurator.configure();
	    //org.apache.log4j.Logger logger = org.apache.log4j.Logger.getRootLogger();
	    //logger.setLevel(org.apache.log4j.Level.OFF);	

	    //			
		if (GUI) {			
						
			TCGUI tcgui = new TCGUI();

			Configurer config = new Configurer();
			BioVariablePlotter bvplotter =new BioVariablePlotter();
			PhyVariablePlotter pvplotter =new PhyVariablePlotter();

			tcgui.setConfigurer(config);
			tcgui.setVarPlotter(bvplotter);
			tcgui.setVar2Plotter(pvplotter);
								
		} else {			//TEM run 

			TEMeqrunner Caliber = new TEMeqrunner();
			Caliber.eqrunner = new runner();
			
			//TEM I/O options
			Caliber.eqrunner.controlfile = "config/calibcontrol.txt";
			
			Caliber.eqrunner.runcht.califilein     = true;  //switch to read-in calibrated parameters from Jcalinput.txt			
			Caliber.eqrunner.runcht.inicali        = true;  //(only valid if 'califilein' above is set to true)switch to read-in initial C conditions, if read-in calpar from Jcalinput.txt

			Caliber.eqrunner.runcht.usecalirestart = false;   //switch to read-in Env. driver for equilibrim-run from calirestart.nc 
			Caliber.eqrunner.runcht.outcalirestart = true;   //only valid if 'usecalirestart' above is set to false
			
			Caliber.eqrunner.runcht.outmodes.OSITER  = false;
			Caliber.eqrunner.runcht.outmodes.ODAY    = false;
			Caliber.eqrunner.runcht.outmodes.OMONTH  = false;
			Caliber.eqrunner.runcht.outmodes.OYEAR   = false;
			Caliber.eqrunner.runcht.outmodes.OREGNER = false;					
			Caliber.eqrunner.runcht.outmodes.OSCLM   = false;					

			Caliber.eqrunner.runcht.GUIgraphic=false;
			//TEM general initialization and data-reading
			Caliber.init();
				
			//cohort IDs and cruID
			
		}
	
	}

}
