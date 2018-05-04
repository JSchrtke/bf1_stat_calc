#ifndef TEST_THINGS_2_BF1_H
#define TEST_THINGS_2_BF1_H

#include <iostream>
#include <string>
#include <map>
#include "game.h"

class Bf1 : public Game
{
    // variables for weapon stats
    double hrec_l_{};
    double hrec_r_{};
    double fssm_{};
    double sips_{};
    double spread_{};
    double spread_ads_stand_not_move_{};
    double spread_ads_stand_move_{};
    double spread_hip_stand_not_move_{};
    double spread_hip_crouch_not_move_{};
    double spread_hip_prone_not_move_{};
    double spread_hip_stand_move_{};
    double spread_hip_crouch_move_{};
    double spread_hip_prone_move_{};
    double spread_max_{};
    int desired_stance_{};
    int desired_aim_{};
    int desired_movement_state_{};

    enum AimState
    {
        ADS,
        Hipfire
    };
    enum Movement
    {
        NotMoving,
        Moving
    };
    enum Stance
    {
        Standing,
        Crouching,
        Prone
    };

    struct SpreadModifier
    {
        AimState aimState;
        Movement movement;
        Stance stance;

        bool operator<(const SpreadModifier &SM) const
        {
            return (stance < SM.stance ||
                    (stance == SM.stance && movement < SM.movement) ||
                    stance == SM.stance && movement == SM.movement && aimState < SM.aimState);
        }

        bool  operator==(const SpreadModifier &SM) const
        {
            return (stance == SM.stance && movement == SM.movement && aimState == SM.aimState);
        }
    };

    std::map<SpreadModifier, double> SpreadData;

public: SpreadModifier GetSpreadModifier(AimState aimState, Movement movement, Stance stance);

    double GetSpreadValue(AimState aimState, Movement movement, Stance stance);

public:
    void Simulation();

    void StatInput();

    void ChangeStance();

};

#endif //TEST_THINGS_2_BF1_H
