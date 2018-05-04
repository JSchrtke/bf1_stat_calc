#ifndef TEST_THINGS_2_GAME_H
#define TEST_THINGS_2_GAME_H


class Game
{
protected:

    //x/y coordinates of the center of the target
    double target_position_x_ = 0.0;
    double target_position_y_ = 0.0;

    //radius of the target circle
    double target_radius_ = 0.25;

    //x/y coordinates of the center of the spread
    double spread_position_x_ = 0.0;
    double spread_position_y_ = 0.0;

    //radius of the spread
    double spread_radius_ = 0;

    //distance to target
    double distance_ = 30.0;

    //magnitude of hrec, this is a random number between hrec_l and hrec_r
    double hrec_magnitude_{};

    //stores burst length
    unsigned long long int burst_length_ = 5;

    //variable to specify how many times the simulation runs
    int hitrate_sim_count_ = 1;

public: enum GameChoice
    {
        kBf1,
        kPs2
    };
public:
    GameChoice SetGame();

    bool ContinueQuit();

    double distBetwPoints(double x_1, double y_1, double x_2, double y_2);

    double offset(double distance, double angle);

    double randomNumberGenerator(double rand_num_min, double rand_num_max);

    double singleBulletSim();

    void getTargetRadius();

    void getDistance();

    void getBurstLength();

    void getHitrateSimCount();

    void getSimulationVariables();

};


#endif //TEST_THINGS_2_GAME_H