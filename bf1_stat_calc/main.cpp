// bf1_stat_calc.cpp
/*
TODO Move SpreadModifier struct into Game class
 TODO Finish ChangeStance function
    - pass instance of SpreadModifier to Simulation function
    - use SpreadData.at() instead of spread_ in Simulation function, with that instance of SpreadModifier
        passed to that functionK
*/
#include "bf1.h"
#include "ps2.h"
#include "game.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    bool main_loop_running = true;
    Game game;
    Game::GameChoice gameChoice;
    gameChoice = game.SetGame();

    if(gameChoice == game.kBf1)
    {
        std::cout << "you chose BF1" << std::endl;
        Bf1 Bf1_sim;

        Bf1_sim.StatInput();

        Bf1_sim.ChangeStance();

        // main program loop; while this is "true" the program will run
        while( main_loop_running )
        {
            Bf1_sim.getSimulationVariables();

            Bf1_sim.Simulation();

            main_loop_running = game.ContinueQuit();
        }
        return 0;
    }
    else if(gameChoice == game.kPs2)
    {
        std::cout << "you chose PS2" << std::endl;
        Ps2 Ps2_sim;

        Ps2_sim.statInput();

        while( main_loop_running )
        {
            Ps2_sim.getSimulationVariables();
            Ps2_sim.simulation();
            main_loop_running = game.ContinueQuit();
        }
        return 0;
    }
    else
    {
        std::cout << "Error! you must choose a game!";
    }
}