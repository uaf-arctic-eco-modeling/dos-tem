package GUI;

import info.monitorenter.gui.chart.*;
import info.monitorenter.gui.chart.traces.Trace2DLtd;

import info.monitorenter.gui.chart.io.ADataCollector;
import info.monitorenter.gui.chart.Chart2D;
import info.monitorenter.gui.chart.ITrace2D;

import java.awt.*;
import javax.swing.JPanel;

public class PlotterMode {
	
	Chart2D chart;
	String name;
	double target;
	ITrace2D trace0;
	ITrace2D trace1;
	
	ADataCollector collector;

	public PlotterMode(String name, double target, int points){
		this.name = name;
		this.target = target;
		
		 chart = new Chart2D();
		 trace0 = new Trace2DLtd(points,"target/Zero");
		 trace0.setColor(Color.BLUE);
		 chart.addTrace(trace0);

		 trace1 = new Trace2DLtd(points, name);
		 trace1.setColor(Color.RED);
		 chart.addTrace(trace1);
		         
	}
	
	public void reset(){		
		trace0.removeAllPoints();
		trace1.removeAllPoints();
	}
	
	public void setTargetValue(double t){
		target = t;	
	}
	
	public JPanel getPanel(){
		JPanel content = new JPanel(new BorderLayout());          
        content.add(chart);
		return content;
	}
		
	public void addPoint(double  x, double y){
		TracePoint2D point0 = new TracePoint2D(x, target);
		trace0.addPoint(point0);

		TracePoint2D point1 = new TracePoint2D(x, y);
		trace1.addPoint(point1);
				
	}	 

}