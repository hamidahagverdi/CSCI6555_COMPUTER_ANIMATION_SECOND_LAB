#include "RightLeg.h"
#include "Function.h"
#include <cmath>

// Constructor
RightLeg::RightLeg(Torso& torso) : t(0.0f), torso(&torso) {
}

// Setter for time parameter
void RightLeg::setT(float t) {
    this->t = t;
}

// Get transformation matrix
std::vector<std::vector<float>> RightLeg::toMatrix() {
    std::vector<std::vector<float>> TAB(4, std::vector<float>(4));
    
    std::vector<std::vector<float>> T1 = {
        {1, 0, 0, 0},
        {0, 1, 0, -0.95f},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    
    // To animate rotation, change θ(t)
    float Angle = -sinf(4 * 3.14 * t - 3.14 / 2) * 3.14 / 4;
    
    std::vector<std::vector<float>> T2 = {
        {cosf(Angle), -sinf(Angle), 0, 0},
        {sinf(Angle), cosf(Angle), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    
    std::vector<std::vector<float>> T3 = {
        {1, 0, 0, 0},
        {0, 1, 0, -0.95f},
        {0, 0, 1, -0.3f},
        {0, 0, 0, 1}
    };
    
    TAB = Function::multiplyMatrix(torso->Matrix, T1);
    TAB = Function::multiplyMatrix(TAB, T2);
    TAB = Function::multiplyMatrix(TAB, T3);
    
    return TAB;
}

// Convert 2D matrix to 1D
std::vector<float> RightLeg::toOneDMatrix() {
    std::vector<std::vector<float>> matrix = toMatrix();
    return Function::convertMatrix(matrix);
}

// Helper function for cosine
float RightLeg::cosf(float angle) const {
    return std::cos(angle);
}

// Helper function for sine (float)
float RightLeg::sinf(float angle) const {
    return std::sin(angle);
}

// Helper function for sine (double)
float RightLeg::sinf(double angle) const {
    return std::sin(angle);
}