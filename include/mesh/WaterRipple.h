//
// Created by anna on 30.05.2016.
//

#ifndef DUCK_WATERRIPPLE_H
#define DUCK_WATERRIPPLE_H

#include <glm/gtc/type_ptr.hpp>
#include "mesh.h"

#define RIPPLE_SIZE 256

class WaterRipple {
    //dimentions of water surpace
    float waterX;
    float waterY;

    float prev_rippleHeights[RIPPLE_SIZE][RIPPLE_SIZE];

    float d[RIPPLE_SIZE][RIPPLE_SIZE];
    float h = 2.0f/((RIPPLE_SIZE)-1.0f);
    float c = 1.0f;
    float dt = 1.0f/(RIPPLE_SIZE);

    float A;
    float B;
public:
    //indexes of the center of the ripple
    int vertexX;
    int vertexY;
    float rippleHeights[RIPPLE_SIZE][RIPPLE_SIZE];

    WaterRipple();
    WaterRipple(int vertexX, int vertexY, int waterX, int waterY);
    //~WaterRipple();
    void UpdateRipple();
};


#endif //DUCK_WATERRIPPLE_H
