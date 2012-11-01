package GUI;

//TEM Calibration Runner GUI

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.io.BufferedReader;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;

import javax.swing.*;
import javax.swing.event.*;

import TEMJNI.soipar_bgc;
import TEMJNI.vegpar_bgc;
import calTEM.Configurer;
import calTEM.ParameterChanger;
import calTEM.TEMeqrunner;
import runTEM.runner;

public class TCGUI{
	BioVariablePlotter varplotter;
	public void setVarPlotter(BioVariablePlotter bvp){
		varplotter = bvp;
	}
	
	PhyVariablePlotter var2plotter;
	public void setVar2Plotter(PhyVariablePlotter pvp){
		var2plotter = pvp;
	}

	TEMeqrunner Caliber = new TEMeqrunner();
	
	Configurer config;
	JTextField configTF;
	
	JTextField controlTF;
	JTextField driverTF;
	JTextField calparTF;
	JTextField outputTF;
		
	JTable calparTB;
	JTable stateTB;
	JTable targetTB;
	JTable fixparTB;
	
	JButton selectConfigB;
	JButton updateConfigB;
	JButton updateCalB;
		 
	JRadioButton[] nfeedjrb = new JRadioButton[2];
	ButtonGroup nfeedjbg = new ButtonGroup();
	JRadioButton[] avlnjrb= new JRadioButton[2];
	ButtonGroup avlnjbg = new ButtonGroup();
	JRadioButton[] baselinejrb= new JRadioButton[2];
	ButtonGroup baselinejbg = new ButtonGroup();	
	JRadioButton[] modulejrb= new JRadioButton[2];
	ButtonGroup modulejbg = new ButtonGroup();
	
	JFrame f;
 
	JButton setupB;
	JButton resetupB;
	JButton runmodeB;
	
	JButton exitB;
	JButton startpauseB;

	JButton parresetB;
	JButton parrestoreB;
	JButton paroutputB;
	 
	ParameterChanger friChanger;

	ParameterChanger cmaxChanger;
	ParameterChanger nmaxChanger;
	ParameterChanger krbChanger;
	ParameterChanger nupChanger;
	
	ParameterChanger nfallChanger;
	ParameterChanger cfallChanger;

	ParameterChanger kdcfibChanger;
	ParameterChanger kdchumChanger;
	ParameterChanger kdcminChanger;
	ParameterChanger kdcslowChanger;
	
	JTabbedPane controlTP;

	public TCGUI(){
		f = new JFrame("TEM Calibrator Java Version");

		f.setLayout(new BorderLayout());
		f.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		
		//
		configTF = new JTextField();
		configTF.setEditable(false);

        controlTF = new JTextField();
        driverTF = new JTextField();
        calparTF = new JTextField();
        outputTF = new JTextField();
        
        selectConfigB = new JButton("Select");
        selectConfigB.addActionListener(new ConfigureSelector());
     
        setupB = new JButton("Setup");
        setupB.addActionListener(new Setup());
        setupB.setEnabled(false);

        resetupB = new JButton("Re-Setup");
        resetupB.addActionListener(new Resetup());
        resetupB.setEnabled(false);

        runmodeB = new JButton("Calibration");
        runmodeB.addActionListener(new RunMode());
        runmodeB.setEnabled(false);

        exitB = new JButton("EXIT");
        exitB.addActionListener(new Exit());
        exitB.setEnabled(true);

        startpauseB = new JButton("Start");
        startpauseB.addActionListener(new StartPause());
        startpauseB.setEnabled(false);
        
        parresetB = new JButton("Reset to Init");
        parresetB.addActionListener(new ParameterResetter());
        parresetB.setEnabled(false);

        parrestoreB = new JButton("Reset to Prev");
        parrestoreB.addActionListener(new ParameterRestorer());
        parrestoreB.setEnabled(false);

        paroutputB = new JButton("Output");
        paroutputB.addActionListener(new ParameterOutputer());
        paroutputB.setEnabled(false);
                
        friChanger = new ParameterChanger("FRI",0.,0, 0);
        friChanger.pmmTF.addActionListener(ParameterChanged);
        friChanger.setEnabled(false);

        cmaxChanger = new ParameterChanger("CMAX",0.,0, 0);
        cmaxChanger.pmmTF.addActionListener(ParameterChanged);
        cmaxChanger.setEnabled(false);
        
        nmaxChanger = new ParameterChanger("NMAX",0., 0, 0);
        nmaxChanger.pmmTF.addActionListener(ParameterChanged);
        nmaxChanger.setEnabled(false);

        krbChanger = new ParameterChanger("KRB",0, 0, 0);
        krbChanger.pmmTF.addActionListener(ParameterChanged);
        krbChanger.setEnabled(false);

        cfallChanger = new ParameterChanger("CFALL", 0.,0, 0);
        cfallChanger.pmmTF.addActionListener(ParameterChanged);
        cfallChanger.setEnabled(false);

        nfallChanger = new ParameterChanger("NFALL", 0.,0, 0);
        nfallChanger.pmmTF.addActionListener(ParameterChanged);
        nfallChanger.setEnabled(false);

        nupChanger = new ParameterChanger("NUP",0.,0, 0);
        nupChanger.pmmTF.addActionListener(ParameterChanged);
        nupChanger.setEnabled(false);

        kdcfibChanger = new ParameterChanger("KDCFIB", 0.,0, 0);
        kdcfibChanger.pmmTF.addActionListener(ParameterChanged);
        kdcfibChanger.setEnabled(false);

        kdchumChanger = new ParameterChanger("KDCHUM", 0.,0, 0);
        kdchumChanger.pmmTF.addActionListener(ParameterChanged);
        kdchumChanger.setEnabled(false);

        kdcminChanger = new ParameterChanger("KDCMIN", 0.,0, 0);
        kdcminChanger.pmmTF.addActionListener(ParameterChanged);
        kdcminChanger.setEnabled(false);
        
        kdcslowChanger = new ParameterChanger("KDCSLOW", 0.,0, 0);
        kdcslowChanger.pmmTF.addActionListener(ParameterChanged);
        kdcslowChanger.setEnabled(false);
        
        String[] calColName = {"Name", "Value",  "Increment"};
        String[] stateColName = {"Name", "Value"};
        
        String[] calName ={"CMAX", "NMAX", "KRB", "NUP","CFALL","NFALL", "KDCFIB", "KDCHUM", "KDCMIN", "KDCSLOW"};
        String[] stateName ={"VEG.TYPE","DRG.TYPE","FIBRIC THICK","HUMIC THICK","INIT. VEGC","INIT. VEGN","INIT. AVL. N","INIT. SOILC","INIT. SOILN"};
        String[] targetName ={"NPP","GPP","NPPSAT", "NUPTAKE", "VEGC", "VEGN",  "SOILC","FIBSOILC","HUMSOILC", "MINESOILC", "AVAILN", "SOILN"};
        String[] fixparName ={"Leaf_m1", "Leaf_m2", "Leaf_m3", "Leaf_m4","Soil_fsoma","Soil_fsompr", "Soil_fsomcr", "Soil_som2co2"};
        
        int rows1 = calName.length;
        int cols1 = 5;
        String[][] calValue = new String[rows1][cols1];
        for(int ir=0; ir<rows1; ir++){
        	calValue[ir][0] = calName[ir];
        	for(int ic =1; ic<cols1; ic++){
        		calValue[ir][ic] =" "; 
        	}
        }
      
        calparTB = new JTable(calValue, calColName);
              
        int rows2 = stateName.length;
        int cols2 = 2;
        String[][] statValue = new String[rows2][cols2];
        for(int ir=0; ir<rows2; ir++){
        	statValue[ir][0] = stateName[ir];
        	for(int ic =1; ic<cols2; ic++){
        		statValue[ir][ic] =" "; 
        	}
        }
      
        stateTB = new JTable(statValue, stateColName);
		stateTB.getModel().addTableModelListener(tabvalueChanger);
        
        int rows3 = targetName.length;
        int cols3 = 2;
        String[][] targetValue = new String[rows3][cols3];
        for(int ir=0; ir<rows3; ir++){
        	targetValue[ir][0] = targetName[ir];
        	for(int ic =1; ic<cols3; ic++){
        		targetValue[ir][ic] =" "; 
        	}
        }
        targetTB = new JTable(targetValue, stateColName);
 
        int rows4 = fixparName.length;
        int cols4 = 2;
        String[][] fixparValue = new String[rows4][cols4];
        for(int ir=0; ir<rows4; ir++){
        	fixparValue[ir][0] = fixparName[ir];
        	for(int ic =1; ic<cols4; ic++){
        		fixparValue[ir][ic] =" "; 
        	}
        }     
        fixparTB = new JTable(fixparValue, stateColName);
		fixparTB.getModel().addTableModelListener(tabvalueChanger);
        
        controlTP = new JTabbedPane();
        try {
 		    
		//Configuration Tab of Control Panel
        	JPanel configP = new JPanel();
		    
		    SpringLayout slayout = new SpringLayout();
			configP.setLayout(slayout);

			JLabel configL = new JLabel("Configure File");
			configL.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, configL, 0,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,configL, 0,SpringLayout.WEST, configP);
			configP.add(configL);
			configTF.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, configTF, 35,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,configTF, 0,SpringLayout.WEST, configP);
			configP.add(configTF);
			 
