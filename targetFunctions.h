#pragma once

#include "Helpers.h"

template <long double(*targetFunction)(long double)>
void GenerateTableForMatLab(long double _minValue, long double _maxValue, int _stepCount, std::string _name)
{
	long double val = _minValue;
	long double minx = _minValue;
	long double maxx = _maxValue;
	long double stepCount = (long double)_stepCount;
	int	  stepCountI = _stepCount;
	long double step = (maxx - minx) / stepCount;

	std::vector<long double> x;
	std::vector<long double> y; 

	for (int i = 0; i < stepCountI; i++)
	{
		x.push_back(val);
		y.push_back( targetFunction(val) );
		val += step;
	}

	std::string filename = _name; 
	filename.append(".csv");
	WriteCSVPrecise( x, y, filename.c_str() );
}

