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
    //std::cout << "spread: " << std::endl;
    //std::cin >> spread;
    std::cout << "spread_ads_stand_not_move: " << std::endl;
    std::cin >> spread_ads_stand_not_move;
    std::cout << "spread_ads_stand_move: " << std::endl;
    std::cin >> spread_ads_stand_move;
    std::cout << "spread_hip_stand_not_move: " << std::endl;
    std::cin >> spread_hip_stand_not_move;
    std::cout << "spread_hip_crouch_not_move: " << std::endl;
    std::cin >> spread_hip_crouch_not_move;
    std::cout << "spread_hip_prone_not_move: " << std::endl;
    std::cin >> spread_hip_prone_not_move;
    std::cout << "spread_hip_stand_move: " << std::endl;
    std::cin >> spread_hip_stand_move;
    std::cout << "spread_hip_crouch_move: " << std::endl;
    std::cin >> spread_hip_crouch_move;
    std::cout << "spread_hip_prone_move: " << std::endl;
    std::cin >> spread_hip_prone_move;
    std::cout << "spread_max: " << std::endl;
    std::cin >> spread_max;

    //converts the stat for left hrec to a negative number
    if ( hrec_l > 0 ) {
        hrec_l = hrec_l * -1;
    }
}

void bf1::changeStance() {
    std::cout << "enter desired aim state:" << std::endl;
    std::cout << "1: ADS" << std::endl;
    std::cout << "2: HIP" << std::endl;
    std::cin >> desired_aim;
    std::cout << "Enter desired movement state:" << std::endl;
    std::cout << "1: not moving" << std::endl;
    std::cout << "2: moving" << std::endl;
    std::cin >> desired_movement_state;
    std::cout << "enter desired stance:" << std::endl;
    std::cout << "1: standing" << std::endl;
    std::cout << "2: crouching" << std::endl;
    std::cout << "3: prone" << std::endl;
    std::cin >> desired_stance;

    switch (desired_aim) {
        case 1 : //ADS
            switch (desired_movement_state) {
                case 1: //ADS, nmove
                    spread = spread_ads_stand_not_move;
                    break;
                case 2: //ADS, move
                    spread = spread_ads_stand_move;
                    break;
                default:break;
            }
            break;
        case 2: //HIP
            switch  (desired_movement_state) {
                case 1: //HIP, nmove
                    switch (desired_stance) {
                        case 1: //HIP, nmove, stand
                            spread = spread_hip_stand_not_move;
                            break;
                        case 2: //HIP, nmove, crouch
                            spread = spread_hip_crouch_not_move;
                            break;
                    case 3: //HIP, nmove, prone
                            spread = spread_hip_prone_not_move;
                            break;
                        default:break;
                    }
                case 2: //HIP, move
                    switch (desired_stance) {
                        case 1: //HIP, move, stand
                            spread = spread_hip_stand_move;
                            break;
                        case 2: // HIP , move, crouch
                            spread = spread_hip_crouch_move;
                            break;
                        case 3: //HIP, move, prone
                            spread = spread_hip_prone_move;
                            break;
                        default:break;
                    }
                default:break;
            }
            break;
        default:break;
    }
}