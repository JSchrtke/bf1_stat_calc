#include <iostream>
#include <vector>
#include <string>
#include "ps2.h"

void ps2::simulation()
{

    int sim_counter = 0;
    double current_spread_angle = spread;
    double hrec_magnitude;
    std::vector<double> shots_in_burst;
    shots_in_burst.resize(burst_length);

    for ( int i = 0;
          i <
          hitrate_sim_count; i++ ) //this loop simulates the hitrate for the # specified by user input
    {
        double hrec_tol_check = 0;
        int hrec_l_r = 0;
        double rand_double = 0;
        spread_radius = offset(distance, spread);
        for ( int j = 0; j <
                         burst_length; j++ ) //this loop simulates the hitrate for each bullet in the given
            // burst length, then stores the value in the array (shots_in_burst)
        {
            hrec_magnitude = random_number_double(hrec_min, hrec_max);
            if ( hrec_tol_check <= (hrec_tol * -1))
            {
                hrec_l_r = 1;
            }
            else if ( hrec_tol_check >= hrec_tol )
            {
                hrec_l_r = -1;
            }
            else
            {
                while ( rand_double == 0 )
                {
                    rand_double = random_number_double(-1, 1);
                    if ( rand_double < 0 )
                    {
                        hrec_l_r = -1;
                    }
                    else if ( rand_double > 0 )
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
            shots_in_burst[j] = shots_in_burst[j] + single_bullet_sim();

            spread_position_x = spread_position_x + offset(distance,
                                                           hrec_magnitude); // offsets spread_position_x due
            // to horizontal recoil

            if ( j == 0 )
            {
                spread_radius = spread_radius + offset(distance, sips *
                                                                 fssm);  // increases spread_radius
                // using fssm
                current_spread_angle = current_spread_angle + sips * fssm;

            }
            else if ( current_spread_angle >= spread_max ||
                      current_spread_angle <= spread )
            {
                spread_radius = spread_radius;

            }
            else
            {
                spread_radius = spread_radius + offset(distance,
                                                       sips); /*increases spread_radius due to
                                                                                * spread increase per shot*/
                current_spread_angle = current_spread_angle + sips;
            }
        }
        sim_counter++;
        spread_position_x = 0.0;
        current_spread_angle = spread;
        hrec_tol_check = 0.0;
    }
    std::cout << "final results" << std::endl;
    for ( int k = 0; k < burst_length; k++ )
    {
        shots_in_burst[k] = shots_in_burst[k] / sim_counter;
        std::cout << "shot #";
        std::cout << k + 1;
        std::cout << ": ";
        std::cout << shots_in_burst[k] * 100;
        std::cout << " %" << std::endl;
    }

    //resets the shots_in_burst array after printing the results
    for ( int k = 0; k < burst_length; k++ )
    {
        shots_in_burst[k] = 0;
    }
    sim_counter = 0;
}

void ps2::stat_input()
{
    std::cout << "hrec_min: " << std::endl;
    std::cin >> hrec_min;
    std::cout << "hrec_max: " << std::endl;
    std::cin >> hrec_max;
    std::cout << "hrec_tol: " << std::endl;
    std::cin >> hrec_tol;
    std::cout << "sips: " << std::endl;
    std::cin >> sips;
    std::cout << "spread: " << std::endl;
    std::cin >> spread;
    std::cout << "spread_max: " << std::endl;
    std::cin >> spread_max;
}