package GUI;

import java.awt.BorderLayout;
import java.awt.Dimension;
//import java.awt.Label;

import javax.swing.BoxLayout;
import javax.swing.JFrame;
//import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
//import javax.swing.SpringLayout;

import com.l2fprod.common.swing.JTaskPane;
import com.l2fprod.common.swing.JTaskPaneGroup;

public class BioVariablePlotter {

	static JFrame f;

	// flux vairables at yearly time-step
	public PlotterMode nppTP;
	public PlotterMode gppTP;
	public PlotterMode innppTP;
	public PlotterMode ingppTP;
	public PlotterMode raTP;
	public PlotterMode rhTP;
	
	public PlotterMode ltrfalcTP;
	public PlotterMode nuptakeTP;
	public PlotterMode netnminTP;
	public PlotterMode ltrfalnTP;
	
	// State variables at yearly time-step
	public PlotterMode vegcTP;
	public PlotterMode vegnTP;
	public PlotterMode fibsoilcTP;
	public PlotterMode humsoilcTP;
	public PlotterMode minesoilcTP;

	public PlotterMode avlnTP;
	public PlotterMode orgnTP;	
	public PlotterMode allsoilcTP;

	public PlotterMode laiTP;	
	public PlotterMode fpcTP;

	// Monthly variables
	public PlotterMode mgppTP;
	public PlotterMode mnppTP;
	public PlotterMode mrespTP;
	public PlotterMode mnetnminTP;
	public PlotterMode mltrfalcTP;
	public PlotterMode mltrfalnTP;
	
	public PlotterMode mlaiTP;
	public PlotterMode mvegcTP;
	public PlotterMode mvegnTP;
	public PlotterMode mavlnTP;

	public BioVariablePlotter() {

		f = new JFrame("Biological Variable Plot Viewer");

		f.setLayout(new BorderLayout());

		try {

			f.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

			JTabbedPane tp = new JTabbedPane();

			JPanel fluxpanel = getFluxPanel();
			JPanel statepanel = getStatePanel();
			JPanel monpanel = getMonthlyPanel();

			tp.add("Yealy Flux", fluxpanel);
			tp.add("Yearly State", statepanel);
			tp.add("Monthly Watch", monpanel);

			f.add(tp, BorderLayout.CENTER);

			f.setLocation(600, 1);
		} catch (Exception x) {

		}

		f.setSize(760, 800);
		f.setVisible(true);

	}

