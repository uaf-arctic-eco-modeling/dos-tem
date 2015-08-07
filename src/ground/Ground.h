/*! \file
 * Ground is used to manipulate the structure of 
 * snow and soil layers
 */
#ifndef GROUND_H_
#define GROUND_H_

#include <sstream>
 
#include <cmath>
#include <iostream>
using namespace std;

#include "DoubleLinkedList.h"

#include "layer/Layer.h"
#include "layer/MossLayer.h"
#include "layer/SnowLayer.h"
#include "layer/MineralLayer.h"
#include "layer/PeatLayer.h"
#include "layer/RockLayer.h"

#include "Snow_Env.h" 
#include "Soil_Env.h"
#include "Rock.h"
#include "../util/Exception.h"
#include "../lookup/SoilLookup.h"

#include "../data/EnvData.h"
#include "../data/FirData.h"
#include "../data/BgcData.h"

#include "../data/RestartData.h"

class Ground: public DoubleLinkedList {

	public :
      	Ground();
      	~Ground();
	  	int updateDaily(const int & yrcnt, const int & year,
		const int & mind, const int & id, const double & tdrv, const double & dayl);
  		//    void updateMonthlyEnviron(const int & yrcnt,const int & year, const int & month, const int & dinmcurr);

		//bool updateDailySoilEnv;
  
		void burnOrganic(const double & intense);

		void checkSnowBlwSoil();
		void checkSnowLayers();

		void initializeLayerStructure();
		int initializeLayerStructure5restart(RestartData * resin);
		//void setOutputer(SnowSoilOutputer * out);

		/* pointers to other components*/
		void setCohortData(const int & drgtype, const int & vegtype);
 
		Soil_Env soil;
		Snow_Env snow;
		Rock rock;

		void setEnvData(EnvData* edp);
		void setFirData(FirData* fdp);
    
		double getSoilTransFactor();    

		void  adjustLayerThickness(const int & yrcnt, const double & mossthick );

		 /*! first soil node */
 		Layer * fstsoill;
 		/*! first snow/soil layer containing phase change plane */
 		Layer * fstfntl;
  		/*! last snow/soil layer containing phase change plane */
 		Layer * lstfntl;
 		/*! first mineral layer*/
 		Layer *fstminl;
 		/*! last mineral layer*/
 		Layer *lstminl;
 		/*! layer used to determine wether use richard equations*/
 		Layer* richardl;
		/*! layer used to determine the subsurface drainage*/
 		Layer* drainl;

		/*! fst and lst shlw layer*/
		Layer* fstshlwl;
		Layer* lstshlwl;
		Layer* fstdeepl;
		Layer* lstdeepl;

   		void burn(const int & yrcnt, const bool & dslmodule);
   		void updateLayer5FireGrowth();
   
	private :
		/*! the maximum dt can be used to run Goodgrich algorithm
 		* unit is day*/
		double dtmax;
		int drgtype;
 		int vegtype;
 
 		// thermal state of soil column, 0: part frozen, 1: totally frozen,, -1: totally unfrozen
 		int tstate;
 
  		/*! whether in growing season, based on thaw position (10 cm)*/
 		int grow;
 
 		/*! the year count: 0, 1, 2, 3*/
 		int curyrcnt ;
 		/*! the current year: 1990, 1991, ..., */
 		int curyear;

		double  meltSnowLayers();
		bool constructSnowLayers(const double & tdrv);
		bool divideSnowLayers();
		bool combineSnowLayers();

		void updateSnowLayerZ();
		void updateSoilLayerZ();
		void updateLayerIndex();
		void updateLayStruct4Disturb();

		void resetLayerIndex();
		void resetSnowLayerIndex();
		void setLayer5Depth();
		void setFstLstShlwLayers();
		void setFstLstDeepLayers();

		void updateFstLstFntLay(); //update fstfntl, lstfntl
		void updateThermState(); //update tstate
 
		void checkTemperatures();

		void updateSWE();

		void updateClayLayers();
		void updateSandLayers();
		void updateSiltLayers();
		void updateAllLayers(); 

		void setFstLstMineLayers();
		void setFstSoilLayer();

		void updateMossThickness(const double & mossthick);
		void updateShlwThickness();
		void updateDeepThickness();

		void divideOneSoilLayerU2L(SoilLayer*usl, SoilLayer* lsl,const double & updz, const double & tempdz);
		void combineTwoSoilLayersU2L(SoilLayer* usl, SoilLayer* lsl);
		void combineTwoSoilLayersL2U(SoilLayer* lsl, SoilLayer* usl);

		/*! update the snow and soil temperatures, phase-change plane position
		 * \arg \c dt time step */
		void updateDailyPrognostic( const double & dt, const int& year, const int& ihd, const double & tdrv, const int & mind);
		
//		SoilLookup  soillu;

		void updateSoilDiagnostics();

		bool rocklayercreated;

		void clean();

		EnvData * ed;
		FirData * fd;

		void cleanSnowSoilLayers();

		/*! initialize the snow and soil structure using input data */
		void initSnowSoilLayers5Thickness();
		void initSnowSoilLayers5Restart(RestartData * resin);
		void initRockLayers();

};

#endif /*GROUND_H_*/