			selectConfigB.setPreferredSize(new Dimension(80, 30));
			slayout.putConstraint(SpringLayout.NORTH, selectConfigB, 35,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,selectConfigB, 405,SpringLayout.WEST, configP);
			configP.add(selectConfigB);
			
			JLabel controlL = new JLabel("Model Control File");
			controlL.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, controlL, 80,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,controlL, 0,SpringLayout.WEST, configP);
			configP.add(controlL);
			controlTF.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, controlTF, 115,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,controlTF, 0,SpringLayout.WEST, configP);
			configP.add(controlTF);

			JLabel driverL = new JLabel("Environmental Driver File");
			driverL.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, driverL, 160,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,driverL, 0,SpringLayout.WEST, configP);
			configP.add(driverL);
			driverTF.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, driverTF, 195,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,driverTF, 0,SpringLayout.WEST, configP);
			configP.add(driverTF);

			JLabel calparL = new JLabel("Initial Parameter File");
			calparL.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, calparL, 230,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,calparL, 0,SpringLayout.WEST, configP);
			configP.add(calparL);
			calparTF.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, calparTF, 265,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,calparTF, 0,SpringLayout.WEST, configP);
			configP.add(calparTF);		
			
			JLabel outputL = new JLabel("Parameter Output File");
			outputL.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, outputL, 300,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,outputL, 0,SpringLayout.WEST, configP);
			configP.add(outputL);
			outputTF.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, outputTF, 335,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,outputTF, 0,SpringLayout.WEST, configP);
			configP.add(outputTF);		
			
			JTabbedPane tableTP = new JTabbedPane();
			
			JScrollPane calparSP = new JScrollPane(calparTB);
			calparSP.setPreferredSize(new Dimension(400, 200));
			tableTP.add("Parameters to calibrate", calparSP);
			
			JScrollPane fixparSP = new JScrollPane(fixparTB);
			fixparSP.setPreferredSize(new Dimension(400, 200));
			tableTP.add("FixedParameters", fixparSP);

			JScrollPane stateSP = new JScrollPane(stateTB);
			stateSP.setPreferredSize(new Dimension(400, 200));
			tableTP.add("InputState", stateSP);
			
			JScrollPane targetSP = new JScrollPane(targetTB);
			targetSP.setPreferredSize(new Dimension(400, 200));
			tableTP.add("TargetState", targetSP);
						
			tableTP.setPreferredSize(new Dimension(400, 200));
			slayout.putConstraint(SpringLayout.NORTH, tableTP, 400,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,tableTP, 0,SpringLayout.WEST, configP);
			configP.add(tableTP);
					
	   // The Calibration Tab of Control Panel		
			JPanel caliP = new JPanel();   			 
			caliP.setLayout(slayout);
			
			//N process switch for TEM
			JLabel label1= new JLabel ("----- TEM N CYCLE SWITCHES ------");
			label1.setPreferredSize(new Dimension(250, 30));
			slayout.putConstraint(SpringLayout.NORTH, label1, 0,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST, label1, 0 ,SpringLayout.WEST, caliP);
			caliP.add(label1);

			JLabel nfeedL= new JLabel ("Nfeed");
			nfeedL.setPreferredSize(new Dimension(60, 25));
			slayout.putConstraint(SpringLayout.NORTH, nfeedL, 20,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST, nfeedL, 10 ,SpringLayout.WEST, caliP);
			caliP.add(nfeedL);
			String nfeedS[] = new String[2];
			nfeedS[0] = "No";
			nfeedS[1] = "Yes";
			JPanel nfeedP = getRBPanel(nfeedjbg, 2, 180, 30, nfeedjrb, nfeedS);
			nfeedP.setPreferredSize(new Dimension(180,30));
			slayout.putConstraint(SpringLayout.NORTH, nfeedP, 20,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,nfeedP, 80,SpringLayout.WEST, caliP);
			caliP.add(nfeedP);
			nfeedjrb[0].addActionListener(ProcessSwitcher);
			nfeedjrb[1].addActionListener(ProcessSwitcher);
			nfeedjrb[0].setEnabled(false);
			nfeedjrb[1].setEnabled(false);
				
			JLabel avlnL= new JLabel ("avlnflag");
			avlnL.setPreferredSize(new Dimension(60, 25));
			slayout.putConstraint(SpringLayout.NORTH, avlnL, 45,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST, avlnL, 10 ,SpringLayout.WEST, caliP);
			caliP.add(avlnL);
			String avlns[] = new String[2];
			avlns[0] = "No";
			avlns[1] = "Yes";
			JPanel avlnP = getRBPanel(avlnjbg, 2, 150, 30, avlnjrb, avlns);
			avlnP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, avlnP, 45,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,avlnP, 80,SpringLayout.WEST, caliP);
			caliP.add(avlnP);
			avlnjrb[0].addActionListener(ProcessSwitcher);
			avlnjrb[1].addActionListener(ProcessSwitcher);
			avlnjrb[0].setEnabled(false);
			avlnjrb[1].setEnabled(false);
				
			JLabel baselineL= new JLabel ("baseline");
			baselineL.setPreferredSize(new Dimension(60, 25));
			slayout.putConstraint(SpringLayout.NORTH, baselineL, 70,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST, baselineL, 10 ,SpringLayout.WEST, caliP);
			caliP.add(baselineL);
			String baselines[] = new String[2];
			baselines[0] = "No";
			baselines[1] = "Yes";
			JPanel baselineP = getRBPanel(baselinejbg, 2, 150, 30, baselinejrb, baselines);
			baselineP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, baselineP, 70,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,baselineP, 80,SpringLayout.WEST, caliP);
			caliP.add(baselineP);
			baselinejrb[0].addActionListener(ProcessSwitcher);
			baselinejrb[1].addActionListener(ProcessSwitcher);
			baselinejrb[0].setEnabled(false);
			baselinejrb[1].setEnabled(false);

			JLabel moduleL= new JLabel ("multi-module");
			moduleL.setPreferredSize(new Dimension(85, 25));
			slayout.putConstraint(SpringLayout.NORTH, moduleL, 95,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST, moduleL, 1 ,SpringLayout.WEST, caliP);
			caliP.add(moduleL);
			String moduleS[] = new String[2];
			moduleS[0] = "No";
			moduleS[1] = "Yes";
			JPanel moduleP = getRBPanel(modulejbg, 2, 150, 30, modulejrb, moduleS);
			moduleP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, moduleP, 95,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,moduleP, 80,SpringLayout.WEST, caliP);
			caliP.add(moduleP);
			modulejrb[0].addActionListener(ProcessSwitcher);
			modulejrb[1].addActionListener(ProcessSwitcher);
			modulejrb[0].setEnabled(false);
			modulejrb[1].setEnabled(false);

			JPanel friP = friChanger.getPanel();
			friP.setPreferredSize(new Dimension(200, 45));
			slayout.putConstraint(SpringLayout.NORTH, friP, 110,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,friP, 20,SpringLayout.WEST, caliP);
			caliP.add(friP);

			//Buttons for Run Model
			JLabel label2= new JLabel ("------- MODEL RUN CONTROLS ----------");
			label2.setPreferredSize(new Dimension(250, 30));
			slayout.putConstraint(SpringLayout.NORTH, label2, 0,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST, label2, 250 ,SpringLayout.WEST, caliP);
			caliP.add(label2);
				
			runmodeB.setPreferredSize(new Dimension(120, 25));
			slayout.putConstraint(SpringLayout.NORTH, runmodeB, 40,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,runmodeB, 250,SpringLayout.WEST, caliP);
			caliP.add(runmodeB);		 

			setupB.setPreferredSize(new Dimension(120, 25));
			slayout.putConstraint(SpringLayout.NORTH, setupB, 70,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,setupB, 250,SpringLayout.WEST, caliP);
			caliP.add(setupB);
			
			resetupB.setPreferredSize(new Dimension(120, 25));
			slayout.putConstraint(SpringLayout.NORTH, resetupB, 100,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,resetupB, 250,SpringLayout.WEST, caliP);
			caliP.add(resetupB);

			exitB.setPreferredSize(new Dimension(70, 40));
			slayout.putConstraint(SpringLayout.NORTH, exitB, 35,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,exitB, 400,SpringLayout.WEST, caliP);
			caliP.add(exitB);		 

			startpauseB.setPreferredSize(new Dimension(70, 40));
			slayout.putConstraint(SpringLayout.NORTH, startpauseB, 90,SpringLayout.NORTH, caliP);
			slayout.putConstraint(SpringLayout.WEST,startpauseB, 400,SpringLayout.WEST, caliP);
			caliP.add(startpauseB);		 

			//Input Box for the Parameters to be calibrated
			JLabel label3= new JLabel ("----------- PARAMETERS for VEGETATION -----------------------");
				label3.setPreferredSize(new Dimension(500, 30));
				slayout.putConstraint(SpringLayout.NORTH, label3, 150,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST, label3, 0 ,SpringLayout.WEST, caliP);
				caliP.add(label3);
								
			JPanel cmaxP = cmaxChanger.getPanel();
				cmaxP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, cmaxP, 180,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,cmaxP, 10,SpringLayout.WEST, caliP);
				caliP.add(cmaxP);
								
			JPanel nmaxP = nmaxChanger.getPanel();
				nmaxP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, nmaxP, 180,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,nmaxP,  250,SpringLayout.WEST, caliP);
				caliP.add(nmaxP);

			JPanel krbP = krbChanger.getPanel();
				krbP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, krbP, 240,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,krbP, 10,SpringLayout.WEST, caliP);
				caliP.add(krbP);

			JPanel cfallP = cfallChanger.getPanel();
				cfallP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, cfallP, 300,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,cfallP, 10,SpringLayout.WEST, caliP);
				caliP.add(cfallP);				
													
			JPanel nfallP = nfallChanger.getPanel();
				nfallP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, nfallP, 300,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,nfallP, 250,SpringLayout.WEST, caliP);
				caliP.add(nfallP);

			JLabel label4= new JLabel ("----------- PARAMETERS for SOIL -------------------------");
				label4.setPreferredSize(new Dimension(300, 30));
				slayout.putConstraint(SpringLayout.NORTH, label4, 370,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST, label4, 0 ,SpringLayout.WEST, caliP);
				caliP.add(label4);
				
			JPanel kdcfibP = kdcfibChanger.getPanel();
				kdcfibP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, kdcfibP, 400,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,kdcfibP, 10,SpringLayout.WEST, caliP);
				caliP.add(kdcfibP);
				
			JPanel kdchumP = kdchumChanger.getPanel();
				kdchumP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, kdchumP, 460,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,kdchumP, 10,SpringLayout.WEST, caliP);
				caliP.add(kdchumP);
				
			JPanel kdcminP = kdcminChanger.getPanel();
				kdcminP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, kdcminP, 520,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,kdcminP, 10,SpringLayout.WEST, caliP);
				caliP.add(kdcminP);
				
			JPanel kdcslowP = kdcslowChanger.getPanel();
				kdcslowP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, kdcslowP, 580,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,kdcslowP, 10,SpringLayout.WEST, caliP);
				caliP.add(kdcslowP);				

				JPanel nupP = nupChanger.getPanel();
				nupP.setPreferredSize(new Dimension(210, 60));
				slayout.putConstraint(SpringLayout.NORTH, nupP, 490,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,nupP, 250,SpringLayout.WEST, caliP);
				caliP.add(nupP);

			//Buttons for Operating the Calibrated Parameters
			JLabel label5= new JLabel ("----------- PARAMETER OPERATIONS -----------------------");
				label5.setPreferredSize(new Dimension(300, 30));
				slayout.putConstraint(SpringLayout.NORTH, label5, 640,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST, label5, 0 ,SpringLayout.WEST, caliP);
				caliP.add(label5);
				
				parresetB.setPreferredSize(new Dimension(120, 30));
				slayout.putConstraint(SpringLayout.NORTH, parresetB, 680,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,parresetB, 50,SpringLayout.WEST, caliP);
				caliP.add(parresetB);

				parrestoreB.setPreferredSize(new Dimension(120, 30));
				slayout.putConstraint(SpringLayout.NORTH, parrestoreB, 680,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,parrestoreB, 200,SpringLayout.WEST, caliP);
				caliP.add(parrestoreB);

				paroutputB.setPreferredSize(new Dimension(120, 30));
				slayout.putConstraint(SpringLayout.NORTH, paroutputB, 680,SpringLayout.NORTH, caliP);
				slayout.putConstraint(SpringLayout.WEST,paroutputB, 350,SpringLayout.WEST, caliP);
				caliP.add(paroutputB);
					 
			controlTP.add("Configurer", configP);
			controlTP.add("Calibrator", caliP);
			
		    f.add(controlTP, BorderLayout.CENTER);
		   		    
		    f.setLocation(1,1);
		    f.setPreferredSize(new Dimension(550, 800));
		    f.setSize(550, 800);
		    f.setVisible(true);
		}catch (Exception e){	  	
		   System.out.println(e.getMessage());
		} finally {
			//System.out.println("In final");
		}
	}
	
	private JPanel getRBPanel(ButtonGroup jbg, int rbnum, int bglength, int rbheight,
			JRadioButton jrb[], String rb[]){
		JPanel rbP = new JPanel();
		SpringLayout slayout = new SpringLayout();
		rbP.setLayout(slayout);
		int j=0;
		int ilength=0;
		for(int i= 0; i<rbnum;i++){
			jrb[i] = new JRadioButton(rb[i]);
			int rblength = Math.max(60, rb[i].length()*10);

			ilength+=rblength+10;
			if(ilength>bglength){
				j+=1;
				ilength=0;
			}
			
			jrb[i].setPreferredSize(new Dimension(rblength, rbheight));
			slayout.putConstraint(SpringLayout.NORTH, jrb[i], j,SpringLayout.NORTH, rbP);
			slayout.putConstraint(SpringLayout.WEST, jrb[i], ilength-rblength,SpringLayout.WEST, rbP);
			rbP.add(jrb[i]);
			jbg.add(jrb[i]);
			
		}		
		jrb[0].setSelected(true);
		
		return rbP;
	};	 
		
	 private void setTargetValues4Plots(){
		//fluxes
		 varplotter.gppTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_GPP, 1)) );
		 varplotter.nppTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_NPP, 1)) );
		 varplotter.innppTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_NPPSAT, 1)) );
		 varplotter.ingppTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_GPP, 1)) );
		 varplotter.raTP.setTargetValue(0);
		 varplotter.rhTP.setTargetValue(0);
		 
		 varplotter.ltrfalcTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_NPP, 1)) );
		 varplotter.nuptakeTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_NUPTAKE, 1)) );
		 varplotter.netnminTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_NUPTAKE, 1)) );
		 varplotter.ltrfalnTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_NUPTAKE, 1)) );
		 
		 //states
		 varplotter.vegcTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_VEGC, 1)) );
		 varplotter.allsoilcTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_SOILC, 1)) );
		 varplotter.fibsoilcTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_FIBSOILC, 1)) );
		 varplotter.humsoilcTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_HUMSOILC, 1)) );
		 varplotter.minesoilcTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_MINESOILC, 1)) );
		 varplotter.vegnTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_VEGN, 1)) );
		 varplotter.orgnTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_SOILN, 1)) );
		 varplotter.avlnTP.setTargetValue(Double.valueOf((String) targetTB.getValueAt(Configurer.I_AVAILN, 1)) );
		 
		 //monthly watch
		 
		 varplotter.mgppTP.setTargetValue(0. );
		 varplotter.mnppTP.setTargetValue(0. );
		 varplotter.mrespTP.setTargetValue(0.);
		 varplotter.mltrfalcTP.setTargetValue(0.);
		 varplotter.mltrfalnTP.setTargetValue(0.);
		 varplotter.mnetnminTP.setTargetValue(0.);
		 
		 varplotter.mlaiTP.setTargetValue(0.);
		 varplotter.mvegcTP.setTargetValue(0.);
		 varplotter.mvegnTP.setTargetValue(0.);
		 varplotter.mavlnTP.setTargetValue(0.);
		 
	};

	public void setConfigurer(Configurer configure){
		config = configure;
	};
	
