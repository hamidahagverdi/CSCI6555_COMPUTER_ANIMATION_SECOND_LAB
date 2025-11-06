#include <GLUT/glut.h>  // macOS uses GLUT/glut.h instead of GL/glut.h
#include "GlobalVariables.h"
#include "MyEventListener.h"
#include <iostream>

// Global instance of event listener
MyEventListener* eventListener = nullptr;

// Display callback function
void display() {
    if (eventListener) {
        eventListener->display();
    }
    glutSwapBuffers();
}

// Reshape callback function
void reshape(int width, int height) {
    if (eventListener) {
        eventListener->reshape(width, height);
    }
}

// Idle callback for animation (called continuously)
void idle() {
    if (eventListener) {
        eventListener->idle();
    }
    glutPostRedisplay();
}

// Keyboard callback
void keyboard(unsigned char key, int x, int y) {
    if (eventListener) {
        eventListener->keyboard(key, x, y);
    }
}

// Special key callback (arrow keys, function keys, etc.)
void specialKeys(int key, int x, int y) {
    if (eventListener) {
        eventListener->specialKeys(key, x, y);
    }
}

// Mouse callback
void mouse(int button, int state, int x, int y) {
    if (eventListener) {
        eventListener->mouse(button, state, x, y);
    }
}

// Mouse motion callback
void motion(int x, int y) {
    if (eventListener) {
        eventListener->motion(x, y);
    }
}

// Initialize OpenGL
void init() {
    if (eventListener) {
        eventListener->init();
    }
}

int main(int argc, char** argv) {
    // Getting the capabilities object of GL2 profile (handled by GLUT initialization)
    glutInit(&argc, argv);
    
    // Set display mode (double buffer, RGBA color, depth buffer)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    // The canvas - set window size
    glutInitWindowSize(GlobalVariables::WIDTH, GlobalVariables::HEIGHT);
    
    // Set window position (centered on screen)
    glutInitWindowPosition(
        (glutGet(GLUT_SCREEN_WIDTH) - GlobalVariables::WIDTH) / 2,
        (glutGet(GLUT_SCREEN_HEIGHT) - GlobalVariables::HEIGHT) / 2
    );
    
    // Creating frame - create window
    glutCreateWindow("Lab2 Hierarchical Object Motion Control System by Chuchu Jin");
    
    // Create event listener
    eventListener = new MyEventListener();
    
    // Initialize OpenGL settings
    init();
    
    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    // Instantiating and Initiating Animator (60 FPS via idle callback)
    glutMainLoop();
    
    // Cleanup
    delete eventListener;
    
    return 0;
}