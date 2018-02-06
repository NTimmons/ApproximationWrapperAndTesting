#pragma once
#include <string>
#include <iostream>

#include "Helpers.h"
#include "Timer.h"
#include "ApproxConfig.h"

//######Testing Functions
using namespace std::chrono;
#define TIMING_UNIT milliseconds
#define TIMING_SAMPLE_COUNT 1024 * 10000
template <long double(*f)(long double)>
__int64 TimeApproxPolyFunction_ld(std::string _name)
{
	Timer<TIMING_UNIT> timer;
	//Evaluation Settings
	unsigned int samples = TIMING_SAMPLE_COUNT;
	long double step = (POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (float)samples;
	long double runningVal = POLYFIT_TARGET_RANGE_MIN;

	timer.Start();
	long double p = 0.f;
	for (unsigned int i = 0; i < samples; i++, runningVal += step)
	{
		p = f(runningVal);
	}
	__int64 time = timer.GetElapsedTime().count();
	std::cout << "Time for " << _name.c_str() << " is: " << time << " " << STRING(TIMING_UNIT) << ". Test value is " << p << "\n";
	return time;
}

template <double(*f)(double)>
__int64 TimeApproxPolyFunction_d(std::string _name)
{
	Timer<TIMING_UNIT> timer;
	//Evaluation Settings
	unsigned int samples = TIMING_SAMPLE_COUNT;
	double step = (POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (float)samples;
	double runningVal = POLYFIT_TARGET_RANGE_MIN;

	timer.Start();
	double p = 0.f;
	for (unsigned int i = 0; i < samples; i++, runningVal += step)
	{
		p = f(runningVal);
	}
	__int64 time = timer.GetElapsedTime().count();
	std::cout << "Time for " << _name.c_str() << " is: " << time << " " << STRING(TIMING_UNIT) << ". Test value is " << p << "\n";
	return time;
}

template <float(*f)(float)>
__int64 TimeApproxPolyFunction_f(std::string _name)
{
	Timer<TIMING_UNIT> timer;
	//Evaluation Settings
	unsigned int samples = TIMING_SAMPLE_COUNT;
	float step = (POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (float)samples;
	float runningVal = POLYFIT_TARGET_RANGE_MIN;

	timer.Start();
	float p = 0.f;
	for (unsigned int i = 0; i < samples; i++, runningVal += step)
	{
		p = f(runningVal);
	}
	__int64 time = timer.GetElapsedTime().count();
	std::cout << "Time for " << _name.c_str() << " is: " << time << " " << STRING(TIMING_UNIT) << ". Test value is " << p << "\n";
	return time;
}


__int64 TimeApproxPolyFunction10()
{
	Timer<TIMING_UNIT> timer;
	//Evaluation Settings
	unsigned int samples = TIMING_SAMPLE_COUNT;
	double step = (POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (double)samples;
	double runningVal = POLYFIT_TARGET_RANGE_MIN;

	timer.Start();
	float p = 0.f;
	for (unsigned int i = 0; i < samples; i++, runningVal += step)
	{
		double _x = runningVal;
		p = ((0.00001674542907576381738196831527876f*(1.0f)) + (0.99963744795746456439644589408999309f*(_x)) + (0.00188035556531662836551865858325527f*(_x* _x)) + (-0.17081612339712609616171334891987499f*(_x* _x * _x)) + (0.00485728660102520675562187690843530f*(_x* _x * _x * _x)) + (0.00497664968620105396812647313709022f*(_x* _x * _x * _x * _x)) + (0.00144032061081068884535183460826602f*(_x* _x * _x * _x * _x * _x)) + (-0.00058557359877529837222792652440262f*(_x* _x * _x * _x * _x * _x * _x)) + (0.00006237651297980173069508691430229f*(_x* _x * _x * _x * _x * _x * _x * _x)) + (-0.00000224576218178413702952246622235f*(_x* _x * _x * _x * _x * _x * _x * _x * _x)) + (0.00000000239661819981204697371404255f*(_x* _x * _x * _x * _x * _x * _x * _x * _x * _x)));
	}
	__int64 time = timer.GetElapsedTime().count();
	std::cout << "Time for " << "Forced inline Tenth Polynomial" << " is: " << time << " " << STRING(TIMING_UNIT) << ". Test value is " << p << "\n";
	return time;
}

template <float(*ref)(float), float(*comp)(float)>
double GetAverageDifferenceInRangeFunction(std::string _name)
{
	//Evaluation Settings
	unsigned int samples = TIMING_SAMPLE_COUNT;
	float startValue = (float)POLYFIT_TARGET_RANGE_MIN;
	float endValue = (float)POLYFIT_TARGET_RANGE_MAX;
	float step = (POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (float)samples;
	float runningVal = startValue;

	double sum = 0.f;
	for (unsigned int i = 0; i < samples; i++, runningVal += step)
	{
		float p0 = ref(runningVal);
		float p1 = comp(runningVal);
		float diff = abs(p0 - p1);
		sum += diff;
	}

	double diffMean = sum / (double)samples;
	std::cout << "Diff for " << _name.c_str() << " is: " << std::setprecision(100) << diffMean << " .\n";
	return diffMean;
}



struct ErrorValues
{ 
	long double _minError;
	long double _maxError;
	long double _meanError;
	long double _medianError;
	long double _totalError;
	__int64	    _runTime;
	std::string _name;
};

template< typename Y>
void GenerateTestData(std::vector<Y>& _testValues, std::vector<Y>& _correctValues)
{
	Y val = (long double)POLYFIT_TARGET_RANGE_MIN;
	Y step = (long double)(POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (long double)POLYFIT_TARGET_RANGE_SAMPLES;

	for (int i = 0; i < POLYFIT_TARGET_RANGE_SAMPLES; i++)
	{
		_testValues.push_back(val);
		_correctValues.push_back(POLYFIT_TARGET_FUNCTION_ACCURATE(val));

		val += step;
	}
}

template <float(*newFunc)(float)>
ErrorValues GetError_f(std::vector<long double>& _testValues, std::vector<long double>& _correctValues, std::string _name)
{
	long double val = (long double)POLYFIT_TARGET_RANGE_MIN;
	long double step = (long double)(POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (long double)POLYFIT_TARGET_RANGE_SAMPLES;

	long double min = 9999.f;
	long double max = -1.f;
	long double sumError = 0.f;

	std::vector<long double> _newResults;
	std::vector<long double> _newError;

	for (int i = 0; i < _testValues.size(); i++)
	{
		float newRes = newFunc(_testValues[i]);
		_newResults.push_back(newRes);

		long double error = fabs(_correctValues[i] - (long double)newRes);
		min = fmin(min, error);
		max = fmax(max, error);
		sumError += error;

		_newError.push_back(error);
	}

	std::sort(_newError.begin(), _newError.end());

	ErrorValues err;
	err._name			= _name;
	err._minError		= min;
	err._maxError		= max;
	err._meanError		= sumError / _newError.size();
	err._medianError	= _newError[_newError.size() / 2];
	err._totalError		= sumError;

	return err;
}

template <double(*newFunc)(double)>
ErrorValues GetError_d(std::vector<long double>& _testValues, std::vector<long double>& _correctValues, std::string _name)
{
	long double val = (long double)POLYFIT_TARGET_RANGE_MIN;
	long double step = (long double)(POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (long double)POLYFIT_TARGET_RANGE_SAMPLES;

	long double min = 9999.f;
	long double max = -1.f;
	long double sumError = 0.f;

	std::vector<long double> _newResults;
	std::vector<long double> _newError;

	for (int i = 0; i < _testValues.size(); i++)
	{
		double newRes = newFunc(_testValues[i]);
		_newResults.push_back(newRes);

		long double error = fabs(_correctValues[i] - (long double)newRes);
		min = fmin(min, error);
		max = fmax(max, error);
		sumError += error;

		_newError.push_back(error);
	}

	std::sort(_newError.begin(), _newError.end());

	ErrorValues err;
	err._name			= _name;
	err._minError		= min;
	err._maxError		= max;
	err._meanError		= sumError / _newError.size();
	err._medianError	= _newError[_newError.size() / 2];
	err._totalError		= sumError;

	return err;
}


template <long double(*newFunc)(long double)>
ErrorValues GetError_ld(std::vector<long double>& _testValues, std::vector<long double>& _correctValues, std::string _name)
{
	long double val = (long double)POLYFIT_TARGET_RANGE_MIN;
	long double step = (long double)(POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (long double)POLYFIT_TARGET_RANGE_SAMPLES;

	long double min = 9999.f;
	long double max = -1.f;
	long double sumError = 0.f;

	std::vector<long double> _newResults;
	std::vector<long double> _newError;

	for (int i = 0; i < _testValues.size(); i++)
	{
		long double newRes = newFunc(_testValues[i]);
		_newResults.push_back(newRes);

		long double error	= fabs(_correctValues[i] - newRes);
		min					= fmin(min, error);
		max					= fmax(max, error);
		sumError		   += error;

		_newError.push_back(error);
	}

	std::sort(_newError.begin(), _newError.end());

	ErrorValues err;
	err._name			= _name;
	err._minError		= min;
	err._maxError		= max;
	err._meanError		= sumError / _newError.size();
	err._medianError	= _newError[_newError.size() / 2];
	err._totalError		= sumError;

	return err;
}


template <float(*newFunc)(float)>
ErrorValues GetError_Float(std::vector<long double>& _testValues, std::vector<long double>& _correctValues, std::string _name)
{
	float val = (float)POLYFIT_TARGET_RANGE_MIN;
	float step = (float)(POLYFIT_TARGET_RANGE_MAX - POLYFIT_TARGET_RANGE_MIN) / (float)POLYFIT_TARGET_RANGE_SAMPLES;

	float min = 9999.f;
	float max = -1.f;
	float sumError = 0.f;  

	std::vector<float> _newResults;
	std::vector<float> _newError;

	for (int i = 0; i < _testValues.size(); i++)
	{
		float newRes = newFunc(_testValues[i]);
		_newResults.push_back(newRes);

		float error = fabs(_correctValues[i] - newRes);
		min = fmin(min, error);
		max = fmax(max, error);
		sumError += error;

		_newError.push_back(error);
	}

	std::sort(_newError.begin(), _newError.end());

	ErrorValues err;
	err._name = _name;
	err._minError = min;
	err._maxError = max;
	err._meanError = sumError / _newError.size();
	err._medianError = _newError[_newError.size() / 2];
	err._totalError = sumError;

	return err;
}

//Function to use when forcing the none-inlining of the target function.
__declspec(noinline) float WrapperBaseForceInline(float _x)
{
	return POLYFIT_TARGET_FUNCTION_RUNTIME(_x);
}

class ErrorOutput
{
public:

	void Print()
	{
		int bigwid = 32;
		int width = 18;
		std::cout << std::setw(bigwid) << "Name " << std::setw(width) << "Min Err. " << std::setw(width)
			<< "Max Err. " << std::setw(width) << "Mean Err. " << std::setw(width) << "Median Err. "
			<< std::setw(width) << "Total Err. "
			<< std::setw(width) << "Runtime \n";

		for (int i = 0; i < m_list.size(); i++)
		{
			if (m_list[i]._maxError == -1.f)
			{
				std::cout << "\n";
			}
			else
			{
				std::cout << std::setw(bigwid) << m_list[i]._name << std::setw(width) << m_list[i]._minError
					<< std::setw(width) << m_list[i]._maxError << std::setw(width) << m_list[i]._meanError
					<< std::setw(width) << m_list[i]._medianError << std::setw(width) << m_list[i]._totalError
					<< std::setw(width) << m_list[i]._runTime << "\n";
			}


		}
		std::cout << "------------------------------------------------------------------------------------------\n";
	}

	void AddNewLine()
	{
		ErrorValues _err;
		_err._maxError = -1.f;
		m_list.push_back(_err);
	}

	void AddErrorData(ErrorValues _err)
	{
		m_list.push_back(_err);
	}
	std::vector<ErrorValues> m_list;
};
