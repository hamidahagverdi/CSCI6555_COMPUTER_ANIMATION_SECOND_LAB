#ifndef MYEVENTLISTENER_H
#define MYEVENTLISTENER_H

#include "Torso.h"
#include "LeftLeg.h"
#include "RightLeg.h"

class MyEventListener {
public:
    MyEventListener();
    ~MyEventListener();
    
    // Main callback functions
    void display();
    void init();
    void reshape(int width, int height);
    void idle();
    
    // Input callbacks
    void keyboard(unsigned char key, int x, int y);
    void specialKeys(int key, int x, int y);
    void mouse(int button, int state, int x, int y);
    void motion(int x, int y);

private:
    Torso* torso;
    LeftLeg* leftLeg;
    RightLeg* rightLeg;
    
    float t;
    int pointIndex;
    
    // Helper function to enable OpenGL settings
    void Enable();
};

#endif // MYEVENTLISTENER_H