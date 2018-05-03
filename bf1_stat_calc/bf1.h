#ifndef TEST_THINGS_2_BF1_H
#define TEST_THINGS_2_BF1_H

#include <iostream>
#include <string>
#include "game.h"

class Bf1 : public Game
{
    // variables for weapon stats
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

    void statInput();

    void changeStance();

};

#endif //TEST_THINGS_2_BF1_H
