#include <iostream>
#include "utility_functions.h"

bool contQuit()
{
    char continue_quit_loop = 'y';
    bool main_loop_running = true;

    // this loop just controls if the user wants to quit
    while( continue_quit_loop == 'y' || continue_quit_loop == 'Y' )
    {
        std::cout << "do you want to continue? (Y/N)" << std::endl;
        std::cin >> continue_quit_loop;
        switch( continue_quit_loop )
        {
            case 'y':
                main_loop_running = true;
                continue_quit_loop = 'x';
                break;
            case 'Y':
                main_loop_running = true;
                continue_quit_loop = 'x';
                break;
            case 'n':
                main_loop_running = false;
                continue_quit_loop = 'x';
                break;
            case 'N':
                main_loop_running = false;
                continue_quit_loop = 'x';
                break;
            default:
                std::cout << "Error!" << std::endl;
                break;
        }
    }
    continue_quit_loop = 'y';
    return main_loop_running;
}



int SetGame()
{
    int x{};
    int game_choice{};
    std::cout << "choose the game you want: " << std::endl;
    std::cout << "0: BF1" << std::endl;
    std::cout << "1: PS2" << std::endl;
    std::cin >> x;
    switch(x)
    {
        case 0:
            game_choice = 0;
            break;
        case 1:
            game_choice = 1;
            break;
        default:
            std::cout << "Error! Not a valid game choice!" << std::endl;
            game_choice = -1;
    }
    return game_choice;
}