	private JPanel getFluxPanel() {
		JPanel targetPanel = new JPanel();
		targetPanel.setLayout(new BoxLayout(targetPanel, BoxLayout.X_AXIS));

		JTaskPane leftJTP = new JTaskPane();

		nppTP = new PlotterMode("NPP", 0, 1000);
		JPanel nppPanel = nppTP.getPanel();
		nppPanel.setPreferredSize(new Dimension(330, 125));

		JTaskPaneGroup nppTG = new JTaskPaneGroup();
		nppTG.setSpecial(false);
		nppTG.setExpanded(true);
		nppTG.setTitle("NPP");
		nppTG.add(nppPanel);
		leftJTP.add(nppTG);

		gppTP = new PlotterMode("GPP", 0, 1000);
		JPanel gppPanel = gppTP.getPanel();
		gppPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup gppTG = new JTaskPaneGroup();
		gppTG.setSpecial(false);
		gppTG.setExpanded(true);
		gppTG.setTitle("GPP");
		gppTG.add(gppPanel);
		leftJTP.add(gppTG);

		ltrfalcTP = new PlotterMode("LTRFALC", 0, 1000);
		JPanel ltrfalcPanel = ltrfalcTP.getPanel();
		ltrfalcPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup ltrfalcTG = new JTaskPaneGroup();
		ltrfalcTG.setSpecial(false);
		ltrfalcTG.setExpanded(true);
		ltrfalcTG.setTitle("LTRFALC");
		ltrfalcTG.add(ltrfalcPanel);
		leftJTP.add(ltrfalcTG);

		innppTP = new PlotterMode("INNPP", 0, 1000);
		JPanel innppPanel = innppTP.getPanel();
		innppPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup innppTG = new JTaskPaneGroup();
		innppTG.setSpecial(false);
		innppTG.setExpanded(true);
		innppTG.setTitle("INNPP");
		innppTG.add(innppPanel);
		leftJTP.add(innppTG);
		
		JTaskPane rightJTP = new JTaskPane();

		nuptakeTP = new PlotterMode("NUPTAKE", 0, 1000);
		JPanel nuptakePanel = nuptakeTP.getPanel();
		nuptakePanel.setPreferredSize(new Dimension(330, 125));

		JTaskPaneGroup nuptakeTG = new JTaskPaneGroup();
		nuptakeTG.setSpecial(false);
		nuptakeTG.setExpanded(true);
		nuptakeTG.setTitle("NUPTAKE");
		nuptakeTG.add(nuptakePanel);
		rightJTP.add(nuptakeTG);

		netnminTP = new PlotterMode("NETNMIN", 0, 1000);
		JPanel netnminPanel = netnminTP.getPanel();
		netnminPanel.setPreferredSize(new Dimension(330, 125));

		JTaskPaneGroup netnminTG = new JTaskPaneGroup();
		netnminTG.setSpecial(false);
		netnminTG.setExpanded(true);
		netnminTG.setTitle("NETNMINE");
		netnminTG.add(netnminPanel);
		rightJTP.add(netnminTG);

		ltrfalnTP = new PlotterMode("LTRFALN", 0, 1000);
		JPanel ltrfalnPanel = ltrfalnTP.getPanel();
		ltrfalnPanel.setPreferredSize(new Dimension(330, 125));

		JTaskPaneGroup ltrfalnTG = new JTaskPaneGroup();
		ltrfalnTG.setSpecial(false);
		ltrfalnTG.setExpanded(true);
		ltrfalnTG.setTitle("LTRFALN");
		ltrfalnTG.add(ltrfalnPanel);
		rightJTP.add(ltrfalnTG);
		
		ingppTP = new PlotterMode("INGPP", 0, 1000);
		JPanel ingppPanel = ingppTP.getPanel();
		ingppPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup ingppTG = new JTaskPaneGroup();
		ingppTG.setSpecial(false);
		ingppTG.setExpanded(true);
		ingppTG.setTitle("INGPP");
		ingppTG.add(ingppPanel);
		rightJTP.add(ingppTG);

		targetPanel.add(leftJTP);
		targetPanel.add(rightJTP);

		raTP = new PlotterMode("RA", 0, 1000);
		JPanel raPanel = raTP.getPanel();
		raPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup raTG = new JTaskPaneGroup();
		raTG.setSpecial(false);
		raTG.setExpanded(true);
		raTG.setTitle("RA");
		raTG.add(raPanel);
		leftJTP.add(raTG);

		rhTP = new PlotterMode("RH", 0, 1000);
		JPanel rhPanel = rhTP.getPanel();
		rhPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup rhTG = new JTaskPaneGroup();
		rhTG.setSpecial(false);
		rhTG.setExpanded(true);
		rhTG.setTitle("RH");
		rhTG.add(rhPanel);
		rightJTP.add(rhTG);
		
		targetPanel.setPreferredSize(new Dimension(420, 900));
		return targetPanel;
	}

