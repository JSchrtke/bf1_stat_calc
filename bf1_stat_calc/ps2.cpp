#include <iostream>
#include <vector>
#include <string>
#include "ps2.h"

void ps2::simulation(double target_position_x, double target_position_y, double target_radius,
                     double spread_position_x, double spread_position_y, double spread_radius, int hitrate_sim_count,
                     unsigned long long int burst_length, double weapon_stats[], double distance) {

    int sim_counter = 0;
    double current_spread_angle = weapon_stats[10];
    double hrec_magnitude;
    std::vector<double> shots_in_burst;
    shots_in_burst.resize(burst_length);

    for ( int i = 0;
          i < hitrate_sim_count; i++ ) //this loop simulates the hitrate for the # specified by user input
    {
        double hrec_tol_check = 0;
        int hrec_l_r = 0;
        double rand_double = 0;
        spread_radius = offset(distance, weapon_stats[10]);
        for ( int j = 0; j < burst_length; j++ ) //this loop simulates the hitrate for each bullet in the given
            // burst length, then stores the value in the array (shots_in_burst)
        {
            hrec_magnitude = random_number_double(weapon_stats[5], weapon_stats[4]);
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
            shots_in_burst[j] = shots_in_burst[j] + single_bullet_sim (target_position_x, target_position_y,
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

            } else if ( current_spread_angle >= weapon_stats[18] || current_spread_angle <= weapon_stats[10] ) {
                spread_radius = spread_radius;

            } else {
                spread_radius = spread_radius + offset(distance,
                                                       weapon_stats[6]); /*increases spread_radius due to
                                                                                * spread increase per shot*/
                current_spread_angle = current_spread_angle + weapon_stats[6];
            }
        }
        sim_counter++;
        spread_position_x = 0.0;
        current_spread_angle = weapon_stats[10];
        hrec_tol_check = 0.0;
    }
    std::cout << "final results" << std::endl;
    for ( int k = 0; k < burst_length; k++ ) {
        shots_in_burst[k] = shots_in_burst[k] / sim_counter;
        std::cout << "shot #";
        std::cout << k + 1;
        std::cout << ": ";
        std::cout << shots_in_burst[k] * 100;
        std::cout << " %" << std::endl;
    }

    //resets the shots_in_burst array after printing the results
    for ( int k = 0; k < burst_length; k++ ) {
        shots_in_burst[k] = 0;
    }
    sim_counter = 0;
}

void ps2::stat_input(double *weapon_stats, std::string *weapon_stat_names) {
    std::cout << "Please enter the weapon stats" << std::endl;
    for ( int i = 0; i <= 19; i++ ) {
        std::cout << weapon_stat_names[i];
        std::cin >> weapon_stats[i];
    }
}