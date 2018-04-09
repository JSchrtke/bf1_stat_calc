// bf1_stat_calc.cpp
/*
TO DO:
-needs to handle fssm
-add stat changes due to stances
-spread_radius variable calculation before the burst loop needs to have another variable so it can use stances
-sanitize user input for hitrate_sim_count
-shots_in_burst and results arrays need to be dynamic in lenght
	*probably use vectors for this
-needs to handle max spread size
-implement hrec mechanic for PS2
-need to add stat changes dues to hip/ads
-hrec_left (weapon_stats[5]) needs to be converted to a negative number
*/
#include "stdafx.h"
#include "math_functions.h"
#include <iostream>
#include <string>
//#define DEBUG
#define MANUAL_STAT_INPUT
using namespace std;

int main()
{
	//weapon stat array
	double weapon_stats[18];
	weapon_stats[0] = 299; //Firerate
	weapon_stats[1] = 700; //Muzzle Velocity
	weapon_stats[2] = 10; //mag size
	weapon_stats[3] = 0.7; //deploy time
	weapon_stats[4] = 0.4; //hrec right
	weapon_stats[5] = -0.4; //hrec left
	weapon_stats[6] = 0.1; //SIPS
	weapon_stats[7] = 1; //fssm ads
	weapon_stats[8] = 1; //fssm hip
	weapon_stats[9] = 3; //spread decrease
	weapon_stats[10] = 0.18; //spread ads not moving
	weapon_stats[11] = 0.82; //spread ads moving
	weapon_stats[12] = 1; //spread hip standing not moving
	weapon_stats[13] = 0.75; //spread hip crouch not moving
	weapon_stats[14] = 0.5; //spread hip prone not moving
	weapon_stats[15] = 1.5; //spread hip standing moving
	weapon_stats[16] = 1.2; //spread hip crouch moving
	weapon_stats[17] = 0.9; //spread hip prone moving
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
	double target_position_x = 0.0;
	double target_postion_y = 0.0;	
	//radius of the target circle
	double target_radius = 0.25;	
	//x/y coordinates of the center of the spread
	double spread_postion_x = 0.0;
	double spread_postion_y = 0.0;	
	//distance to target
	double distance = 30.0;
	//radius of the spread
	double spread_radius;
	//magnitude of hrec, this is a random number between hrec_l and hrec_r
	double hrec_magnitude;
	//variables for controlling if the main loop is running
	bool main_loop_running = true;
	//variable for the loop that allows to continue or quit the program
	char continue_quit_loop = 'y';
	//variable to specify how many times the simulation runs
	int hitrate_sim_count = 1;
	//array for storing the results of individual bullets that hit/miss in a burst; first index = sim runs, second = shots in the burst
	double shots_in_burst[2500][50];
	//array that stores the results
	double results[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	//stores burst lenght
	int burst_lenght = 5;
	//distance between the centers of the two circles
	double dist_circle;
	//counts the # of sim runs
	int sim_counter = 0;

	//manual weapon stat input
#ifdef MANUAL_STAT_INPUT
	cout << "Please enter the weapon stats" << endl;
	for (int i = 0; i <= 17; i++)
	{
		cout << weapon_stat_names[i];
		cin >> weapon_stats[i];
	}
#endif // MANUAL_STAT_INPUT

	//main program loop
	while (main_loop_running)
	{
		cout << "enter the distance: ";
		cin >> distance;
		cout << "enter burst length(max. 50): ";
		cin >> burst_lenght;
		cout << "enter simulation run count(max. 2500): ";
		cin >> hitrate_sim_count;

		//first iteration of what will be the main simulation loop
		for (int i = 0; i < hitrate_sim_count; i++) //this loop simluates the hitrate for the # specified by user input
		{
			spread_radius = offset(distance, weapon_stats[10]);
			for (int j = 0; j < burst_lenght; j++) //this loop simulates the hitrate for each bullet in the given burst length, then stores the value in the array (shots_in_burst)
			{
				if (j >= 50) //this needs to be the size of shots_in_burst, so the code doesnt break
				{
					break;

				}
				else
				{	
					hrec_magnitude = random_number(weapon_stats[5], weapon_stats[4]);
					shots_in_burst[sim_counter][j] = single_bullet_sim(target_position_x, target_postion_y, target_radius,
						spread_postion_x, spread_postion_y, spread_radius);
					spread_postion_x = spread_postion_x + offset(distance, hrec_magnitude);
					spread_radius = spread_radius + offset(distance, weapon_stats[6]);
				}
			}
			sim_counter++;
			spread_postion_x = 0.0;
			spread_radius = 0.0;
		}

		/*prints results for indivdual columns of the shots_in_burst array, for debug purpose;
		adds up all the results from the sim runs and stores them in the results array*/
		for (int l = 0; l < sim_counter; l++)
		{
			for (int k = 0; k < burst_lenght; k++)
			{
				results[k] = results[k] + shots_in_burst[l][k];
			}
		}
		for (int k = 0; k < burst_lenght; k++)
		{
			results[k] = results[k] / sim_counter;
		}

		//prints the final results
		cout << "final results" << endl;
		for (int k = 0; k < burst_lenght; k++)
		{
			cout << "shot #";
			cout << k + 1;
			cout << ": ";
			cout << results[k] * 100;
			cout << " %" << endl;
		}

		//resets the results array after printing the results
		for (int k = 0; k < burst_lenght; k++)
		{
			results[k] = 0;
		}
		sim_counter = 0;	

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
				cout << "Error!" << endl;
				break;
			}
		}
			continue_quit_loop = 'y';
	}
	return 0;
}