	private JPanel getStatePanel() {
		JPanel targetPanel = new JPanel();
		targetPanel.setLayout(new BoxLayout(targetPanel, BoxLayout.X_AXIS));

		JTaskPane leftJTP = new JTaskPane();

		vegcTP = new PlotterMode("VEGC", 0, 2000);
		JPanel vegcPanel = vegcTP.getPanel();
		vegcPanel.setPreferredSize(new Dimension(330, 125));

		JTaskPaneGroup vegcTG = new JTaskPaneGroup();
		vegcTG.setSpecial(false);
		vegcTG.setExpanded(true);
		vegcTG.setTitle("VEGC");
		vegcTG.add(vegcPanel);
		leftJTP.add(vegcTG);

		fibsoilcTP = new PlotterMode("FIBRIC", 0, 2000);
		JPanel fibsoilcPanel = fibsoilcTP.getPanel();
		fibsoilcPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup fibsoilcTG = new JTaskPaneGroup();
		fibsoilcTG.setSpecial(false);
		fibsoilcTG.setExpanded(true);
		fibsoilcTG.setTitle("FIBRIC");
		fibsoilcTG.add(fibsoilcPanel);
		leftJTP.add(fibsoilcTG);

		humsoilcTP = new PlotterMode("HUMIC", 0, 2000);
		JPanel humsoilcPanel = humsoilcTP.getPanel();
		humsoilcPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup humsoilcTG = new JTaskPaneGroup();
		humsoilcTG.setSpecial(false);
		humsoilcTG.setExpanded(true);
		humsoilcTG.setTitle("HUMIC");
		humsoilcTG.add(humsoilcPanel);
		leftJTP.add(humsoilcTG);

		minesoilcTP = new PlotterMode("MINERAL", 0, 2000);
		JPanel minesoilcPanel = minesoilcTP.getPanel();
		minesoilcPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup minesoilcTG = new JTaskPaneGroup();
		minesoilcTG.setSpecial(false);
		minesoilcTG.setExpanded(true);
		minesoilcTG.setTitle("MINERAL");
		minesoilcTG.add(minesoilcPanel);
		leftJTP.add(minesoilcTG);

		allsoilcTP = new PlotterMode("ALLSOILC", 0, 2000);
		JPanel allsoilcPanel = allsoilcTP.getPanel();
		allsoilcPanel.setPreferredSize(new Dimension(330, 125));

		JTaskPaneGroup allsoilcTG = new JTaskPaneGroup();
		allsoilcTG.setSpecial(false);
		allsoilcTG.setExpanded(true);
		allsoilcTG.setTitle("ALLSOILC");
		allsoilcTG.add(allsoilcPanel);
		leftJTP.add(allsoilcTG);		

		JTaskPane rightJTP = new JTaskPane();

		vegnTP = new PlotterMode("VEGN", 0, 2000);
		JPanel vegnPanel = vegnTP.getPanel();
		vegnPanel.setPreferredSize(new Dimension(330, 125));

		JTaskPaneGroup vegnTG = new JTaskPaneGroup();
		vegnTG.setSpecial(false);
		vegnTG.setExpanded(true);
		vegnTG.setTitle("VEGN");
		vegnTG.add(vegnPanel);
		rightJTP.add(vegnTG);

		orgnTP = new PlotterMode("ORGN", 0, 2000);
		JPanel orgnPanel = orgnTP.getPanel();
		orgnPanel.setPreferredSize(new Dimension(330, 125));

		JTaskPaneGroup orgnTG = new JTaskPaneGroup();
		orgnTG.setSpecial(false);
		orgnTG.setExpanded(true);
		orgnTG.setTitle("ORGN");
		orgnTG.add(orgnPanel);
		rightJTP.add(orgnTG);

		avlnTP = new PlotterMode("AVLN", 0, 2000);
		JPanel avlnPanel = avlnTP.getPanel();
		avlnPanel.setPreferredSize(new Dimension(330, 125));

		JTaskPaneGroup avlnTG = new JTaskPaneGroup();
		avlnTG.setSpecial(false);
		avlnTG.setExpanded(true);
		avlnTG.setTitle("AVLN");
		avlnTG.add(avlnPanel);
		rightJTP.add(avlnTG);

		laiTP = new PlotterMode("LAI", 0, 2000);
		JPanel laiPanel = laiTP.getPanel();
		laiPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup laiTG = new JTaskPaneGroup();
		laiTG.setSpecial(false);
		laiTG.setExpanded(true);
		laiTG.setTitle("LAI");
		laiTG.add(laiPanel);
		rightJTP.add(laiTG);

		fpcTP = new PlotterMode("FPC", 0, 2000);
		JPanel fpcPanel = fpcTP.getPanel();
		fpcPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup fpcTG = new JTaskPaneGroup();
		fpcTG.setSpecial(false);
		fpcTG.setExpanded(true);
		fpcTG.setTitle("FPC");
		fpcTG.add(fpcPanel);
		rightJTP.add(fpcTG);

		targetPanel.add(leftJTP);
		targetPanel.add(rightJTP);
		
		targetPanel.setPreferredSize(new Dimension(420, 900));
		return targetPanel;
	}

