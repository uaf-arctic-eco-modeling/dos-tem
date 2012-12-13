/*
 * TEMrun.i
 *
 */

	%module temcore

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
				#include "../../src/run/AtmOutData.h"
				#include "../../src/run/Cohort.h"
				#include "../../src/run/Controller.h"
				#include "../../src/run/Grid.h"
				#include "../../src/run/ModelData.h"
				#include "../../src/run/RegnOutData.h"
				#include "../../src/run/SiteIn.h"
				#include "../../src/run/SnowSoilOutData.h"
				#include "../../src/run/Timer.h"
				#include "../../src/run/VegOutData.h"
			%}

			%include "../../src/run/AtmOutData.h"
			%include "../../src/run/Cohort.h"
			%include "../../src/run/Controller.h"
			%include "../../src/run/Grid.h"
			%include "../../src/run/ModelData.h"
			%include "../../src/run/RegnOutData.h"
			%include "../../src/run/SiteIn.h"
			%include "../../src/run/SnowSoilOutData.h"
			%include "../../src/run/Timer.h"
			%include "../../src/run/VegOutData.h"
