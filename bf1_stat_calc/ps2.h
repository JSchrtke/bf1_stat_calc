#ifndef BF1_STAT_CALC_PS2_H
#define BF1_STAT_CALC_PS2_H
#include "game.h"
#include <string>
#include <iostream>

class ps2 : public game {
public:
    void simulation(double target_position_x, double target_position_y, double target_radius,
                    double spread_position_x, double spread_position_y, double spread_radius, int hitrate_sim_count,
                    unsigned long long int burst_length, double weapon_stats[], double distance);

    void stat_input(double weapon_stats[], std::string weapon_stat_names[]);
};

#endif //BF1_STAT_CALC_PS2_H