	private JPanel getMonthlyPanel() {
		JPanel targetPanel = new JPanel();
		targetPanel.setLayout(new BoxLayout(targetPanel, BoxLayout.X_AXIS));

		JTaskPane leftJTP = new JTaskPane();

		mgppTP = new PlotterMode("GPP", 0, 25);
		JPanel mgppPanel = mgppTP.getPanel();
		mgppPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mgppTG = new JTaskPaneGroup();
		mgppTG.setSpecial(false);
		mgppTG.setExpanded(true);
		mgppTG.setTitle("GPP");
		mgppTG.add(mgppPanel);
		leftJTP.add(mgppTG);

		mnppTP = new PlotterMode("NPP", 0, 25);
		JPanel mnppPanel = mnppTP.getPanel();
		mnppPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mnppTG = new JTaskPaneGroup();
		mnppTG.setSpecial(false);
		mnppTG.setExpanded(true);
		mnppTG.setTitle("NPP");
		mnppTG.add(mnppPanel);
		leftJTP.add(mnppTG);

		mrespTP = new PlotterMode("RESP", 0, 25);
		JPanel mrecoPanel = mrespTP.getPanel();
		mrecoPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mrecoTG = new JTaskPaneGroup();
		mrecoTG.setSpecial(false);
		mrecoTG.setExpanded(true);
		mrecoTG.setTitle("RESP");
		mrecoTG.add(mrecoPanel);
		leftJTP.add(mrecoTG);
		
		mltrfalcTP = new PlotterMode("LTRFALC", 0, 25);
		JPanel mltrfalcPanel = mltrfalcTP.getPanel();
		mltrfalcPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mltrfalcTG = new JTaskPaneGroup();
		mltrfalcTG.setSpecial(false);
		mltrfalcTG.setExpanded(true);
		mltrfalcTG.setTitle("LTRFALC");
		mltrfalcTG.add(mltrfalcPanel);
		leftJTP.add(mltrfalcTG);
				
		mltrfalnTP = new PlotterMode("LTRFALN", 0, 25);
		JPanel mltrfalnPanel = mltrfalnTP.getPanel();
		mltrfalnPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mltrfalnTG = new JTaskPaneGroup();
		mltrfalnTG.setSpecial(false);
		mltrfalnTG.setExpanded(true);
		mltrfalnTG.setTitle("LTRFALN");
		mltrfalnTG.add(mltrfalnPanel);
		leftJTP.add(mltrfalnTG);
				
		JTaskPane rightJTP = new JTaskPane();

		mlaiTP = new PlotterMode("LAI", 0, 25);
		JPanel mlaiPanel = mlaiTP.getPanel();
		mlaiPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mlaiTG = new JTaskPaneGroup();
		mlaiTG.setSpecial(false);
		mlaiTG.setExpanded(true);
		mlaiTG.setTitle("LAI");
		mlaiTG.add(mlaiPanel);
		rightJTP.add(mlaiTG);
		
		mvegcTP = new PlotterMode("VEGC", 0, 25);
		JPanel mvegcPanel = mvegcTP.getPanel();
		mvegcPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mvegcTG = new JTaskPaneGroup();
		mvegcTG.setSpecial(false);
		mvegcTG.setExpanded(true);
		mvegcTG.setTitle("VEGC");
		mvegcTG.add(mvegcPanel);
		rightJTP.add(mvegcTG);

		mvegnTP = new PlotterMode("VEGN", 0, 25);
		JPanel mvegnPanel = mvegnTP.getPanel();
		mvegnPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mvegnTG = new JTaskPaneGroup();
		mvegnTG.setSpecial(false);
		mvegnTG.setExpanded(true);
		mvegnTG.setTitle("VEGN");
		mvegnTG.add(mvegnPanel);
		rightJTP.add(mvegnTG);

		mavlnTP = new PlotterMode("AVLN", 0, 25);
		JPanel mavlnPanel = mavlnTP.getPanel();
		mavlnPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mavlnTG = new JTaskPaneGroup();
		mavlnTG.setSpecial(false);
		mavlnTG.setExpanded(true);
		mavlnTG.setTitle("AVLN");
		mavlnTG.add(mavlnPanel);
		rightJTP.add(mavlnTG);

		mnetnminTP = new PlotterMode("NETNMIN", 0, 25);
		JPanel mnetnminPanel = mnetnminTP.getPanel();
		mnetnminPanel.setPreferredSize(new Dimension(330, 125));
		JTaskPaneGroup mnetnminTG = new JTaskPaneGroup();
		mnetnminTG.setSpecial(false);
		mnetnminTG.setExpanded(true);
		mnetnminTG.setTitle("NETNMIN");
		mnetnminTG.add(mnetnminPanel);
		rightJTP.add(mnetnminTG);

		targetPanel.add(leftJTP);
		targetPanel.add(rightJTP);

		targetPanel.setPreferredSize(new Dimension(420, 900));
		return targetPanel;
	}
	
	public void reset() {
		nppTP.reset();
		gppTP.reset();
		innppTP.reset();
		ingppTP.reset();
		raTP.reset();
		rhTP.reset();
		ltrfalcTP.reset();
		ltrfalnTP.reset();
		nuptakeTP.reset();
		netnminTP.reset();
		
		vegcTP.reset();
		vegnTP.reset();
		allsoilcTP.reset();
		fibsoilcTP.reset();
		humsoilcTP.reset();
		minesoilcTP.reset();
		avlnTP.reset();
		orgnTP.reset();
		laiTP.reset();
		fpcTP.reset();
		
		mgppTP.reset();
		mnppTP.reset();
		mrespTP.reset();
		mltrfalcTP.reset();
		mltrfalnTP.reset();
		mnetnminTP.reset();
		mlaiTP.reset();
		mvegcTP.reset();
		mvegnTP.reset();
		mavlnTP.reset();
		
	}

}