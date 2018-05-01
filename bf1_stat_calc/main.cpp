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
        bf1 bf1_sim;

        bf1_sim.stat_input();

        bf1_sim.changeStance();

        // main program loop; while this is "true" the program will run
        while ( main_loop_running )
        {
            bf1_sim.GetSimulationVariables();

            bf1_sim.simulation();

            main_loop_running = cont_quit();
        }
        return 0;
    }
    else if ( game_choice == 1 )
    {
        cout << "you chose PS2" << endl;
        ps2 ps2_sim;

        ps2_sim.stat_input();

        while ( main_loop_running )
        {
            ps2_sim.GetSimulationVariables();

            ps2_sim.simulation();
            main_loop_running = cont_quit();
        }
        return 0;
    }
    else
    {
        cout << "Error! you must choose a game!";
    }
}