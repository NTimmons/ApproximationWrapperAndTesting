
#include "ApproxConfig.h"

#include "OptimisationWrappers.h"
#include "TestingHelpers.h"
#include "Helpers.h"

#include "generatedApprox.h"
#include "targetFunctions.h"
#include "testfunctions.h"

#include "ErrorPropagationClass.h"
#include "ApproxType.h"

int main() 
{
	//Error propagation management.
	ErrorPropagationType<float> a;
	ErrorPropagationType<float> b;
	auto c = operator+(a, b);

	ApproxType<float, 1> aa;
	ApproxType<float, 3> bb;
	auto cc = aa + bb;


	std::vector<long double> testValues;
	std::vector<long double> correctValues;
	GenerateTestData(testValues, correctValues); 

	ErrorOutput err;
	
	//Get Accuracy Data
	ErrorValues SourceFunction				 = GetError_f<POLYFIT_TARGET_FUNCTION_RUNTIME>(testValues, correctValues, "Source Function");
	ErrorValues CTTableError_Float			 = GetError_f<ApproximateFunction_CompileTimeTableBasedInterp_Rf_Only<POLYFIT_APPROX_FUNCTION_RUNTIME_F>>(testValues, correctValues, "CompileTimeTable_Float");
	ErrorValues CTTableError_LongDouble		 = GetError_ld<ApproximateFunction_CompileTimeTableBasedInterp_Rld_Only<POLYFIT_APPROX_FUNCTION_RUNTIME_LD>>(testValues, correctValues, "CompileTimeTable_LongDouble");
	ErrorValues RTTableError_Float			 = GetError_f<ApproximateFunction_RuntimeTableBasedInterp_Rf_Only >							(testValues, correctValues, "RunTimeTable_Float");
	ErrorValues RTTableError_LongDouble		 = GetError_ld<ApproximateFunction_RuntimeTableBasedInterp_Rld_Only>						(testValues, correctValues, "RunTimeTable_LongDouble");
	
	//ErrorValues ComputeError_Float			 = GetError_f<POLYFIT_APPROX_FUNCTION_RUNTIME_F>											(testValues, correctValues, "ApproximateComputed_Float");
	//ErrorValues ComputeError_LongDouble		 = GetError_ld<POLYFIT_APPROX_FUNCTION_RUNTIME_LD>											(testValues, correctValues, "ApproximateComputed_LongDouble");

	ErrorValues ComputeError10_Float		= GetError_f <functionPoly_float_Order10>		(testValues, correctValues	, STRING(functionPoly_float_Order10));
	ErrorValues ComputeError10_Double		= GetError_d <functionPoly_double_Order10>		(testValues, correctValues  , STRING(functionPoly_double_Order10));
	ErrorValues ComputeError10_LongDouble	= GetError_ld<functionPoly_longdouble_Order10>	(testValues, correctValues	, STRING(functionPoly_longdouble_Order10));
	ErrorValues ComputeError9_Float			= GetError_f <functionPoly_float_Order9>		(testValues, correctValues	, STRING(functionPoly_float_Order9));
	ErrorValues ComputeError9_Double		= GetError_d <functionPoly_double_Order9>		(testValues, correctValues  , STRING(functionPoly_double_Order9));
	ErrorValues ComputeError9_LongDouble	= GetError_ld<functionPoly_longdouble_Order9>	(testValues, correctValues	, STRING(functionPoly_longdouble_Order9));
	ErrorValues ComputeError8_Float			= GetError_f <functionPoly_float_Order8>		(testValues, correctValues	, STRING(functionPoly_float_Order8));
	ErrorValues ComputeError8_Double		= GetError_d <functionPoly_double_Order8>		(testValues, correctValues  , STRING(functionPoly_double_Order8));
	ErrorValues ComputeError8_LongDouble	= GetError_ld<functionPoly_longdouble_Order8>	(testValues, correctValues	, STRING(functionPoly_longdouble_Order8));
	ErrorValues ComputeError7_Float			= GetError_f <functionPoly_float_Order7>		(testValues, correctValues	, STRING(functionPoly_float_Order7));
	ErrorValues ComputeError7_Double		= GetError_d <functionPoly_double_Order7>		(testValues, correctValues  , STRING(functionPoly_double_Order7));
	ErrorValues ComputeError7_LongDouble	= GetError_ld<functionPoly_longdouble_Order7>	(testValues, correctValues	, STRING(functionPoly_longdouble_Order7));
	ErrorValues ComputeError6_Float			= GetError_f <functionPoly_float_Order6>		(testValues, correctValues	, STRING(functionPoly_float_Order6));
	ErrorValues ComputeError6_Double		= GetError_d <functionPoly_double_Order6>		(testValues, correctValues  , STRING(functionPoly_double_Order6));
	ErrorValues ComputeError6_LongDouble	= GetError_ld<functionPoly_longdouble_Order6>	(testValues, correctValues	, STRING(functionPoly_longdouble_Order6));
	ErrorValues ComputeError5_Float			= GetError_f <functionPoly_float_Order5>		(testValues, correctValues	, STRING(functionPoly_float_Order5));
	ErrorValues ComputeError5_Double		= GetError_d <functionPoly_double_Order5>		(testValues, correctValues  , STRING(functionPoly_double_Order5));
	ErrorValues ComputeError5_LongDouble	= GetError_ld<functionPoly_longdouble_Order5>	(testValues, correctValues	, STRING(functionPoly_longdouble_Order5));
	ErrorValues ComputeError4_Float			= GetError_f <functionPoly_float_Order4>		(testValues, correctValues	, STRING(functionPoly_float_Order4));
	ErrorValues ComputeError4_Double		= GetError_d <functionPoly_double_Order4>		(testValues, correctValues  , STRING(functionPoly_double_Order4));
	ErrorValues ComputeError4_LongDouble	= GetError_ld<functionPoly_longdouble_Order4>	(testValues, correctValues	, STRING(functionPoly_longdouble_Order4));
	ErrorValues ComputeError3_Float			= GetError_f <functionPoly_float_Order3>		(testValues, correctValues	, STRING(functionPoly_float_Order3));
	ErrorValues ComputeError3_Double		= GetError_d <functionPoly_double_Order3>		(testValues, correctValues  , STRING(functionPoly_double_Order3));
	ErrorValues ComputeError3_LongDouble	= GetError_ld<functionPoly_longdouble_Order3>	(testValues, correctValues	, STRING(functionPoly_longdouble_Order3));


	//Get Timing Data
	SourceFunction				._runTime = TimeApproxPolyFunction_f<POLYFIT_TARGET_FUNCTION_RUNTIME>("Source Function");
	CTTableError_Float			._runTime = TimeApproxPolyFunction_f<ApproximateFunction_CompileTimeTableBasedInterp_Rf_Only<POLYFIT_APPROX_FUNCTION_RUNTIME_F>>	(STRING(CompileTime Float Table));
	CTTableError_LongDouble		._runTime = TimeApproxPolyFunction_ld<ApproximateFunction_CompileTimeTableBasedInterp_Rld_Only<POLYFIT_APPROX_FUNCTION_RUNTIME_LD>>	(STRING(CompileTime Long Double Table));
	RTTableError_Float			._runTime = TimeApproxPolyFunction_f<ApproximateFunction_RuntimeTableBasedInterp_Rf_Only >		(STRING(Runtime Float Table));
	RTTableError_LongDouble		._runTime = TimeApproxPolyFunction_ld<ApproximateFunction_RuntimeTableBasedInterp_Rld_Only>		(STRING(Runtime Long Double Table));
	//ComputeError_Float			._runTime = TimeApproxPolyFunction_f<POLYFIT_APPROX_FUNCTION_RUNTIME_F>							(STRING(functionPoly_float_Order10));
	//ComputeError_LongDouble		._runTime = TimeApproxPolyFunction_ld<POLYFIT_APPROX_FUNCTION_RUNTIME_LD>						(STRING(functionPoly_longdouble_Order10));

	ComputeError10_Float		._runTime = TimeApproxPolyFunction_f<functionPoly_float_Order10>			(STRING(functionPoly_float_Order10));
	ComputeError10_Double		._runTime = TimeApproxPolyFunction_d<functionPoly_double_Order10>			(STRING(functionPoly_double_Order10));
	ComputeError10_LongDouble	._runTime = TimeApproxPolyFunction_ld<functionPoly_longdouble_Order10>		(STRING(functionPoly_longdouble_Order10));
	ComputeError9_Float			._runTime = TimeApproxPolyFunction_f<functionPoly_float_Order9>				(STRING(functionPoly_float_Order9));
	ComputeError9_Double		._runTime = TimeApproxPolyFunction_d<functionPoly_double_Order9>			(STRING(functionPoly_double_Order9));
	ComputeError9_LongDouble	._runTime = TimeApproxPolyFunction_ld<functionPoly_longdouble_Order9>		(STRING(functionPoly_longdouble_Order9));
	ComputeError8_Float			._runTime = TimeApproxPolyFunction_f<functionPoly_float_Order8>				(STRING(functionPoly_float_Order8));
	ComputeError8_Double		._runTime = TimeApproxPolyFunction_d<functionPoly_double_Order8>			(STRING(functionPoly_double_Order8));
	ComputeError8_LongDouble	._runTime = TimeApproxPolyFunction_ld<functionPoly_longdouble_Order8>		(STRING(functionPoly_longdouble_Order8));
	ComputeError7_Float			._runTime = TimeApproxPolyFunction_f<functionPoly_float_Order7>				(STRING(functionPoly_float_Order7));
	ComputeError7_Double		._runTime = TimeApproxPolyFunction_d<functionPoly_double_Order7>			(STRING(functionPoly_double_Order7));
	ComputeError7_LongDouble	._runTime = TimeApproxPolyFunction_ld<functionPoly_longdouble_Order7>		(STRING(functionPoly_longdouble_Order7));
	ComputeError6_Float			._runTime = TimeApproxPolyFunction_f<functionPoly_float_Order6>				(STRING(functionPoly_float_Order6));
	ComputeError6_Double		._runTime = TimeApproxPolyFunction_d<functionPoly_double_Order6>			(STRING(functionPoly_double_Order6));
	ComputeError6_LongDouble	._runTime = TimeApproxPolyFunction_ld<functionPoly_longdouble_Order6>		(STRING(functionPoly_longdouble_Order6));
	ComputeError5_Float			._runTime = TimeApproxPolyFunction_f<functionPoly_float_Order5>				(STRING(functionPoly_float_Order5));
	ComputeError5_Double		._runTime = TimeApproxPolyFunction_d<functionPoly_double_Order5>			(STRING(functionPoly_double_Order5));
	ComputeError5_LongDouble	._runTime = TimeApproxPolyFunction_ld<functionPoly_longdouble_Order5>		(STRING(functionPoly_longdouble_Order5));
	ComputeError4_Float			._runTime = TimeApproxPolyFunction_f<functionPoly_float_Order4>				(STRING(functionPoly_float_Order4));
	ComputeError4_Double		._runTime = TimeApproxPolyFunction_d<functionPoly_double_Order4>			(STRING(functionPoly_double_Order4));
	ComputeError4_LongDouble	._runTime = TimeApproxPolyFunction_ld<functionPoly_longdouble_Order4>		(STRING(functionPoly_longdouble_Order4));
	ComputeError3_Float			._runTime = TimeApproxPolyFunction_f<functionPoly_float_Order3>				(STRING(functionPoly_float_Order3));
	ComputeError3_Double		._runTime = TimeApproxPolyFunction_d<functionPoly_double_Order3>			(STRING(functionPoly_double_Order3));
	ComputeError3_LongDouble	._runTime = TimeApproxPolyFunction_ld<functionPoly_longdouble_Order3>		(STRING(functionPoly_longdouble_Order3));

	err.AddErrorData(SourceFunction					);
	err.AddErrorData(CTTableError_Float				);
	err.AddErrorData(CTTableError_LongDouble		); 
	err.AddErrorData(RTTableError_Float				);
	err.AddErrorData(RTTableError_LongDouble		);
	
	err.AddNewLine();

	err.AddErrorData(ComputeError10_Float);
	err.AddErrorData(ComputeError10_Double);
	err.AddErrorData(ComputeError10_LongDouble);
	err.AddErrorData(ComputeError9_Float);
	err.AddErrorData(ComputeError9_Double);
	err.AddErrorData(ComputeError9_LongDouble);
	err.AddErrorData(ComputeError8_Float);
	err.AddErrorData(ComputeError8_Double);
	err.AddErrorData(ComputeError8_LongDouble);
	err.AddErrorData(ComputeError7_Float);
	err.AddErrorData(ComputeError7_Double);
	err.AddErrorData(ComputeError7_LongDouble);
	err.AddErrorData(ComputeError6_Float);
	err.AddErrorData(ComputeError6_Double);
	err.AddErrorData(ComputeError6_LongDouble);
	err.AddErrorData(ComputeError5_Float);
	err.AddErrorData(ComputeError5_Double);
	err.AddErrorData(ComputeError5_LongDouble);
	err.AddErrorData(ComputeError4_Float);
	err.AddErrorData(ComputeError4_Double);
	err.AddErrorData(ComputeError4_LongDouble);
	err.AddErrorData(ComputeError3_Float);
	err.AddErrorData(ComputeError3_Double);
	err.AddErrorData(ComputeError3_LongDouble);

	err.Print();
	 
	system("PAUSE");

	return 0;    
} 
