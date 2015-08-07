/*! \file
 */
#ifndef MINERAL_H_
#define MINERAL_H_
 
#include <iostream>
#include "../inc/layerconst.h"
using namespace std;

class Mineral{
	public:
	Mineral();
	/*! number of mineral layer*/
	int num;
  
	double dza[MAX_MIN_LAY]; // there are maximum 2 layers
 
 	int clay[MAX_MIN_LAY]; // there are maximum 2 layers
 	int sand[MAX_MIN_LAY]; // there are maximum 2 layers
 	int silt[MAX_MIN_LAY]; // there are maximum 2 layers
   
	double thick;

	void initThicknesses(const double & thickness);
	void updateThicknesses(int type[], double dz[],const int & maxnum);
	
	void updateClay(int clays[], const int & numtype);
	void updateSand(int sands[], const int & numtype);
	void updateSilt(int silts[], const int & numtype);
	
};
#endif /*MINERAL_H_*/
