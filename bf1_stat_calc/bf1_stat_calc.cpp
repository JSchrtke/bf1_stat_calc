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

int main() {
    //variables for controlling if the main loop is running
    bool main_loop_running = true;
    //variable to choose the game
    int game_choice = 0;

    //game choice
    cout << "choose the game:\n";
    cout << "0: BF1\n";
    cout << "1: PS2" << endl;
    cin >> game_choice;

    if (game_choice == 0) {

        cout << "you chose BF1" << endl;
        bf1 bf1_sim;

        //manual weapon stat input
        bf1_sim.stat_input();

        bf1_sim.changeStance();

        //main program loop
        while ( main_loop_running ) {
            bf1_sim.GetSimulationVariables();

            bf1_sim.simulation();

            main_loop_running = cont_quit();
        }
        return 0;
    }
    else if (game_choice == 1) {
        cout << "you chose PS2" << endl;
        ps2 ps2_sim;

        //manual weapon stat input
        ps2_sim.stat_input();

        //main program loop
        while ( main_loop_running ) {
            ps2_sim.GetSimulationVariables();

            ps2_sim.simulation();
            main_loop_running = cont_quit();
        }
        return 0;
    }
    else {
        cout << "Error! you must choose a game!";
    }
}