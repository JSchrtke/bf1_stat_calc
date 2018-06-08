// This file includes some code that has some better handling of stances and such in it
// I need to work through this to see where to implement this in the main stat calculator 
// and see where I left off with that.

#include <iostream>
#include <map>
#include <stdexcept>

enum AimState
{
    kADS,
    kHipfire
};
enum Movement
{
    kNotMoving,
    kMoving
};
enum Stance
{
    kStanding,
    kCrouched,
    kProne
};

class Bf1
{
struct SpreadModifier
    {
        AimState aimState;
        Movement movement;
        Stance stance;

        bool operator<(const SpreadModifier &SM) const
        {
            return (stance < SM.stance ||
                    (stance == SM.stance && movement < SM.movement) ||
                    (stance == SM.stance && movement == SM.movement && aimState < SM.aimState));
        }

        bool operator==(const SpreadModifier &SM) const
        {
            return (stance == SM.stance && movement == SM.movement && aimState == SM.aimState);
        }
    };

    std::map<SpreadModifier, double> weaponData;

public:

    SpreadModifier SetSpreadModifier()
    {
        int temp_aim_state;
        int temp_movement_state;
        int temp_stance_state;
        SpreadModifier spreadModifier{};
        std::cout << "aimState: " << std::endl;
        std::cout << "1: ADS\n" << "2: HIP" << std::endl;
        std::cin >> temp_aim_state;
        switch(temp_aim_state)
        {
            case 1:
                spreadModifier.aimState = kADS;
                break;
            case 2:
                spreadModifier.aimState = kHipfire;
            default:
                std::cout << "Error! Not a valid AimState!" << std::endl;
                break;
        }
        std::cout << "Movement state: " << std::endl;
        std::cout << "1: not moving\n" << "2: moving" << std::endl;
        std::cin >> temp_movement_state;
        switch(temp_movement_state)
        {
            case 1:
                spreadModifier.movement = kNotMoving;
                break;
            case 2:
                spreadModifier.movement = kMoving;
            default:
                std::cout << "Error! Not a valid movement state!" << std::endl;
                break;
        }
        std::cout << "Enter stance: " << std::endl;
        std::cout << "1: standing\n" << "2: crouched\n" << "3: prone" << std::endl;
        std::cin >> temp_stance_state;
        switch(temp_stance_state)
        {
            case 1:
                spreadModifier.stance = kStanding;
                break;
            case 2:
                spreadModifier.stance = kCrouched;
                break;
            case 3:
                spreadModifier.stance = kProne;
                break;
            default:
                std::cout << "Error! Not a valid stance!" << std::endl;
                break;
        }
        return spreadModifier;
    }

    void SetSpread()
    {
        SpreadModifier spreadModifier{};
        weaponData.insert(std::make_pair(SetSpreadModifier(), GetSpreadValue()));
    }

    double GetSpreadValue()
    {
        double spread;
        std::cout << "Enter spread: " << std::endl;
        std::cin >> spread;
        return spread;
    }

    double GetSpread(SpreadModifier)
    {
        SpreadModifier spreadModifier{};
        double spread;
        spread = weaponData.at(spreadModifier);
        return spread;
    }
};


int main()
{
    Bf1 bf1;
    bf1.SetSpread();
    std::cout << bf1.GetSpread(bf1.SetSpreadModifier()) << std::endl;
    return 0;
}