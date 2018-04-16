// bf1_stat_calc.cpp
/*
TODO need to add stat changes dues to hip/ads
TODO add stat changes due to stances
TODO shots_in_burst and results arrays need to be dynamic in length
	TODO *probably use vectors for this
*/
#include "stdafx.h"
#include "math_functions.h"
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
//#define DEBUG
//#define DEBUG_EXEC_TIME
//#define MANUAL_STAT_INPUT
//#define PS2_RECOIL
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
    weapon_stats[7] = 10; //fssm ads
    weapon_stats[8] = 1; //fssm hip
    weapon_stats[9] = 3; //spread decrease
    weapon_stats[10] = 0.0; //spread ads not moving
    weapon_stats[11] = 0.82; //spread ads moving
    weapon_stats[12] = 1; //spread hip standing not moving
    weapon_stats[13] = 0.75; //spread hip crouch not moving
    weapon_stats[14] = 0.5; //spread hip prone not moving
    weapon_stats[15] = 1.5; //spread hip standing moving
    weapon_stats[16] = 1.2; //spread hip crouch moving
    weapon_stats[17] = 0.9; //spread hip prone moving
    weapon_stats[18] = 7.0; //max spread
#ifdef PS2_RECOIL
    weapon_stats[19] = 0;
#endif
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
    double spread_radius;
    //magnitude of hrec, this is a random number between hrec_l and hrec_r
    double hrec_magnitude;
    //variables for controlling if the main loop is running
    bool main_loop_running = true;
    //variable for the loop that allows to continue or quit the program
    char continue_quit_loop = 'y';
    //variable to specify how many times the simulation runs
    int hitrate_sim_count = 1;
    /*array for storing the results of individual bullets that hit/miss in a burst;
     * first index = sim runs, second = shots in the burst*/
    vector<vector<double>> shots_in_burst;
    //vector that stores the results
    vector<double> results;
    //stores burst length
    int burst_length = 5;
    //counts the # of sim runs
    int sim_counter = 0;
    //checks if the the hrec_magnitude exceeds the hrec_tolerance(for PS2)
#ifdef PS2_RECOIL
    double hrec_tol_check = 0;
#endif // !PS2_RECOIL
    //determines if the hrec goes left/right (for PS2)
    int hrec_l_r = 0;
    double rand_double = 0;
    // variable for checking if the max spread has been reached
    double current_spread_angle = weapon_stats[10];

#ifdef DEBUG
    cout << "DEBUG MODE ON" << endl;
#endif // !DEBUG

#ifdef MANUAL_STAT_INPUT
    //manual weapon stat input
    cout << "Please enter the weapon stats" << endl;
    for ( int i = 0; i <= 18; i++ ) {
        cout << weapon_stat_names[i];
        cin >> weapon_stats[i];
    }
#ifdef PS2_RECOIL
    cout << weapon_stat_names[19];
    cin >> weapon_stats[19];
#endif // PS2_RECOIL

#endif // !MANUAL_STAT_INPUT


#ifndef PS2_RECOIL
    //converts the stat for left hrec to a negative number
    if ( weapon_stats[5] > 0 ) {
        weapon_stats[5] = weapon_stats[5] * -1;
    }
#endif // !PS2_RECOIL

#ifdef DEBUG
    cout << "DEBUG: weapon_stats[5]: " << weapon_stat_names[5] << weapon_stats[5] << endl;
#endif // !DEBUG

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

#ifdef DEBUG_EXEC_TIME
        auto start_exec_timer = chrono::steady_clock::now();
        cout << "DEBUG: started execution timer" << endl;
