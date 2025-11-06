#ifndef RIGHTLEG_H
#define RIGHTLEG_H

#include <vector>
#include "Torso.h"

class RightLeg {
public:
    // Constructor
    RightLeg(Torso& torso);
    
    // Setter for time parameter
    void setT(float t);
    
    // Get transformation matrix
    std::vector<std::vector<float>> toMatrix();
    
    // Convert 2D matrix to 1D
    std::vector<float> toOneDMatrix();

private:
    float t;
    Torso* torso;
    
    // Helper functions
    float cosf(float angle) const;
    float sinf(float angle) const;
    float sinf(double angle) const;
};

#endif // RIGHTLEG_H