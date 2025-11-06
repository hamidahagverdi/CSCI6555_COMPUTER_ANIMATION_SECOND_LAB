#ifndef EULERANGLE_H
#define EULERANGLE_H

#include <cmath>
#include <vector>
#include <cassert>

class Quaternion; // Forward declaration

class EulerAngle {
public:
    float a, b, c; // rotate angle a by X axes, angle b by Y axes, angle c by Z axes
    float x, y, z; // position

    // Constructor with individual parameters
    EulerAngle(float a, float b, float c, float x, float y, float z);

    // Constructor with array
    EulerAngle(const std::vector<float>& m);

    // Get the point as a vector
    std::vector<float> getPoint() const;

    // Get the rotation matrix R and transition matrix T, return T*R
    std::vector<std::vector<float>> toMatrix() const;

    // Convert 2D matrix to 1D
    std::vector<float> toOneDMatrix() const;

    // Convert euler angle to quaternion (from wikipedia)
    Quaternion toQuaternion() const;

private:
    // Helper function for cosine
    float cosf(float angle) const;

    // Helper function for sine
    float sinf(float angle) const;

    // Matrix multiplication helper
    static std::vector<std::vector<float>> multiplyMatrix(
        const std::vector<std::vector<float>>& A,
        const std::vector<std::vector<float>>& B);

    // Matrix conversion helper
    static std::vector<float> convertMatrix(const std::vector<std::vector<float>>& matrix);
};

#endif // EULERANGLE_H