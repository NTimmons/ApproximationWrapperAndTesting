#pragma once
float ApproximateFunction_TableBasedRuntimeNoInterp_Rf_Only(float _val)
{
	int index = (float)POLYFIT_TARGET_RANGE_GET_INDEX_RUNTIME(_val);
	return Results_Float[index];
}

float ApproximateFunction_RuntimeTableBasedInterp_Rf_Only(float _val)
{
	float pos = POLYFIT_TARGET_RANGE_GET_INDEX_RUNTIME(_val);
	int lowIndex = (int)pos;
	int highIndex = lowIndex + 1;
	float val0 = Results_Float[lowIndex];
	float val1 = Results_Float[highIndex];

	float scale = pos - floor(pos);
	float res = ((1.0f - scale) * val0) + ((scale)* val1);

	return res;
}

long double ApproximateFunction_RuntimeTableBasedInterp_Rld_Only(long double _val)
{
	long double pos = POLYFIT_TARGET_RANGE_GET_INDEX_RUNTIME(_val);
	int lowIndex = (int)pos;
	int highIndex = lowIndex + 1;
	long double val0 = Results_LongDouble[lowIndex];
	long double val1 = Results_LongDouble[highIndex];

	long double scale = pos - floor(pos);
	long double res = ((1.0f - scale) * val0) + ((scale)* val1);

	return res;
}

double ApproximateFunction_RuntimeTableBasedInterp_Rd_Only(double _val)
{
	double pos = POLYFIT_TARGET_RANGE_GET_INDEX_RUNTIME(_val);
	int lowIndex = (int)pos;
	int highIndex = lowIndex + 1;
	double val0 = Results_Double[lowIndex];
	double val1 = Results_Double[highIndex];

	double scale = pos - floor(pos);
	double res = ((1.0f - scale) * val0) + ((scale)* val1);

	return res;
}
