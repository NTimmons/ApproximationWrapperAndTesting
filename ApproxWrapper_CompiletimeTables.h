#pragma once
#include <array>


// Array lookup table building -> need to expand with variadics to allow for function arguments other than index number.
/////////////////////

template<class Function, std::size_t... Indices>
constexpr auto MakeLookUpTableHelper(Function f, const float _min, const float _stepSize, std::index_sequence<Indices...>)
->std::array<typename std::result_of<Function(float)>::type, sizeof...(Indices)>
{
	return { { f(_min + (Indices*_stepSize))... } };
}

template<int N, class Function>
constexpr auto MakeLookUpTable(Function f, const float _min, const float _stepSize)
->std::array<typename std::result_of<Function(std::size_t)>::type, N>
{
	return MakeLookUpTableHelper(f, _min, _stepSize, std::make_index_sequence<N>{});
}

//We want min and max in the template but C++ template is arbitrarily not allowing it. See below...
/*
14.3.2 / 1      Template non - type arguments[temp.arg.nontype]

A template - argument for a non - type, non - template template - parameter shall be one of :

for a non - type template - parameter of integral or enumeration type, a converted constant expression(5.19) of the type of the template - parameter;
the name of a non - type template - parameter; or
a constant expression(5.19) that designates the address of an object with static storage duration and external or internal linkage or a function with external or internal linkage, including function templates and function template - ids but excluding non - static class members, expressed(ignoring parentheses) as & id - expression, except that the & may be omitted if the name refers to a function or array and shall be omitted if the corresponding template - parameter is a reference; or
a constant expression that evaluates to a null pointer value(4.10); or
a constant expression that evaluates to a null member pointer value(4.11); or
a pointer to member expressed as described in 5.3.1.
*/
///////////////////////////////////////////////////////////////////////////////////////

template <float(*approx)(float), float(*accurate)(float)>
constexpr float ApproximateFunction_TableBasedNoInterp_Rf(float _val, float _min, float _max)
{
	static constexpr auto lookupTable = MakeLookUpTable<POLYFIT_TARGET_RANGE_SAMPLES>(approx, POLYFIT_TARGET_RANGE_MIN, POLYFIT_TARGET_RANGE_STEP_SIZE);

	//want to hide this where possible. Should be using std::conditional(?) on _min/_max to specialise
	if (_val < _max && _val > _min)
	{
		return lookupTable[POLYFIT_TARGET_RANGE_GET_INDEX(_val)];
	}
	else
	{
		return accurate(_val);
	}
}

template <float(*approx)(float), float(*accurate)(float)>
constexpr float ApproximateFunction_TableBasedNoInterp_Rf(float _val)
{
	static constexpr auto lookupTable = MakeLookUpTable<POLYFIT_TARGET_RANGE_SAMPLES>(approx, POLYFIT_TARGET_RANGE_MIN, POLYFIT_TARGET_RANGE_STEP_SIZE);

	//want to hide this where possible. Should be using std::conditional(?) on _min/_max to specialise
	if (_val < POLYFIT_TARGET_RANGE_MAX && _val > POLYFIT_TARGET_RANGE_MIN)
	{
		return lookupTable[POLYFIT_TARGET_RANGE_GET_INDEX(_val)];
	}
	else
	{
		return accurate(_val);
	}
}

#ifndef __INTEL_COMPILER
template <float(*approx)(float)>
constexpr float ApproximateFunction_TableBasedNoInterp_Rf_Only(float _val)
{
	static constexpr auto lookupTable = MakeLookUpTable<POLYFIT_TARGET_RANGE_SAMPLES>(approx, POLYFIT_TARGET_RANGE_MIN, POLYFIT_TARGET_RANGE_STEP_SIZE);

	return lookupTable.at((int)POLYFIT_TARGET_RANGE_GET_INDEX(_val));
}

template <float(*approx)(float)>
constexpr float ApproximateFunction_CompileTimeTableBasedInterp_Rf_Only(float _val)
{
	static constexpr auto lookupTable = MakeLookUpTable<POLYFIT_TARGET_RANGE_SAMPLES>(approx, POLYFIT_TARGET_RANGE_MIN, POLYFIT_TARGET_RANGE_STEP_SIZE);

	float pos = POLYFIT_TARGET_RANGE_GET_INDEX(_val);
	int lowIndex = (int)pos;
	int highIndex = lowIndex + 1;
	float val0 = lookupTable[std::min(POLYFIT_TARGET_RANGE_SAMPLES - 1, lowIndex)];
	float val1 = lookupTable[std::min(POLYFIT_TARGET_RANGE_SAMPLES - 1, highIndex)];

	float scale = pos - floor(pos);
	float res = ((1.0f - scale) * val0) + ((scale)* val1);

	return res;
}

template <float(*approx)(float)>
constexpr double ApproximateFunction_CompileTimeTableBasedInterp_Rd_Only(double _val)
{
	static constexpr auto lookupTable = MakeLookUpTable<POLYFIT_TARGET_RANGE_SAMPLES>(approx, POLYFIT_TARGET_RANGE_MIN, POLYFIT_TARGET_RANGE_STEP_SIZE);

	double pos = POLYFIT_TARGET_RANGE_GET_INDEX(_val);
	int lowIndex = (int)pos;
	int highIndex = lowIndex + 1;
	double val0 = lookupTable[std::min(POLYFIT_TARGET_RANGE_SAMPLES - 1, lowIndex)];
	double val1 = lookupTable[std::min(POLYFIT_TARGET_RANGE_SAMPLES - 1, highIndex)];

	double scale = pos - floor(pos);
	double res = ((1.0f - scale) * val0) + ((scale)* val1);

	return res;
}

template <long double(*approx)(long double)>
constexpr long double ApproximateFunction_CompileTimeTableBasedInterp_Rld_Only(long double _val)
{
	static constexpr auto lookupTable = MakeLookUpTable<POLYFIT_TARGET_RANGE_SAMPLES>(approx, POLYFIT_TARGET_RANGE_MIN, POLYFIT_TARGET_RANGE_STEP_SIZE);

	long double pos = POLYFIT_TARGET_RANGE_GET_INDEX(_val);
	int lowIndex = (int)pos;
	int highIndex = lowIndex + 1;
	long double val0 = lookupTable[std::min(POLYFIT_TARGET_RANGE_SAMPLES - 1, lowIndex)];
	long double val1 = lookupTable[std::min(POLYFIT_TARGET_RANGE_SAMPLES - 1, highIndex)];

	long double scale = pos - floor(pos);
	long double res = ((1.0f - scale) * val0) + ((scale)* val1);

	return res;
}

#endif // !__INTEL_COMPILER