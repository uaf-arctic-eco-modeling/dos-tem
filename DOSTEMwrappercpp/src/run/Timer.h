#ifndef TIMER_H_
#define TIMER_H_
/*! \file
 * Time Related Class for TEM
 */

#include <iostream>
using namespace std;

#include "../inc/timeconst.h"

class Timer{
	public:
		Timer();
		~Timer();

		static int dinm[MINY];
		static int doyindfst[MINY];

		bool spinfinished ; // finished spinup
		
	 	int yearind;
		int monind;

		int maxeqrunyrs;		/*! number of spin years*/

		int spinbegyr;		/*! beginning year of spinup*/
		int spinendyr;		/*! end year of spin up*/
		int spinnumyr;      /*! number of spin years*/

		int trsbegyr;
		int trsendyr;
		int trsnumyr;
				
		int scbegyr;		/*! beginning year of scenrio simulation*/
		int scendyr;		/*! end year of scenrio simulation*/
		int scnumyr;		/*! number of scenrio simulation year*/
		
		int outbegyr;		/*! start of output year */
		int outendyr;		/*! end of output year*/
		int dlyinterval ;   /*! output interval (year) for daily time step simulation*/
		
		int numrunyr;		/*! actual number of years that TEM has run*/

		int getInputYearIndex(bool & equiled, bool &spined);
		int getOutputYearIndex(bool & equiled, bool &spined, bool & outputSpinup);
		int getDOYIndex(const int &mon, const int &id);

		void reset();

		int getTranNumberOfYears();
		int getScenNumberOfYears();

		int getDaysInMonth(int & mon);
		int getCurrentMonthIndex();
		int getNextMonthIndex();
		int getCurrentYearIndex();

		void advanceOneMonth();
	
	    int getCalendarYear( bool & equiled, bool &spined);


	private:

		void updateDiagnostic();

};

#endif /*TIMER_H_*/
