#include "stdafx.h"
#include "math_functions.h"
#include <iostream>

const double PI = 3.141592653589793238463;

double hrec(double distance, double hrec_magnitude)
{
	double hrec_hor_shift;
	hrec_hor_shift = tan(hrec_magnitude * (PI / 180)) * distance;
	return hrec_hor_shift;
}
