/*! \file
 * Superclass for SoilLayer and SnowLayer
 */
#ifndef LAYER_H_
#define LAYER_H_

#include<string>
#include <iostream>
//#include "../inoutput/Logger.h"
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

#include "../../inc/PhysicalConstants.h"

class Layer {
	public:
	 Layer();
	 virtual ~Layer();
	 enum typekey {I_LAY, I_SOIL, I_SNOW, I_MOSS, I_PEAT, I_MINE, I_ROCK};
	 
	 /*! thickness of layer (unit : \f$ m \f$)*/
	 double dz;
	 /*! distance to the ground surface 
	  * <ol>
	  * <li>+ means below surface, for soil layer
	  * <li>- means above surface, for snow layer
	  * </ol>
	  */
	  double z;
	 /*! density of this layer (unit : \f$ kg m^{-3} \f$)*/
	 double rho;
	 
	  
    /*! point to next layer */
	Layer* nextl;
	/*! point to previous layer */
	Layer* prevl;

    /*! layer index, start from 1 */
    int indl;
    
    /*! soil layer index, start from 1*/
    int solind;

    /*! thermal state of soil, 0: undetermined, 1: frozen, -1: unfrozen*/
    int frozen;
    
    /*! age of a layer (year)*/
    double age;
    
   
    void check();
    
    double minliq; // minimum liq water content//kg/m2
    
    double maxliq; // maximum liq water content
    
    double maxice; // maximum ice content
    
    double tcmin; // minimum thermal conductivity, to consider the effect of air and water convection
    /* color of layer*/
    int color;


    void advanceOneDay();

   // virtual void updateDensity()=0;

     double getHeatCapacity();

     double getThermalConductivity();

 
    virtual bool isSnow()=0;
    virtual bool isSoil()=0; 
    virtual bool isRock()=0; 
    
    void addOneMoreFront(const double & deltaz,const int & frzing);
    void addOneMoreFront5Bot(const double & deltaz,const int & frzing);
    void removeAllFronts(const int & frzing);
    void moveFrontDown(const double & partd, const int & fntind);
    void moveFrontUp(const double & partd, const int & fntind);

/// variables 	
	/*! temperature, Note: here the temperature of one layer
	 * means the temperature at the bottom of one layer.
	 * This definition is for Goodrich method */
	double tem;

	   	
	// get frozen layer thermal conductivity
	   virtual double getFrzThermCond()=0;
	// get unfrozen layer thermal conductivity
	   virtual double getUnfThermCond()=0;
	// get frozen layer specific heat capcity
	   virtual double getFrzVolHeatCapa()=0;
	// get unfrozen layer specific heat capacity
	   virtual double getUnfVolHeatCapa()=0;
	   virtual double getMixVolHeatCapa()=0;   //Yuan
    // get albedo of visible radition
       virtual double getAlbedoVis()=0;
    // get albedo of Nir radition
       virtual double getAlbedoNir()=0;
	/*!liquid water kg/m2*/
	double liq;
	/*!ice content kg/m2*/
	double ice;
	
	/*! total water conent*/
	double wat;
	
	/*! porosity*/
	double poro;
	
	/*! bulk density: the kg solid/ volume of whole layer*/
	double bulkden;
	
	/*!bulk density /density of water*/
	double dbdw;
	

	

	//double mass; //the mass of a layer
	/*! the name of class for the distinction between moss, peat and mineral soil layer*/
	typekey tkey;

	void printFrontsInfo();
	
	//void logLayerInfo(Logger * logger);
	
	int checkFrontsValidity();
	
	void updateNumberOfFronts(int & numfrz, int & numthw);
	
	/*!get volumetric soil water content*/
	double getVolWater();
	 
	double getVolLiq();
	
	double getVolIce();
	
	double getEffVolWater();
	
	//Yuan:
	double tcond;
	double hcond;
	
};
#endif /*LAYER_H_*/
