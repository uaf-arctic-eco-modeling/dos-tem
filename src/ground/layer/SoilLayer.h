/*! \file
 * 
 */
#ifndef SOILLAYER_H_
#define SOILLAYER_H_
#include "Layer.h"


#include "../../inc/PhysicalConstants.h"

#include <math.h>
#include <cmath>
#include <deque>
#include <vector>
#include <memory>
using namespace std;

#include "../../lookup/SoilLookup.h"
#include "Front.h"
#include "../../util/Exception.h"

class SoilLayer:public Layer{
	public:
	
		/*! the texture class is from ATBeringer52001a*/
	enum STKEY {I_SAND, I_LOAMY_SAND, I_SANDY_LOAM, 
		         I_LOAM, I_SILTY_LOAM, I_SANDY_CLAY_LOAM, I_CLAY_LOAM, 
		         I_SILTY_CLAY_LOAM, I_SANDY_CLAY, I_SILTY_CLAY, I_CLAY};
		
	virtual ~SoilLayer();	         
		SoilLayer();
		/*! thermal state:
		 * -1 : frozen
		 * 0: undetermined, with freezing/thawing front(s)
		 * 1: unfrozen */
		bool tstate ;
        
       
		
	    STKEY stkey; // texture key
		/*! saturated matric potential*/
		double psisat; 
		/*! saturated matric potential*/
		double hksat;
		/*! Clap and Hornberger consant*/
		double bsw;
		
		/*! dry matter thermal conductivity W/mK*/
		double tcdry;
		
		/*! solid thermal conductivity W/mK*/
		double tcsolid;
		
		/*! solid volumetric heat capacity*/
		double vhcsolid;
		
		double cfrac; //fraction of carbon
		
		double nfrac; //fraction of nitrogen
		/*! saturated frozen soil thermal conductivity*/
		double tcsatfrz;
		
		/*! saturated unfrozen soil thermal conductivity*/
		double tcsatunf;
		
		//albedo
		double  albdryvis;
		double  albdrynir;
		double  albsatvis;
		double  albsatnir;
		
		//field capacity
		double fldcap;
		
		//wilting point;
		double wltpnt;
		
		/*! particle density*/
		double prtlden;
		
		/*! fraction of root mass in this layer, relative to total root*/
		double rootfrac;
		
		/*! soil carbon pool unit : \f$\frac{kgC}{m^2} \f$ */
		double reac;
		
		double nonc; //non reactive c

    void clean();//used to release memory of front
	void updateProperty4LayerChange();
		
	virtual bool isSnow();
    virtual bool isSoil(); 		
    virtual bool isRock(); 	
    
    
    virtual bool isMoss()=0;
    virtual bool isMineral()=0;
    virtual bool isPeat()=0;
   
 
    bool fromFire; // converted from fire
        
    void updateWater5Front();
     
     void combineFronts();
       
    double getFrzPoint();

    void adjustTem5State();
    
    double getUnfrzColumn();
    
    deque<Front*> fronts;

    void addOneFront5Top(const double & deltaz,const int & frzing);
     void addOneFront5Top4restart(const double & deltaz,const int & frzing);
     	
    void addOneFront5Bot(const double & deltaz,const int & frzing);
    void moveOneFrontDown(const double & partd, const int & fntind);
    void moveOneFrontUp(const double & partd, const int & fntind);
    void removeAllFronts(const int & frzing);
    void removeTopFront();
    void removeBotFront();
    
    
    // get frozen layer thermal conductivity
	   virtual double getFrzThermCond();
	// get unfrozen layer thermal conductivity
	   virtual double getUnfThermCond();
	// get frozen layer specific heat capcity
	   virtual double getFrzVolHeatCapa();
	// get unfrozen layer specific heat capacity
	   virtual double getUnfVolHeatCapa();

	   virtual double getMixVolHeatCapa();   //Yuan: all soil components
	   
	     // get albedo of visible radition
     virtual double getAlbedoVis();
    // get albedo of Nir radition
     virtual double getAlbedoNir();

    
    double getMatricPotential();
    
    double getHydraulicCond1();
    
    double getUnfWatFactor(const double & t);
    
    void deriveProperty();
    	
    double getFrozenFraction();
    
     	
    SoilLookup* soillu;
    
    void checkFronts();
    
    void adjustFronts();
    double getDryThermCond(const double & tcsolid, const double & bulkden, const double & partden);
};
#endif /*SOILLAYER_H_*/
