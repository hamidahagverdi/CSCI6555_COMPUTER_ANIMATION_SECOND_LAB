#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <vector>

class GlobalVariables {
public:
    static const int WIDTH;
    static const int HEIGHT;
    
    // The Catmull Rom Spline M Matrix
    static const float a;
    static const std::vector<std::vector<float>> CRSplineM;
    
    // The B Spline M Matrix
    static const std::vector<std::vector<float>> BSplineM;
    
    // Position x,y,z in world Cartesian System
    static const std::vector<std::vector<float>> position;
    
    // 7 Points represented in Euler Angle
    // The first 3 numbers represent x_angle, y_angle, z_angle in Euler angle
    // and the rest 3 numbers represent the position x,y,z in world Cartesian System
    static const std::vector<std::vector<float>> points;
    
    // Number of points
    static const int pointNum;
};

#endif // GLOBALVARIABLES_H