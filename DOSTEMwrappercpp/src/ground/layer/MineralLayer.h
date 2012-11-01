/*! \file
 * 
 */
#ifndef MINERALLAYER_H_
#define MINERALLAYER_H_
#include "SoilLayer.h"
#include "../../inc/PhysicalConstants.h"

#include <string>
#include <cmath>
using namespace std;

class MineralLayer: public SoilLayer{
	public:

	MineralLayer(const double & pdz, int sttype , SoilLookup * soillup);


    void  updateProperty5Lookup();
    double getDryThermCond(const double & bulkden);
    double getDryThermCond(const double & tcsolid, const double & bulkden, const double & partden);
    virtual bool isMoss();
    virtual bool isMineral();
	virtual bool isPeat();
};
#endif /*MINERALLAYER_H_*/
