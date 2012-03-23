/*! \file
 *
 */
#ifndef SNOWLAYER_H_
#define SNOWLAYER_H_
#include "Layer.h"
#include "../../inc/PhysicalConstants.h"

#include <string>
#include <cmath>
using namespace std;

class SnowLayer: public Layer{
	public:
	SnowLayer();
	~SnowLayer();
	
    virtual bool isSnow();
    virtual bool isSoil(); 	
    virtual bool isRock(); 	
        
    /*assign same member to another layer*/
    void clone(SnowLayer* sl);
 //   int ctype;// cohort type
    double newden;
    
    double albmin; // minimum snow albedo
    double albmax; // maximum snow albedo
    
    /*! the maximum density of snow, this is region specific*/
    double denmax;
    void updateThick();
    void updateDensity();
    
    void check();
    // get albedo of visible radition
    virtual double getAlbedoVis();
    // get albedo of Nir radition
    virtual double getAlbedoNir();
     
    // get frozen layer thermal conductivity
	   virtual double getFrzThermCond();
	// get unfrozen layer thermal conductivity
	   virtual double getUnfThermCond();
	// get frozen layer specific heat capcity
	   virtual double getFrzVolHeatCapa();
	// get unfrozen layer specific heat capacity
	   virtual double getUnfVolHeatCapa();

	   virtual double getMixVolHeatCapa();  //Yuan:

	private:
	   double getThermCond5Sturm();
	   double getThermCond5Jordan();
	    
};
#endif /*SNOWLAYER_H_*/
