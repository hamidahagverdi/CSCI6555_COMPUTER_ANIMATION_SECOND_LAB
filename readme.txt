*Name:* Hamida Hagverdiyeva

Email: hamida.hagverdiyeva@gwmail.gwu.edu

Hierarchical Object Motion Control System
A C++ implementation of a 3D hierarchical object animation system using OpenGL and GLUT. The system animates a hierarchical structure (torso with legs) along a spline-based trajectory.
Project Overview
This project demonstrates:

Hierarchical modeling and animation
Spline-based motion (Catmull-Rom and B-Spline)
Euler angle and Quaternion representations
3D transformations and matrix operations

## Requirements

- macOS with Xcode Command Line Tools
- OpenGL and GLUT frameworks (built-in on macOS)
- C++11 or later

Project Structure
EulerAngle.h          EulerAngle.cpp
Quaternion.h          Quaternion.cpp
Function.h            Function.cpp
GlobalVariables.h     GlobalVariables.cpp
Torso.h               Torso.cpp
LeftLeg.h             LeftLeg.cpp
RightLeg.h            RightLeg.cpp
MyEventListener.h     MyEventListener.cpp

Compilation
To compile the project, navigate to the project directory and run:
```g++ -std=c++11 main.cpp EulerAngle.cpp Quaternion.cpp Function.cpp GlobalVariables.cpp Torso.cpp LeftLeg.cpp RightLeg.cpp MyEventListener.cpp -o hierarchical -framework OpenGL -framework GLUT```

Running the Program
After successful compilation, run:
```./hierarchical```

Customizing the Trajectory
You can modify the animation path by editing the trajectory points in GlobalVariables.cpp:
```// Position x,y,z in world Cartesian System
const std::vector<std::vector<float>> GlobalVariables::position = {
    {8, 0, -20},    // point 1
    {-8, 0, -20},   // point 2
    {-5, 0, -10},   // point 3
    {5, 0, -10},    // point 4
    {3, 0, -5},     // point 5
    {-3, 0, -5},    // point 6
    {1, 0, -3}      // point 7
};```
Each point is defined as {x, y, z} coordinates in world space. After modifying, recompile the project.


