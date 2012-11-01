#ifndef VEGETATION_ENV_H_
#define VEGETATION_ENV_H_
#include <cmath>
using namespace std;

#include "../lookup/CohortLookup.h"
#include "../inc/states.h"
#include "../inc/fluxes.h"
#include "../inc/diagnostics.h"
#include "../inc/parameters.h"

#include "../data/EnvData.h"
#include "../data/FirData.h"
#include "../data/RestartData.h"


class Vegetation_Env{
	  public:

		Vegetation_Env();
		~Vegetation_Env();

		bool updateLAI5Vegc;
		float envlaiall[12];
		double envlai;

		vegpar_env envpar;
	
		void setCohortLookup(CohortLookup * chtlup);
		void setEnvData(EnvData* edatap);
		void setFirData(FirData* fdp);
    
		void initializeParameter(const int & drgtypep,const int & vegtypep);
    
		void initializeState(const int & drgtypep,const int & vegtypep);

		void initializeState5restart(RestartData* resin);
     
		void updateDaily(const double & dayl);
		void updateEnvLai(const int & currmind, const double & lai);//at begin of month
  
		void beginOfMonth(const double & dayl);
   

   private:
   
		//function
		double getRainInterception(const double & rain);
		double getSnowInterception(const double & snow, const double & lai);
		double getLeafStomaCond(const double & ta, const double &  parin,
		        const double & vpdin, const double & lai, const double& btran,
		        double & m_ppfd, double & m_vpd );
		double getRadiationThrough(const double & rac, const double & lai);
		double getCanopySubl(const double & rac, const double & sinter, const double & lai );
   
		double getPenMonET(const double & ta, const double& vpd, const double &irad,
				const double &rv, const double & rh);
   
    EnvData * ed;
    FirData * fd;
	CohortLookup * chtlu;
   
};
#endif /*VEGETATION_ENV_H_*/
