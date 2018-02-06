#pragma once

#include <cmath>

//CONFIG SETTINGS///////////////
#define POLYFIT_TARGET_FUNCTION_ACCURATE		std::cos
#define POLYFIT_TARGET_FUNCTION_RUNTIME			std::cosf
#define POLYFIT_APPROX_FUNCTION_RUNTIME_LD		functionPoly_longdouble_Order8
#define POLYFIT_APPROX_FUNCTION_RUNTIME_D		functionPoly_double_Order8
#define POLYFIT_APPROX_FUNCTION_RUNTIME_F		functionPoly_float_Order8
#define POLYFIT_TARGET_RANGE_MIN				0.0
#define POLYFIT_TARGET_RANGE_MAX				3.14159
#define POLYFIT_TARGET_RANGE_SAMPLES			1024
#define POLYFIT_TARGET_RANGE_SAMPLES_MATLAB		16384
#define POLYFIT_TARGET_RANGE_RUNTIME_SAMPLES	POLYFIT_TARGET_RANGE_SAMPLES
//#define POLYFIT_INCLUDE testfunctions.h
////////////////////////////////

#define POLYFIT_TARGET_RANGE_STEP_SIZE		(float)(POLYFIT_TARGET_RANGE_MAX-POLYFIT_TARGET_RANGE_MIN) /(float)POLYFIT_TARGET_RANGE_SAMPLES
#define POLYFIT_TARGET_RANGE_GET_INDEX(x)	((float)((x  - POLYFIT_TARGET_RANGE_MIN))) / ((float)POLYFIT_TARGET_RANGE_STEP_SIZE)

#define POLYFIT_TARGET_RANGE_STEP_SIZE_RUNTIME		(float)(POLYFIT_TARGET_RANGE_MAX-POLYFIT_TARGET_RANGE_MIN) /(float)POLYFIT_TARGET_RANGE_RUNTIME_SAMPLES
#define POLYFIT_TARGET_RANGE_GET_INDEX_RUNTIME(x)	((float)((x  - POLYFIT_TARGET_RANGE_MIN))) / ((float)POLYFIT_TARGET_RANGE_STEP_SIZE)
 
static float		Results_Float		[POLYFIT_TARGET_RANGE_RUNTIME_SAMPLES];
static double		Results_Double		[POLYFIT_TARGET_RANGE_RUNTIME_SAMPLES];
static long double  Results_LongDouble	[POLYFIT_TARGET_RANGE_RUNTIME_SAMPLES];

class PreMainFunction
{
public:
	PreMainFunction() {}
	static bool Initialise()
	{
		long double val			= POLYFIT_TARGET_RANGE_MIN;
		long double minx		= POLYFIT_TARGET_RANGE_MIN;
		long double maxx		= POLYFIT_TARGET_RANGE_MAX;
		long double stepCount	= (long double)POLYFIT_TARGET_RANGE_RUNTIME_SAMPLES;
		int			stepCountI	= POLYFIT_TARGET_RANGE_RUNTIME_SAMPLES;
		long double step		= (maxx- minx) / stepCount;

		for (int i = 0; i < stepCountI; i++)
		{
			Results_LongDouble[i]	= POLYFIT_TARGET_FUNCTION_ACCURATE(val);
			Results_Double[i]		= POLYFIT_TARGET_FUNCTION_ACCURATE((double)val);
			Results_Float[i]		= POLYFIT_TARGET_FUNCTION_ACCURATE((float)val);
			val += step;
		}
		return true;
	}
};

bool AreTablesInitialised = PreMainFunction::Initialise();




