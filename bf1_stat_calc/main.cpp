// bf1_stat_calc.cpp
/*
TODO implement stance handling for PS2
*/
#include "stdafx.h"
#include "bf1.h"
#include "ps2.h"
#include "continue_quit_function.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // variable for controlling if the main loop is running, this needs to evaluate to "true" for the program to run
    bool main_loop_running = true;
    //variable for choosing the game; 0 = BF1, 1 = PS2
    int game_choice = 0;

    /* sets the game_choice variable to the games corresponding value, so that the right functions can be called in the
     * following conditional statement
     */
    cout << "choose the game:\n";
    cout << "0: BF1\n";
    cout << "1: PS2" << endl;
    cin >> game_choice;

    if ( game_choice == 0 )
    {

        cout << "you chose BF1" << endl;
        Bf1 Bf1_sim;

        Bf1_sim.statInput();

        Bf1_sim.changeStance();

        // main program loop; while this is "true" the program will run
        while ( main_loop_running )
        {
            Bf1_sim.getSimulationVariables();

            Bf1_sim.simulation();

            main_loop_running = contQuit();
        }
        return 0;
    }
    else if ( game_choice == 1 )
    {
        cout << "you chose PS2" << endl;
        Ps2 Ps2_sim;

        Ps2_sim.statInput();

        while ( main_loop_running )
        {
            Ps2_sim.getSimulationVariables();

            Ps2_sim.simulation();
            main_loop_running = contQuit();
        }
        return 0;
    }
    else
    {
        cout << "Error! you must choose a game!";
    }
}