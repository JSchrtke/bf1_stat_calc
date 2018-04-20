#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include "game.h"
#define PI 3.141592653589793238463

double game::dist_betw_points(double x_1, double y_1, double x_2, double y_2) {
    double dist_x, dist_y, dist_points;
    dist_x = std::abs(x_1) + std::abs(x_2);
    dist_y = std::abs(y_1) + std::abs(y_2);
    dist_points = std::sqrt(dist_x * dist_x + dist_y * dist_y);
    return dist_points;
}

double game::offset(double distance, double angle) {
    double hrec_hor_shift;
    hrec_hor_shift = tan(angle * (PI / 180)) * distance;
    return hrec_hor_shift;
}

double game::random_number_double(double rand_num_min, double rand_num_max) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(rand_num_min, rand_num_max);
    double rand_double = dist(gen);
    return rand_double;
}

double game::single_bullet_sim(double target_position_x, double target_position_y, double target_radius,
                               double spread_position_x, double spread_position_y, double spread_radius) {
    double dist_circles = dist_betw_points(target_position_x, target_position_y, spread_position_x, spread_position_y);
    double t_r_sq = target_radius * target_radius;
    double s_r_sq = spread_radius * spread_radius;
    double d_c_sq = dist_circles * dist_circles;
    double intersect_area;
    double hit_miss; //hitchance
    if (dist_circles <= target_radius && dist_circles + spread_radius <= target_radius)
    {
        hit_miss = 1;
    }
    else if (dist_circles > target_radius && target_radius + spread_radius <= dist_circles)
    {
        hit_miss = 0;
    }
    else if (spread_radius >= target_radius && dist_circles + target_radius <= spread_radius)
    {
        hit_miss = t_r_sq / s_r_sq;
    }
    else
    {
        intersect_area = s_r_sq * acos((d_c_sq + s_r_sq - t_r_sq) / (2 * dist_circles * spread_radius)) +
                         t_r_sq * acos((d_c_sq + t_r_sq - s_r_sq) / (2 * dist_circles * target_radius)) -
                         0.5 * sqrt((-dist_circles + spread_radius + target_radius) *
                                    (dist_circles + spread_radius - target_radius) *
                                    (dist_circles - spread_radius + target_radius) *
                                    (dist_circles + spread_radius + target_radius));
        hit_miss = intersect_area / (PI * s_r_sq);
    }
    return hit_miss;
}