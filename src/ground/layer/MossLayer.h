/*! \file
 * can photosynthesize
 */
#ifndef MOSSLAYER_H_
#define MOSSLAYER_H_
#include "SoilLayer.h"
#include "../../inc/PhysicalConstants.h"

#include <string>
#include <cmath>
using namespace std;
class MossLayer: public SoilLayer{
	public:
	 MossLayer(const double &pdz, const int & sphagnum);
	 
	 /*fraction of live moss*/
	 double fraclive;

    int sphagnum;  //=1 sphagnum, 0= feathermoss
    virtual bool isMoss();
    virtual bool isMineral();
    virtual bool isPeat();
    
   
};
#endif /*MOSSLAYER_H_*/
