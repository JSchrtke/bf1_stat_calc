#include <iostream>
#include <vector>
#include <string>
#include "bf1.h"

void bf1::simulation() {

    int sim_counter = 0;
    double current_spread_angle = spread;
    double hrec_magnitude;
    std::vector<double> shots_in_burst;
    shots_in_burst.resize(burst_length);

    for ( int i = 0;
          i < hitrate_sim_count; i++ ) //this loop simulates the hitrate for the # specified by user input
    {
        spread_radius = offset(distance, spread);
    for ( int j = 0; j < burst_length; j++) //this loop simulates the hitrate for each bullet in the given
            // burst length, then stores the value in the array (shots_in_burst)
        {
            hrec_magnitude = random_number_double(hrec_l, hrec_r);
            shots_in_burst[j] = shots_in_burst[j] + single_bullet_sim ();

            spread_position_x = spread_position_x + offset(distance,
                                                           hrec_magnitude); // offsets spread_position_x due
            // to horizontal recoil

            if ( j == 0 ) {
                spread_radius = spread_radius + offset(distance, sips *
                                                                 fssm);  // increases spread_radius
                // using fssm
                current_spread_angle = current_spread_angle + sips * fssm;

            } else if ( current_spread_angle >= spread_max || current_spread_angle <= spread ) {
                spread_radius = spread_radius;

            } else {
                spread_radius = spread_radius + offset(distance,
                                                       sips); /*increases spread_radius due to
                                                                                * spread increase per shot*/
                current_spread_angle = current_spread_angle + sips;
            }
        }
        sim_counter++;
        spread_position_x = 0.0;
        current_spread_angle = spread;

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

void bf1::stat_input() {
    std::cout << "hrec_l: " << std::endl;
    std::cin >> hrec_l;
    std::cout << "hrec_r: " << std::endl;
    std::cin >> hrec_r;
    std::cout << "fssm: " << std::endl;
    std::cin >> fssm;
    std::cout << "sips: " << std::endl;
    std::cin >> sips;
    std::cout << "spread: " << std::endl;
    std::cin >> spread;
    std::cout << "spread_max: " << std::endl;
    std::cin >> spread_max;

    //converts the stat for left hrec to a negative number
    if ( hrec_l > 0 ) {
        hrec_l = hrec_l * -1;
    }
}


//void bf1::stat_input(double weapon_stats[], std::string weapon_stat_names[]) {
//    std::cout << "Please enter the weapon stats" << std::endl;
//    for ( int i = 0; i <= 18; i++ ) {
//        std::cout << weapon_stat_names[i];
//        std::cin >> weapon_stats[i];
//    }
//}