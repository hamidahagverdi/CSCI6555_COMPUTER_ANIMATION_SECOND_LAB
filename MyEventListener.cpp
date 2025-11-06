#include "MyEventListener.h"
#include "GlobalVariables.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

MyEventListener::MyEventListener() : t(0.0f), pointIndex(0) {
    torso = new Torso();
    leftLeg = new LeftLeg(*torso);
    rightLeg = new RightLeg(*torso);
}

MyEventListener::~MyEventListener() {
    delete torso;
    delete leftLeg;
    delete rightLeg;
}

void MyEventListener::Enable() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // default
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK); // default
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    // Light source attributes
    float LightAmbient[] = { 1.0f, 0.4f, 0.7f, 1.0f };  // Pink ambient light
    float LightDiffuse[] = { 1.0f, 0.5f, 0.8f, 1.0f };  // Pink diffuse light
    //float LightAmbient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    //float LightDiffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    
    float LightSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float LightPosition[] = { 5.0f, 5.0f, 5.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

    // Surface material attributes
    float material_Ka[] = { 1.0f, 0.7f, 0.85f, 1.0f };   // Light pink ambient
    float material_Kd[] = { 1.0f, 0.6f, 0.8f, 1.0f };    // Pink diffuse
    float material_Ks[] = { 1.0f, 0.8f, 0.9f, 1.0f };    // Bright pink specular (highlights)
    float material_Ke[] = { 0.3f, 0.1f, 0.2f, 1.0f };    // Subtle pink emission
    //float material_Ka[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    //float material_Kd[] = { 0.43f, 0.47f, 0.54f, 1.0f };
    //float material_Ks[] = { 0.33f, 0.33f, 0.52f, 1.0f };
    //float material_Ke[] = { 0.1f, 0.0f, 0.1f, 1.0f };
    float material_Se = 10.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT, GL_SHININESS, material_Se);
}

void MyEventListener::display() {
    Enable();
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);  // Sky blue background
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    torso->setT(t);
    torso->setPointIndex(pointIndex);
    std::vector<float> torsoMatrix = torso->toOneDMatrix();
    glLoadMatrixf(torsoMatrix.data());
    glutSolidSphere(0.8, 20, 20);

    leftLeg->setT(t);
    std::vector<float> leftLegMatrix = leftLeg->toOneDMatrix();
    glLoadMatrixf(leftLegMatrix.data());
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    GLUquadric* quad1 = gluNewQuadric();
    gluCylinder(quad1, 0.15, 0.15, 2.0, 20, 20);
    gluDeleteQuadric(quad1);

    rightLeg->setT(t);
    std::vector<float> rightLegMatrix = rightLeg->toOneDMatrix();
    glLoadMatrixf(rightLegMatrix.data());
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    GLUquadric* quad2 = gluNewQuadric();
    gluCylinder(quad2, 0.15, 0.15, 2.0, 20, 20);
    gluDeleteQuadric(quad2);

    glFlush();

    // Timer
    t = t + 0.005f;
    if (t >= 1.0f) {
        t = 0.0f;
        if (pointIndex < GlobalVariables::pointNum - 1) {
            pointIndex++;
        } else {
            pointIndex = 0;
        }
    }
}

void MyEventListener::init() {
    // Initialization code (empty in original Java)
}

void MyEventListener::reshape(int width, int height) {
    // Viewport
    glViewport(0, 0, width, height);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, (float)width / (float)height, 1.0, 30.0);
}

void MyEventListener::idle() {
    // Called continuously for animation
    // Animation is handled in display() function
}

void MyEventListener::keyboard(unsigned char key, int x, int y) {
    // Handle keyboard input (add your implementation)
}

void MyEventListener::specialKeys(int key, int x, int y) {
    // Handle special keys like arrow keys (add your implementation)
}

void MyEventListener::mouse(int button, int state, int x, int y) {
    // Handle mouse input (add your implementation)
}

void MyEventListener::motion(int x, int y) {
    // Handle mouse motion (add your implementation)
}