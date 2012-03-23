/*! \file
 * 
 */
#ifndef PEATLAYER_H_
#define PEATLAYER_H_
#include "SoilLayer.h"
#include "../../inc/PhysicalConstants.h"

#include <string>
#include <cmath>
using namespace std;

class PeatLayer: public SoilLayer {
 public:

 	PeatLayer(const double & pdz, const int & upper);

    bool isFibric;
    bool isHumic;
    void humify();
    void fireConvert(SoilLayer* sl);
    virtual bool isMoss();
    virtual bool isMineral();
 	virtual bool isPeat();
    
};
#endif /*PEATLAYER_H_*/
