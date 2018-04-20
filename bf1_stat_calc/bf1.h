#ifndef TEST_THINGS_2_BF1_H
#define TEST_THINGS_2_BF1_H


#include "game.h"

class bf1 : public game {
public:
    void simulation(double target_position_x, double target_position_y, double target_radius,
                    double spread_position_x, double spread_position_y, double spread_radius, int hitrate_sim_count,
                    unsigned long long int burst_length, double weapon_stats[], double distance);
};


#endif //TEST_THINGS_2_BF1_H
