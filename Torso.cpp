#include "Torso.h"
#include "Function.h"
#include "GlobalVariables.h"

// Constructor
Torso::Torso() : t(0.0f), pointIndex(0), loopIndex(0) {
    torsoPosition.resize(3, 0.0f);
    tangent.resize(3, 0.0f);
    normal.resize(3, 0.0f);
    biNormal.resize(3, 0.0f);
    Matrix.resize(4, std::vector<float>(4, 0.0f));
}

// Setters
void Torso::setTorsoPosition(const std::vector<float>& torsoPosition) {
    this->torsoPosition = torsoPosition;
}

void Torso::setTangent(std::vector<float> tangent) {
    this->tangent = tangent;
    Function::vectorNormal(this->tangent);
}

void Torso::setNormal(std::vector<float> normal) {
    this->normal = normal;
    Function::vectorNormal(this->normal);
}

void Torso::setBiNormal(std::vector<float> biNormal) {
    this->biNormal = biNormal;
    Function::vectorNormal(this->biNormal);
}

void Torso::setT(float t) {
    this->t = t;
}

void Torso::setPointIndex(int pointIndex) {
    this->pointIndex = pointIndex;
}

// Interpolation function
void Torso::torsoInterpolate() {
    // Using Catmull-Rom spline
    std::vector<std::vector<float>> MS = GlobalVariables::CRSplineM;
    
    // Set up T matrix
    std::vector<std::vector<float>> T = {{t*t*t, t*t, t, 1}};
    
    // Set up Tangent T matrix
    std::vector<std::vector<float>> TangentTMatrix = {{3*t*t, 2*t, 1, 0}};
    
    std::vector<std::vector<float>> G(4, std::vector<float>(3));
    for (int i = 0; i < 4; i++) {
        // 4 points
        G[i] = GlobalVariables::position[(pointIndex + i) % GlobalVariables::pointNum];
    }
    
    setTorsoPosition(Function::blend(T, MS, G));
    setTangent(Function::blend(TangentTMatrix, MS, G));
    
    if (pointIndex == 0 && loopIndex == 0) { // loop starts from the beginning
        std::vector<float> TempVector = {1, 0, 0}; // Pick an arbitrary vector V
        Function::vectorNormal(TempVector);
        setNormal(Function::vectorCross(tangent, TempVector));
        setBiNormal(Function::vectorCross(normal, tangent));
        loopIndex++;
    }
    else { // loop does not start from the beginning
        setNormal(Function::vectorCross(tangent, biNormal));
        setBiNormal(Function::vectorCross(normal, tangent));
    }
}

// Get transformation matrix
std::vector<std::vector<float>> Torso::toMatrix() {
    this->torsoInterpolate();
    
    float px = torsoPosition[0];
    float py = torsoPosition[1];
    float pz = torsoPosition[2];
    
    std::vector<std::vector<float>> M = {
        {tangent[0], tangent[1], tangent[2], px},
        {normal[0], normal[1], normal[2], py},
        {biNormal[0], biNormal[1], biNormal[2], pz},
        {0, 0, 0, 1}
    };
    
    this->Matrix = M;
    return M;
}

// Convert 2D matrix to 1D
std::vector<float> Torso::toOneDMatrix() {
    this->toMatrix();
    return Function::convertMatrix(this->Matrix);
}