﻿// bf1_stat_calc.cpp
/*
TODO Make weapon stats into a class
TODO Make manual stat input a separate function, probably tied to the individual game class
TODO Integrate conversion to negative number for hrec_left into the BF1 class
TODO FIGURE OUT A WAY TO HANDLE STANCES
*/
#include "stdafx.h"
#include "bf1.h"
#include "ps2.h"
#include "continue_quit_function.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    //weapon stat array
    double weapon_stats[20];
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
    weapon_stats[18] = 1.2; //max spread
    weapon_stats[19] = 0;

    //weapon stat name array
    string weapon_stat_names[20];
    weapon_stat_names[0] = "Firerate: ";
    weapon_stat_names[1] = "Muzzle velocity: ";
    weapon_stat_names[2] = "mag size: ";
    weapon_stat_names[3] = "deploy time: ";
    weapon_stat_names[4] = "hrec right(max): ";
    weapon_stat_names[5] = "hrec left(min): ";
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
    weapon_stat_names[18] = "max spread: ";
    weapon_stat_names[19] = "hrec tolerance: ";
    //x/y coordinates of the center of the target
    double target_position_x = 0.0;
    double target_position_y = 0.0;
    //radius of the target circle
    double target_radius = 0.25;
    //x/y coordinates of the center of the spread
    double spread_position_x = 0.0;
    double spread_position_y = 0.0;
    //distance to target
    double distance = 30.0;
    //radius of the spread
    double spread_radius = 0;
    //magnitude of hrec, this is a random number between hrec_l and hrec_r
    double hrec_magnitude;
    //variables for controlling if the main loop is running
    bool main_loop_running = true;
    //variable for the loop that allows to continue or quit the program
    char continue_quit_loop = 'y';
    //variable to specify how many times the simulation runs
    int hitrate_sim_count = 1;
    //stores burst length
    unsigned long long int burst_length = 5;
    //variable to choose the game
    int game_choice = 0;

    //game choice
    cout << "choose the game:\n";
    cout << "0: BF1\n";
    cout << "1: PS2" << endl;
    cin >> game_choice;

    if (game_choice == 0) {

        cout << "you chose BF1" << endl;
        bf1 bf1_sim;

        //manual weapon stat input
        bf1_sim.stat_input(weapon_stats, weapon_stat_names);

        //converts the stat for left hrec to a negative number
        if ( weapon_stats[5] > 0 ) {
            weapon_stats[5] = weapon_stats[5] * -1;
        }

        //main program loop
        while ( main_loop_running ) {
            cout << "enter the distance: ";
            cin >> distance;
            cout << "enter the target size(radius in m): ";
            cin >> target_radius;
            cout << "enter burst length: ";
            cin >> burst_length;
            cout << "enter simulation run count: ";
            cin >> hitrate_sim_count;

            bf1_sim.simulation(target_position_x, target_position_y, target_radius,
                               spread_position_x, spread_position_y, spread_radius,
                               hitrate_sim_count, burst_length, weapon_stats, distance);

            main_loop_running = cont_quit();
        }
        return 0;
    }
    else if (game_choice == 1) {
        cout << "you chose PS2" << endl;
        ps2 ps2_sim;

        //manual weapon stat input
        ps2_sim.stat_input(weapon_stats, weapon_stat_names);

        //main program loop
        while ( main_loop_running ) {
            cout << "enter the distance: ";
            cin >> distance;
            cout << "enter the target size(radius in m): ";
            cin >> target_radius;
            cout << "enter burst length: ";
            cin >> burst_length;
            cout << "enter simulation run count: ";
            cin >> hitrate_sim_count;

            ps2_sim.simulation(target_position_x, target_position_y, target_radius,
                               spread_position_x, spread_position_y, spread_radius,
                               hitrate_sim_count, burst_length, weapon_stats, distance);
            main_loop_running = cont_quit();
        }
        return 0;
    }
    else {
        cout << "Error! you must choose a game!";
    }
}