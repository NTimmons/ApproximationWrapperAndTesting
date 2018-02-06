#pragma once
#include "ApproxConfig.h"

//######Wrapper Functions
template <float(*approx)(float), float(*accurate)(float)>
constexpr float ApproximateFunction_RangeBased_Rf(float _val, float _min, float _max)
{
	//want to hide this where possible. Should be using std::conditional on _min/_max to specialise
	if (_val < _max && _val > _min)
	{
		return approx(_val);
	}
	else
	{
		return accurate(_val);
	}
}

template <float(*approx)(float), float(*accurate)(float)>
constexpr float ApproximateFunction_RangeBased_Rf(float _val)
{
	//want to hide this where possible. Should be using std::conditional on _min/_max to specialise
	if (_val < POLYFIT_TARGET_RANGE_MAX && _val > POLYFIT_TARGET_RANGE_MIN)
	{
		return approx(_val);
	}
	else
	{
		return accurate(_val);
	}
}

template <float(*approx)(float)>
constexpr float ApproximateFunction_RangeBased_Rf_Only(float _val)
{
	return approx(_val);
}



