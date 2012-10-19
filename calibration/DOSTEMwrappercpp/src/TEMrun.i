/*
 * TEMrun.i
 *
 */

	%module TEMrun

//Translate operators
%rename(add) operator+;
%rename(elementAt) operator[];
%rename(getValue) operator();
%rename(subtract) operator-;
%rename(multiply) operator*;
%rename(divide) operator/;
%rename(equals) operator==;
%rename(unEquals) operator!=;
%rename(shiftLeft) operator<<;
%rename(shiftRight) operator>>;
%rename(lessThan) operator<;
%rename(lessThanOrEquals) operator<=;
%rename(greaterThan) operator>=;
%rename(greaterThanOrEquals) operator>=;
%rename(addOne) operator++;
%rename(subtractOne) operator--;
%rename(addAndAssign) operator+=;
%rename(subtractAndAssign) operator-=;
%rename(multiplyAndAssign) operator*=;
%rename(divideAndAssign) operator/=;
%rename(clone) operator=;

%include "arrays_java.i"
%include "coredata.i"
%include "coreinc.i"
%include "corelookup.i"

			%{
				#include "run/AtmOutData.h"
				#include "run/Cohort.h"
				#include "run/Controller.h"
				#include "run/Grid.h"
				#include "run/ModelData.h"
				#include "run/RegnOutData.h"
				#include "run/SiteIn.h"
				#include "run/SnowSoilOutData.h"
				#include "run/Timer.h"
				#include "run/VegOutData.h"
			%}

			%include "run/AtmOutData.h"
			%include "run/Cohort.h"
			%include "run/Controller.h"
			%include "run/Grid.h"
			%include "run/ModelData.h"
			%include "run/RegnOutData.h"
			%include "run/SiteIn.h"
			%include "run/SnowSoilOutData.h"
			%include "run/Timer.h"
			%include "run/VegOutData.h"
