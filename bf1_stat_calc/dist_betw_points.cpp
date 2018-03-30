//dist_between_points.cpp
//function to return the distance between two points in a cartesian coordinate system
#include <cmath>
#include <iostream>
#include "stdafx.h"
#include "math.h"
#include "dist_betw_points.h"

double dist_betw_points(double x_1, double y_1, double x_2, double y_2)
{
	double dist_x, dist_y, dist_points;
	dist_x = fabs(x_1) + fabs(x_2);
	dist_y = fabs(y_1) + fabs(y_2);
	dist_points = sqrt(dist_x * dist_x + dist_y * dist_y);
	return dist_points;
}
