package GUI;

//TEM GUI for both site-specific/regional run

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
import java.util.Arrays;

import javax.swing.*;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;

import runTEM.*;

import TEMJNI.SiteIn;
import TEMJNI.soipar_cal;
import TEMJNI.vegpar_cal;
import TEMJNI.vegpar_bgc;
import TEMJNI.soipar_bgc;

public class TEMGUI {
	runner TEM;
	public int errid;
	public int chtList[];
	public int chtSelected[];
	public int icht;
	
	BioVariablePlotter bvplotter;	
	PhyVariablePlotter pvplotter;
	
	GUIconfigurer config;

	//control panel
	JFrame f = new JFrame("TEM Control Pannel");
	JTabbedPane controlTP = new JTabbedPane();

	//configurer Tab of Control Panel
	JTextField controlfileTF = new JTextField();
	JButton selectControlfileB = new JButton("Select");
	
    JTextField outputdirTF       = new JTextField();
    JTextField reginputdirTF     = new JTextField();
    JTextField grdinputdirTF     = new JTextField();
    JTextField eqchtinputdirTF   = new JTextField();
    JTextField spchtinputdirTF   = new JTextField();
    JTextField trchtinputdirTF   = new JTextField();
    JTextField restartinputdirTF = new JTextField();
    JTextField calibrationdirTF  = new JTextField(); 
	
    ButtonGroup runstageBG       = new ButtonGroup();
	JRadioButton runstageRB[]    = new JRadioButton[4];
	
	ButtonGroup initmodeBG       = new ButtonGroup();
  	JRadioButton initmodeRB []   = new JRadioButton[3];
	
  	ButtonGroup clmmodeBG       = new ButtonGroup();
  	JRadioButton clmmodeRB []    = new JRadioButton[2];
	
  	ButtonGroup co2modeBG       = new ButtonGroup();
  	JRadioButton co2modeRB []   = new JRadioButton[2];
    
  	JTextField casenameTF        = new JTextField();  		
	JButton updateControlfileB = new JButton("Update");

  	JCheckBox califileinCB = new JCheckBox("Read-in Parameters from File (e.g.,Jcalinput.txt):");
    JTextField califileTF  = new JTextField();

    JCheckBox ccdfileinCB = new JCheckBox("Use soil climate driver file (e.g., soilclm.nc):");
    JTextField ccdfileTF  = new JTextField();  	

  	ButtonGroup outmodeBG       = new ButtonGroup();
  	JRadioButton outmodeRB []   = new JRadioButton[3];
  	JCheckBox outdlyCB = new JCheckBox("Daily");
  	JCheckBox outmlyCB = new JCheckBox("Monthly");
  	JCheckBox outylyCB = new JCheckBox("Yearly");

  	JCheckBox opGraphCB = new JCheckBox("PhyVarGraph");
  	JCheckBox obGraphCB = new JCheckBox("BioVarGraph");
 	
	//model runner Tab
	JRadioButton[] nfeedjrb = new JRadioButton[2];
	ButtonGroup nfeedjbg = new ButtonGroup();
	JRadioButton[] avlnjrb= new JRadioButton[2];
	ButtonGroup avlnjbg = new ButtonGroup();
	JRadioButton[] baselinejrb= new JRadioButton[2];
	ButtonGroup baselinejbg = new ButtonGroup();
	
	JRadioButton[] envmodulejrb= new JRadioButton[2];
	ButtonGroup envmodulejbg = new ButtonGroup();
	JRadioButton[] ecomodulejrb= new JRadioButton[2];
	ButtonGroup ecomodulejbg = new ButtonGroup();
	JRadioButton[] dslmodulejrb= new JRadioButton[2];
	ButtonGroup dslmodulejbg = new ButtonGroup();
	JRadioButton[] dsbmodulejrb= new JRadioButton[2];
	ButtonGroup dsbmodulejbg = new ButtonGroup();

	JComboBox runchtCB = new JComboBox();
    JTextField grdidTF  = new JTextField();
    JTextField eqchtidTF  = new JTextField();
    JTextField spchtidTF  = new JTextField();
    JTextField trchtidTF  = new JTextField();
    JTextField vegidTF  = new JTextField();
    JTextField drgidTF  = new JTextField();

	JButton setupB   = new JButton("Setup");
	JButton exitB    = new JButton("Exit");
	JButton startstopB = new JButton("Start");

	JTable stateTB;
	JTable initTB;
	JTable fixparTB;
	JTable calparTB;

	JCheckBox consoleCB = new JCheckBox("Console messages in detail?");
	JCheckBox tocdlCB   = new JCheckBox("Output in CDL as well?");
		
////////////////////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------------------
	public void setConfigurer(GUIconfigurer configure){
		config = configure;
	};
	
	//--------------------------------------------------------------------------------------	
	public TEMGUI(){

		f.setLayout(new BorderLayout());
		f.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		
		//model configurer tab of the control panel
		controlfileTF.setEditable(true); 
		controlfileTF.addActionListener(ControlfileUpdater);
		
        selectControlfileB.addActionListener(new ConfigureSelector());
        
        updateControlfileB.addActionListener(new ConfigureUpdater());
        updateControlfileB.setEnabled(false);
     
        //model runner Tab of the control panel

        String[] tabColName = {"Name", "Value"};      
        String[] stateName ={"VEG. TYPE Code","DRAINAGE TYPE Code", "Grid ID", "Cohort ID - EQ", "Cohort ID - SP","Cohort ID - TR"};
        String[] initName ={"MOSS THICK", "FIBRIC THICK", "HUMIC THICK", "VEGC", "VEGN",  "SOILC","FIBSOILC","HUMSOILC", "MINESOILC", "AVAILN", "SOILN"};
        String[] calparName ={"CMAX", "NMAX", "KRB", "NUP","CFALL","NFALL", "KDCFIB", "KDCHUM", "KDCMIN", "KDCSLOW"};
        String[] fixparName ={"Leaf_m1", "Leaf_m2", "Leaf_m3", "Leaf_m4","Soil_fsoma","Soil_fsompr", "Soil_fsomcr", "Soil_som2co2"};
                     
        int rows1 = stateName.length;
        int cols1 = 2;
        String[][] statValue = new String[rows1][cols1];
        for(int ir=0; ir<rows1; ir++){
        	statValue[ir][0] = stateName[ir];
        	for(int ic =1; ic<cols1; ic++){
        		statValue[ir][ic] =" "; 
        	}
        }
        stateTB = new JTable(statValue, tabColName);
        
        int rows2 = initName.length;
        int cols2 = 2;
        String[][] initValue = new String[rows2][cols2];
        for(int ir=0; ir<rows2; ir++){
        	initValue[ir][0] = initName[ir];
        	for(int ic =1; ic<cols2; ic++){
        		initValue[ir][ic] =" "; 
        	}
        }      
        initTB = new JTable(initValue, tabColName);
		initTB.getModel().addTableModelListener(initvalueChanger);

        int rows3 = fixparName.length;
        int cols3 = 2;
        String[][] fixparValue = new String[rows3][cols3];
        for(int ir=0; ir<rows3; ir++){
        	fixparValue[ir][0] = fixparName[ir];
        	for(int ic =1; ic<cols3; ic++){
        		fixparValue[ir][ic] =" "; 
        	}
        }     
        fixparTB = new JTable(fixparValue, tabColName);
		fixparTB.getModel().addTableModelListener(initvalueChanger);
        
        int rows4 = calparName.length;
        int cols4 = 2;
        String[][] calparValue = new String[rows4][cols4];
        for(int ir=0; ir<rows4; ir++){
        	calparValue[ir][0] = calparName[ir];
        	for(int ic =1; ic<cols4; ic++){
        		calparValue[ir][ic] =" "; 
        	}
        }            
        calparTB = new JTable(calparValue, tabColName);
		calparTB.getModel().addTableModelListener(calparChanger);
        
        setupB.addActionListener(new Setup());
        setupB.setEnabled(false);

        runchtCB.addActionListener(new CohortSelector());
        runchtCB.setEnabled(false);

        exitB.addActionListener(new Exit());
        exitB.setEnabled(true);

        startstopB.addActionListener(new StartStop());
        startstopB.setEnabled(false);
        
        try {
 		    
		//Configuration Tab of Control Panel
        	JPanel configP = new JPanel();
		    
		    SpringLayout slayout = new SpringLayout();
			configP.setLayout(slayout);
			JLabel controlfileL = new JLabel("===== MODEL CONTROL FILE =====");
			controlfileL.setPreferredSize(new Dimension(360, 20));
			slayout.putConstraint(SpringLayout.NORTH, controlfileL, 5,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,controlfileL, 0,SpringLayout.WEST, configP);
			configP.add(controlfileL);
			controlfileTF.setPreferredSize(new Dimension(360, 30));
			slayout.putConstraint(SpringLayout.NORTH, controlfileTF, 30,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,controlfileTF, 5,SpringLayout.WEST, configP);
			configP.add(controlfileTF);
			 
			selectControlfileB.setPreferredSize(new Dimension(80, 30));
			slayout.putConstraint(SpringLayout.NORTH, selectControlfileB,10,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,selectControlfileB, 400,SpringLayout.WEST, configP);
			configP.add(selectControlfileB);

			updateControlfileB.setPreferredSize(new Dimension(80, 30));
			slayout.putConstraint(SpringLayout.NORTH, updateControlfileB,50,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,updateControlfileB, 400,SpringLayout.WEST, configP);
			configP.add(updateControlfileB);

			////////////////////////////////////////////
			JLabel casenameL = new JLabel("Case Title");
			casenameL.setPreferredSize(new Dimension(90, 20));
			slayout.putConstraint(SpringLayout.NORTH, casenameL, 80,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,casenameL, 5,SpringLayout.WEST, configP);
			configP.add(casenameL);
			casenameTF.setPreferredSize(new Dimension(260, 20));
			slayout.putConstraint(SpringLayout.NORTH, casenameTF, 80,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,casenameTF, 100,SpringLayout.WEST, configP);
			casenameTF.addActionListener(ControlfileUpdater);
			casenameTF.setEditable(true);
			casenameTF.setEnabled(false);
			configP.add(casenameTF);
			
			JLabel outputdirL = new JLabel("Output Directory");
			outputdirL.setPreferredSize(new Dimension(360, 20));
			slayout.putConstraint(SpringLayout.NORTH, outputdirL, 105,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,outputdirL, 5,SpringLayout.WEST, configP);
			configP.add(outputdirL);
			outputdirTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, outputdirTF, 130,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,outputdirTF, 100,SpringLayout.WEST, configP);
			outputdirTF.setEditable(true);
			outputdirTF.addActionListener(ControlfileUpdater);
			outputdirTF.setEnabled(false);
			configP.add(outputdirTF);

			JLabel inputdirL = new JLabel("Input Directories/Files");
			inputdirL.setPreferredSize(new Dimension(360, 20));
			slayout.putConstraint(SpringLayout.NORTH, inputdirL, 155,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,inputdirL, 5,SpringLayout.WEST, configP);
			configP.add(inputdirL);

			JLabel reginputdirL = new JLabel("region-level:");
			reginputdirL.setPreferredSize(new Dimension(100, 20));
			slayout.putConstraint(SpringLayout.NORTH, reginputdirL, 180,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,reginputdirL, 15,SpringLayout.WEST, configP);
			configP.add(reginputdirL);
			reginputdirTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, reginputdirTF, 180,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,reginputdirTF, 100,SpringLayout.WEST, configP);
			reginputdirTF.addActionListener(ControlfileUpdater);
			reginputdirTF.setEditable(true);
			reginputdirTF.setEnabled(false);
			configP.add(reginputdirTF);

