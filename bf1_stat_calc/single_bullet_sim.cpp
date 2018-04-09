//single_bullet_sim.cpp
#include "stdafx.h"
#include "math_functions.h"
#include <iostream>
#include <cmath>
//#define DEBUG

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
		hit_miss = 1;
	}
	else if (dist_circles > target_radius && target_radius + spread_radius <= dist_circles)
	{
		hit_miss = 0;
	}
	else if (spread_radius >= target_radius && dist_circles + target_radius <= spread_radius)
	{
		hit_miss = t_r_sq / s_r_sq;
	}
	else
	{
#ifdef DEBUG
		if ((-dist_circles + spread_radius + target_radius) *
			(dist_circles + spread_radius - target_radius) *
			(dist_circles - spread_radius + target_radius) *
			(dist_circles + spread_radius + target_radius) < 0)
		{
			std::cout << "sqrt of negative number!" << std::endl;
			std::cout << (-dist_circles + spread_radius + target_radius) *
				(dist_circles + spread_radius - target_radius) *
				(dist_circles - spread_radius + target_radius) *
				(dist_circles + spread_radius + target_radius) << std::endl;
			std::cout << "target_pos_x: " << target_position_x << std::endl;
			std::cout << "target_radius: " << target_radius << std::endl;
			std::cout << "spread_pos_x: " << spread_position_x << std::endl;
			std::cout << "spread_radius: " << spread_radius << std::endl;
			std::cout << "dist_circles: " << dist_circles << std::endl;
			hit_miss = 0;
		}
		else
		{
#endif //DEBUG
			intersect_area = s_r_sq * acos((d_c_sq + s_r_sq - t_r_sq) / (2 * dist_circles * spread_radius)) +
				t_r_sq * acos((d_c_sq + t_r_sq - s_r_sq) / (2 * dist_circles * target_radius)) -
				0.5 * sqrt((-dist_circles + spread_radius + target_radius) *
				(dist_circles + spread_radius - target_radius) *
					(dist_circles - spread_radius + target_radius) *
					(dist_circles + spread_radius + target_radius));
			hit_miss = intersect_area / (PI * s_r_sq);
#ifdef DEBUG
		}
#endif // DEBUG

	}
	return hit_miss;
}