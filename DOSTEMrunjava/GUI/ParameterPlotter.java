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

public class ParameterPlotter {

	static JFrame f;

	// parameter
	public PlotterMode cmaxTP;
	public PlotterMode nmaxTP;
	public PlotterMode krbTP;

	public PlotterMode cfallTP;
	public PlotterMode nfallTP;

	public PlotterMode kdcfibTP;
	public PlotterMode kdchumTP;
	public PlotterMode kdcminfastTP;
	public PlotterMode kdcminslowTP;
	public PlotterMode nupTP;

	public ParameterPlotter() {

		f = new JFrame("Parameter Monitor");

		f.setLayout(new BorderLayout());

		try {

			f.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

			JTabbedPane tp = new JTabbedPane();

			JPanel parapanel = getParameterPanel();

			tp.add("Parameter", parapanel);

			f.add(tp, BorderLayout.CENTER);

			f.setLocation(500, 1);
		} catch (Exception x) {

		}

		f.setSize(400, 400);
		f.setVisible(true);

		f.setSize(930, 850);
		f.setVisible(true);

	}

	private JPanel getParameterPanel() {
		JPanel targetPanel = new JPanel();
		targetPanel.setLayout(new BoxLayout(targetPanel, BoxLayout.X_AXIS));

		JTaskPane leftJTP = new JTaskPane();

		cmaxTP = new PlotterMode("CMAX", 0, 2000);
		JPanel cmaxPanel = cmaxTP.getPanel();
		cmaxPanel.setPreferredSize(new Dimension(420, 130));

		JTaskPaneGroup cmaxTG = new JTaskPaneGroup();
		cmaxTG.setSpecial(false);
		cmaxTG.setExpanded(true);
		cmaxTG.setTitle("CMAX");
		cmaxTG.add(cmaxPanel);
		leftJTP.add(cmaxTG);

		cfallTP = new PlotterMode("CFALL", 0, 2000);
		JPanel cfallPanel = cfallTP.getPanel();
		cfallPanel.setPreferredSize(new Dimension(420, 130));
		JTaskPaneGroup cfallTG = new JTaskPaneGroup();
		cfallTG.setSpecial(false);
		cfallTG.setExpanded(true);
		cfallTG.setTitle("CFALL");
		cfallTG.add(cfallPanel);
		leftJTP.add(cfallTG);

		krbTP = new PlotterMode("KRB", 0, 2000);
		JPanel krbPanel = krbTP.getPanel();
		krbPanel.setPreferredSize(new Dimension(420, 130));
		JTaskPaneGroup krbTG = new JTaskPaneGroup();
		krbTG.setSpecial(false);
		krbTG.setExpanded(true);
		krbTG.setTitle("KRB");
		krbTG.add(krbPanel);
		leftJTP.add(krbTG);

		kdcfibTP = new PlotterMode("KDCFIB", 0, 2000);
		JPanel kdcfibPanel = kdcfibTP.getPanel();
		kdcfibPanel.setPreferredSize(new Dimension(420, 130));
		JTaskPaneGroup kdcfibTG = new JTaskPaneGroup();
		kdcfibTG.setSpecial(false);
		kdcfibTG.setExpanded(true);
		kdcfibTG.setTitle("KDCFIB");
		kdcfibTG.add(kdcfibPanel);
		leftJTP.add(kdcfibTG);
		
		kdchumTP = new PlotterMode("KDCHUM", 0, 2000);
		JPanel kdchumPanel = kdchumTP.getPanel();
		kdchumPanel.setPreferredSize(new Dimension(420, 130));
		JTaskPaneGroup kdchumTG = new JTaskPaneGroup();
		kdchumTG.setSpecial(false);
		kdchumTG.setExpanded(true);
		kdchumTG.setTitle("KDCHUM");
		kdchumTG.add(kdchumPanel);
		leftJTP.add(kdchumTG);
		
		
		kdcminfastTP = new PlotterMode("KDCMINFAST", 0, 2000);
		JPanel kdcminfastPanel = kdcminfastTP.getPanel();
		kdcminfastPanel.setPreferredSize(new Dimension(420, 130));
		JTaskPaneGroup kdcminfastTG = new JTaskPaneGroup();
		kdcminfastTG.setSpecial(false);
		kdcminfastTG.setExpanded(true);
		kdcminfastTG.setTitle("KDCMINFAST");
		kdcminfastTG.add(kdcminfastPanel);
		leftJTP.add(kdcminfastTG);
		
		
		kdcminslowTP = new PlotterMode("KDCMINSLOW", 0, 2000);
		JPanel kdcminslowPanel = kdcminslowTP.getPanel();
		kdcminslowPanel.setPreferredSize(new Dimension(420, 130));
		JTaskPaneGroup kdcminslowTG = new JTaskPaneGroup();
		kdcminslowTG.setSpecial(false);
		kdcminslowTG.setExpanded(true);
		kdcminslowTG.setTitle("KDCMINSLOW");
		kdcminslowTG.add(kdcminslowPanel);
		leftJTP.add(kdcminslowTG);

		JTaskPane rightJTP = new JTaskPane();

		nmaxTP = new PlotterMode("NMAX", 0, 2000);
		JPanel nmaxPanel = nmaxTP.getPanel();
		nmaxPanel.setPreferredSize(new Dimension(420, 130));

		JTaskPaneGroup nmaxTG = new JTaskPaneGroup();
		nmaxTG.setSpecial(false);
		nmaxTG.setExpanded(true);
		nmaxTG.setTitle("NMAX");
		nmaxTG.add(nmaxPanel);
		rightJTP.add(nmaxTG);
		
		nfallTP = new PlotterMode("NFALL", 0, 2000);
		JPanel nfallPanel = nfallTP.getPanel();
		nfallPanel.setPreferredSize(new Dimension(420, 130));

		JTaskPaneGroup nfallTG = new JTaskPaneGroup();
		nfallTG.setSpecial(false);
		nfallTG.setExpanded(true);
		nfallTG.setTitle("NFALL");
		nfallTG.add(nfallPanel);
		rightJTP.add(nfallTG);

		nupTP = new PlotterMode("NUP", 0, 2000);
		JPanel nupPanel = nupTP.getPanel();
		nupPanel.setPreferredSize(new Dimension(420, 130));

		JTaskPaneGroup nupTG = new JTaskPaneGroup();
		nupTG.setSpecial(false);
		nupTG.setExpanded(true);
		nupTG.setTitle("NUP");
		nupTG.add(nupPanel);
		rightJTP.add(nupTG);

		targetPanel.add(leftJTP);
		targetPanel.add(rightJTP);

		targetPanel.setPreferredSize(new Dimension(420, 900));
		return targetPanel;
	}
	
	public void reset() {
		
		cmaxTP.reset();
		nmaxTP.reset();
		krbTP.reset();

		cfallTP.reset();
		nfallTP.reset();
		
		kdcfibTP.reset();
		kdchumTP.reset();
		kdcminfastTP.reset();
		kdcminslowTP.reset();
		
		nupTP.reset();
		
	}

}