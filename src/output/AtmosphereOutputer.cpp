/*! \file
*/
#include "AtmosphereOutputer.h"

AtmosphereOutputer::AtmosphereOutputer(){
	reinit();
	
}; 

void AtmosphereOutputer::reinit(){
	
};

#ifdef ODAY
	void AtmosphereOutputer::outputDayGridVars(const int & yrcnt){  // at end of execution of one grid
		//int yrcnt= outputer->getYrInd();
		tdrvGDV->put_rec(&atmod->tdrvd[0],yrcnt);
		rainGDV->put_rec(&atmod->raind[0], yrcnt);
		snowGDV->put_rec(&atmod->snowd[0], yrcnt);
		svpGDV->put_rec(&atmod->svpd[0],  yrcnt);
		dersvpGDV->put_rec(&atmod->dersvpd[0],yrcnt);
		rhoaGDV->put_rec(&atmod->rhoad[0], yrcnt);
		abshdGDV->put_rec(&atmod->abshdd[0], yrcnt);
		dsrGDV->put_rec(&atmod->dsrd[0], yrcnt);
	};

	void AtmosphereOutputer::defineDayGridVars(){
	
		daygf = siteoutputer->dayGrdFile;
		dgyearD = daygf->get_dim("year");
		dgdayD = daygf->get_dim("day");
 
  
  		tdrvGDV= daygf->add_var("TDRVGDV", ncFloat,dgyearD, dgdayD);
      	tdrvGDV->add_att("units","degC");
    	tdrvGDV->add_att("title", "Air Temperature");
    	
    	rainGDV= daygf->add_var("RAIN", ncFloat,dgyearD, dgdayD);
  	    rainGDV->add_att("units","mm/day");
    	rainGDV->add_att("title", "Rainfall");
    	
    	snowGDV= daygf->add_var("SNOW", ncFloat,dgyearD, dgdayD);
        snowGDV->add_att("units","mm/day");
    	snowGDV->add_att("title", "Snowfall");
    	dsrGDV= daygf->add_var("DSR", ncFloat,dgyearD, dgdayD);
  
    	svpGDV= daygf->add_var("SVP", ncFloat,dgyearD, dgdayD);
    	svpGDV->add_att("units","Pa");
    	svpGDV->add_att("title", "Saturated Vapor Pressure");
    	dersvpGDV= daygf->add_var("DERSVP", ncFloat,dgyearD, dgdayD);
      	svpGDV->add_att("units","Pa/degC");
    	svpGDV->add_att("title", "Derivative of SVP");
    	 
    	rhoaGDV= daygf->add_var("RHOA", ncFloat,dgyearD, dgdayD);
  	    rhoaGDV->add_att("units","kg/m3");
    	rhoaGDV->add_att("title", "Air Density");
    	 
    	abshdGDV= daygf->add_var("ABSHD", ncFloat,dgyearD, dgdayD);	
	};

#endif

//output Monthlyvars at the end of model run
void AtmosphereOutputer::outputMonthGridVars(const int & yrcnt){
     //int yrcnt =outputer->getYrInd();
	
		taGMV->put_rec(&atmod->ta[0], yrcnt);
		co2GMV->put_rec(&atmod->co2[0],yrcnt);
		cldsGMV->put_rec(&atmod->clds[0], yrcnt);
		eetGMV->put_rec(&atmod->eet[0],yrcnt);
		petGMV->put_rec(&atmod->pet[0], yrcnt);
		rnflGMV->put_rec(&atmod->rnfl[0], yrcnt);
		snflGMV->put_rec(&atmod->snfl[0], yrcnt);
		girrGMV->put_rec(&atmod->girr[0], yrcnt);
		nirrGMV->put_rec(&atmod->nirr[0], yrcnt);
		parGMV->put_rec(&atmod->par[0],yrcnt);
};

void AtmosphereOutputer::defineMonthGridVars(){
		mongf = siteoutputer->monGrdFile;    	 
		mgyearD = mongf->get_dim("year");
		mgmonD = mongf->get_dim("month");
  
		eetGMV = mongf->add_var("EET", ncFloat, mgyearD, mgmonD);   	
		eetGMV->add_att("units","mm/day");
		eetGMV->add_att("title", "Actual Evapotranspiration");
    	 
		petGMV = mongf->add_var("PET", ncFloat, mgyearD, mgmonD);  
		petGMV->add_att("units","mm/day");
		petGMV->add_att("title", "Potential Evapotranspiration");
    
		co2GMV = mongf->add_var("CO2", ncFloat, mgyearD, mgmonD);
		co2GMV->add_att("units","ppmv");
		co2GMV->add_att("title", "CO2 Concentration");
    
		taGMV = mongf->add_var("TA", ncFloat, mgyearD, mgmonD);
		taGMV->add_att("units","degC");
		taGMV->add_att("title", "Air Temperature");
    
		rnflGMV = mongf->add_var("RNFL", ncFloat, mgyearD, mgmonD);
		rnflGMV->add_att("units","mm");
		rnflGMV->add_att("title", "Snowfall");
		snflGMV = mongf->add_var("SNFL", ncFloat, mgyearD, mgmonD);
        snflGMV->add_att("units","mm");
    	snflGMV->add_att("title", "Snowfall");
    	
    	nirrGMV = mongf->add_var("NIRR", ncFloat, mgyearD, mgmonD);
        nirrGMV->add_att("units","W/m2");
    	nirrGMV->add_att("title", "Incident Solar Raidation at Surface");
    	
    	girrGMV = mongf->add_var("GIRR", ncFloat, mgyearD, mgmonD);
        girrGMV->add_att("units","W/m2");
    	girrGMV->add_att("title", "GIRR");
    	
    	parGMV = mongf->add_var("PAR", ncFloat, mgyearD, mgmonD);
        parGMV->add_att("units","W/m2");
    	parGMV->add_att("title", "Photosynthetic Active Raditaion");
    	
    	cldsGMV = mongf->add_var("CLDS", ncFloat, mgyearD, mgmonD);
        cldsGMV->add_att("units","percent");
    	cldsGMV->add_att("title", "Cloud Fraction");
};

void AtmosphereOutputer::outputYearGridVars(const int & yrcnt){
   
		rnflGYV->put_rec(&atmod->yrrnfl, yrcnt);
		snflGYV->put_rec(&atmod->yrsnfl,yrcnt);
		taGYV->put_rec(&atmod->yrta,yrcnt);
		
};

void AtmosphereOutputer::defineYearGridVars(){
		yrgf = siteoutputer->yrGrdFile;    	 
		ygyearD = yrgf->get_dim("year");
		rnflGYV = yrgf->add_var("RNFL", ncFloat, ygyearD);
		snflGYV = yrgf->add_var("SNFL", ncFloat, ygyearD);
		taGYV = yrgf->add_var("TA", ncFloat, ygyearD);
};

void AtmosphereOutputer::setOutputer(SiteOutputer * outputerp){
	siteoutputer = outputerp;
	
	// define output var after the outputer pointing
	#ifdef ODAY
		defineDayGridVars();
	#endif
	
	if(OMONTH){
		defineMonthGridVars();
	}
	
	if(OYEAR){
		defineYearGridVars();
	}
	
};

void AtmosphereOutputer::setOutdata( AtmOutData* outdata){
	atmod = outdata;
};	



