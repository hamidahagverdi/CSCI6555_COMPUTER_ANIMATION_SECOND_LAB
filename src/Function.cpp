#include "Function.h"
#include "EulerAngle.h"
#include "Quaternion.h"
#include "GlobalVariables.h"
#include <iostream>
#include <cmath>
#include <cassert>

// Matrix multiplication
std::vector<std::vector<float>> Function::multiplyMatrix(
    const std::vector<std::vector<float>>& a,
    const std::vector<std::vector<float>>& b) {
    
    assert(a[0].size() == b.size() && "Matrix can't be multiplied");
    
    std::vector<std::vector<float>> product(a.size(), std::vector<float>(b[0].size(), 0.0f));
    
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < b[0].size(); j++) {
            for (size_t k = 0; k < a[0].size(); k++) {
                product[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    return product;
}

// Convert 2D matrix to 1D
std::vector<float> Function::convertMatrix(const std::vector<std::vector<float>>& m) {
    std::vector<float> M(m.size() * m[0].size());
    
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m[0].size(); j++) {
            M[i + j * m.size()] = m[i][j];
        }
    }
    
    return M;
}

// Vector normalization (modifies vector in place)
void Function::vectorNormal(std::vector<float>& v) {
    assert(v.size() == 3 && "invalid vector");
    
    float x = v[0];
    float y = v[1];
    float z = v[2];
    float magnitude = std::sqrt(x*x + y*y + z*z);
    
    // Avoid divide by 0
    if (magnitude != 0) {
        x = x / magnitude;
        y = y / magnitude;
        z = z / magnitude;
    }
    
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

// Vector cross product
std::vector<float> Function::vectorCross(const std::vector<float>& a, const std::vector<float>& b) {
    assert(a.size() == 3 && b.size() == 3 && "invalid vector");
    
    std::vector<float> cross(3);
    cross[0] = a[1] * b[2] - b[1] * a[2];
    cross[1] = a[2] * b[0] - b[2] * a[0];
    cross[2] = a[0] * b[1] - b[0] * a[1];
    
    return cross;
}

// Vector dot product
float Function::vectorDot(const std::vector<float>& a, const std::vector<float>& b) {
    assert(a.size() == 3 && b.size() == 3 && "invalid vector");
    
    float dot = 0;
    for (size_t i = 0; i < a.size(); i++) {
        dot += a[i] * b[i];
    }
    
    return dot;
}

// Display matrix
void Function::displayProduct(const std::vector<std::vector<float>>& product) {
    std::cout << "Product matrix is: " << std::endl;
    for (const auto& row : product) {
        for (float column : row) {
            std::cout << column << "    ";
        }
        std::cout << std::endl;
    }
}

// Print matrix
void Function::printMatrix(const std::vector<float>& m) {
    for (float val : m) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// Blending Function: Q(t) = T*M*G, finding out the vector position of time t
std::vector<float> Function::blend(
    const std::vector<std::vector<float>>& T,
    const std::vector<std::vector<float>>& MS,
    const std::vector<std::vector<float>>& G) {
    
    // B is the result of T*M
    std::vector<std::vector<float>> B = multiplyMatrix(T, MS);
    // Generate the result of T*M*G
    std::vector<std::vector<float>> Qt = multiplyMatrix(B, G);
    
    return convertMatrix(Qt);
}

// Euler angle interpolation
EulerAngle Function::eInterpolation(const std::string& splineType, float t, int pointIndex) {
    std::vector<std::vector<float>> MS;
    
    if (splineType == "Catmull-Rom Spline") {
        MS = GlobalVariables::CRSplineM;
    }
    else if (splineType == "B Spline") {
        MS = GlobalVariables::BSplineM;
    }
    else {
        // Return a default EulerAngle or throw an exception
        return EulerAngle(0, 0, 0, 0, 0, 0);
    }
    
    std::vector<std::vector<float>> T = {{t*t*t, t*t, t, 1}};
    std::vector<std::vector<float>> G(4, std::vector<float>(6));
    
    for (int i = 0; i < 4; i++) {
        // 4 points
        G[i] = GlobalVariables::points[pointIndex + i];
    }
    
    return EulerAngle(blend(T, MS, G));
}

// Quaternion interpolation
Quaternion Function::qInterpolation(const std::string& splineType, float t, int pointIndex) {
    std::vector<std::vector<float>> MS;
    
    if (splineType == "Catmull-Rom Spline") {
        MS = GlobalVariables::CRSplineM;
    }
    else if (splineType == "B Spline") {
        MS = GlobalVariables::BSplineM;
    }
    else {
        // Return a default Quaternion or throw an exception
        return Quaternion(1, 0, 0, 0, 0, 0, 0);
    }
    
    std::vector<std::vector<float>> T = {{t*t*t, t*t, t, 1}};
    std::vector<std::vector<float>> G(4, std::vector<float>(7));
    
    for (int i = 0; i < 4; i++) {
        // 4 points
        EulerAngle e(GlobalVariables::points[pointIndex + i]);
        // Convert points in euler angle to quaternion
        G[i] = e.toQuaternion().getPoint();
    }
    
    return Quaternion(blend(T, MS, G));
}