//--------------Operations on Configure Tab of Control Panel --------------------------------------
	//
	private ActionListener ProcessSwitcher = new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			startpauseB.setEnabled(false);    //any selection will re-set model run
			resetupB.setEnabled(true);
			setupB.setEnabled(false);			
		}
				
	};

	private TableModelListener tabvalueChanger = new TableModelListener() {
		public void tableChanged(TableModelEvent e) {
		    startpauseB.setEnabled(false);    //any selection will re-set model run
			resetupB.setEnabled(true);
			setupB.setEnabled(false);	
			
		}
				
	};

	private ActionListener ParameterChanged = new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			
			startpauseB.setEnabled(false);    //any modification on parameter value(s) will re-set model run
			resetupB.setEnabled(true);
			setupB.setEnabled(true);
			
			//store parameters to old values
			 friChanger.storeOldValue();
			 cmaxChanger.storeOldValue();
			 nmaxChanger.storeOldValue();
			 cfallChanger.storeOldValue();
			 nfallChanger.storeOldValue();
			 nupChanger.storeOldValue();
			
			 krbChanger.storeOldValue();
			 kdcfibChanger.storeOldValue();
			 kdchumChanger.storeOldValue();
			 kdcminChanger.storeOldValue();
			 kdcslowChanger.storeOldValue();
			 
		}
				
	};

	public class ConfigureSelector implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
			//open file chooser
			String defaultdir = "config/";
			JFileChooser fc = new JFileChooser(defaultdir);
			int returnVal =fc.showOpenDialog(selectConfigB);
			if (returnVal == JFileChooser.APPROVE_OPTION) {
	            File file = fc.getSelectedFile();
	            
	            //set-up the configurer Tab of Control Panel
	            configTF.setText(file.getPath());
	            setConfig();

	            //set-up the changer Tab of Control Panel
				nfeedjrb[0].setEnabled(true);
				nfeedjrb[1].setEnabled(true);
				avlnjrb[0].setEnabled(true);
				avlnjrb[1].setEnabled(true);
				baselinejrb[0].setEnabled(true);
				baselinejrb[1].setEnabled(true);
				modulejrb[0].setEnabled(true);
				modulejrb[1].setEnabled(true);
				friChanger.setEnabled(true);

				cmaxChanger.setEnabled(true);
		        nmaxChanger.setEnabled(true);
		        krbChanger.setEnabled(true);
		        cfallChanger.setEnabled(true);
		        nfallChanger.setEnabled(true);
		        nupChanger.setEnabled(true);
		        kdcfibChanger.setEnabled(true);
		        kdchumChanger.setEnabled(true);
		        kdcminChanger.setEnabled(true);
		        kdcslowChanger.setEnabled(true);

		        parresetB.setEnabled(true);
		        parrestoreB.setEnabled(true);
		        paroutputB.setEnabled(true);
	            
		        //set-up plot viewers
		        varplotter.reset();
	            var2plotter.reset();
		        setTargetValues4Plots();
		        
				PhyVariablePlotter.f.setVisible(true);     //by default, showing this plot
				BioVariablePlotter.f.setVisible(true);      //by default, showing this plot

		        //connecting plotters
		        Caliber.plotting.setPlotter(varplotter);
		    	Caliber.plotting.setPlotter2(var2plotter);
		    	
		    	//initializing TEM eqrunner
		    	runnerinit(false);  //first initialization has to redo calirestart.nc
	        	//
	        	setConfigFromTEM();
		    	
	            //model controls reading from configurer and changer Tabs
	            setTEMoptionsFromChanger();
		        setTEMparsFromConfig();           
				setTEMinitstateFromConfig();	
				setTEMinitparFromConfig();	

		        //enable model run setup controls in the changer Tab
	            runmodeB.setEnabled(true);
	            resetupB.setEnabled(true);
	            setupB.setEnabled(true);

			}
		}
	};
	
		private void runnerinit(boolean usecalirestart) {
			try {
		    	//initialize the Caliber.eqrunner
				Caliber.eqrunner = new runner();
				
		        //set control file name
		        Caliber.eqrunner.controlfile=config.controlfile;


		    	//model running options (can be updated later on)
		    	Caliber.eqrunner.runcht.califilein= false;       //switch to read-in calibrated parameters from Jcalinput.txt
		    	Caliber.eqrunner.runcht.inicali   = false;  //(only valid if 'califilein' above is set to true)switch to read-in initial C conditions, if read-in calpar from Jcalinput.txt

		    	Caliber.eqrunner.runcht.usecalirestart = usecalirestart;    //switch to read-in Env. driver for equilibrim-run from calirestart.nc 
		    	if (usecalirestart){
			    	Caliber.eqrunner.runcht.outcalirestart = false;   //switch to output Env. driver to calirestart.nc for equilibrim-run, if usecalirestart false  
		    	} else {
		    		Caliber.eqrunner.runcht.outcalirestart = true;   //switch to output Env. driver to calirestart.nc for equilibrim-run, if usecalirestart false  
		    	}

		        
		        //control file
		        Caliber.eqrunner.runcht.ccdfile=config.envdriverfile;

		        Caliber.init(); //default control options/parameters included

		        //set the initial FRI from default grid-level input
			    double fri=Caliber.eqrunner.gd.getFri();
			    friChanger.updateValue(fri, 0);
	            	            
	        } catch (Exception e) {
		    	System.err.println("TEM eq run initializaion failed! - "+e);
	        }
		
		};
	
		// update the drive and parameter file, called by Class ConfigureSelector
		private void setConfig(){
		
		    String status ="";
		    try {
		    	status ="reading configure file";
		    	String aFile = configTF.getText();
			    config.configurefile = aFile;

		      BufferedReader input =  new BufferedReader(new FileReader(aFile));
		      try {
		        
		        config.controlfile = input.readLine();
		        config.envdriverfile = input.readLine();
		        config.caliparfile = input.readLine();
		        config.outputfile = input.readLine();
		        
		        controlTF.setText(config.controlfile);
		        driverTF.setText(config.envdriverfile);
		        calparTF.setText(config.caliparfile);
		        outputTF.setText(config.outputfile);
		        //check existence of driver file
		        status ="reading driver file";
		        File drvF = new File(config.envdriverfile);
		        if(!drvF.exists()){
		        	JOptionPane.showMessageDialog(f, status+" failed");
		        }
		        
		        status ="reading parameter file";
		        File parF = new File(config.caliparfile);
		        if(!parF.exists()){
		        	JOptionPane.showMessageDialog(f, status+" not exist");
		        }else{
		        	//reading parameters
		        	readConfigparFromFile();
		        	
		        }
		        
		        paroutputB.setEnabled(true);
		      }catch (Exception e){
		    	  JOptionPane.showMessageDialog(f, status+" failed");
		      }
		      finally {
		        input.close();
		      }
		    }
		    catch (IOException ex){
		      ex.printStackTrace();
		    }		
		};
		
		//reading data from file, called by updateConfig(), and class: Restarter;
		private void readConfigparFromFile() throws IOException{
			 
			 BufferedReader input =  new BufferedReader(new FileReader(config.caliparfile));

			 String dummy="";
		      dummy = input.readLine();
	 	      stateTB.setValueAt(dummy, Configurer.I_VEGETATION, 1);
	 	      dummy = input.readLine();
		      stateTB.setValueAt(dummy, Configurer.I_DRAINAGE, 1);
		      dummy = input.readLine();
		      stateTB.setValueAt(dummy, Configurer.I_FIBTHICK, 1);
		      dummy = input.readLine();
		      stateTB.setValueAt(dummy, Configurer.I_HUMTHICK, 1);
		
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_NPP, 1);      
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_GPP, 1);      
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_NPPSAT, 1);	      
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_NUPTAKE, 1);
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_VEGC, 1);	      
		      stateTB.setValueAt(dummy, Configurer.I_IVEGC, 1);     //initial= targetted
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_VEGN, 1);
		      stateTB.setValueAt(dummy, Configurer.I_IVEGN, 1);     //initial= targetted
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_SOILC, 1);
		      stateTB.setValueAt(dummy, Configurer.I_ISOILC, 1);    //initial = targetted
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_FIBSOILC, 1);
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_HUMSOILC, 1);
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_MINESOILC, 1);
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_AVAILN, 1);		      
		      stateTB.setValueAt(dummy, Configurer.I_IAVLN, 1);     //initial= targetted
		      dummy = input.readLine();
		      targetTB.setValueAt(dummy, Configurer.I_SOILN, 1);
		      stateTB.setValueAt(dummy, Configurer.I_ISOILN, 1);     //initial= targetted

		      String element[] = new String[2];
		      double delement[] = new double[2];
		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		    	  calparTB.setValueAt(element[ic-1], Configurer.I_CMAX, ic);
		    	  delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      cmaxChanger.updateValue(delement[0],   (int)delement[1]  );
		    
		       
		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		      calparTB.setValueAt(element[ic-1], Configurer.I_NMAX, ic);
		      delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      nmaxChanger.updateValue(delement[0],   (int)delement[1]  );

		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		      calparTB.setValueAt(element[ic-1], Configurer.I_KRB, ic);
		      delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      krbChanger.updateValue(delement[0],   (int)delement[1]  );
		      
		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		      calparTB.setValueAt(element[ic-1], Configurer.I_NUP, ic);
		      delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      nupChanger.updateValue(delement[0],   (int)delement[1]  );
		     
		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		      calparTB.setValueAt(element[ic-1], Configurer.I_CFALL, ic);
		      delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      cfallChanger.updateValue(delement[0],   (int)delement[1]  );
		      
		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		      calparTB.setValueAt(element[ic-1], Configurer.I_NFALL, ic);
		      delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      nfallChanger.updateValue(delement[0],   (int)delement[1]  );
		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		      calparTB.setValueAt(element[ic-1], Configurer.I_KDCFIB, ic);
		      delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      kdcfibChanger.updateValue(delement[0],   (int)delement[1]  );
		      
		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		      calparTB.setValueAt(element[ic-1], Configurer.I_KDCHUM, ic);
		      delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      kdchumChanger.updateValue(delement[0],   (int)delement[1]  );
		      		      
		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		      calparTB.setValueAt(element[ic-1], Configurer.I_KDCMIN, ic);
		      delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      kdcminChanger.updateValue(delement[0],   (int)delement[1]  );
		           
		      dummy = input.readLine();
		      element = dummy.split(",");
		      for(int ic =1; ic<=2; ic++){ 
		      calparTB.setValueAt(element[ic-1], Configurer.I_KDCSLOW, ic);
		      delement[ic-1]= Double.valueOf(element[ic-1]);
		      }
		      kdcslowChanger.updateValue(delement[0],   (int)delement[1]  );
		      
		      input.close();
		      		      
		};
		
		//model default parameters after model initialization
	    private void setConfigFromTEM(){

	       //
	           	vegpar_bgc vbpar = new vegpar_bgc();
	           	soipar_bgc sbpar = new soipar_bgc();
	           	Caliber.eqrunner.runcht.cht.getBgcPar(vbpar, sbpar);

	       float ddummy;
	       ddummy=vbpar.getM1(); 	 
	           	fixparTB.setValueAt(Float.toString(ddummy), Configurer.I_m1, 1);
	       ddummy=vbpar.getM2(); 	 
	           	fixparTB.setValueAt(Float.toString(ddummy), Configurer.I_m2, 1);
	       ddummy=vbpar.getM3(); 	 
	           	fixparTB.setValueAt(Float.toString(ddummy), Configurer.I_m3, 1);
	       ddummy=vbpar.getM4(); 	 
	           	fixparTB.setValueAt(Float.toString(ddummy), Configurer.I_m4, 1);
	       ddummy=sbpar.getFsoma(); 	 
	           	fixparTB.setValueAt(Float.toString(ddummy), Configurer.I_fsoma, 1);
	       ddummy=sbpar.getFsompr(); 	 
	           	fixparTB.setValueAt(Float.toString(ddummy), Configurer.I_fsompr, 1);
	       ddummy=sbpar.getFsomcr(); 	 
	           	fixparTB.setValueAt(Float.toString(ddummy), Configurer.I_fsomcr, 1);  		
	       ddummy=sbpar.getSom2co2(); 	 
	           	fixparTB.setValueAt(Float.toString(ddummy), Configurer.I_som2co2, 1);
	           			   		
	    };	

		
		//pass the parameters from config-Tab of Control Panel to TEM model
		//called by Class:ConfigureSelector,Class: Restarter
		private void setTEMparsFromConfig(){		 
			 	 		 
			 Caliber.vbcalpar
			    .setCmax(Float.valueOf((String) calparTB.getValueAt(Configurer.I_CMAX, 1)));
			 Caliber.vbcalpar
		        .setNmax(Float.valueOf((String) calparTB.getValueAt(Configurer.I_NMAX, 1)));
			 Caliber.vbcalpar
		        .setKrb(Float.valueOf((String) calparTB.getValueAt(Configurer.I_KRB, 1)));
			 Caliber.vbcalpar
		        .setCfall(Float.valueOf((String) calparTB.getValueAt(Configurer.I_CFALL, 1)));
			 Caliber.vbcalpar
		        .setNfall(Float.valueOf((String) calparTB.getValueAt(Configurer.I_NFALL, 1)));

			 Caliber.sbcalpar
		        .setNup(Float.valueOf((String) calparTB.getValueAt(Configurer.I_NUP, 1)));
			 Caliber.sbcalpar
		        .setKdcfib(Float.valueOf((String) calparTB.getValueAt(Configurer.I_KDCFIB, 1)));
			 Caliber.sbcalpar
		        .setKdchum(Float.valueOf((String) calparTB.getValueAt(Configurer.I_KDCHUM, 1)));
			 Caliber.sbcalpar
		        .setKdcmin(Float.valueOf((String) calparTB.getValueAt(Configurer.I_KDCMIN, 1)));
			 Caliber.sbcalpar
		        .setKdcslow(Float.valueOf((String) calparTB.getValueAt(Configurer.I_KDCSLOW, 1)));
			  		  
		 };

