/*! \file
 */
 
#ifndef ATMOSPHEREOUTPUTER_H_
#define ATMOSPHEREOUTPUTER_H_

#include "netcdfcpp.h"
#include "ncvalues.h"

#include "SiteOutputer.h"
#include "../run/AtmOutData.h"
#include "../inc/timeconst.h"

class AtmosphereOutputer {
	public:

		AtmosphereOutputer();
	 
		#ifdef ODAY
// for grid
			void outputDayGridVars(const int & yrcnt);
			void defineDayGridVars();

			NcFile * daygf;	
			NcVar* tdrvGDV;
			NcVar* rainGDV;
			NcVar* snowGDV;
			NcVar* svpGDV;
			NcVar* dersvpGDV;
			NcVar* rhoaGDV;
			NcVar* dsrGDV;
			NcVar* abshdGDV;
	
	// for daily
			NcDim * dgdayD;
			NcDim * dgyearD;
			NcDim * dggrdD;	
		 
		#endif
	 
// monthly outputs
			void outputMonthGridVars(const int & yrcnt);
			void defineMonthGridVars();
	  
			NcFile * mongf;
		// for monthly	
			NcDim * mggrdD;
			NcDim * mgmonD;
			NcDim * mgyearD;
			NcVar * taGMV;
			NcVar * co2GMV;
			NcVar * cldsGMV;
			NcVar * eetGMV;
			NcVar * petGMV;
			NcVar * snflGMV;
			NcVar * rnflGMV;
			NcVar * girrGMV;
			NcVar * nirrGMV;
			NcVar * parGMV;
	
//yearly outputs
			void outputYearGridVars(const int & yrcnt);
			void defineYearGridVars();
	  	
			NcFile * yrgf;
	
			NcDim * yggrdD;
			NcDim * ygyearD;
	
			NcVar * rnflGYV;
			NcVar * snflGYV;
			NcVar* taGYV;

	 
		void setOutputer(SiteOutputer * outputer);
	 	void setOutdata(AtmOutData * outdata);
	 	AtmOutData * atmod;
	 	SiteOutputer * siteoutputer;
	 	
	 private:
		 int daycnt;
		 void reinit();
	};
#endif /*ATMOSPHEREOUTPUTER_H_*/
