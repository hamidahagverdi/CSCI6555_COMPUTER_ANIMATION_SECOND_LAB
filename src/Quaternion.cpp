#include "Quaternion.h"
#include "Function.h"
#include <cmath>
#include <cassert>

// Constructor with individual parameters
Quaternion::Quaternion(float w, float x, float y, float z, float px, float py, float pz)
    : w(w), x(x), y(y), z(z), px(px), py(py), pz(pz) {
    // w,x,y,z represent quaternion
    // px,py,pz represent the position in world Cartesian System
    this->Normalization(); // get a normal quaternion
}

// Constructor with array
Quaternion::Quaternion(const std::vector<float>& m) {
    assert(m.size() == 7 && "Not a valid quaternion");
    this->w = m[0];
    this->x = m[1];
    this->y = m[2];
    this->z = m[3];
    this->px = m[4];
    this->py = m[5];
    this->pz = m[6];
    this->Normalization();
}

// Get the point as a vector
std::vector<float> Quaternion::getPoint() const {
    return {w, x, y, z, px, py, pz};
}

// Unit Quaternion normalization
void Quaternion::Normalization() {
    float magnitude = std::sqrt(w*w + x*x + y*y + z*z);
    // Avoid divide by 0
    if (magnitude != 0) {
        w = w / magnitude;
        x = x / magnitude;
        y = y / magnitude;
        z = z / magnitude;
    }
}

// Get the rotation matrix R and transition matrix T, return T*R
std::vector<std::vector<float>> Quaternion::toMatrix() const {
    std::vector<std::vector<float>> rotation = {
        {1 - 2*y*y - 2*z*z, 2*x*y - 2*w*z, 2*x*z + 2*w*y, 0},
        {2*x*y + 2*w*z, 1 - 2*x*x - 2*z*z, 2*y*z - 2*w*x, 0},
        {2*x*z - 2*w*y, 2*y*z + 2*w*x, 1 - 2*x*x - 2*y*y, 0},
        {0, 0, 0, 1}
    };
    
    std::vector<std::vector<float>> T = {
        {1, 0, 0, px},
        {0, 1, 0, py},
        {0, 0, 1, pz},
        {0, 0, 0, 1}
    };
    
    return Function::multiplyMatrix(T, rotation);
}

// Convert 2D matrix to 1D
std::vector<float> Quaternion::toOneDMatrix() const {
    std::vector<std::vector<float>> matrix = toMatrix();
    return Function::convertMatrix(matrix);
}