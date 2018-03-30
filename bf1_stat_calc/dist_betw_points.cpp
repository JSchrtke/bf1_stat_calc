//dist_between_points.cpp
//function to return the distance between two points in a cartesian coordinate system
#include <iostream>
#include "stdafx.h"
#include <cmath>
#include "dist_betw_points.h"

double dist_betw_points(double x_1, double y_1, double x_2, double y_2)
{
	double dist_x, dist_y, dist_points;
	dist_x = abs(x_1) + abs(x_2);
	dist_y = abs(y_1) + abs(y_2);
	dist_points = std::sqrt(dist_x * dist_x + dist_y * dist_y);
	return dist_points;
}
