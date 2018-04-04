// bf1_stat_calc.cpp
/*
TO DO:
-make the function to calculate the hitrate for each individual bullet in a burst
*/
#include "stdafx.h"
#include "math_functions.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	//weapon stat array
	double weapon_stats[18];
	weapon_stats[0] = 359; //Firerate
	weapon_stats[1] = 660; //Muzzle Velocity
	weapon_stats[2] = 5; //mag size
	weapon_stats[3] = 0.7; //deploy time
	weapon_stats[4] = 0.15; //hrec right
	weapon_stats[5] = -0.15; //hrec left
	weapon_stats[6] = 0.062; //SIPS
	weapon_stats[7] = 1; //fssm ads
	weapon_stats[8] = 1; //fssm hip
	weapon_stats[9] = 3.75; //spread decrease
	weapon_stats[10] = 0.12; //spread ads not moving
	weapon_stats[11] = 0.82; //spread ads moving
	weapon_stats[12] = 2; //spread hip standing not moving
	weapon_stats[13] = 1.5; //spread hip crouch not moving
	weapon_stats[14] = 1; //spread hip prone not moving
	weapon_stats[15] = 2.5; //spread hip standing moving
	weapon_stats[16] = 2; //spread hip crouch moving
	weapon_stats[17] = 1.5; //spread hip prone moving
	//weapon stat name array
	string weapon_stat_names[18];
	weapon_stat_names[0] = "Firerate: ";
	weapon_stat_names[1] = "Muzzle velocity: ";
	weapon_stat_names[2] = "mag size: ";
	weapon_stat_names[3] = "deploy time: ";
	weapon_stat_names[4] = "hrec right: ";
	weapon_stat_names[5] = "hrec left: ";
	weapon_stat_names[6] = "sips: ";
	weapon_stat_names[7] = "fssm ads: ";
	weapon_stat_names[8] = "fssm hip: ";
	weapon_stat_names[9] = "spread decrease: ";
	weapon_stat_names[10] = "spread ads not moving: ";
	weapon_stat_names[11] = "spread ads moving: ";
	weapon_stat_names[12] = "spread hip stand not moving: ";
	weapon_stat_names[13] = "spread hip crouch not moving: ";
	weapon_stat_names[14] = "spread hip prone not moving: ";
	weapon_stat_names[15] = "spread hip standing moving: ";
	weapon_stat_names[16] = "spread hip crouch moving: ";
	weapon_stat_names[17] = "spread hip prone moving: ";
	//x/y coordinates of the center of the target
	double target_position_x = -0.0;
	double target_postion_y = -0.0;	
	//radius of the target circle
	double target_radius = 0.25;	
	//x/y coordinates of the center of the spread
	double spread_postion_x = 0.0;
	double spread_postion_y = 0.0;	
	//radius of the spread
	double spread_radius = 0.0;
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
	//array for individual bullets that hit/miss in a burst
	int shots_in_burst[50];
	//stores burst lenght
	int burst_lenght = 5;

	//main program loop
	while (main_loop_running)
	{
		cout << "enter burst length: " << endl;
		cin >> burst_lenght;
		cout << "how many times do you want to simluate hitrate" << endl;
		cin >> hitrate_sim_count; //this user input need to be sanitized, probably write function to do that

		//first iteration of what will be the main simulation loop
		for (int i = 0; i < hitrate_sim_count; i++) //this loop simluates the hitrate for the # specified by user input
		{
			for (int j = 0; j < burst_lenght; j++) //this loop simulates the hitrate for each bullet in the given burst length, then stores the value in the array (shots_in_burst)
			{
				if (j >= 50) //this needs to be the size of shots_in_burst, so the code doesnt break
				{
					break;
				}
				else
				{	
					hrec_magnitude = random_number(weapon_stats[5], weapon_stats[4]);
					shots_in_burst[j] = 1; //function for single shot sim goes here, instead of 1
					single_bullet_sim(spread_radius, spread_postion_x, spread_postion_y, target_position_x, target_postion_y);
					spread_postion_x = spread_postion_x + hrec(distance, hrec_magnitude);
					spread_radius = spread_radius + weapon_stats[6];
					cout << "spread_postion_x: " << spread_postion_x << endl;
					cout << "spread_radius: " << spread_radius << endl;
				}
			}
			spread_postion_x = 0.0;
			spread_radius = 0.0;
		}
		
		//prints the results, as in the # of the shot in the burst and if it hit
		//1 = hit, 0 = miss
		cout << "Results: " << endl;
		for (int k = 0; k < burst_lenght; k++)
		{
			cout << "shot #";
			cout << k + 1;
			cout << ": ";
			cout << shots_in_burst[k] << endl;
		}

		// this loop just controls if the user wants to quit
		while (continue_quit_loop == 'y' || continue_quit_loop == 'Y')
		{
			cout << "do you want to continue? (Y/N)" << endl;
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