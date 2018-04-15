//offset.cpp
/*
This function calculates a distance offset based on an angle(such as hrec or spread values) and a distance(from a target etc.)
*/
#include "stdafx.h"
#include "math_functions.h"
#include <cmath>
#include <iostream>

const double PI = 3.141592653589793238463;

double offset(double distance, double angle)
{
	double hrec_hor_shift;
	hrec_hor_shift = tan(angle * (PI / 180)) * distance;
	return hrec_hor_shift;
}
