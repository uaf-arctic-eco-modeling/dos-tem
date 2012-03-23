/*! \file
 * Time Related Class for TEM
 */

#include "Timer.h"

int Timer::dinm[] =     {31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31};
int Timer::doyindfst[] ={ 0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334};
 
Timer::Timer(){
 	monind=0;
 	
 	// Yuan: the following is calculated from those in timeconst.h 
//	maxeqrunyrs=30000;  //maximum number of years for equilibrium run (NOT USED)
  
	spinbegyr = BEG_SP_YR;
	spinendyr = END_SP_YR;
	trsbegyr  = BEG_TR_YR;
	trsendyr  = END_TR_YR;
	scbegyr   = BEG_SC_YR;
	scendyr   = END_SC_YR;
	
	spinnumyr = spinendyr-spinbegyr+1;
	trsnumyr  = trsendyr-trsbegyr+1;
	scnumyr   = scendyr-scbegyr+1;
	
};
 
Timer::~Timer(){

}

void Timer::reset(){
  	yearind =0;
  	monind  =0;	
};
 
int Timer::getTranNumberOfYears(){
   	return trsnumyr;	
};

int Timer::getScenNumberOfYears(){
   	return scnumyr;	
};
 
int Timer::getDOYIndex(const int &mind, const int &did){
  // here the mon is month index, March = 2
  // id is day index
  	int doy =doyindfst[mind]+ did;
 	return doy;
};
 
int Timer::getDaysInMonth(int & monind){
   	return dinm[monind];	
};
 
int Timer::getCurrentMonthIndex(){
 	return monind;
};
 
int Timer::getNextMonthIndex(){
 	int next = monind+1;
 	if(next ==-1) next =11;
 	if(next ==12) next =0;
 	return next;
};
 
int Timer::getCurrentYearIndex(){
   	return yearind;	
};
 
void Timer::advanceOneMonth(){
   	monind++;
   	if(monind>=12){
   		monind =0;
   		yearind++;
   	}
};

int Timer::getCalendarYear( bool & equiled, bool &spined){
	if(!equiled){
	  	return 1000;  //Yuan:???	
	}else if(!spined){
	  	return yearind+spinbegyr;
	}else{
	  	return yearind+trsbegyr;
	}

};
 
int Timer::getOutputYearIndex(bool & equiled, bool &spined, bool & outputSpinup){
	if(!equiled){
	  	return yearind;	
	}else if(!spined){
	  	return yearind;
	}else{
	  	if(outputSpinup){
	  		return yearind+spinnumyr;
	  	}else{
	  		return yearind;
	  	}
	}

};

int Timer::getInputYearIndex(bool & equiled, bool &spined){
	if(!equiled){
	  	return yearind;	
	}else if(!spined){
	  	return yearind%30;
	}else{
	  	return yearind;
	}
	
};