			JLabel grdinputdirL = new JLabel("grid-level:");
			grdinputdirL.setPreferredSize(new Dimension(100, 20));
			slayout.putConstraint(SpringLayout.NORTH, grdinputdirL, 205,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,grdinputdirL, 15,SpringLayout.WEST, configP);
			configP.add(grdinputdirL);
			grdinputdirTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, grdinputdirTF, 205,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,grdinputdirTF, 100,SpringLayout.WEST, configP);
			grdinputdirTF.addActionListener(ControlfileUpdater);
			grdinputdirTF.setEditable(true);
			grdinputdirTF.setEnabled(false);
			configP.add(grdinputdirTF);

			JLabel eqchtinputdirL = new JLabel("eq-cohort:");
			eqchtinputdirL.setPreferredSize(new Dimension(100, 20));
			slayout.putConstraint(SpringLayout.NORTH, eqchtinputdirL, 230,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,eqchtinputdirL, 15,SpringLayout.WEST, configP);
			configP.add(eqchtinputdirL);
			eqchtinputdirTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, eqchtinputdirTF, 230,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,eqchtinputdirTF, 100,SpringLayout.WEST, configP);
			eqchtinputdirTF.addActionListener(ControlfileUpdater);
			eqchtinputdirTF.setEditable(true);
			eqchtinputdirTF.setEnabled(false);
			configP.add(eqchtinputdirTF);

			JLabel spchtinputdirL = new JLabel("spinup-cohort:");
			spchtinputdirL.setPreferredSize(new Dimension(100, 20));
			slayout.putConstraint(SpringLayout.NORTH, spchtinputdirL, 255,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,spchtinputdirL, 15,SpringLayout.WEST, configP);
			configP.add(spchtinputdirL);
			spchtinputdirTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, spchtinputdirTF, 255,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,spchtinputdirTF, 100,SpringLayout.WEST, configP);
			spchtinputdirTF.addActionListener(ControlfileUpdater);
			spchtinputdirTF.setEditable(true);
			spchtinputdirTF.setEnabled(false);
			configP.add(spchtinputdirTF);
		
			JLabel trchtinputdirL = new JLabel("transit-cohort:");
			trchtinputdirL.setPreferredSize(new Dimension(100, 20));
			slayout.putConstraint(SpringLayout.NORTH, trchtinputdirL, 280,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,trchtinputdirL, 15,SpringLayout.WEST, configP);
			configP.add(trchtinputdirL);
			trchtinputdirTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, trchtinputdirTF, 280,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,trchtinputdirTF, 100,SpringLayout.WEST, configP);
			trchtinputdirTF.addActionListener(ControlfileUpdater);
			trchtinputdirTF.setEditable(true);
			trchtinputdirTF.setEnabled(false);
			configP.add(trchtinputdirTF);

			JLabel restartinputdirL = new JLabel("initial input:");
			restartinputdirL.setPreferredSize(new Dimension(100, 20));
			slayout.putConstraint(SpringLayout.NORTH, restartinputdirL, 305,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,restartinputdirL, 15,SpringLayout.WEST, configP);
			configP.add(restartinputdirL);
			restartinputdirTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, restartinputdirTF, 305,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,restartinputdirTF, 100,SpringLayout.WEST, configP);
			restartinputdirTF.addActionListener(ControlfileUpdater);
			restartinputdirTF.setEditable(true);
			restartinputdirTF.setEnabled(false);
			configP.add(restartinputdirTF);
			
			JLabel calibrationdirL = new JLabel("Parameters:");
			calibrationdirL.setPreferredSize(new Dimension(100, 20));
			slayout.putConstraint(SpringLayout.NORTH, calibrationdirL, 330,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,calibrationdirL, 15,SpringLayout.WEST, configP);
			configP.add(calibrationdirL);
			calibrationdirTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, calibrationdirTF, 330,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,calibrationdirTF, 100,SpringLayout.WEST, configP);
			calibrationdirTF.addActionListener(ControlfileUpdater);
			calibrationdirTF.setEditable(true);
			calibrationdirTF.setEnabled(false);
			configP.add(calibrationdirTF);

			JLabel runstageL= new JLabel ("Run Stage");
			runstageL.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, runstageL, 360,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST, runstageL, 5 ,SpringLayout.WEST, configP);
			configP.add(runstageL);
			String stagenames[] = new String[4];
			stagenames[0] = "Equilibrium";
			stagenames[1] = "Spinup ";
			stagenames[2] = "Transit";
			stagenames[3] = "Spinup-Transit";			
			JPanel runstageP = getRBPanel(runstageBG, 4, 450, 20, runstageRB, stagenames);
			runstageP.setPreferredSize(new Dimension(450,30));
			slayout.putConstraint(SpringLayout.NORTH, runstageP, 360,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,runstageP, 60,SpringLayout.WEST, configP);
			runstageRB[0].addActionListener(RunstageIoptioner);
			runstageRB[1].addActionListener(RunstageIoptioner);
			runstageRB[2].addActionListener(RunstageIoptioner);
			runstageRB[3].addActionListener(RunstageIoptioner);
			runstageRB[0].addActionListener(ControlfileUpdater);
			runstageRB[1].addActionListener(ControlfileUpdater);
			runstageRB[2].addActionListener(ControlfileUpdater);
			runstageRB[3].addActionListener(ControlfileUpdater);
			runstageBG.clearSelection();
			configP.add(runstageP);
			
			JLabel initmodeL= new JLabel ("Initial Mode");
			initmodeL.setPreferredSize(new Dimension(80, 20));
			slayout.putConstraint(SpringLayout.NORTH, initmodeL, 390,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST, initmodeL, 5 ,SpringLayout.WEST, configP);
			configP.add(initmodeL);
			String initmodes[] = new String[3];
			initmodes[0] = "default  ";
			initmodes[1] = "restart  ";
			initmodes[2] = "sitein   ";
			JPanel initmodeP = getRBPanel(initmodeBG, 3, 450, 20, initmodeRB, initmodes);
			initmodeP.setPreferredSize(new Dimension(450,30));
			slayout.putConstraint(SpringLayout.NORTH, initmodeP, 390,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,initmodeP, 80,SpringLayout.WEST, configP);
			initmodeRB[0].addActionListener(ControlfileUpdater);
			initmodeRB[1].addActionListener(ControlfileUpdater);
			initmodeRB[2].addActionListener(ControlfileUpdater);
			initmodeBG.clearSelection();
			configP.add(initmodeP);

			JLabel clmmodeL= new JLabel ("Climate Mode");
			clmmodeL.setPreferredSize(new Dimension(80, 20));
			slayout.putConstraint(SpringLayout.NORTH, clmmodeL, 420,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST, clmmodeL, 5 ,SpringLayout.WEST, configP);
			configP.add(clmmodeL);
			String clmmodes[] = new String[2];
			clmmodes[0] = "normal   ";
			clmmodes[1] = "dynamic  ";
			JPanel clmmodeP = getRBPanel(clmmodeBG, 2, 450, 20, clmmodeRB, clmmodes);
			clmmodeP.setPreferredSize(new Dimension(450,30));
			slayout.putConstraint(SpringLayout.NORTH, clmmodeP, 420,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,clmmodeP, 80,SpringLayout.WEST, configP);
			clmmodeRB[0].addActionListener(ControlfileUpdater);
			clmmodeRB[1].addActionListener(ControlfileUpdater);
			clmmodeBG.clearSelection();
			configP.add(clmmodeP);

			JLabel co2modeL= new JLabel ("CO2 Mode");
			co2modeL.setPreferredSize(new Dimension(80, 20));
			slayout.putConstraint(SpringLayout.NORTH, co2modeL, 450,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST, co2modeL, 5 ,SpringLayout.WEST, configP);
			configP.add(co2modeL);
			String co2modes[] = new String[2];
			co2modes[0] = "initial  ";
			co2modes[1] = "dynamic  ";
			JPanel co2modeP = getRBPanel(co2modeBG, 2, 450, 20, co2modeRB, co2modes);
			co2modeP.setPreferredSize(new Dimension(450,30));
			slayout.putConstraint(SpringLayout.NORTH, co2modeP, 450,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,co2modeP, 80,SpringLayout.WEST, configP);
			co2modeRB[0].addActionListener(ControlfileUpdater);
			co2modeRB[1].addActionListener(ControlfileUpdater);
			co2modeBG.clearSelection();
			configP.add(co2modeP);
			
			//panels for other input options
			JLabel inmodeL= new JLabel ("============== OTHER INPUT OPTIONS ===================");
			inmodeL.setPreferredSize(new Dimension(500, 20));
			slayout.putConstraint(SpringLayout.NORTH, inmodeL, 490,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST, inmodeL, 0 ,SpringLayout.WEST, configP);
			configP.add(inmodeL);
			
			califileinCB.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, califileinCB,510,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,califileinCB, 30,SpringLayout.WEST, configP);
			califileinCB.setSelected(false);
			califileinCB.addActionListener(InoptionsSwitcher);
			configP.add(califileinCB);
			califileTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, califileTF, 540,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,califileTF, 100,SpringLayout.WEST, configP);
			califileTF.addActionListener(InoptionsSwitcher);
			califileTF.setEditable(true);
			califileTF.setEnabled(false);
			configP.add(califileTF);
			
			ccdfileinCB.setPreferredSize(new Dimension(400, 30));
			slayout.putConstraint(SpringLayout.NORTH, ccdfileinCB,560,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,ccdfileinCB, 30,SpringLayout.WEST, configP);
			ccdfileinCB.setSelected(false);
			ccdfileinCB.addActionListener(InoptionsSwitcher);
			ccdfileinCB.setEnabled(false);
			configP.add(ccdfileinCB);
			ccdfileTF.setPreferredSize(new Dimension(300, 20));
			slayout.putConstraint(SpringLayout.NORTH, ccdfileTF, 590,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,ccdfileTF, 100,SpringLayout.WEST, configP);
			ccdfileTF.addActionListener(InoptionsSwitcher);
			ccdfileTF.setEditable(true);
			ccdfileTF.setEnabled(false);
			configP.add(ccdfileTF);

			//
			JLabel outmodeL= new JLabel ("============= OTHER OUTPUT OPTIONS ================");
			outmodeL.setPreferredSize(new Dimension(500, 25));
			slayout.putConstraint(SpringLayout.NORTH, outmodeL, 620,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST, outmodeL, 0 ,SpringLayout.WEST, configP);
			configP.add(outmodeL);
			String outmodes[] = new String[3];
			outmodes[0] = "Single-Cohort";
			outmodes[1] = "Multi-Cohorts";
			outmodes[2] = "Graphic Only";
			JPanel outmodeP = getRBPanel(outmodeBG, 3, 450, 20, outmodeRB, outmodes);
			outmodeP.setPreferredSize(new Dimension(450,25));
			slayout.putConstraint(SpringLayout.NORTH, outmodeP, 640,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,outmodeP, 20,SpringLayout.WEST, configP);
			outmodeRB[0].addActionListener(OutoptionsSwitcher);
			outmodeRB[1].addActionListener(OutoptionsSwitcher);
			outmodeRB[2].addActionListener(OutoptionsSwitcher);
			outmodeBG.clearSelection();
			
			configP.add(outmodeP);
						
			outdlyCB.setPreferredSize(new Dimension(120, 15));
			slayout.putConstraint(SpringLayout.NORTH, outdlyCB,665,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,outdlyCB, 50,SpringLayout.WEST, configP);
			outdlyCB.setSelected(false);
			outdlyCB.addActionListener(OutoptionsSwitcher);
			outdlyCB.setEnabled(false);
			configP.add(outdlyCB);

			outmlyCB.setPreferredSize(new Dimension(120, 15));
			slayout.putConstraint(SpringLayout.NORTH, outmlyCB,680,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,outmlyCB, 50,SpringLayout.WEST, configP);
			outmlyCB.setSelected(false);
			outmlyCB.addActionListener(OutoptionsSwitcher);
			outmlyCB.setEnabled(false);
			configP.add(outmlyCB);
			
			outylyCB.setPreferredSize(new Dimension(120, 15));
			slayout.putConstraint(SpringLayout.NORTH, outylyCB,695,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,outylyCB, 50,SpringLayout.WEST, configP);
			outylyCB.setSelected(false);
			outylyCB.addActionListener(OutoptionsSwitcher);
			outylyCB.setEnabled(false);
			configP.add(outylyCB);
					
			opGraphCB.setPreferredSize(new Dimension(120, 15));
			slayout.putConstraint(SpringLayout.NORTH, opGraphCB,665,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,opGraphCB, 320,SpringLayout.WEST, configP);
			opGraphCB.setSelected(false);
			opGraphCB.addActionListener(OutoptionsSwitcher);
			opGraphCB.setEnabled(false);
			configP.add(opGraphCB);

			obGraphCB.setPreferredSize(new Dimension(120, 15));
			slayout.putConstraint(SpringLayout.NORTH, obGraphCB,680,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,obGraphCB, 320,SpringLayout.WEST, configP);
			obGraphCB.setSelected(false);
			obGraphCB.addActionListener(OutoptionsSwitcher);
			obGraphCB.setEnabled(false);
			configP.add(obGraphCB);

			//console message in detail or not
			consoleCB.setPreferredSize(new Dimension(250, 30));
			slayout.putConstraint(SpringLayout.NORTH, consoleCB,710,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,consoleCB, 10,SpringLayout.WEST, configP);
			consoleCB.setSelected(true);
			consoleCB.addActionListener(consoleSwitcher);
			configP.add(consoleCB);

			//netcdf file conversion to CDL or not
			tocdlCB.setPreferredSize(new Dimension(250, 30));
			slayout.putConstraint(SpringLayout.NORTH, tocdlCB,710,SpringLayout.NORTH, configP);
			slayout.putConstraint(SpringLayout.WEST,tocdlCB, 260,SpringLayout.WEST, configP);
			tocdlCB.setSelected(false);
			tocdlCB.addActionListener(netcdfSwitcher);
			tocdlCB.setEnabled(false);
			configP.add(tocdlCB);

			// The TEM runner Tab of Control Panel		
			JPanel runnerP = new JPanel();   			 
			runnerP.setLayout(slayout);
						
			//N process switch for TEM
			JLabel label1= new JLabel ("----- TEM Module SWITCHES ------");
			label1.setPreferredSize(new Dimension(200, 30));
			slayout.putConstraint(SpringLayout.NORTH, label1, 0,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label1, 0 ,SpringLayout.WEST, runnerP);
			runnerP.add(label1);

			JLabel nfeedL= new JLabel ("Nfeed");
			nfeedL.setPreferredSize(new Dimension(60, 25));
			slayout.putConstraint(SpringLayout.NORTH, nfeedL, 30,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, nfeedL, 0 ,SpringLayout.WEST, runnerP);
			runnerP.add(nfeedL);
			String nfeedS[] = new String[2];
			nfeedS[0] = "No";
			nfeedS[1] = "Yes";
			JPanel nfeedP = getRBPanel(nfeedjbg, 2, 150, 30, nfeedjrb, nfeedS);
			nfeedP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, nfeedP, 30,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,nfeedP, 40,SpringLayout.WEST, runnerP);
			runnerP.add(nfeedP);
			nfeedjrb[0].addActionListener(ProcessSwitcher);
			nfeedjrb[1].addActionListener(ProcessSwitcher);
			nfeedjrb[0].setEnabled(false);
			nfeedjrb[1].setSelected(true);
			nfeedjrb[1].setEnabled(false);
				
			JLabel avlnL= new JLabel ("avlnflag");
			avlnL.setPreferredSize(new Dimension(60, 25));
			slayout.putConstraint(SpringLayout.NORTH, avlnL, 60,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, avlnL, 0 ,SpringLayout.WEST, runnerP);
			runnerP.add(avlnL);
			String avlns[] = new String[2];
			avlns[0] = "No";
			avlns[1] = "Yes";
			JPanel avlnP = getRBPanel(avlnjbg, 2, 150, 30, avlnjrb, avlns);
			avlnP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, avlnP, 60,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,avlnP, 40,SpringLayout.WEST, runnerP);
			runnerP.add(avlnP);
			avlnjrb[0].addActionListener(ProcessSwitcher);
			avlnjrb[1].addActionListener(ProcessSwitcher);
			avlnjrb[0].setEnabled(false);
			avlnjrb[1].setSelected(true);
			avlnjrb[1].setEnabled(false);
				
			JLabel baselineL= new JLabel ("baseline");
			baselineL.setPreferredSize(new Dimension(60, 25));
			slayout.putConstraint(SpringLayout.NORTH, baselineL, 90,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, baselineL, 0 ,SpringLayout.WEST, runnerP);
			runnerP.add(baselineL);
			String baselines[] = new String[2];
			baselines[0] = "No";
			baselines[1] = "Yes";
			JPanel baselineP = getRBPanel(baselinejbg, 2, 150, 30, baselinejrb, baselines);
			baselineP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, baselineP, 90,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,baselineP, 40,SpringLayout.WEST, runnerP);
			runnerP.add(baselineP);
			baselinejrb[0].addActionListener(ProcessSwitcher);
			baselinejrb[1].addActionListener(ProcessSwitcher);
			baselinejrb[0].setEnabled(false);
			baselinejrb[1].setSelected(true);
			baselinejrb[1].setEnabled(false);

			//Modules switch for TEM
			JLabel label2= new JLabel ("----- TEM N Cycle SWITCHES ------");
			label2.setPreferredSize(new Dimension(200, 30));
			slayout.putConstraint(SpringLayout.NORTH, label1, 0,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label1, 250 ,SpringLayout.WEST, runnerP);
			runnerP.add(label2);

			JLabel envmoduleL= new JLabel ("ENV Module");
			envmoduleL.setPreferredSize(new Dimension(80, 25));
			slayout.putConstraint(SpringLayout.NORTH, envmoduleL, 30,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, envmoduleL, 250 ,SpringLayout.WEST, runnerP);
			runnerP.add(envmoduleL);
			String envmoduleS[] = new String[2];
			envmoduleS[0] = "No";
			envmoduleS[1] = "Yes";
			JPanel envmoduleP = getRBPanel(envmodulejbg, 2, 150, 30, envmodulejrb, envmoduleS);
			envmoduleP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, envmoduleP, 30,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,envmoduleP, 320,SpringLayout.WEST, runnerP);
			runnerP.add(envmoduleP);
			envmodulejrb[0].addActionListener(ProcessSwitcher);
			envmodulejrb[1].addActionListener(ProcessSwitcher);
			envmodulejrb[0].setEnabled(false);
			envmodulejrb[1].setSelected(true);
			envmodulejrb[1].setEnabled(false);
		 
			JLabel ecomoduleL= new JLabel ("ECO Module");
			ecomoduleL.setPreferredSize(new Dimension(80, 25));
			slayout.putConstraint(SpringLayout.NORTH, ecomoduleL, 60,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, ecomoduleL, 250 ,SpringLayout.WEST, runnerP);
			runnerP.add(ecomoduleL);
			String ecomoduleS[] = new String[2];
			ecomoduleS[0] = "No";
			ecomoduleS[1] = "Yes";
			JPanel ecomoduleP = getRBPanel(ecomodulejbg, 2, 150, 30, ecomodulejrb, ecomoduleS);
			ecomoduleP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, ecomoduleP, 60,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,ecomoduleP, 320,SpringLayout.WEST, runnerP);
			runnerP.add(ecomoduleP);
			ecomodulejrb[0].addActionListener(ProcessSwitcher);
			ecomodulejrb[1].addActionListener(ProcessSwitcher);
			ecomodulejrb[0].setEnabled(false);
			ecomodulejrb[1].setSelected(true);
			ecomodulejrb[1].setEnabled(false);
		 
			JLabel dslmoduleL= new JLabel ("DSL Module");
			dslmoduleL.setPreferredSize(new Dimension(80, 25));
			slayout.putConstraint(SpringLayout.NORTH, dslmoduleL, 90,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, dslmoduleL, 250 ,SpringLayout.WEST, runnerP);
			runnerP.add(dslmoduleL);
			String dslmoduleS[] = new String[2];
			dslmoduleS[0] = "No";
			dslmoduleS[1] = "Yes";
			JPanel dslmoduleP = getRBPanel(dslmodulejbg, 2, 150, 30, dslmodulejrb, dslmoduleS);
			dslmoduleP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, dslmoduleP, 90,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,dslmoduleP, 320,SpringLayout.WEST, runnerP);
			runnerP.add(dslmoduleP);
			dslmodulejrb[0].addActionListener(ProcessSwitcher);
			dslmodulejrb[1].addActionListener(ProcessSwitcher);
			dslmodulejrb[0].setEnabled(false);
			dslmodulejrb[1].setSelected(true);
			dslmodulejrb[1].setEnabled(false);		 

			JLabel dsbmoduleL= new JLabel ("DSB Module");
			dsbmoduleL.setPreferredSize(new Dimension(80, 25));
			slayout.putConstraint(SpringLayout.NORTH, dsbmoduleL, 120,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, dsbmoduleL, 250 ,SpringLayout.WEST, runnerP);
			runnerP.add(dsbmoduleL);
			String dsbmoduleS[] = new String[2];
			dsbmoduleS[0] = "No";
			dsbmoduleS[1] = "Yes";
			JPanel dsbmoduleP = getRBPanel(dsbmodulejbg, 2, 150, 30, dsbmodulejrb, dsbmoduleS);
			dsbmoduleP.setPreferredSize(new Dimension(150,30));
			slayout.putConstraint(SpringLayout.NORTH, dsbmoduleP, 120,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,dsbmoduleP, 320,SpringLayout.WEST, runnerP);
			runnerP.add(dsbmoduleP);
			dsbmodulejrb[0].addActionListener(ProcessSwitcher);
			dsbmodulejrb[1].addActionListener(ProcessSwitcher);
			dsbmodulejrb[0].setEnabled(false);
			dsbmodulejrb[1].setSelected(true);
			dsbmodulejrb[1].setEnabled(false);
		 
			//Buttons for Run Model
			JLabel label3= new JLabel ("----------- MODEL RUN CONTROLS ---------------------------------");
			label3.setPreferredSize(new Dimension(350, 30));
			slayout.putConstraint(SpringLayout.NORTH, label3, 180,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label3, 0 ,SpringLayout.WEST, runnerP);
			runnerP.add(label3);
			
			runnerP.setToolTipText("if 'setup' inactive, in Configurer Tab, " +
					"click ModelControlFile 'select' or 'updateControlFile' !");
				
			JLabel label4= new JLabel ("Please Select Cohort(s)");
			label4.setPreferredSize(new Dimension(150, 30));
			slayout.putConstraint(SpringLayout.NORTH, label4, 210,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label4, 30 ,SpringLayout.WEST, runnerP);
			runnerP.add(label4);

			runchtCB.setPreferredSize(new Dimension(90, 25));
			slayout.putConstraint(SpringLayout.NORTH, runchtCB, 220,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,runchtCB, 200,SpringLayout.WEST, runnerP);
			runnerP.add(runchtCB);

			JLabel label4a= new JLabel("Grid id");
			label4a.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, label4a, 250,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label4a, 50 ,SpringLayout.WEST, runnerP);
			runnerP.add(label4a);
			grdidTF.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, grdidTF, 270,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,grdidTF, 50,SpringLayout.WEST, runnerP);
			grdidTF.setEditable(false);
			grdidTF.setText("--");
			runnerP.add(grdidTF);
						
			JLabel label4b= new JLabel("EQ-CHT id");
			label4b.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, label4b, 250,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label4b, 120 ,SpringLayout.WEST, runnerP);
			runnerP.add(label4b);
			eqchtidTF.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, eqchtidTF, 270,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,eqchtidTF, 120,SpringLayout.WEST, runnerP);
			eqchtidTF.setEditable(false);
			eqchtidTF.setText("--");
			runnerP.add(eqchtidTF);

			JLabel label4c= new JLabel("SP-CHT id");
			label4c.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, label4c, 250,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label4c, 190 ,SpringLayout.WEST, runnerP);
			runnerP.add(label4c);
			spchtidTF.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, spchtidTF, 270,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,spchtidTF, 190,SpringLayout.WEST, runnerP);
			spchtidTF.setEditable(false);
			spchtidTF.setText("--");
			runnerP.add(spchtidTF);

			JLabel label4d= new JLabel("TR-CHT id");
			label4d.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, label4d, 250,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label4d, 260 ,SpringLayout.WEST, runnerP);
			runnerP.add(label4d);
			trchtidTF.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, trchtidTF, 270,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,trchtidTF, 260,SpringLayout.WEST, runnerP);
			trchtidTF.setEditable(false);
			trchtidTF.setText("--");
			runnerP.add(trchtidTF);

			JLabel label4e= new JLabel("Veg Code");
			label4e.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, label4e, 250,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label4e, 330 ,SpringLayout.WEST, runnerP);
			runnerP.add(label4e);
			vegidTF.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, vegidTF, 270,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,vegidTF, 330,SpringLayout.WEST, runnerP);
			vegidTF.setEditable(false);
			vegidTF.setText("--");
			runnerP.add(vegidTF);

			JLabel label4f= new JLabel("Drg Code");
			label4f.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, label4f, 250,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST, label4f, 400 ,SpringLayout.WEST, runnerP);
			runnerP.add(label4f);
			drgidTF.setPreferredSize(new Dimension(60, 20));
			slayout.putConstraint(SpringLayout.NORTH, drgidTF, 270,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,drgidTF, 400,SpringLayout.WEST, runnerP);
			drgidTF.setEditable(false);
			drgidTF.setText("--");
			runnerP.add(drgidTF);

			setupB.setPreferredSize(new Dimension(70, 40));
			slayout.putConstraint(SpringLayout.NORTH, setupB, 320,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,setupB, 100,SpringLayout.WEST, runnerP);
			runnerP.add(setupB);
			
			exitB.setPreferredSize(new Dimension(70, 40));
			slayout.putConstraint(SpringLayout.NORTH, exitB, 320,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,exitB, 250,SpringLayout.WEST, runnerP);
			runnerP.add(exitB);	
			exitB.setToolTipText("Terminate TEM and exit!");

			startstopB.setPreferredSize(new Dimension(120, 40));
			slayout.putConstraint(SpringLayout.NORTH, startstopB, 370,SpringLayout.NORTH, runnerP);
			slayout.putConstraint(SpringLayout.WEST,startstopB, 150,SpringLayout.WEST, runnerP);
			runnerP.add(startstopB);		 
			
			//Simulation Information
			JLabel dashlineL= new JLabel ("------------- CURRENT SIMULATION INFORMATION " +
			"----------------------");
				dashlineL.setPreferredSize(new Dimension(440, 20));
				slayout.putConstraint(SpringLayout.NORTH, dashlineL, 420,SpringLayout.NORTH, configP);
				slayout.putConstraint(SpringLayout.WEST, dashlineL, 0 ,SpringLayout.WEST, configP);
				runnerP.add(dashlineL);

			JTabbedPane tableTP = new JTabbedPane();
				tableTP.setPreferredSize(new Dimension(400, 250));
				slayout.putConstraint(SpringLayout.NORTH, tableTP, 460,SpringLayout.NORTH, configP);
				slayout.putConstraint(SpringLayout.WEST,tableTP, 10,SpringLayout.WEST, configP);
				runnerP.add(tableTP);
	
				JScrollPane stateSP = new JScrollPane(stateTB);
				stateSP.setPreferredSize(new Dimension(400, 250));
				tableTP.add("Fixed State", stateSP);
	
				JScrollPane initSP = new JScrollPane(initTB);
				initSP.setPreferredSize(new Dimension(400, 250));
				tableTP.add("Initial State", initSP);

				JScrollPane fixparSP = new JScrollPane(fixparTB);
				fixparSP.setPreferredSize(new Dimension(400, 250));
				tableTP.add("Fixed Parameters", fixparSP);

				JScrollPane calparSP = new JScrollPane(calparTB);
				calparSP.setPreferredSize(new Dimension(400, 250));
				tableTP.add("Cal. Parameters", calparSP);
				
			///
			controlTP.add("TEM Configurer", configP);
			controlTP.add("TEM runner", runnerP);
			
		    f.add(controlTP, BorderLayout.CENTER);
		   		    
		    f.setLocation(1,1);
		    f.setPreferredSize(new Dimension(500, 800));
		    f.setSize(500, 800);
		    f.setVisible(true);
		}catch (Exception e){	  	
		   System.out.println(e.getMessage());
		} finally {
			//System.out.println("In final");
		}
	};
	
	private JPanel getRBPanel(ButtonGroup jbg, int rbnum, int bglength, int rbheight,
			JRadioButton jrb[], String rb[]){
		JPanel rbP = new JPanel();
		SpringLayout slayout = new SpringLayout();
		rbP.setLayout(slayout);
		int j=0;
		int ilength=0;
		for(int i= 0; i<rbnum;i++){
			jrb[i] = new JRadioButton(rb[i]);
			int rblength = Math.max(50, rb[i].length()*10);

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

	//
	private ActionListener ControlfileUpdater = new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			startstopB.setEnabled(false);    //any selection will re-set model run
			setupB.setEnabled(false);
			
			nfeedjrb[0].setEnabled(false);
			nfeedjrb[1].setEnabled(false);
			avlnjrb[0].setEnabled(false);
			avlnjrb[1].setEnabled(false);
			baselinejrb[0].setEnabled(false);
			baselinejrb[1].setEnabled(false);
		
			envmodulejrb[0].setEnabled(false);
			envmodulejrb[1].setEnabled(false);
			ecomodulejrb[0].setEnabled(false);
			ecomodulejrb[1].setEnabled(false);
			dslmodulejrb[0].setEnabled(false);
			dslmodulejrb[1].setEnabled(false);
			dsbmodulejrb[0].setEnabled(false);
			dsbmodulejrb[1].setEnabled(false);
			
			runchtCB.setEnabled(false);
						
			//controlfile editable
			controlfileTF.setEditable(true);
			
			//must update the control file, before model setup for run
			updateControlfileB.setEnabled(true);   //then, update the controller in configurer
			updateControlfileB.setToolTipText("Must click this to activate 'setup' in runner tab!");
		
		}
				
	};
	
	private ActionListener RunstageIoptioner = new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			if (runstageRB[0].isSelected()){
				ccdfileinCB.setEnabled(true);
				ccdfileTF.setEnabled(true);
			} else {
				ccdfileinCB.setSelected(false);
				
				ccdfileinCB.setEnabled(false);
				ccdfileTF.setText("");
				ccdfileTF.setEnabled(false);
			}

		}
	};
	
	//
	private ActionListener InoptionsSwitcher = new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			startstopB.setEnabled(false);    //will reset the model run
			if (controlfileTF.getText().isEmpty() 
					|| updateControlfileB.isEnabled()) {
				setupB.setEnabled(false);     //if the general I/O files NOT ready
			} else {
				setupB.setEnabled(true);
			}
					
			//then, update the IO options in configurer	
			//1) calibrated parameters read-in
			if (califileinCB.isSelected()) {
				config.califilein=true;
				if(califileTF.getText().length()==0) {
					califileTF.setText("");  //default
				}
				califileTF.setEnabled(true);
				config.califile=califileTF.getText();
			}else {
				config.califilein=false;
				califileTF.setText("");
				califileTF.setEnabled(false);
				config.califile="";
			}
			
			// 2a) calirestart.nc file use
			if (ccdfileinCB.isSelected()) {
				config.ccdfilein=true;
				
				ccdfileTF.setEnabled(true);
				if(ccdfileTF.getText().length()==0) {
					ccdfileTF.setText(config.calibrationdir+"calirestart.nc");  //default
				}
				config.ccdfile=ccdfileTF.getText();
				
			}else {
				config.ccdfilein=false;
			
			}

		}
				
	};

	//
	private ActionListener OutoptionsSwitcher = new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			startstopB.setEnabled(false);    //any selection will re-set model run
			if (controlfileTF.getText().isEmpty() 
					|| updateControlfileB.isEnabled()) {
				setupB.setEnabled(false);     //if the general I/O files NOT ready
			} else {
				setupB.setEnabled(true);
			}
					
			//then, update the IO options in configurer
			if (outmodeRB[0].isSelected()) {
				config.OSITE=true;
				config.OREGN=false;
				
				outdlyCB.setEnabled(true);
				outmlyCB.setEnabled(true);
				outylyCB.setEnabled(true);
								
				if (outdlyCB.isSelected()) {
					config.OSDLY=true;
				} else {
					config.OSDLY=false;
				}
				if (outmlyCB.isSelected()) {
					config.OSMLY=true;
				}else {
					config.OSMLY=false;
				}
				
				if (outylyCB.isSelected()) {
					config.OSYLY=true;
				}else {
					config.OSYLY=false;
				}

			} else if (outmodeRB[1].isSelected()) {
				config.OSITE=false;
				config.OREGN=true;
				
				outdlyCB.setSelected(false);     //Because those options are for Sing-Site run only
				outmlyCB.setSelected(false);
				outylyCB.setSelected(false);
				
				outdlyCB.setEnabled(false);
				outmlyCB.setEnabled(false);
				outylyCB.setEnabled(false);

			} else if (outmodeRB[2].isSelected()) {
				config.OSITE=false;
				config.OREGN=false;
				
				outdlyCB.setSelected(false);     //Because those options are for Sing-Site run only
				outmlyCB.setSelected(false);
				outylyCB.setSelected(false);
				
				outdlyCB.setEnabled(false);
				outmlyCB.setEnabled(false);
				outylyCB.setEnabled(false);

			}
			
			//
			opGraphCB.setEnabled(true);
			obGraphCB.setEnabled(true);
			if (opGraphCB.isSelected()) {
				config.OPGRAPH=true;
			}else {
				config.OPGRAPH=false;
			}

			if (obGraphCB.isSelected()) {
				config.OBGRAPH=true;
			}else {
				config.OBGRAPH=false;
			}

			config.OGRAPH=false;
			if (config.OBGRAPH || config.OPGRAPH) {
				config.OGRAPH=true;
			}
		}
				
	};

	//
	private ActionListener ProcessSwitcher = new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			if (startstopB.isEnabled()) {
				setupB.setEnabled(true);
				startstopB.setEnabled(false);
			}
			
			if (TEM!=null) setTEMswitchesFromRunner();
		}
				
	};

	//
	private ActionListener consoleSwitcher = new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			
			if (TEM!=null) {
				if (consoleCB.isSelected()) {
					TEM.md.setConsoledebug(true);
				} else {
					TEM.md.setConsoledebug(false);					
				}
			}
		}
				
	};

	//
	private ActionListener netcdfSwitcher = new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			
			if (TEM!=null) {
				if (tocdlCB.isSelected()) {
				// code needed for converting netcdf to CDL
				} else {
				// code needed here
				}
			}
		}
				
	};

	private TableModelListener initvalueChanger = new TableModelListener() {
		public void tableChanged(TableModelEvent e) {
			setupB.setEnabled(true);	
			exitB.setEnabled(true);
		}
				
	};

	private TableModelListener calparChanger = new TableModelListener() {
		public void tableChanged(TableModelEvent e) {
			setupB.setEnabled(true);
			exitB.setEnabled(true);
		}
				
	};