//------ Operations on Calibration Tab of Control Panel --------------------------------------
	public class Exit implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
			System.exit(0);	 
		}
				
	};

	public class RunMode implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
			//
			startpauseB.setEnabled(false);
			
			if(runmodeB.getText().equals("NewCaliDriver")){
				runmodeB.setText("Calibration");
				Caliber.eqrunner.runcht.usecalirestart=true;
				
				PhyVariablePlotter.f.setVisible(true);
				BioVariablePlotter.f.setVisible(true);
				
			}else if(runmodeB.getText().equals("Calibration")){
				runmodeB.setText("NewCaliDriver");
				Caliber.eqrunner.runcht.usecalirestart=false;
				Caliber.eqrunner.runcht.ccdfile=config.envdriverfile;

				if (BioVariablePlotter.f.isVisible()) BioVariablePlotter.f.setVisible(false);
				PhyVariablePlotter.f.setVisible(true);

			}

			System.out.println("\n"+runmodeB.getText()+" Mode Switched ON ...");

		}
		
	};

	public class StartPause implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
					
			// 1) "Pause" - temporarily stop the in-progress run, in order to check or change setting-up
			if (startpauseB.getText().equals("Pause")){
				startpauseB.setText("Start");
				resetupB.setEnabled(true);
				setupB.setEnabled(true);
				exitB.setEnabled(true);
				 
				Caliber.stop();
				 
			// 2) after all above, Start the run as expected
			} else if(startpauseB.getText().equals("Start")){
				startpauseB.setText("Pause");
				resetupB.setEnabled(false);
				setupB.setEnabled(false);
				exitB.setEnabled(false);
				
				if (runmodeB.getText().equals("NewCaliDriver")) {
					var2plotter.reset();
					Caliber.updatedriver();
				} else if (runmodeB.getText().equals("Calibration")){
					Caliber.start();
				}
			}
			
			 
		}
		
	};
	
	// Model "Resetup" - after modifying one or more model setting-up, first UPDATE the setting, 
	//         then restart a new model run		
	public class Resetup implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
			setupB.setEnabled(true);	
			startpauseB.setEnabled(true);
			startpauseB.setText("Start");
					
			varplotter.reset();
			var2plotter.reset();
			setTargetValues4Plots();			
							
			Caliber.reset();
			runnerinit(false);     //reset-up DOES update calirestart.nc
				
			setTEMoptionsFromChanger();
			setTEMcalparsFromChanger();
			setTEMinitstateFromConfig();
			setTEMinitparFromConfig();
		}
		
	};
		//after clicking start, update the initital state variables to tem, called by Class: Resetup
		private void setTEMinitstateFromConfig(){
		
	      float fibthick = Float.valueOf((String) stateTB.getValueAt(Configurer.I_FIBTHICK, 1));
	      float humthick = Float.valueOf((String) stateTB.getValueAt(Configurer.I_HUMTHICK, 1));
	      float vegc     = Float.valueOf((String) stateTB.getValueAt(Configurer.I_IVEGC, 1));
	      float vegn     = Float.valueOf((String) stateTB.getValueAt(Configurer.I_IVEGN, 1));
	      float avln     = Float.valueOf((String) stateTB.getValueAt(Configurer.I_IAVLN, 1));
	      float soilc    = Float.valueOf((String) stateTB.getValueAt(Configurer.I_ISOILC, 1));
	      float soiln    = Float.valueOf((String) stateTB.getValueAt(Configurer.I_ISOILN, 1));

	      Caliber.eqrunner.runcht.initstate.setFibthick(fibthick);
	      Caliber.eqrunner.runcht.initstate.setHumthick(humthick);
	      Caliber.eqrunner.runcht.initstate.setVegc(vegc);
	      Caliber.eqrunner.runcht.initstate.setVegn(vegn);
	      Caliber.eqrunner.runcht.initstate.setAvln(avln);
	      Caliber.eqrunner.runcht.initstate.setOrgn(soiln);
	      Caliber.eqrunner.runcht.initstate.setSoilc(soilc);
	      
	      Caliber.eqrunner.runcht.cht.setSiteStates
	                  (Caliber.eqrunner.runcht.initstate);
	      
		};

		//Some biogeochemical parameters to be controlled
		private void setTEMinitparFromConfig(){
			
			String fdummy=" ";
			
			soipar_bgc sbbgcpar = new soipar_bgc();
			vegpar_bgc vbbgcpar = new vegpar_bgc();

			fdummy =(String) fixparTB.getValueAt(Configurer.I_m1, 1);
			if (fdummy!=" ") vbbgcpar.setM1(Float.valueOf(fdummy));
			fdummy =(String) fixparTB.getValueAt(Configurer.I_m2, 1);
			if (fdummy!=" ") vbbgcpar.setM2(Float.valueOf(fdummy));
			fdummy =(String) fixparTB.getValueAt(Configurer.I_m3, 1);
			if (fdummy!=" ") vbbgcpar.setM3(Float.valueOf(fdummy));
			fdummy =(String) fixparTB.getValueAt(Configurer.I_m4, 1);
			if (fdummy!=" ") vbbgcpar.setM4(Float.valueOf(fdummy));
			fdummy =(String) fixparTB.getValueAt(Configurer.I_fsoma, 1);
			if (fdummy!=" ") sbbgcpar.setFsoma(Float.valueOf(fdummy));
			fdummy =(String) fixparTB.getValueAt(Configurer.I_fsompr, 1);
			if (fdummy!=" ") sbbgcpar.setFsompr(Float.valueOf(fdummy));
			fdummy =(String) fixparTB.getValueAt(Configurer.I_fsomcr, 1);
			if (fdummy!=" ") sbbgcpar.setFsomcr(Float.valueOf(fdummy));
			fdummy =(String) fixparTB.getValueAt(Configurer.I_som2co2, 1);
			if (fdummy!=" ") sbbgcpar.setSom2co2(Float.valueOf(fdummy));
			
			Caliber.eqrunner.runcht.cht.resetBgcPar(vbbgcpar, sbbgcpar);
								
		};

		
	// Model-run "Setup" - after modifying one or more model setting-up, 
	// UPDATE the setting from the Changer Tab of control panel 
	public class Setup implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
	
			startpauseB.setEnabled(true);
			startpauseB.setText("Start");
			
			setTEMoptionsFromChanger();
			setTEMcalparsFromChanger();
				
		}
		
	};

	//update model process switches to tem, called by Class: Setup/Resetup
	private void setTEMoptionsFromChanger(){
		int nfeed =0;
		int avlnflg =0; 
		int baseline =0;
		
		if(nfeedjrb[1].isSelected()){
			nfeed =1;
		}
		
		if(avlnjrb[1].isSelected()){
			avlnflg =1;
		}
		
		if(baselinejrb[1].isSelected()){
			baseline =1;
		}
		
		Caliber.eqrunner.runcht.cht.getBd().setBaseline(baseline); 	 
		Caliber.eqrunner.runcht.cht.getBd().setAvlnflg(avlnflg);
		Caliber.eqrunner.runcht.cht.getBd().setNfeed(nfeed);
        
		if(modulejrb[0].isSelected()){
			Caliber.eqrunner.runcht.cht.setEquiled(false);
			
			// options
			Caliber.useeq    = true;   //use ENV-module ONLY run derived forcing

			//Turn Eco-Module on ONLY 
			Caliber.eqrunner.runcht.cht.setEnvmodule(false);
			Caliber.eqrunner.runcht.cht.setEcomodule(true);
			Caliber.eqrunner.runcht.cht.setDsbmodule(false);
			Caliber.eqrunner.runcht.cht.setDslmodule(false);
			
			friChanger.setEnabled(false);
			
		} else if(modulejrb[1].isSelected()){			// This is for all modules, but with normal atm driving
			Caliber.eqrunner.runcht.cht.setEquiled(true);
			// options
			Caliber.useeq    = false;   //not use ENV-module ONLY run derived forcing

			//Turn Modules on/off
			Caliber.eqrunner.runcht.cht.setEnvmodule(true);
			Caliber.eqrunner.runcht.cht.setEcomodule(true);
			Caliber.eqrunner.runcht.cht.setDslmodule(true);
			Caliber.eqrunner.runcht.cht.setDsbmodule(false);

			//set fri.changer on AND DSB module on if FRI>0
			friChanger.setEnabled(true);
			if (friChanger.getValue()>0.0) {
				Caliber.eqrunner.runcht.cht.setDsbmodule(true);
				Caliber.friderived = true;

			}
		}
		
	};
	
	//after clicking start, update the parameters to tem, called by Class: Setup/Resetup
	private void setTEMcalparsFromChanger(){
		
		double nmax =nmaxChanger.getValue();
		double cmax =cmaxChanger.getValue();
		
		double nup =nupChanger.getValue();
		double krb =krbChanger.getValue();
		double cfall =cfallChanger.getValue();
		double nfall =nfallChanger.getValue();
		double kdcfib =kdcfibChanger.getValue();
		double kdchum =kdchumChanger.getValue();
		double kdcmin =kdcminChanger.getValue();
		double kdcslow =kdcslowChanger.getValue();
			
		Caliber.vbcalpar.setCmax((float)cmax);
		Caliber.vbcalpar.setNmax((float)nmax);
		Caliber.vbcalpar.setCfall((float)cfall);
		Caliber.vbcalpar.setNfall((float)nfall);
		Caliber.vbcalpar.setKrb((float)krb);
				
		Caliber.sbcalpar.setKdcfib((float)kdcfib);
		Caliber.sbcalpar.setKdchum((float)kdchum);
		Caliber.sbcalpar.setKdcmin((float)kdcmin);
		Caliber.sbcalpar.setKdcslow((float)kdcslow);
		Caliber.sbcalpar.setNup((float)nup);
		
		//
		int fri = (int)friChanger.getValue();
		Caliber.eqrunner.gd.setFri(fri);
				 
	};

	//reset calibration parameters to the initial values (i.e., from config files)
	public class ParameterResetter implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {

			setChangerFromConfig();
			setTEMparsFromConfig();
			
			startpauseB.setEnabled(false);
			setupB.setEnabled(true);
			resetupB.setEnabled(true);
						 
		}
		
	};

	//reading data from file, called by class: ParameterResetter;
	private void setChangerFromConfig() {
		 
		double value;
		double order;
		
		value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_CMAX, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_CMAX, 2));    
		cmaxChanger.updateValue(value,  (int)order);
	       
		value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_NMAX, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_NMAX, 2));    
	    nmaxChanger.updateValue(value,  (int)order);

		value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KRB, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KRB, 2));    
	    krbChanger.updateValue(value,  (int)order);
	      
		value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_NUP, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_NUP, 2));    
		nupChanger.updateValue(value,  (int)order);
	     
		value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_CFALL, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_CFALL, 2));    
	    cfallChanger.updateValue(value,  (int)order);
	      
		value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_NFALL, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_NFALL, 2));    
	    nfallChanger.updateValue(value,  (int)order);

	    value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KDCFIB, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KDCFIB, 2));    
		kdcfibChanger.updateValue(value,  (int)order);
	      
		value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KDCHUM, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KDCHUM, 2));    
	    kdchumChanger.updateValue(value,  (int)order);
	      
		value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KDCMIN, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KDCMIN, 2));    
	    kdcminChanger.updateValue(value,  (int)order);
 	      
		value = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KDCSLOW, 1));
		order = Double.valueOf((String) calparTB.getValueAt(Configurer.I_KDCSLOW, 2));    
	    kdcslowChanger.updateValue(value,  (int)order);
	      
	};
	
	//restore calibration parameters to the previous calibrated (NOT the initial values as Resetter does)
	public class ParameterRestorer implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
			 friChanger.restore();
			 cmaxChanger.restore();
			 nmaxChanger.restore();
			 cfallChanger.restore();
			 nfallChanger.restore();
			 nupChanger.restore();
			 
			 krbChanger.restore();
			 kdcfibChanger.restore();
			 kdchumChanger.restore();
			 kdcminChanger.restore();
			 kdcslowChanger.restore();
			 
			 startpauseB.setEnabled(false);
			 setupB.setEnabled(true);
			 resetupB.setEnabled(true);
			 	 
		}
		
	};
	
	public class ParameterOutputer implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
			//output calibrated parameters
			 
			try {
			      PrintStream out = new PrintStream(new FileOutputStream(
			    		  config.outputfile));

			      //first output pools
			      String vegs = (String) stateTB.getValueAt(Configurer.I_VEGETATION, 1);
			      out.println(vegs);
			      String drgs = (String) stateTB.getValueAt(Configurer.I_DRAINAGE, 1);
			      out.println(drgs);
			      String fibric = (String) stateTB.getValueAt(Configurer.I_FIBTHICK, 1);
			      out.println(fibric);
			      String humic = (String) stateTB.getValueAt(Configurer.I_HUMTHICK, 1);
			      out.println(humic);
			      String vegcs = (String) targetTB.getValueAt(Configurer.I_VEGC, 1);
			      out.println(vegcs);
			      String strns = (String) targetTB.getValueAt(Configurer.I_VEGN, 1);
			      out.println(strns);
			      String avlns = (String) targetTB.getValueAt(Configurer.I_AVAILN, 1);
			      out.println(avlns);
			      String soilns = (String) targetTB.getValueAt(Configurer.I_SOILN, 1);
			      out.println(soilns);
			  			      
			      //then output parameters		      
			      out.println(Caliber.vbcalpar.getCmax());
			      out.println(Caliber.vbcalpar.getNmax());
			      out.println(Caliber.vbcalpar.getKrb());
			      out.println(Caliber.sbcalpar.getNup());

			      out.println(Caliber.vbcalpar.getCfall());
			      out.println(Caliber.vbcalpar.getNfall());

			      out.println(Caliber.sbcalpar.getKdcfib()); //needed to check
			      out.println(Caliber.sbcalpar.getKdchum()); //needed to check?
			      out.println(Caliber.sbcalpar.getKdcmin()); //needed to check?
			      out.println(Caliber.sbcalpar.getKdcslow()); //needed to check?			        			        
			        
			      out.close();

			    } catch (FileNotFoundException e) {
			      e.printStackTrace();
			    }
			 
		}
			
	};
			
}