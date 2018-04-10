#ifndef math_functions_h_
#define math_functions_h_
// hrec horizontal offset function
double offset(double distance, double angle);

//function to calculate the distance between 2 points in cartesian coordinate system
double dist_betw_points(double x_1, double y_1, double x_2, double y_2);

//function to generate a random double number with equal distribution
double random_number_double(double rand_num_min, double rand_num_max);

//function to generate random integer with equal distribution
int random_number_int(int rand_num_min, int rand_num_max);

//function to simulate if single bullet hit/miss
double single_bullet_sim(double target_position_x, double target_position_y, double target_radius,
	double spread_position_x, double spread_position_y, double spread_radius);

//function to be able to handle PS2's hrec mechanics
double ps2_hrec(double hrec_magnitude, double hrec_tol_check, double weapon_stats_18,
	double rand_double, int hrec_l_r);

#endif //math_functions_h_