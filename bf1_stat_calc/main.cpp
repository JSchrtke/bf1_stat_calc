﻿// bf1_stat_calc.cpp
/*
TODO implement stance handling for PS2
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

        Bf1_sim.statInput();

        //Bf1_sim.changeStance();

        // main program loop; while this is "true" the program will run
        while( main_loop_running )
        {
            Bf1_sim.getSimulationVariables();

            Bf1_sim.simulation();

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