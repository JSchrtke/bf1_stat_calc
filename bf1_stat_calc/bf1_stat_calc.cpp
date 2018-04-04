// bf1_stat_calc.cpp
/*
TO DO:
*/
#include "stdafx.h"
#include "math_functions.h"
#include <iostream>
using namespace std;

int main()
{
	//Weapon stat variables
	int rpm = 359;
	int muz_vel = 660;
	int mag_size = 5;
	float deploy_time = 0.7;
	float hrec_r = 0.15;
	float hrec_l = -0.15;
	float sips = 0.062;
	float fssm_ads = 1;
	float fssm_hip = 1;
	float spread_dec = 3.75;
	float spread_ads_not_move = 0.12;
	float spread_ads_move = 0.82;
	float spread_hip_stand_not_move = 2;
	float spread_hip_crouch_not_move = 1.5;
	float spread_hip_prone_not_move = 1;
	float spread_hip_stand_move = 2.5;
	float spread_hip_crouch_move = 2;
	float spread_hip_prone_move = 1.5;

	//x/y coordinates of the center of the target
	double target_position_x = -0.0;
	double target_postion_y = -0.0;
	
	//radius of the target circle
	double target_radius = 1.0;
	
	//x/y coordinates of the center of the spread
	double spread_postion_x = 1.0;
	double spread_postion_y = 1.0;
	
	//radius of the spread
	double spread_radius = 1.0;

	//distance to target
	double distance = 10.0;

	//magnitude of hrec, this is a random number between hrec_l and hrec_r
	double hrec_magnitude;
	

	//variables for controlling if the main loop is running
	bool main_loop_running = true;

	//variable for the loop that allows to continue or quit the program
	char continue_quit_loop = 'y';

	//variable to specify how many times the simulation runs
	int hitrate_sim_count = 1;

	//variables for number of shots in burst USE ARRAYS FOR THIS!!!!!!
	int s_1 = 0;
	//main program loop
	while (main_loop_running)
	{
		hrec_magnitude = random_number(hrec_l, hrec_r);

		cout << "how many times do you want to simluate hitrate" << endl;
		cin >> hitrate_sim_count; //this user input need to be sanitized, probably write finction to do that

		for (int i = 0; i < hitrate_sim_count; i++)
		{
			s_1 = s_1 + 1; //function for single shot sim goes here, instead of 1
			spread_postion_x = spread_postion_x + hrec(distance, hrec_magnitude);
			//continues like this:
			//s_n = s_n + single shot function
			//spread_position_x = spread_position_x + hrec(distance, hrec_magnitude);
		}

		cout << "Results: " << endl;
		cout << "Debug info: s_1 = " << s_1 << "line 82, remove when done" << endl; //debug info, remove when done
		cout << "s_1: ";
		cout << (s_1 / hitrate_sim_count) * 100;
		cout << "%" << endl;

		// this loop just controls if the user wants to quit
		while (continue_quit_loop == 'y' || continue_quit_loop == 'Y')
		{
			cout << "do you wan to continue? (Y/N)" << endl;
			cin >> continue_quit_loop;
			switch (continue_quit_loop)
			{
			case 'y':
				main_loop_running = true;
				continue_quit_loop = 'x';
				break;
			case 'Y':
				main_loop_running = true;
				continue_quit_loop = 'x';
				break;
			case 'n':
				main_loop_running = false;
				continue_quit_loop = 'x';
				break;
			case 'N':
				main_loop_running = false;
				continue_quit_loop = 'x';
				break;
			default:
				cout << "Error! Debug info: continue_quit_loop, line 111, switch statement default case" << endl;
				break;
			}
		}
			continue_quit_loop = 'y';
	}
	return 0;
}