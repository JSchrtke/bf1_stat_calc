#ifndef BF1_STAT_CALC_PS2_H
#define BF1_STAT_CALC_PS2_H

#include "game.h"
#include <string>
#include <iostream>

class Ps2 : public Game
{
    double hrec_min{};
    double hrec_max{};
    double hrec_tol{};
    double fssm{};
    double sips{};
    double spread{};
    double spread_max{};

public:
    void simulation();

    void statInput();
};

#endif //BF1_STAT_CALC_PS2_H
