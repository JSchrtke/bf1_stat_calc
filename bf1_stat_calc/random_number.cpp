﻿//random_number.cpp
#include "stdafx.h"
#include "random_number.h"
#include <iostream>
#include <random>

double random_number(double rand_num_min, double rand_num_max)
{
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_real_distribution<> dis(rand_num_min, rand_num_max);
	double rand_double = dis(gen);
	return rand_double;
}
