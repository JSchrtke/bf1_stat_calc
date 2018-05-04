#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include "game.h"

#define PI 3.141592653589793238463

/*
 * This function calculates the distance between to cartesian coordinates. In this program, the distance between the
 * spread and target circle is needed to calculate the amount of overlap and by that the htichance
 */
double Game::distBetwPoints(double x_1, double y_1, double x_2, double y_2)
{
    double dist_x, dist_y, dist_points;
    dist_x = std::abs(x_1) + std::abs(x_2);
    dist_y = std::abs(y_1) + std::abs(y_2);
    dist_points = std::sqrt(dist_x * dist_x + dist_y * dist_y);
    return dist_points;
}

//This function converts an angle into a length, being given a distance.
double Game::offset(double distance, double angle)
{
    double hrec_hor_shift;
    hrec_hor_shift = tan(angle * (PI / 180)) * distance;
    return hrec_hor_shift;
}

// RNG
double Game::randomNumberGenerator(double rand_num_min, double rand_num_max)
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(rand_num_min, rand_num_max);
    double rand_double = dist(gen);
    return rand_double;
}

// Function that calculates the hitchance for a single bullet
double Game::singleBulletSim()
{
    /* the distance between the spread circle and target circle needs to be calculated to determine how much they
     * overlap */
    double dist_circles = distBetwPoints(target_position_x, target_position_y, spread_position_x, spread_position_y);

    /* The next 3 expressions calculate the squares of their corresponding variables, to make the functions later
     * easier to read and write */
    double t_r_sq = target_radius * target_radius;
    double s_r_sq = spread_radius * spread_radius;
    double d_c_sq = dist_circles * dist_circles;
    double intersect_area;
    double hit_miss; //hitchance

    /* If this statement is true, the spread circle is smaller and inside the target circle, which means that the
     * bullet must always hit. */
    if( dist_circles <= target_radius && dist_circles + spread_radius <= target_radius )
    {
        hit_miss = 1;
    }

        //If this statement is true, the circles dont overlap at all, which means that the bullet must always miss
    else if( dist_circles > target_radius && target_radius + spread_radius <= dist_circles )
    {
        hit_miss = 0;
    }

        /* If this statement is true, the target is completely inside the spread circle and the spread is larger than
         * the target. That means the hitchance is determined by the ratio between the target and the spread area */
    else if( spread_radius >= target_radius && dist_circles + target_radius <= spread_radius )
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

void Game::getTargetRadius()
{
    std::cout << "enter the target size(radius in m): ";
    std::cin >> target_radius;
}

void Game::getDistance()
{
    std::cout << "enter the distance: ";
    std::cin >> distance;
}

void Game::getBurstLength()
{
    std::cout << "enter burst length: ";
    std::cin >> burst_length;
}

void Game::getHitrateSimCount()
{
    std::cout << "Enter simulation run count: ";
    std::cin >> hitrate_sim_count;
}

void Game::getSimulationVariables()
{
    getDistance();
    getTargetRadius();
    getBurstLength();
    getHitrateSimCount();
}
