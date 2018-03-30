// bf1_stat_calc.cpp
/*
TO DO:
- Figure out how to make random_number_max a double without messing up the
 random_number function
*/
#include "stdafx.h"
#include "random_number.h"
#include <iostream>
#include <ctime>

int main()
{
	int random_number_max; /*maximum number for the random_number function;
													it generates a number from 0 to this value*/
	std::cin >> random_number_max;
	std::cout << random_number(random_number_max) << std::endl;
    return 0;
}
