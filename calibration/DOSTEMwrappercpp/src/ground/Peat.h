/*! \file
 */
#ifndef PEAT_H_
#define PEAT_H_
 
#include "iostream"
using namespace std;
#include "../inc/layerconst.h"

class Peat{
	public:
		Peat();
		~Peat();
	
	/*! number of peat layers*/
		int shlwnum;
		double shlwthick;
	
		double shlworgc;
		double extrashlworgc;
		double extrashlwthick;
	
		int deepnum;
		double deepthick;
		double deeporgc;
		double extradeeporgc;
		double extradeepthick;

		double oldshlwthick;
		double olddeepthick;
		double dlstshlw;
		double olddlstshlw;
		bool shlwchanged;
	
		double shlwdza[MAX_SLW_LAY];
		double deepdza[MAX_DEP_LAY];
	
		bool sameShlwThickRange(const double & thickness);
		bool sameDeepThickRange(const double & thickness);
	
		void initShlwThicknesses(const double & thickness);
		void initDeepThicknesses(const double & thickness);
	
		void updateShlwThicknesses(int type[], double dz[],const int & maxnum);
		void updateDeepThicknesses(int type[], double dz[],const int & maxnum);
	
	
};
#endif /*PEAT_H_*/
