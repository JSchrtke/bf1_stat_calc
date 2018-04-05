//single_bullet_sim.cpp
/*
Note: if shot_radius <= spread_radius && target_to_shot_radius <= target_radius
	{
		the shot is in the intersection between the circles
	}
*/
/*
TO DO:
- put in cases for 0, 180 and 360°
*/
#include "stdafx.h"
#include "math_functions.h"
#include <iostream>

const double PI = 3.141592653589793238463;

int single_bullet_sim(double spread_radius, double spread_position_x, double spread_position_y, double target_position_x, double target_position_y, double target_radius)
{
	double shot_angle; //random angle to determine position of shot within the spread circle
	double shot_radius; //random radius to determine position of shot within spread circle
	double target_to_shot_radius; //distance from the center of the target circle to the point of the randonly picked shot
	double dist_betw_circles; //determines the distance between th centers of the two circles
	double h; //height of the triangle formed by connecting the point of the shot with the centers of the circles
	double result; //determines if the shot hits/misses 1 = hit, 0 = miss

	shot_radius = (sqrt(random_number(0, 1))) * spread_radius;
	shot_angle = random_number(0, 359.9999999999999);
	dist_betw_circles = dist_betw_points(spread_position_x, spread_position_y, target_position_x, target_position_y);
	h = tan(shot_angle * (PI / 180)) * shot_radius;
	target_to_shot_radius = sqrt((dist_betw_circles - sqrt(shot_radius * shot_radius + h * h) * (dist_betw_circles - sqrt(shot_radius * shot_radius + h * h))) + (h * h));
	if (shot_radius <= spread_radius && target_to_shot_radius <= target_radius)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}