#ifndef TEST_THINGS_2_BF1_H
#define TEST_THINGS_2_BF1_H

#include <iostream>
#include <string>
#include "game.h"

class bf1 : public game {
    // temp variables for stat changes
    double temp_base_spread{}; //variable that stores the base spread after stance choice
    double temp_fssm{}; //stores fssm after stance choice
    double temp_sips{}; // stores sips after stance choice

    //test variables for weapon stats
    double hrec_l{};
    double hrec_r{};
    double fssm{};
    double sips{};
    double spread{};
    double spread_ads_stand_not_move{};
    double spread_ads_stand_move{};
    double spread_hip_stand_not_move{};
    double spread_hip_crouch_not_move{};
    double spread_hip_prone_not_move{};
    double spread_hip_stand_move{};
    double spread_hip_crouch_move{};
    double spread_hip_prone_move{};
    double spread_max{};
    int desired_stance{};
    int desired_aim{};
    int desired_movement_state{};

public:
    void simulation();

    void stat_input();

    void changeStance();

};
#endif //TEST_THINGS_2_BF1_H
