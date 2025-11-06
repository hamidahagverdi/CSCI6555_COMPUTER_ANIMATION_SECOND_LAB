#include "EulerAngle.h"
#include "Quaternion.h" // Include the Quaternion header

// Constructor with individual parameters
EulerAngle::EulerAngle(float a, float b, float c, float x, float y, float z)
    : a(a), b(b), c(c), x(x), y(y), z(z) {
    // a,b,c represent x_angle, y_angle, z_angle in Euler angle
    // x,y,z represent the position in world Cartesian System
}

// Constructor with array
EulerAngle::EulerAngle(const std::vector<float>& m) {
    assert(m.size() == 6 && "Not a valid euler angle");
    this->a = m[0];
    this->b = m[1];
    this->c = m[2];
    this->x = m[3];
    this->y = m[4];
    this->z = m[5];
}

// Get the point as a vector
std::vector<float> EulerAngle::getPoint() const {
    return {a, b, c, x, y, z};
}

// Get the rotation matrix R and transition matrix T, return T*R
std::vector<std::vector<float>> EulerAngle::toMatrix() const {
    // if rotate about z first, then y, then x
    std::vector<std::vector<float>> Rz = {
        {cosf(c), -sinf(c), 0, 0},
        {sinf(c), cosf(c), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    
    std::vector<std::vector<float>> Ry = {
        {cosf(b), 0, sinf(b), 0},
        {0, 1, 0, 0},
        {-sinf(b), 0, cosf(b), 0},
        {0, 0, 0, 1}
    };
    
    std::vector<std::vector<float>> Rx = {
        {1, 0, 0, 0},
        {0, cosf(a), -sinf(a), 0},
        {0, sinf(a), cosf(a), 0},
        {0, 0, 0, 1}
    };
    
    std::vector<std::vector<float>> T = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };
    
    std::vector<std::vector<float>> R = multiplyMatrix(Rx, Ry);
    R = multiplyMatrix(R, Rz);
    return multiplyMatrix(T, R);
}

// Convert 2D matrix to 1D
std::vector<float> EulerAngle::toOneDMatrix() const {
    std::vector<std::vector<float>> matrix = toMatrix();
    return convertMatrix(matrix);
}

// Convert euler angle to quaternion (from wikipedia)
Quaternion EulerAngle::toQuaternion() const {
    float half_a = this->a / 2;
    float half_b = this->b / 2;
    float half_c = this->c / 2;
    
    float w = cosf(half_c) * cosf(half_b) * cosf(half_a) + sinf(half_c) * sinf(half_b) * sinf(half_a);
    float qx = sinf(half_c) * cosf(half_b) * cosf(half_a) - cosf(half_c) * sinf(half_b) * sinf(half_a);
    float qy = cosf(half_c) * sinf(half_b) * cosf(half_a) + sinf(half_c) * cosf(half_b) * sinf(half_a);
    float qz = cosf(half_c) * cosf(half_b) * sinf(half_a) - sinf(half_c) * sinf(half_b) * cosf(half_a);
    
    return Quaternion(w, qx, qy, qz, this->x, this->y, this->z);
}

// Helper function for cosine
float EulerAngle::cosf(float angle) const {
    return std::cos(angle);
}

// Helper function for sine
float EulerAngle::sinf(float angle) const {
    return std::sin(angle);
}

// Matrix multiplication helper (4x4 matrices)
std::vector<std::vector<float>> EulerAngle::multiplyMatrix(
    const std::vector<std::vector<float>>& A,
    const std::vector<std::vector<float>>& B) {
    
    int rows = A.size();
    int cols = B[0].size();
    int inner = B.size();
    
    std::vector<std::vector<float>> result(rows, std::vector<float>(cols, 0.0f));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < inner; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return result;
}

// Matrix conversion helper (2D to 1D, row-major order)
std::vector<float> EulerAngle::convertMatrix(const std::vector<std::vector<float>>& matrix) {
    std::vector<float> result;
    
    for (const auto& row : matrix) {
        for (float val : row) {
            result.push_back(val);
        }
    }
    
    return result;
}