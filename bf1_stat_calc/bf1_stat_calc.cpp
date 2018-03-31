// bf1_stat_calc.cpp
/*
TO DO:
-add weapon stat variables
*/
#include "stdafx.h"
#include "random_number.h"
#include "dist_betw_points.h"
#include "hrec.h"
#include <iostream>

int main()
{
	//x/y coordinates of the center of the target
	double target_position_x = -0.0;
	double target_postion_y = -0.0;
	
	//radius of the target circle
	double target_radius = 1.0;
	
	//x/y coordinates of the center of the spread
	double spread_postion_x = 1.0;
	double spread_postion_y = 1.0;
	
	//radius of the spread
	double spread_radius = 1.0;

	//distance to target
	double distance = 10.0;

	//magnitude of hrec
	double hrec_magnitude;
	
	//Weapon stat variables
	int rpm = 359;
	int muz_vel = 660;
	int mag_size = 5;
	float deploy_time = 0.7;
	float hor_recoil_r = 0.15;
	float hor_recoil_l = -0.15;
	float sips = 0.062;
	float fssm_ads = 1;
	float fssm_hip = 1;
	float spread_dec = 3.75;
	float spread_ads_not_move = 0.12;
	float spread_ads_move = 0.82;
	float spread_hip_stand_not_move = 2;
	float spread_hip_crouch_not_move = 1.5;
	float spread_hip_prone_not_move = 1;
	float spread_hip_stand_move = 2.5;
	float spread_hip_crouch_move = 2;
	float spread_hip_prone_move = 1.5;


	return 0;
}