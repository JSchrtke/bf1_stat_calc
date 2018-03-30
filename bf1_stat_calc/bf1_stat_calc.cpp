// bf1_stat_calc.cpp
/*
TO DO:
*/
#include "stdafx.h"
#include "random_number.h"
#include "dist_betw_points.h"
#include <iostream>

int main()
{
	//x/y coordinates of the center of the target
	double target_position_x = 0.0;
	double target_postion_y = 0.0;
	
	//radius of the target circle
	double target_radius = 1.0;
	
	//x/y coordinates of the center of the spread
	double spread_postion_x = 1.0;
	double spread_postion_y = 1.0;
	
	//radius of the spread
	double spread_radius = 1.0;

	double dist_betw_circle;
	//min/max number for random number generator, generates random double between those
	double rand_num_min = 0.0;
	double rand_num_max = 1.0;

	std::cout << dist_betw_points(target_position_x, target_postion_y, spread_postion_x, spread_postion_y) << std::endl;
	std::cout << random_number(rand_num_min, rand_num_max) << std::endl;
	return 0;
}
