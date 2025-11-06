#ifndef TORSO_H
#define TORSO_H

#include <vector>

class Torso {
public:
    // Public member for use by LeftLeg and RightLeg
    std::vector<std::vector<float>> Matrix;
    
    // Constructor
    Torso();
    
    // Setters
    void setTorsoPosition(const std::vector<float>& torsoPosition);
    void setTangent(std::vector<float> tangent);
    void setNormal(std::vector<float> normal);
    void setBiNormal(std::vector<float> biNormal);
    void setT(float t);
    void setPointIndex(int pointIndex);
    
    // Get transformation matrix
    std::vector<std::vector<float>> toMatrix();
    
    // Convert 2D matrix to 1D
    std::vector<float> toOneDMatrix();

private:
    std::vector<float> torsoPosition; // position of torso
    std::vector<float> tangent;       // torso facing tangent
    std::vector<float> biNormal;
    std::vector<float> normal;
    float t;
    int pointIndex;
    int loopIndex;
    
    // Interpolation function
    void torsoInterpolate();
};

#endif // TORSO_H