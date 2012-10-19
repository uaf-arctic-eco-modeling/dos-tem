/*
 * coreinc.i
 *
 */

	%module coreinc

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

			%{
				#include "inc\cohortconst.h"
				#include "inc\cohortkey.h"
				#include "inc\diagnostics.h"
				#include "inc\ErrorCode.h"
				#include "inc\fluxes.h"
				#include "inc\layerconst.h"
				#include "inc\parameters.h"
				#include "inc\PhysicalConstants.h"
				#include "inc\runmode.h"
				#include "inc\states.h"
				#include "inc\temconst.h"
				#include "inc\timeconst.h"
			%}

			%include "inc\cohortconst.h"
			%include "inc\cohortkey.h"
			%include "inc\diagnostics.h"
			%include "inc\ErrorCode.h"
			%include "inc\fluxes.h"
			%include "inc\layerconst.h"
			%include "inc\parameters.h"
			%include "inc\PhysicalConstants.h"
			%include "inc\runmode.h"
			%include "inc\states.h"
			%include "inc\temconst.h"
			%include "inc\timeconst.h"
