#include "stdafx.h"
#include "math_functions.h"
#include <iostream>
//#define DEBUG
using namespace std;

double ps2_hrec(double hrec_magnitude, double hrec_tol_check, double weapon_stats_18,
                double rand_double, int hrec_l_r)
{
    if (hrec_tol_check <= (weapon_stats_18 * -1))
    {
#ifdef DEBUG
        cout << "DEBUG: hrec_tol_check <= hrec_tol: " << hrec_tol_check << endl;
#endif // DEBUG
        hrec_l_r = 1;
    }
    else if (hrec_tol_check >= weapon_stats_18)
    {
#ifdef DEBUG
        cout << "DEBUG: hrec_tol_check >= hrec_tol: " << hrec_tol_check << endl;
#endif // DEBUG
        hrec_l_r = -1;
    }
    else
    {
#ifdef DEBUG
        cout << "DEBUG: hrec_tol_check fine: " << hrec_tol_check << endl;
#endif // DEBUG
        while (rand_double == 0)
        {
            rand_double = random_number_double(-1, 1);
            if (rand_double < 0)
            {
#ifdef DEBUG
                cout << "DEBUG: rand_double < 0" << endl;
				cout << "DEBUG: hrec_l_r: " << hrec_l_r << endl;
#endif // !DEBUG
                hrec_l_r = -1;
            }
            else
            {
#ifdef DEBUG
                cout << "DEBUG: rand_double > 0" << endl;
				cout << "DEBUG: hrec_l_r: " << hrec_l_r << endl;
#endif // !DEBUG
                hrec_l_r = 1;
            }
        }
    }
    hrec_magnitude = hrec_magnitude * hrec_l_r;
    return hrec_magnitude;
}