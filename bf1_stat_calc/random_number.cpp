﻿//random_number.cpp
//this function generates a random number, currently int
//TO DO: MAKE THIS GENERATE A double
#include "stdafx.h"
#include "random_number.h"
#include <iostream>
#include <ctime>



int random_number(int random_number_max)
{
	srand(time(NULL));
	int rand_int;
	rand_int = rand() % random_number_max + 1;
	return rand_int;
}