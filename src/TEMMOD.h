/**
 * Definition of TEM run mode and output options
 * 
 * for extrarun and siterun, need first spinnup and than transient run
 * for siterun and calibrun, only one point is used, and usually use one process, 
 * can output diagnostic message to monitor
 * for extrarun, for mulitiple regions, output is simpler
 *  
*/

#ifndef TEMMOD_H_
	#define TEMMOD_H_
	
	// defines the mode of run: Singe-site or Multiple-site (regional)

//	#define SITERUN
	#define REGNRUN

	//the output time-step option(s) for SITE-RUN
	#ifdef SITERUN
		const bool SITEMODE=true;
		const bool REGNMODE=false;
		
		const bool OMONTH=true;
		const bool OYEAR=true;
		//#define ODAY   //daily output if needed

		const bool OSOILCLM=false; //for output soil climate driver
	#endif

	//the output time-step option(s) for REGN-RUN
	#ifdef REGNRUN
		const bool SITEMODE=false;
		const bool REGNMODE=true;

		const bool OMONTH=false;   //this switch for SITE-RUN only, so set to false here
		const bool OYEAR=false;   //this switch for SITE-RUN only, so set to false here

		const bool OSOILCLM=false;

	#endif

#endif /*TEMMOD_H_*/
