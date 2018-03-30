// bf1_stat_calc.cpp
#include "stdafx.h"
#include "random_number.h"
#include <iostream>
#include <ctime>

int main()
{	
	int random_number_max;
	std::cin >> random_number_max;
	std::cout << random_number(random_number_max) << std::endl;
    return 0;
}