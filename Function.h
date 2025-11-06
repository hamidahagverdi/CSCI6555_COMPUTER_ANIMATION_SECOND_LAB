#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>

class EulerAngle;
class Quaternion;

class Function {
public:
    // Matrix multiplication
    static std::vector<std::vector<float>> multiplyMatrix(
        const std::vector<std::vector<float>>& a,
        const std::vector<std::vector<float>>& b);

    // Convert 2D matrix to 1D
    static std::vector<float> convertMatrix(const std::vector<std::vector<float>>& m);

    // Vector normalization (modifies vector in place)
    static void vectorNormal(std::vector<float>& v);

    // Vector cross product
    static std::vector<float> vectorCross(const std::vector<float>& a, const std::vector<float>& b);

    // Vector dot product
    static float vectorDot(const std::vector<float>& a, const std::vector<float>& b);

    // Display matrix
    static void displayProduct(const std::vector<std::vector<float>>& product);

    // Print matrix
    static void printMatrix(const std::vector<float>& m);

    // Blending Function: Q(t) = T*M*G, finding out the vector position of time t
    static std::vector<float> blend(
        const std::vector<std::vector<float>>& T,
        const std::vector<std::vector<float>>& MS,
        const std::vector<std::vector<float>>& G);

    // Euler angle interpolation
    static EulerAngle eInterpolation(const std::string& splineType, float t, int pointIndex);

    // Quaternion interpolation
    static Quaternion qInterpolation(const std::string& splineType, float t, int pointIndex);
};

#endif // FUNCTION_H