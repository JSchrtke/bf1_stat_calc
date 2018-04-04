//single_bullet_sim.cpp
#include "stdafx.h"
#include "math_functions.h"
#include <iostream>

const double PI = 3.141592653589793238463;

int single_bullet_sim(double spread_radius, double spread_position_x, double spread_position_y, double target_position_x, double target_position_y)
{
	double shot_angle;
	double shot_radius;
	double dist_betw_circles;
	double h;
	double result;
	shot_radius = random_number(0, spread_radius);
	/*std::cout << "shot radius: ";
	std::cout << shot_radius << std::endl;*/
	shot_angle = random_number(0, 359.9999999999999);
	dist_betw_circles = dist_betw_points(spread_position_x, spread_position_y, target_position_x, target_position_y);
	/*std::cout << "shot angle: ";
	std::cout << shot_angle << std::endl;*/
	h = tan(shot_angle * (PI / 180)) * shot_radius;
	//std::cout << "h: " << h << std::endl;
	return h;
}