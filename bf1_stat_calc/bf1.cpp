#include <iostream>
#include <vector>
#include <string>
#include "bf1.h"

void Bf1::Simulation()
{
    int sim_counter = 0;
    double current_spread_angle = spread_;
    double hrec_magnitude;
    std::vector<double> shots_in_burst;

    // vector needs to be resized to fit the length of the burst
    shots_in_burst.resize (burst_length_);

    // Loop for one full burst simulation
    for ( int i = 0; i < hitrate_sim_count_; i++ )
    {
        spread_radius_ = offset (distance_, spread_);

        // Loop for a single bullet sim
        for ( int j = 0; j < burst_length_; j++ )
        {
            hrec_magnitude = randomNumberGenerator (hrec_l_, hrec_r_);
            shots_in_burst[j] = shots_in_burst[j] + singleBulletSim ();

            // this needs to change every sim run due to horizontal recoil
            spread_position_x_ = spread_position_x_ +
                                offset (distance_, hrec_magnitude);

            /* This conditional statement checks if its is the first shot in the burst(first statement) or if
             * the maximum or minimum spread value has been reached (second statement) */
            if ( j == 0 )
            {
                /* first shot in the burst, so this expression increases the spread radius using the
                 * first-shot-spread-multiplier */
                spread_radius_ = spread_radius_ + offset (distance_, sips_ * fssm_);
                current_spread_angle = current_spread_angle + sips_ * fssm_;
            }
                /* This statement needs to keep the spread radius constant because either the minimum or
                 * maximum spread was reached */
            else if ( current_spread_angle >= spread_max_ || current_spread_angle <= spread_ )
            {
                spread_radius_ = spread_radius_;
            }
                /* any shot in the burst that isn't the first, or for which max or min spread hasn't been
                 * reached. Spread gets increased using the normal spread increase per shot */
            else
            {
                spread_radius_ = spread_radius_ + offset (distance_, sips_);
                current_spread_angle = current_spread_angle + sips_;
            }
        }
        sim_counter++;

        //The position of the spread needs to be reset to the starting position after the burst
        spread_position_x_ = 0.0;
        current_spread_angle = spread_;

    }
    std::cout << "final results" << std::endl;
    for ( int k = 0; k < burst_length_; k++ )
    {
        //The hitchances need to be divided by the amount of simulation runs to get the average hitchance
        shots_in_burst[k] = shots_in_burst[k] / sim_counter;

        std::cout << "shot #";
        std::cout << k + 1;
        std::cout << ": ";
        std::cout << shots_in_burst[k] * 100;
        std::cout << " %" << std::endl;
    }
    /* The vector for storing the bullets hitchances needs to be reset so the simulation can run again
     * without having residual calculations stored */
    for ( int k = 0; k < burst_length_; k++ )
    {
        shots_in_burst[k] = 0;
    }
}

