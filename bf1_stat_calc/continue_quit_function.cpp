#include <iostream>
#include "continue_quit_function.h"

bool cont_quit() {
    char continue_quit_loop = 'y';
    bool main_loop_running = true;
    // this loop just controls if the user wants to quit
    while ( continue_quit_loop == 'y' || continue_quit_loop == 'Y' ) {
        std::cout << "do you want to continue? (Y/N)" << std::endl;
        std::cin >> continue_quit_loop;
        switch ( continue_quit_loop ) {
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
