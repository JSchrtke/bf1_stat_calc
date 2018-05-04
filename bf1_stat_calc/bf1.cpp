#include <iostream>
#include <vector>
#include <string>
#include "bf1.h"

void Bf1::simulation()
{
    /* this variable stores how many times the simulation has run, this is used later as the denominator when
     * calculating the average hitrate from all the simulation runs */
    int sim_counter = 0;

    //This is used to later check if the minimum or maximum spread value has been reached
    double current_spread_angle = spread;

    /* This variable needs to be calculated for every simulation run, because the horizontal recoil is a random value
     * between a minimum and a maximum */
    double hrec_magnitude;

    /* This vector stores the sum of all the individual bullet's hitchances. Later gets divided by sim_counter to get
     * the average hitchance */
    std::vector<double> shots_in_burst;

    //This needs to be the size of the burst length to be able to store the combined hitchances for all shots
    shots_in_burst.resize (burst_length_);

    // this first for loop runs the simulation a certain number of times, specified by the user
    for ( int i = 0; i < hitrate_sim_count_; i++ )
    {
        /*
         * This calculation is needed to convert the value of the spread from
         * an angle to a length
         */
        spread_radius_ = offset (distance_ , spread);
        /*
         * this second for-loop runs the single-bullet simulation for each
         * bullet in the burst
         */
        for ( int j = 0; j < burst_length_; j++ )
        {
            hrec_magnitude = randomNumberGenerator (hrec_l, hrec_r);
            shots_in_burst[j] = shots_in_burst[j] + singleBulletSim ();

            // this needs to change every sim run due to horizontal recoil
            spread_position_x_ = spread_position_x_ +
                                offset (distance_, hrec_magnitude);

            /* This conditional statement checks if its is the first shot in the burst(first statement) or if the
             * maximum or minimum spread value has been reached (second statement) */
            if ( j == 0 )
            {
                /* first shot in the burst, so this expression increases the spread radius using the
                 * first-shot-spread-multiplier */
                spread_radius_ = spread_radius_ + offset (distance_, sips * fssm);
                current_spread_angle = current_spread_angle + sips * fssm;
            }
                /*
                 * This statement needs to keep the spread radius constant
                 * because either the minimum or maximum spread was reached */
            else if ( current_spread_angle >= spread_max || current_spread_angle <= spread )
            {
                spread_radius_ = spread_radius_;
            }
                /*
                 * any shot in the burst that isn't the first, or for which
                 * max or min spread hasn't been reached. Spread gets
                 * increased using the normal spread increase per shot
                 */
            else
            {
                spread_radius_ = spread_radius_ + offset (distance_, sips);
                current_spread_angle = current_spread_angle + sips;
            }
        }
        sim_counter++;
        /*
         * The position of the spread needs to be reset to the starting
         * position after the burst
         */
        spread_position_x_ = 0.0;
        current_spread_angle = spread;

    }
    std::cout << "final results" << std::endl;
    for ( int k = 0; k < burst_length_; k++ )
    {
        /*
         * The hitchances need to be divided by the amount of simulation runs
         * to get the average hitchance
         */
        shots_in_burst[k] = shots_in_burst[k] / sim_counter;

        std::cout << "shot #";
        std::cout << k + 1;
        std::cout << ": ";
        std::cout << shots_in_burst[k] * 100;
        std::cout << " %" << std::endl;
    }

    /*
     * The vector for storing the bullets hitchances needs to be reset so the
     * simulation can run again without having residual calculations stored
     */
    for ( int k = 0; k < burst_length_; k++ )
    {
        shots_in_burst[k] = 0;
    }
}

void Bf1::statInput()
{
    std::cout << "hrec_l: " << std::endl;
    std::cin >> hrec_l;
    std::cout << "hrec_r: " << std::endl;
    std::cin >> hrec_r;
    std::cout << "fssm: " << std::endl;
    std::cin >> fssm;
    std::cout << "sips: " << std::endl;
    std::cin >> sips;
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

    /*
     * converts the stat for left hrec to a negative number; this needs to be
     * done because the BF1 weapon data specifies values for left and right
     * horizontal recoil; in this program left is  handled as a negative
     * value while right is a positive value
     */
    if ( hrec_l > 0 )
    {
        hrec_l = hrec_l * -1;
    }
}

void Bf1::changeStance()
{
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

    switch ( desired_aim )
    {
        case 1 : //ADS
            switch ( desired_movement_state )
            {
                case 1: //ADS, nmove
                    spread = spread_ads_stand_not_move;
                    break;
                case 2: //ADS, move
                    spread = spread_ads_stand_move;
                    break;
                default:
                    break;
            }
            break;
        case 2: //HIP
            switch ( desired_movement_state )
            {
                case 1: //HIP, nmove
                    switch ( desired_stance )
                    {
                        case 1: //HIP, nmove, stand
                            spread = spread_hip_stand_not_move;
                            break;
                        case 2: //HIP, nmove, crouch
                            spread = spread_hip_crouch_not_move;
                            break;
                        case 3: //HIP, nmove, prone
                            spread = spread_hip_prone_not_move;
                            break;
                        default:
                            break;
                    }
                case 2: //HIP, move
                    switch ( desired_stance )
                    {
                        case 1: //HIP, move, stand
                            spread = spread_hip_stand_move;
                            break;
                        case 2: // HIP , move, crouch
                            spread = spread_hip_crouch_move;
                            break;
                        case 3: //HIP, move, prone
                            spread = spread_hip_prone_move;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
            break;
        default:
            break;
    }
}