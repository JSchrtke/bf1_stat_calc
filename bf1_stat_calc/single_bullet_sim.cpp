//single_bullet_sim.cpp
/*
TO DO:
*/
#include "stdafx.h"
#include "math_functions.h"
#include <iostream>
#include <cmath>

const double PI = 3.141592653589793238463;

double single_bullet_sim(double target_position_x, double target_position_y,double target_radius,
	double spread_position_x, double spread_position_y, double spread_radius)
{
	double result;
	double dist_circles = dist_betw_points(target_position_x, target_position_y, spread_position_x, spread_position_y);
	double d_1;
	double d_2;
	double t_r_sq = target_radius * target_radius;
	double s_r_sq = spread_radius * spread_radius;
	double d_c_sq = dist_circles * dist_circles;
	double intersect_area;
	double hit_miss; //hitchance
	if (dist_circles <= target_radius && dist_circles + spread_radius <= target_radius)
	{
		std::cout << "hit_miss should be 1; dist_circles <= target_radius && dist_circles + spread_radius <= target_radius" << std::endl;
		hit_miss = 1;
	}
	else if (dist_circles > target_radius && target_radius + spread_radius >= dist_circles)
	{
		std::cout << "hit_miss should be 0; dist_circles > target_radius && target_radius + spread_radius >= dist_circles" << std::endl;
		hit_miss = 0;
	}
	else if (spread_radius >= target_radius && dist_circles + target_radius <= spread_radius)
	{
		std::cout << "hit_miss determined by t_r_sq / s_r_sq; spread_radius >= target_radius && dist_circles + target_radius <= spread_radius" << std::endl;
		hit_miss = t_r_sq / s_r_sq;
	}
	else
	{
		std::cout << "hit miss calculated by maths (4th case)"; //debug line, remove when functional
		intersect_area = s_r_sq * acos((d_c_sq + s_r_sq - t_r_sq) / (2 * dist_circles * spread_radius)) +
			t_r_sq * acos((d_c_sq + t_r_sq - s_r_sq) / (2 * dist_circles * target_radius)) -
			0.5 * sqrt((-dist_circles + spread_radius + target_radius) *
			(dist_circles + spread_radius - target_radius) *
				(dist_circles - spread_radius + target_radius) *
				(dist_circles + spread_radius + target_radius));

		hit_miss = intersect_area / (PI * s_r_sq);
	}
	return hit_miss;
}