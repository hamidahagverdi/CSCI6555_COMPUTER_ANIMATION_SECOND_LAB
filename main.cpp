#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <cmath>
#include <cassert>
#include <vector>
#include <string>
#include <iostream>

/* =========================================================
   GLOBAL VARIABLES
   - Window size
   - Spline matrices (Catmull-Rom & B-Spline)
   - Control points for motion and orientation
   ========================================================= */
class GlobalVariables {
public:
    static const int WIDTH;
    static const int HEIGHT;

    static const float a;
    static const std::vector<std::vector<float>> CRSplineM;
    static const std::vector<std::vector<float>> BSplineM;

    static const std::vector<std::vector<float>> position;
    static const std::vector<std::vector<float>> points;

    static const int pointNum;
};

const int GlobalVariables::WIDTH = 400;
const int GlobalVariables::HEIGHT = 400;
const float GlobalVariables::a = 0.5f;

const std::vector<std::vector<float>> GlobalVariables::CRSplineM = {
    {-a, 2.0f - a, a - 2.0f, a},
    {2.0f * a, a - 3.0f, 3.0f - 2.0f * a, -a},
    {-a, 0.0f, a, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f}
};

const std::vector<std::vector<float>> GlobalVariables::BSplineM = {
    {-1.0f / 6, 3.0f / 6, -3.0f / 6, 1.0f / 6},
    {3.0f / 6, -6.0f / 6, 3.0f / 6, 0.0f},
    {-3.0f / 6, 0.0f, 3.0f / 6, 0.0f},
    {1.0f / 6, 4.0f / 6, 1.0f / 6, 0.0f}
};

const std::vector<std::vector<float>> GlobalVariables::position = {
    {8, 0, -20}, {-8, 0, -20}, {-5, 0, -10},
    {5, 0, -10}, {3, 0, -5}, {-3, 0, -5}, {1, 0, -3}
};

const std::vector<std::vector<float>> GlobalVariables::points = {
    {90,0,45,-5,0,-5}, {70,20,65,-3,3,-10}, {50,40,85,-1,1,-15},
    {30,60,105,0,-5,-20}, {50,40,85,1,1,-15},
    {70,20,65,3,3,-10}, {90,0,45,5,0,-5}
};

const int GlobalVariables::pointNum = (int)GlobalVariables::position.size();

/* =========================================================
   FUNCTION UTILITIES
   - Matrix multiplication
   - Vector math (normalize, cross product)
   - Generic spline blending function
   ========================================================= */
class EulerAngle;
class Quaternion;

class Function {
public:
    static std::vector<std::vector<float>> multiplyMatrix(
        const std::vector<std::vector<float>>& a,
        const std::vector<std::vector<float>>& b);

    static std::vector<float> convertMatrix(const std::vector<std::vector<float>>& m);
    static void vectorNormal(std::vector<float>& v);
    static std::vector<float> vectorCross(const std::vector<float>& a, const std::vector<float>& b);
    static std::vector<float> blend(
        const std::vector<std::vector<float>>& T,
        const std::vector<std::vector<float>>& MS,
        const std::vector<std::vector<float>>& G);
};

/* =========================================================
   QUATERNION
   - Stores rotation + position
   - Converts quaternion to transformation matrix
   ========================================================= */
class Quaternion {
public:
    float w,x,y,z,px,py,pz;
    Quaternion(float w,float x,float y,float z,float px,float py,float pz);
    Quaternion(const std::vector<float>& m);
    std::vector<float> getPoint() const;
    std::vector<std::vector<float>> toMatrix() const;
    std::vector<float> toOneDMatrix() const;
private:
    void Normalization();
};

/* =========================================================
   EULER ANGLE
   - Stores Euler rotation + position
   - Converts Euler angles to matrix
   - Converts Euler angles to quaternion
   ========================================================= */
class EulerAngle {
public:
    float a,b,c,x,y,z;
    EulerAngle(float a,float b,float c,float x,float y,float z);
    EulerAngle(const std::vector<float>& m);
    std::vector<std::vector<float>> toMatrix() const;
    std::vector<float> toOneDMatrix() const;
    Quaternion toQuaternion() const;
};

/* =========================================================
   TORSO (PARENT OBJECT)
   - Moves along spline path
   - Builds Frenet frame (tangent, normal, binormal)
   - Provides parent transformation matrix
   ========================================================= */
class Torso {
public:
    std::vector<std::vector<float>> Matrix;
    Torso();
    void setT(float t);
    void setPointIndex(int index);
    std::vector<float> toOneDMatrix();
private:
    std::vector<float> pos,tangent,normal,binormal;
    float t;
    int pointIndex, loopIndex;
    void torsoInterpolate();
};

/* =========================================================
   LEFT LEG & RIGHT LEG
   - Child objects of torso
   - Use torso matrix as parent
   - Animate using sinusoidal rotation
   ========================================================= */
class LeftLeg {
public:
    LeftLeg(Torso& torso);
    void setT(float t);
    std::vector<float> toOneDMatrix();
private:
    float t;
    Torso* torso;
};

class RightLeg {
public:
    RightLeg(Torso& torso);
    void setT(float t);
    std::vector<float> toOneDMatrix();
private:
    float t;
    Torso* torso;
};

/* =========================================================
   EVENT LISTENER
   - Handles OpenGL state
   - Draws torso and legs
   - Updates animation time & spline index
   ========================================================= */
class MyEventListener {
public:
    MyEventListener();
    ~MyEventListener();
    void display();
    void reshape(int w,int h);
    void idle();
private:
    Torso* torso;
    LeftLeg* leftLeg;
    RightLeg* rightLeg;
    float t;
    int pointIndex;
    void Enable();
};

/* =========================================================
   GLUT CALLBACK WRAPPERS
   ========================================================= */
MyEventListener* eventListener=nullptr;

void displayCB(){ eventListener->display(); glutSwapBuffers(); }
void reshapeCB(int w,int h){ eventListener->reshape(w,h); }
void idleCB(){ eventListener->idle(); glutPostRedisplay(); }

/* =========================================================
   MAIN FUNCTION
   - Initializes GLUT
   - Creates window
   - Registers callbacks
   - Starts render loop
   ========================================================= */
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(GlobalVariables::WIDTH,GlobalVariables::HEIGHT);
    glutCreateWindow("Lab2 Hierarchical Object Motion Control System");

    glEnable(GL_DEPTH_TEST);

    eventListener = new MyEventListener();

    glutDisplayFunc(displayCB);
    glutReshapeFunc(reshapeCB);
    glutIdleFunc(idleCB);

    glutMainLoop();
    return 0;
}
