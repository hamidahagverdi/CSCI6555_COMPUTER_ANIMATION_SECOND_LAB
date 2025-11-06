#ifndef QUATERNION_H
#define QUATERNION_H

#include <vector>

class Quaternion {
public:
    float w, x, y, z;    // quaternion
    float px, py, pz;    // position
    
    // Constructor with individual parameters
    Quaternion(float w, float x, float y, float z, float px, float py, float pz);
    
    // Constructor with array
    Quaternion(const std::vector<float>& m);
    
    // Get the point as a vector
    std::vector<float> getPoint() const;
    
    // Get the rotation matrix R and transition matrix T, return T*R
    std::vector<std::vector<float>> toMatrix() const;
    
    // Convert 2D matrix to 1D
    std::vector<float> toOneDMatrix() const;

private:
    // Unit Quaternion normalization
    void Normalization();
};

#endif // QUATERNION_H