#endif // !DEBUG_EXEC_TIME
        shots_in_burst.resize(hitrate_sim_count, vector<double>(burst_length));
        //first iteration of what will be the main simulation loop
        for ( int i = 0;
              i < hitrate_sim_count; i++ ) //this loop simulates the hitrate for the # specified by user input
        {
            spread_radius = offset(distance, weapon_stats[10]);
            for ( int j = 0; j < burst_length; j++ ) //this loop simulates the hitrate for each bullet in the given
                                                    // burst length, then stores the value in the array (shots_in_burst)
            {
                if ( j >= 50 ) { //this needs to be the size of shots_in_burst, so the code doesnt break

                    break;
                } else {
                    hrec_magnitude = random_number_double(weapon_stats[5], weapon_stats[4]);
#ifdef PS2_RECOIL
                    if (hrec_tol_check <= (weapon_stats[19] * -1))
                    {
                        hrec_l_r = 1;
                    }
                    else if (hrec_tol_check >= weapon_stats[19])
                    {
                        hrec_l_r = -1;
                    }
                    else
                    {
                        while (rand_double == 0)
                        {
                            rand_double = random_number_double(-1, 1);
                            if (rand_double < 0)
                            {
                                hrec_l_r = -1;
                            }
                            else if (rand_double > 0)
                            {
                                hrec_l_r = 1;
                            }
                            else
                            {
                                rand_double = 0;
                            }
                        }
                    }
                    rand_double = 0;
                    hrec_magnitude = hrec_magnitude * hrec_l_r;
                    hrec_tol_check = hrec_tol_check + hrec_magnitude;
#endif // !PS2_RECOIL
                    shots_in_burst[sim_counter][j] = single_bullet_sim(target_position_x, target_position_y,
                                                                       target_radius,
                                                                       spread_position_x, spread_position_y,
                                                                       spread_radius);

                    spread_position_x = spread_position_x + offset(distance,
                                                                   hrec_magnitude); // offsets spread_position_x due
                                                                                    // to horizontal recoil

                    if ( j == 0 ) {
                        spread_radius = spread_radius + offset(distance, weapon_stats[6] *
                                                                         weapon_stats[7]);  // increases spread_radius
                                                                                            // using fssm
                        current_spread_angle = current_spread_angle + weapon_stats[6] * weapon_stats[7];
                    } else if ( current_spread_angle >= weapon_stats[18] || current_spread_angle <= weapon_stats[10]) {
                        spread_radius = spread_radius;
                    } else {
                        spread_radius = spread_radius + offset(distance,
                                                               weapon_stats[6]); /*increases spread_radius due to
                                                                                    * spread increase per shot*/
                        current_spread_angle = current_spread_angle + weapon_stats[6];
                    }
                }
            }
            sim_counter++;
            spread_position_x = 0.0;
            current_spread_angle = weapon_stats[10];
#ifdef PS2_RECOIL
            hrec_tol_check = 0.0;
#endif // !PS2_RECOIL
        }
        /*adds up all the results from the sim runs and stores them in the results array*/
        results.resize(static_cast<unsigned long long int>(burst_length));
        for ( int l = 0; l < sim_counter; l++ ) {
            for ( int k = 0; k < burst_length; k++ ) {
                results[k] = results[k] + shots_in_burst[l][k];
            }
        }
        for ( int k = 0; k < burst_length; k++ ) {
            results[k] = results[k] / sim_counter;
        }

        //prints the final results
        cout << "final results" << endl;
        for ( int k = 0; k < burst_length; k++ ) {
            cout << "shot #";
            cout << k + 1;
            cout << ": ";
            cout << results[k] * 100;
            cout << " %" << endl;
        }

        //resets the results array after printing the results
        for ( int k = 0; k < burst_length; k++ ) {
            results[k] = 0;
        }
        sim_counter = 0;

#ifdef DEBUG_EXEC_TIME
        auto end_exec_timer = chrono::steady_clock::now();
        auto exec_time = end_exec_timer - start_exec_timer;
        cout << "execution time of main loops: " << chrono::duration <double, milli>(exec_time).count() << " ms" << endl;
#endif //!DEBUG_EXEC_TIME

        // this loop just controls if the user wants to quit
        while ( continue_quit_loop == 'y' || continue_quit_loop == 'Y' ) {
            cout << "do you want to continue? (Y/N)" << endl;
            cin >> continue_quit_loop;
            switch ( continue_quit_loop ) {
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