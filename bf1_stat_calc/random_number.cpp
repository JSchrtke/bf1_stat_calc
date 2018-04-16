//random_number.cpp
#include "stdafx.h"
#include "math_functions.h"
#include <iostream>
#include <random>
#include <chrono>

double random_number_double(double rand_num_min, double rand_num_max)
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(rand_num_min, rand_num_max);
    double rand_double = dist(gen);
    return rand_double;
}