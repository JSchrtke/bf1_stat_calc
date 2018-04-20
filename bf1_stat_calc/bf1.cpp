#include <iostream>
#include <vector>
#include "bf1.h"

void bf1::simulation(double target_position_x, double target_position_y, double target_radius,
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
        spread_radius = offset(distance, weapon_stats[10]);
        for ( int j = 0; j < burst_length; j++ ) //this loop simulates the hitrate for each bullet in the given
            // burst length, then stores the value in the array (shots_in_burst)
        {
            hrec_magnitude = random_number_double(weapon_stats[5], weapon_stats[4]);
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