/*! \file
 * 
 */
#ifndef ROCKLAYER_H_
#define ROCKLAYER_H_
#include "Layer.h"

#include "../../inc/PhysicalConstants.h"

#include <string>
#include <cmath>
using namespace std;

class RockLayer:public Layer{
	public:

		RockLayer(const double & thick);
		~RockLayer();
		
		double tcsolid;   /*! solid thermal conductivity W/mK*/
		double vhcsolid;  /*! solid volumetric heat capacity*/
		double tcsatfrz;  /*! saturated frozen soil thermal conductivity*/
		double tcsatunf;  /*! saturated unfrozen soil thermal conductivity*/
		
		virtual bool isSnow();
		virtual bool isSoil();
		virtual bool isRock();

		virtual double getFrzThermCond();// get frozen layer thermal conductivity
		virtual double getUnfThermCond();// get unfrozen layer thermal conductivity
		virtual double getFrzVolHeatCapa();// get frozen layer specific heat capcity
		virtual double getUnfVolHeatCapa();// get unfrozen layer specific heat capacity
		virtual double getMixVolHeatCapa();// get blended layer specific heat capacity
		virtual double getAlbedoVis();// get albedo of visible radition
		virtual double getAlbedoNir();// get albedo of Nir radition
     
		void updateProperty();
    
};
#endif /*ROCKLAYER_H_*/
