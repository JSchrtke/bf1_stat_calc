//
// Created by Joharnis on 20/04/2018.
//

#ifndef TEST_THINGS_2_GAME_H
#define TEST_THINGS_2_GAME_H


class game {
public:
    double dist_betw_points(double x_1, double y_1, double x_2, double y_2);
    double offset (double distance, double angle);
    double random_number_double (double rand_num_min, double rand_num_max);
    double single_bullet_sim (double target_position_x, double target_position_y, double target_radius,
                              double spread_position_x, double spread_position_y, double spread_radius);
};


#endif //TEST_THINGS_2_GAME_H