//------ Operations on Configure Tab of Control Panel ------------------------------------
	public class ConfigureSelector implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
			//open file chooser
			String defaultdir = "config";
					
			JFileChooser fc = new JFileChooser(defaultdir);
			int returnVal =fc.showOpenDialog(selectControlfileB);
			if (returnVal == JFileChooser.APPROVE_OPTION) {
	            File file = fc.getSelectedFile();
	            
	            //set-up the configurer Tab of Control Panel
				outputdirTF.setEnabled(true);
				reginputdirTF.setEnabled(true);
				grdinputdirTF.setEnabled(true);
				eqchtinputdirTF.setEnabled(true);
				spchtinputdirTF.setEnabled(true);
				trchtinputdirTF.setEnabled(true);
				restartinputdirTF.setEnabled(true);
				calibrationdirTF.setEnabled(true);
				casenameTF.setEnabled(true);

				updateControlfileB.setEnabled(false);   //default
	            
	            controlfileTF.setText(file.getPath());
	            defaultConfig();
	            		                  
		        //enable model run setup controls in the runner Tab
				nfeedjrb[0].setEnabled(true);
				nfeedjrb[1].setEnabled(true);
				avlnjrb[0].setEnabled(true);
				avlnjrb[1].setEnabled(true);
//				baselinejrb[0].setEnabled(true);
//				baselinejrb[1].setEnabled(true);
           
				envmodulejrb[0].setEnabled(true);
				envmodulejrb[1].setEnabled(true);
				ecomodulejrb[0].setEnabled(true);
				ecomodulejrb[1].setEnabled(true);
				dslmodulejrb[0].setEnabled(true);
				dslmodulejrb[1].setEnabled(true);
				dsbmodulejrb[0].setEnabled(true);
				dsbmodulejrb[1].setEnabled(true);
 
				runchtCB.setEnabled(true);    
	            setupB.setEnabled(true);
	            
	            //start a new TEM run
	            initTEM();

	        } 		
		}
		
	};
	
		// read-in default control file, called by Class ConfigureSelector
		private void defaultConfig(){
		
		    String status ="";
		    try {
		    	status ="reading control file";
		    	String aFile = controlfileTF.getText();
			    config.controlfile = aFile;

		      BufferedReader input =  new BufferedReader(new FileReader(aFile));
		      try {
		        
		        config.outputdir = input.readLine();		        
		        outputdirTF.setText(config.outputdir);
		        config.reginputdir = input.readLine();		        
		        reginputdirTF.setText(config.reginputdir);
		        config.grdinputdir = input.readLine();		        
		        grdinputdirTF.setText(config.grdinputdir);
		        config.eqchtinputdir = input.readLine();		        
		        eqchtinputdirTF.setText(config.eqchtinputdir);
		        config.spchtinputdir = input.readLine();		        
		        spchtinputdirTF.setText(config.spchtinputdir);
		        config.trchtinputdir = input.readLine();		        
		        trchtinputdirTF.setText(config.trchtinputdir);
		        config.restartinputdir = input.readLine();		        
		        restartinputdirTF.setText(config.restartinputdir);
		        config.calibrationdir = input.readLine();		        
		        calibrationdirTF.setText(config.calibrationdir);
		        
		        config.runstage = input.readLine();
		        if (config.runstage.equalsIgnoreCase("eq")) {
		        	runstageRB[0].setSelected(true);
		        } else if (config.runstage.equalsIgnoreCase("sp")) {
		        	runstageRB[1].setSelected(true);		        	
		        } else if (config.runstage.equalsIgnoreCase("tr")) {
		        	runstageRB[2].setSelected(true);		        	
		        } else if (config.runstage.equalsIgnoreCase("sptr")) {
		        	runstageRB[3].setSelected(true);		        	
		        }
		        
		        config.initmode = input.readLine();		        
		        if (config.initmode.equalsIgnoreCase("lookup")) {
		        	initmodeRB[0].setSelected(true);
		        } else if (config.initmode.equalsIgnoreCase("restart")) {
		        	initmodeRB[1].setSelected(true);
		        } else if (config.initmode.equalsIgnoreCase("sitein")) {
		        	initmodeRB[2].setSelected(true);		        	
		        }
		        
		        config.climatemode = input.readLine();		        
		        if (config.climatemode.equalsIgnoreCase("normal")) {
		        	clmmodeRB[0].setSelected(true);
		        } else if (config.climatemode.equalsIgnoreCase("dynamic")) {
		        	clmmodeRB[1].setSelected(true);		        	
		        }

		        config.co2mode = input.readLine();		        
		        if (config.co2mode.equalsIgnoreCase("initial")) {
		        	co2modeRB[0].setSelected(true);
		        } else if (config.co2mode.equalsIgnoreCase("dynamic")) {
		        	co2modeRB[1].setSelected(true);
		        }

		        config.casename = input.readLine();		        
		        casenameTF.setText(config.casename);
     
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

		//runchort list
		private void runchtlist(int idlist []){	 
		
			try {
				chtList = new int[idlist.length];
				runchtCB.setModel(new DefaultComboBoxModel());
				runchtCB.addItem("ALL");
				for(int i=0; i<idlist.length; i++){
					runchtCB.addItem(String.valueOf(idlist[i]));
					chtList[i]=idlist[i];
				}
								
			} catch (Exception e) {
				System.err.println("Error in reading cohort list"+e);
			}
		};
		
	//Control file can be modified, in which case the model-run will be initialized again
	public class ConfigureUpdater implements ActionListener {

		public void actionPerformed(ActionEvent arg0) {
			
			//1) make sure all dir name is ending with "/"
			if (!outputdirTF.getText().endsWith("/")) 
				outputdirTF.setText(outputdirTF.getText()+"/");

			if (!reginputdirTF.getText().endsWith("/")) 
				reginputdirTF.setText(reginputdirTF.getText()+"/");

			if (!grdinputdirTF.getText().endsWith("/")) 
				grdinputdirTF.setText(grdinputdirTF.getText()+"/");

			if (!eqchtinputdirTF.getText().endsWith("/")) 
				eqchtinputdirTF.setText(eqchtinputdirTF.getText()+"/");

			if (!spchtinputdirTF.getText().endsWith("/")) 
				spchtinputdirTF.setText(spchtinputdirTF.getText()+"/");

			if (!trchtinputdirTF.getText().endsWith("/")) 
				trchtinputdirTF.setText(trchtinputdirTF.getText()+"/");

//			if (!restartinputdirTF.getText().endsWith("/")) 
				restartinputdirTF.setText(restartinputdirTF.getText());

			if (!calibrationdirTF.getText().endsWith("/")) 
				calibrationdirTF.setText(calibrationdirTF.getText()+"/");
			
			config.controlfile = controlfileTF.getText();

			//2) Modify the control file
			try {
			      PrintStream out = new PrintStream(new FileOutputStream(
			    		  config.controlfile));

			      //first output pools
			      out.println(outputdirTF.getText());
			      out.println(reginputdirTF.getText());
			      out.println(grdinputdirTF.getText());
			      out.println(eqchtinputdirTF.getText());
			      out.println(spchtinputdirTF.getText());
			      out.println(trchtinputdirTF.getText());
			      out.println(restartinputdirTF.getText());
			      out.println(calibrationdirTF.getText());
			      
			      String dumy="";
			      if (runstageRB[0].isSelected()) {
			    	  dumy="eq";
			      } else if (runstageRB[1].isSelected()) {
			    	  dumy="sp";
			      } else if (runstageRB[2].isSelected()) {
			    	  dumy="tr";
			      } else if (runstageRB[3].isSelected()) {
			    	  dumy="sptr";
			      }
			      out.println(dumy);
			      
			      if (initmodeRB[0].isSelected()) {
			    	  dumy="lookup";
			      } else if (initmodeRB[1].isSelected()) {
			    	  dumy="restart";
			      } else if (initmodeRB[2].isSelected()) {
			    	  dumy="sitein";
			      }		      
			      out.println(dumy);
			      
			      if (clmmodeRB[0].isSelected()) {
			    	  dumy="normal";
			      } else if (clmmodeRB[1].isSelected()) {
			    	  dumy="dynamic";
			      }		      
			      out.println(dumy);

			      if (co2modeRB[0].isSelected()) {
			    	  dumy="initial";
			      } else if (co2modeRB[1].isSelected()) {
			    	  dumy="dynamic";
			      }		      
			      out.println(dumy);

			      out.println(casenameTF.getText());

			      out.close();
			      
			      updateControlfileB.setEnabled(false);

			} catch (FileNotFoundException e) {
			      e.printStackTrace();
			}
	            
	     //3) enable model run setup controls in the runner Tab
			nfeedjrb[0].setEnabled(true);
			nfeedjrb[1].setEnabled(true);
			avlnjrb[0].setEnabled(true);
			avlnjrb[1].setEnabled(true);
//			baselinejrb[0].setEnabled(true);
//			baselinejrb[1].setEnabled(true);
       
			envmodulejrb[0].setEnabled(true);
			envmodulejrb[1].setEnabled(true);
			ecomodulejrb[0].setEnabled(true);
			ecomodulejrb[1].setEnabled(true);
			dslmodulejrb[0].setEnabled(true);
			dslmodulejrb[1].setEnabled(true);
			dsbmodulejrb[0].setEnabled(true);
			dsbmodulejrb[1].setEnabled(true);

			runchtCB.setEnabled(true);
			
			setupB.setEnabled(true);
						
			//Then, resume a new TEM run
			initTEM();
		}		
	};

	//------ Operations on Runner Tab of Control Panel --------------------------------------
	public class Exit implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
			System.exit(0);	 
		}
				
	};

	public class CohortSelector implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
			//			 
			String Index = runchtCB.getSelectedItem().toString();					
			System.out.println("\n Cohort(s): "+Index+" Selected for running ...");
			
			try {

				if (Index.compareToIgnoreCase("ALL")==0) {
					int idlist []=TEM.runcht.cinputer.grdidlist;
					int idlist1 []=TEM.runcht.cinputer.eqchtidlist;
					int idlist2 []=TEM.runcht.cinputer.spchtidlist;
					int idlist3 []=TEM.runcht.cinputer.trchtidlist;
					int idlist4 []=TEM.runcht.cinputer.vegidlist;
					int idlist5 []=TEM.runcht.cinputer.drgidlist;

					chtSelected = new int[chtList.length];
					chtSelected = chtList;

					Arrays.sort(idlist);
					grdidTF.setText(""+idlist[0]+"~"+idlist[idlist.length-1]);
					
					Arrays.sort(idlist1);
					eqchtidTF.setText(""+idlist1[0]+"~"+idlist1[idlist1.length-1]);

					if (TEM.md.getRunsp() || TEM.md.getRuntr()) {
						Arrays.sort(idlist2);
						spchtidTF.setText(""+idlist2[0]+"~"+idlist2[idlist2.length-1]);
					}else {
						spchtidTF.setText("--");						
					}
					
					if (TEM.md.getRuntr()) {
						Arrays.sort(idlist3);
						trchtidTF.setText(""+idlist3[0]+"~"+idlist3[idlist3.length-1]);
					}else {
						trchtidTF.setText("--");						
					}

					Arrays.sort(idlist4);
					vegidTF.setText(""+idlist4[0]+"~"+idlist4[idlist4.length-1]);

					Arrays.sort(idlist5);
					drgidTF.setText(""+idlist5[0]+"~"+idlist5[idlist5.length-1]);

				} else {
					int i = Integer.valueOf(Index)-1;
					chtSelected = new int[1];
					chtSelected[0]=chtList[i];
					
					TEM.runchtid = chtSelected[0];
					errid = TEM.setids();
						
					grdidTF.setText(""+TEM.grdid);
					eqchtidTF.setText(""+TEM.eqchtid);
					spchtidTF.setText(""+TEM.spchtid);
					trchtidTF.setText(""+TEM.trchtid);
					vegidTF.setText(""+TEM.vegid);
					drgidTF.setText(""+TEM.drgid);
					
				}

			} catch (Exception e) {
				System.err.println("Error in reading ids for Selected Cohorts");
			}
		}
		
	};

	public class StartStop implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
					
			// 1) "Stop" - Stop the in-progress run, in order to check or change setting-up
			if (startstopB.getText().equals("Continue")){
				startstopB.setText("Start");
				setupB.setEnabled(true);
				exitB.setEnabled(true);
				
				if (TEM.runchtid!=TEM.prechtid && chtSelected.length>1) {
					icht++;
					TEM.prechtid = TEM.runchtid;
				} 
								 
			// 2) after all above, Start the run as defined
			} else if(startstopB.getText().equals("Start")){
				startstopB.setText("Continue");
				setupB.setEnabled(false);
				exitB.setEnabled(false);
				
				runTEM();
				
			}
		}
	};

	// run cohort(s) 
		private void runTEM() {
	    	
	    	try {
				while (icht<chtSelected.length) {
						// clean the plotter, if exists, for showing next cohort
						if (bvplotter!=null) bvplotter.reset();
						if (pvplotter!=null) pvplotter.reset();

						// 2a) get cohort IDs and cruid
						TEM.runchtid=chtSelected[icht];
						errid = TEM.setids();

						System.out.println("\n Cohort: "+TEM.runchtid + " is Running ......");

						// 2b) get data for the cohort
						TEM.runcht.califile="";   //must clean-up
						errid = TEM.chtdata();				
						// 2c) UPDATE the initial and parameters from the runner Tab of control panel, before .run()
						setTEMinitsFromRunner();
						setTEMparsFromRunner();
						// 2d) UPDATE the process setting from the runner Tab of control panel, before .run() 
						setTEMswitchesFromRunner();
						// 2e) Display information
						TEMrunInfo();
						
						if (errid!=0) {
							break;
						} else {						
							errid = TEM.chtrun();
							if (errid>=0) {
								System.out.println("Cohort "+TEM.runchtid+" successfully done!");
							} else {
								System.out.println("error in running: "+ TEM.runchtid);
							}
						}
						
						TEMrunInfo();
						Thread.currentThread().wait(10000);	
												
					}
				}catch (Exception e) {
//					System.err.println("Error in run cohort:" + TEM.runchtid);
				}
			};
		
	// Model-run "Setup" -  1) I/O options was setup in Config Tab
	//  AND/OR              2) module/process switches on/off in Runner Tab
	public class Setup implements ActionListener{

		public void actionPerformed(ActionEvent arg0) {
				
			//clean-up before setup
			if ((PhyVariablePlotter.f)!=null) PhyVariablePlotter.f.dispose();
			if ((BioVariablePlotter.f)!=null) BioVariablePlotter.f.dispose();
			
			icht   = 0;
			errid  = 0;
			// 1) get I/O options from GUI configurer
			setTEMiosFromConfig();
			
			// 2) initilize model output options
			errid = TEM.initOutputs();
								
			// 3) get cohort IDs and cruid for the first selected cohort
			TEM.prechtid=-1;
			TEM.runcht.cohortcount=0;
			TEM.runchtid=chtSelected[0];
			errid = TEM.setids();
			
			// 4) get data for run a cohort
			errid = TEM.chtdata();
			
			// 5) UPDATE the initial and parameters from the runner Tab of control panel, before .run()
			setTEMinitsFromRunner();
			setTEMparsFromRunner();
			
			// 6) UPDATE the process setting from the runner Tab of control panel, before .run() 
			setTEMswitchesFromRunner();
			if (!consoleCB.isSelected()) TEM.md.setConsoledebug(false);
			
			// 7) Display information
			TEMrunInfo();

			startstopB.setEnabled(true);
			startstopB.setText("Start");

		}
		
	};

