//
// Created by jakub on 5/26/16.
//

#ifndef DUCK_CONTROLS_H
#define DUCK_CONTROLS_H


#include <camera.h>

class Controls {
private:
    Camera* camera;

    float movementSpeed;
    float rotationSpeed;

    float mouselastX;
    float mouselastY;

    bool mousePressed;

public:

    Controls(Camera* camera,
             float movementSpeed = 0.1f,
             float rotationSpeed = 0.1f);

    ~Controls();

    void setMousePress(bool value);
    bool doMovement();

    void setPressedPosition(float x, float y);

    void onMouseAction(float dx, float dy);
    void onKeyboardAction(int action, int key);
};


#endif //DUCK_CONTROLS_H
