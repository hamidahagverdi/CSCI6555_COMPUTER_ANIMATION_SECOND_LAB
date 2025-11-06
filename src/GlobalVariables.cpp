#include "GlobalVariables.h"

// Initialize static constants
const int GlobalVariables::WIDTH = 400;
const int GlobalVariables::HEIGHT = 400;

// The Catmull Rom Spline M Matrix
const float GlobalVariables::a = 0.5f;

const std::vector<std::vector<float>> GlobalVariables::CRSplineM = {
    {-a, 2.0f - a, a - 2.0f, a},
    {2.0f * a, a - 3.0f, 3.0f - 2.0f * a, -a},
    {-a, 0.0f, a, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f}
};

// The B Spline M Matrix
const std::vector<std::vector<float>> GlobalVariables::BSplineM = {
    {-1.0f / 6, 3.0f / 6, -3.0f / 6, 1.0f / 6},
    {3.0f / 6, -6.0f / 6, 3.0f / 6, 0.0f},
    {-3.0f / 6, 0.0f, 3.0f / 6, 0.0f},
    {1.0f / 6, 4.0f / 6, 1.0f / 6, 0.0f}
};

// Position x,y,z in world Cartesian System
const std::vector<std::vector<float>> GlobalVariables::position = {
    {8, 0, -20},    // point 1
    {-8, 0, -20},   // point 2
    {-5, 0, -10},   // point 3
    {5, 0, -10},    // point 4
    {3, 0, -5},     // point 5
    {-3, 0, -5},    // point 6
    {1, 0, -3}      // point 7
};

// 7 Points represented in Euler Angle
// The first 3 numbers represent x_angle, y_angle, z_angle in Euler angle
// and the rest 3 numbers represent the position x,y,z in world Cartesian System
const std::vector<std::vector<float>> GlobalVariables::points = {
    {90, 0, 45, -5, 0, -5},
    {70, 20, 65, -3, 3, -10},
    {50, 40, 85, -1, 1, -15},
    {30, 60, 105, 0, -5, -20},
    {50, 40, 85, 1, 1, -15},
    {70, 20, 65, 3, 3, -10},
    {90, 0, 45, 5, 0, -5}
};

// Number of points
const int GlobalVariables::pointNum = position.size();