//--------------------------------------------------------------------------------------
	private void initTEM(){
        try {
        	//start a TEM run 
        	TEM=new runner();
        	
        	TEM.interactively = false;
        	
        	//control file
        	TEM.controlfile = config.controlfile;
        	//initialize TEM inputs
        	errid = TEM.initInputs(0, 1, "siter");

        	//cohort id lists from cohortinputer
        	if (TEM.md.getRuneq()) {
        		runchtlist(TEM.runcht.cinputer.eqchtidlist);
        	} else if (TEM.md.getRunsp()) {
        		runchtlist(TEM.runcht.cinputer.spchtidlist);
        	} else if (TEM.md.getRuntr()) {
        		runchtlist(TEM.runcht.cinputer.trchtidlist);
        	}
        	
			icht = 0;

        } catch (Exception e) {
        	//
        }
	}

	//setup model options for model run, 
	//called by Class: setup
	private void setTEMiosFromConfig(){
		
		//model I/O options
		TEM.runcht.califilein = config.califilein;  //switch to read-in calibrated parameters from Jcalinput.txt			
		TEM.runcht.califile   = config.califile;
		
		TEM.runcht.usecalirestart = config.ccdfilein;   //switch to read-in Env. driver for equilibrim-run from calirestart.nc 
		TEM.runcht.outcalirestart = false;   //only valid if 'usecalirestart' above is set to false
		TEM.runcht.ccdfile        = config.ccdfile;
		
		TEM.runcht.outmodes.OSITER  = config.OSITE;
		TEM.runcht.outmodes.ODAY    = config.OSDLY;
		TEM.runcht.outmodes.OMONTH  = config.OSMLY;
		TEM.runcht.outmodes.OYEAR   = config.OSYLY;
		TEM.runcht.outmodes.OREGNER = config.OREGN;					
	
		//plotters when NO output file
		TEM.runcht.GUIgraphic = config.OGRAPH;
		if (TEM.runcht.GUIgraphic) {

			bvplotter =new BioVariablePlotter();			
			pvplotter =new PhyVariablePlotter();
			
			TEM.runcht.plotting.setPlotter(bvplotter);
			TEM.runcht.plotting.setPlotter2(pvplotter);
			
			if (config.OBGRAPH) {
				BioVariablePlotter.f.setVisible(true);
			} else {
				BioVariablePlotter.f.setVisible(false);
			}
			if (config.OPGRAPH) {
				PhyVariablePlotter.f.setVisible(true);
			} else {
				PhyVariablePlotter.f.setVisible(false);
			}
		}

	};

	//update model process switches for model initialization/run, 
	//called by Class: Setup/StartPause, after .chtdata() but before .chtrun().
	private void setTEMswitchesFromRunner(){
		//
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
		TEM.runcht.cht.getBd().setBaseline(baseline); 	 
        TEM.runcht.cht.getBd().setAvlnflg(avlnflg);
        TEM.runcht.cht.getBd().setNfeed(nfeed);
        
        //
        if (envmodulejrb[0].isSelected())
        	TEM.runcht.cht.setEnvmodule(false);
        if (envmodulejrb[1].isSelected())
        	TEM.runcht.cht.setEnvmodule(true);

        if (ecomodulejrb[0].isSelected())
        	TEM.runcht.cht.setEcomodule(false);
        if (ecomodulejrb[1].isSelected())
        	TEM.runcht.cht.setEcomodule(true);
        
        if (dslmodulejrb[0].isSelected())
        	TEM.runcht.cht.setDslmodule(false);
        if (dslmodulejrb[1].isSelected())
        	TEM.runcht.cht.setDslmodule(true);

        if (dsbmodulejrb[0].isSelected())
        	TEM.runcht.cht.setDsbmodule(false);
        if (dsbmodulejrb[1].isSelected())
        	TEM.runcht.cht.setDsbmodule(true);
	};


	//after clicking start, update the initital state variables to tem, called by Class: Setup
	private void setTEMinitsFromRunner(){
	
		SiteIn inits = new SiteIn();
		
		String dummy=" ";
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_MOSSTHICK, 1);
		if (dummy!=" ") inits.setMossthick(Float.valueOf(dummy));
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_FIBTHICK, 1);
		if (dummy!=" ") inits.setFibthick(Float.valueOf(dummy));
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_HUMTHICK, 1);
		if (dummy!=" ") inits.setHumthick(Float.valueOf(dummy));
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_VEGC, 1);
		if (dummy!=" ") inits.setVegc(Float.valueOf(dummy));
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_VEGN, 1);
		if (dummy!=" ") inits.setVegn(Float.valueOf(dummy));
		
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_SOILC, 1);
		if (dummy!=" ") inits.setSoilc(Float.valueOf(dummy));
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_FIBSOILC, 1);
		if (dummy!=" ") inits.setFibc(Float.valueOf(dummy));
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_HUMSOILC, 1);
		if (dummy!=" ") inits.setHumc(Float.valueOf(dummy));
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_MINESOILC, 1);
		if (dummy!=" ") inits.setMinc(Float.valueOf(dummy));
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_AVAILN, 1);
		if (dummy!=" ") inits.setAvln(Float.valueOf(dummy));
		dummy = (String)initTB.getValueAt(GUIconfigurer.I_SOILN, 1);
		if (dummy!=" ") inits.setOrgn(Float.valueOf(dummy));
           
		if (dummy!=" ") TEM.runcht.cht.setSiteStates(inits);
      
	};

	
	//after clicking start, update the parameters to tem, called by Class: Setup/Resetup
	private void setTEMparsFromRunner(){
		
		String fdummy=" ";
		
		soipar_cal sbcalpar = new soipar_cal();
		vegpar_cal vbcalpar = new vegpar_cal();	
		
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_CMAX, 1);
		if (fdummy!=" ") vbcalpar.setCmax(Float.valueOf(fdummy));
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_NMAX, 1);
		if (fdummy!=" ") vbcalpar.setNmax(Float.valueOf(fdummy));
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_CFALL, 1);
		if (fdummy!=" ") vbcalpar.setCfall(Float.valueOf(fdummy));
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_NFALL, 1);
		if (fdummy!=" ") vbcalpar.setNfall(Float.valueOf(fdummy));
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_KRB, 1);
		if (fdummy!=" ") vbcalpar.setKrb(Float.valueOf(fdummy));
				
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_KDCFIB, 1);
		if (fdummy!=" ") sbcalpar.setKdcfib(Float.valueOf(fdummy));
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_KDCHUM, 1);
		if (fdummy!=" ") sbcalpar.setKdchum(Float.valueOf(fdummy));
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_KDCMIN, 1);
		if (fdummy!=" ") sbcalpar.setKdcmin(Float.valueOf(fdummy));
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_KDCSLOW, 1);
		if (fdummy!=" ") sbcalpar.setKdcslow(Float.valueOf(fdummy));
		fdummy = (String)calparTB.getValueAt(GUIconfigurer.I_NUP, 1);
		if (fdummy!=" ") sbcalpar.setNup(Float.valueOf(fdummy));
		
		if (fdummy!=" ") TEM.runcht.cht.resetCalPar(vbcalpar, sbcalpar);

		//
		soipar_bgc sbbgcpar = new soipar_bgc();
		vegpar_bgc vbbgcpar = new vegpar_bgc();

		fdummy =(String) fixparTB.getValueAt(GUIconfigurer.I_m1, 1);
		if (fdummy!=" ") vbbgcpar.setM1(Float.valueOf(fdummy));
		fdummy =(String) fixparTB.getValueAt(GUIconfigurer.I_m2, 1);
		if (fdummy!=" ") vbbgcpar.setM2(Float.valueOf(fdummy));
		fdummy =(String) fixparTB.getValueAt(GUIconfigurer.I_m3, 1);
		if (fdummy!=" ") vbbgcpar.setM3(Float.valueOf(fdummy));
		fdummy =(String) fixparTB.getValueAt(GUIconfigurer.I_m4, 1);
		if (fdummy!=" ") vbbgcpar.setM4(Float.valueOf(fdummy));
		fdummy =(String) fixparTB.getValueAt(GUIconfigurer.I_fsoma, 1);
		if (fdummy!=" ") sbbgcpar.setFsoma(Float.valueOf(fdummy));
		fdummy =(String) fixparTB.getValueAt(GUIconfigurer.I_fsompr, 1);
		if (fdummy!=" ") sbbgcpar.setFsompr(Float.valueOf(fdummy));
		fdummy =(String) fixparTB.getValueAt(GUIconfigurer.I_fsomcr, 1);
		if (fdummy!=" ") sbbgcpar.setFsomcr(Float.valueOf(fdummy));
		fdummy =(String) fixparTB.getValueAt(GUIconfigurer.I_som2co2, 1);
		if (fdummy!=" ") sbbgcpar.setSom2co2(Float.valueOf(fdummy));
		
		if (fdummy!=" ") TEM.runcht.cht.resetBgcPar(vbbgcpar, sbbgcpar);
				
	};

	//model initial conditions and calibration parameters 
    //called by Class: Setup, after .chtreint() And before during .run().
    private void TEMrunInfo(){

       int idummy;
       idummy=TEM.runcht.cht.getCd().getVegtype(); 	 
           	stateTB.setValueAt(Integer.toString(idummy), GUIconfigurer.I_VEGETATION, 1);
       idummy=TEM.runcht.cht.getCd().getDrgtype(); 	 
           	stateTB.setValueAt(Integer.toString(idummy), GUIconfigurer.I_DRAINAGE, 1);
       idummy=TEM.runcht.cht.getCd().getGrdid(); 	 
           	stateTB.setValueAt(Integer.toString(idummy), GUIconfigurer.I_GRD, 1);
       idummy=TEM.runcht.cht.getCd().getEqchtid(); 	 
           	stateTB.setValueAt(Integer.toString(idummy), GUIconfigurer.I_EQCHT, 1);
       idummy=TEM.runcht.cht.getCd().getSpchtid(); 	 
           	stateTB.setValueAt(Integer.toString(idummy), GUIconfigurer.I_SPCHT, 1);
       idummy=TEM.runcht.cht.getCd().getTrchtid(); 	 
       	    stateTB.setValueAt(Integer.toString(idummy), GUIconfigurer.I_TRCHT, 1);
        	    
       float ddummy;
       ddummy=(float)TEM.runcht.initstate.getMossthick(); 	 
           	initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_MOSSTHICK, 1);
       ddummy=(float)TEM.runcht.initstate.getFibthick(); 	 
           	initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_FIBTHICK, 1);
       ddummy=(float)TEM.runcht.initstate.getHumthick(); 	 
           	initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_HUMTHICK, 1);
       ddummy=(float)TEM.runcht.initstate.getVegc(); 	 
           	initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_VEGC, 1);
       ddummy=(float)TEM.runcht.initstate.getVegn(); 	 
           	initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_VEGN, 1);		
       ddummy=(float)TEM.runcht.initstate.getSoilc(); 	 
           	initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_SOILC, 1);	    
       ddummy=(float)TEM.runcht.initstate.getFibc(); 	 
       		initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_FIBSOILC, 1);
       ddummy=(float)TEM.runcht.initstate.getHumc(); 	 
       		initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_HUMSOILC, 1);
       ddummy=(float)TEM.runcht.initstate.getMinc(); 	 
       		initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_MINESOILC, 1);
       ddummy=(float)TEM.runcht.initstate.getAvln(); 	 
           	initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_AVAILN, 1);
       ddummy=(float)TEM.runcht.initstate.getOrgn(); 	 
           	initTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_SOILN, 1);

       //
           	vegpar_bgc vbpar = new vegpar_bgc();
           	soipar_bgc sbpar = new soipar_bgc();
           	TEM.runcht.cht.getBgcPar(vbpar, sbpar);

       ddummy=vbpar.getM1(); 	 
           	fixparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_m1, 1);
       ddummy=vbpar.getM2(); 	 
           	fixparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_m2, 1);
       ddummy=vbpar.getM3(); 	 
           	fixparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_m3, 1);
       ddummy=vbpar.getM4(); 	 
           	fixparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_m4, 1);
       ddummy=sbpar.getFsoma(); 	 
           	fixparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_fsoma, 1);
       ddummy=sbpar.getFsompr(); 	 
           	fixparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_fsompr, 1);
       ddummy=sbpar.getFsomcr(); 	 
           	fixparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_fsomcr, 1);  		
       ddummy=sbpar.getSom2co2(); 	 
           	fixparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_som2co2, 1);
           	
            //
            vegpar_cal vcpar = new vegpar_cal();
            soipar_cal scpar = new soipar_cal();
            TEM.runcht.cht.getCalPar(vcpar, scpar);

       ddummy=vcpar.getCmax(); 	 
           	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_CMAX, 1);
       ddummy=vcpar.getNmax(); 	 
           	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_NMAX, 1);
       ddummy=vcpar.getKrb(); 	 
           	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_KRB, 1);
       ddummy=vcpar.getCfall(); 	 
           	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_CFALL, 1);
       ddummy=vcpar.getNfall(); 	 
           	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_NFALL, 1);
           	
       ddummy=scpar.getNup(); 	 
           	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_NUP, 1);
       ddummy=scpar.getKdcfib(); 	 
           	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_KDCFIB, 1);
       ddummy=scpar.getKdchum(); 	 
           	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_KDCHUM, 1);
       ddummy=scpar.getKdcmin(); 	 
          	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_KDCMIN, 1);
       ddummy=scpar.getKdcslow(); 	 
           	calparTB.setValueAt(Float.toString(ddummy), GUIconfigurer.I_KDCSLOW, 1);
	   		
    };	
						
}