void Bf1::StatInput()
{
    std::cout << "hrec_l: " << std::endl;
    std::cin >> hrec_l_;
    std::cout << "hrec_r: " << std::endl;
    std::cin >> hrec_r_;
    std::cout << "fssm: " << std::endl;
    std::cin >> fssm_;
    std::cout << "sips: " << std::endl;
    std::cin >> sips_;
    std::cout << "spread_ads_stand_not_move: " << std::endl;
    std::cin >> spread_ads_stand_not_move_;
    std::cout << "spread_ads_stand_move_: " << std::endl;
    std::cin >> spread_ads_stand_move_;
    std::cout << "spread_hip_stand_not_move_: " << std::endl;
    std::cin >> spread_hip_stand_not_move_;
    std::cout << "spread_hip_crouch_not_move_: " << std::endl;
    std::cin >> spread_hip_crouch_not_move_;
    std::cout << "spread_hip_prone_not_move_: " << std::endl;
    std::cin >> spread_hip_prone_not_move_;
    std::cout << "spread_hip_stand_move_: " << std::endl;
    std::cin >> spread_hip_stand_move_;
    std::cout << "spread_hip_crouch_move_: " << std::endl;
    std::cin >> spread_hip_crouch_move_;
    std::cout << "spread_hip_prone_move_: " << std::endl;
    std::cin >> spread_hip_prone_move_;
    std::cout << "spread_max: " << std::endl;
    std::cin >> spread_max_;

    SpreadData.insert(std::make_pair(GetSpreadModifier(ADS, NotMoving, Standing),
                                     spread_ads_stand_not_move_));
    SpreadData.insert(std::make_pair(GetSpreadModifier(ADS, Moving, Standing),
                                     spread_ads_stand_move_));
    SpreadData.insert(std::make_pair(GetSpreadModifier(Hipfire, NotMoving, Standing),
                                     spread_hip_stand_not_move_));
    SpreadData.insert(std::make_pair(GetSpreadModifier(Hipfire, NotMoving, Crouching),
                                     spread_hip_crouch_not_move_));
    SpreadData.insert(std::make_pair(GetSpreadModifier(Hipfire, NotMoving, Prone),
                                     spread_hip_prone_not_move_));
    SpreadData.insert(std::make_pair(GetSpreadModifier(Hipfire, Moving, Standing),
                                    spread_hip_stand_move_));
    SpreadData.insert(std::make_pair(GetSpreadModifier(Hipfire, Moving, Crouching),
                                    spread_hip_crouch_move_));
    SpreadData.insert(std::make_pair(GetSpreadModifier(Hipfire, Moving, Prone),
                                    spread_hip_prone_move_));

    /* converts the stat for left hrec to a negative number; this needs to be done because the BF1 weapon
     * data specifies values for left and right horizontal recoil; in this program left is  handled as a
     * negative value while right is a positive value */
    if ( hrec_l_ > 0 )
    {
        hrec_l_ = hrec_l_ * -1;
    }
}


Bf1::SpreadModifier Bf1::GetSpreadModifier(AimState aimState, Movement movement, Stance stance)
{
    SpreadModifier spreadModifier{};

    spreadModifier.aimState = aimState;
    spreadModifier.movement = movement;
    spreadModifier.stance = stance;

    return spreadModifier;
}

double Bf1::GetSpreadValue(Bf1::AimState aimState, Bf1::Movement movement, Bf1::Stance stance)
{
    return SpreadData.at(GetSpreadModifier(aimState, movement, stance));
}

void Bf1::ChangeStance()
{
    std::cout << "enter desired aim state:" << std::endl;
    std::cout << "1: ADS" << std::endl;
    std::cout << "2: HIP" << std::endl;
    std::cin >> desired_aim_;
    std::cout << "Enter desired movement state:" << std::endl;
    std::cout << "1: not moving" << std::endl;
    std::cout << "2: moving" << std::endl;
    std::cin >> desired_movement_state_;
    std::cout << "enter desired stance:" << std::endl;
    std::cout << "1: standing" << std::endl;
    std::cout << "2: crouching" << std::endl;
    std::cout << "3: prone" << std::endl;
    std::cin >> desired_stance_;

    switch ( desired_aim_ )
    {
        case 1 : //ADS
            switch ( desired_movement_state_ )
            {
                case 1: //ADS, nmove
                    spread_ = spread_ads_stand_not_move_;
                    break;
                case 2: //ADS, move
                    spread_ = spread_ads_stand_move_;
                    break;
                default:
                    break;
            }
            break;
        case 2: //HIP
            switch ( desired_movement_state_ )
            {
                case 1: //HIP, nmove
                    switch ( desired_stance_ )
                    {
                        case 1: //HIP, nmove, stand
                            spread_ = spread_hip_stand_not_move_;
                            break;
                        case 2: //HIP, nmove, crouch
                            spread_ = spread_hip_crouch_not_move_;
                            break;
                        case 3: //HIP, nmove, prone
                            spread_ = spread_hip_prone_not_move_;
                            break;
                        default:
                            break;
                    }
                case 2: //HIP, move
                    switch ( desired_stance_ )
                    {
                        case 1: //HIP, move, stand
                            spread_ = spread_hip_stand_move_;
                            break;
                        case 2: // HIP , move, crouch
                            spread_ = spread_hip_crouch_move_;
                            break;
                        case 3: //HIP, move, prone
                            spread_ = spread_hip_prone_move_;
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

