#ifndef TEST_THINGS_2_GAME_H
#define TEST_THINGS_2_GAME_H


class game
{
protected:
//x/y coordinates of the center of the target
    double target_position_x = 0.0;
    double target_position_y = 0.0;
    //radius of the target circle
    double target_radius = 0.25;
    //x/y coordinates of the center of the spread
    double spread_position_x = 0.0;
    double spread_position_y = 0.0;
    //distance to target
    double distance = 30.0;
    //radius of the spread
    double spread_radius = 0;
    //magnitude of hrec, this is a random number between hrec_l and hrec_r
    double hrec_magnitude{};
    //stores burst length
    unsigned long long int burst_length = 5;
    //variable to specify how many times the simulation runs
    int hitrate_sim_count = 1;
public:
    double dist_betw_points(double x_1, double y_1, double x_2, double y_2);

    double offset(double distance, double angle);

    double random_number_double(double rand_num_min, double rand_num_max);

    double single_bullet_sim();

    void GetTargetRadius();

    void GetDistance();

    void GetBurstLength();

    void GetHitrateSimCount();

    void GetSimulationVariables();

};


#endif //TEST_THINGS_2_GAME_H
