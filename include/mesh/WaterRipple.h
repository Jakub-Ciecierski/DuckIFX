//
// Created by anna on 30.05.2016.
//

#ifndef DUCK_WATERRIPPLE_H
#define DUCK_WATERRIPPLE_H

#include <glm/gtc/type_ptr.hpp>
#include "mesh.h"

#define RIPPLE_SIZE 256

class WaterRipple {
    Mesh* waterSurface;
    //dimentions of water surpace
    float waterX;
    float waterY;

    float rippleHeights[RIPPLE_SIZE][RIPPLE_SIZE];
    float prev_rippleHeights[RIPPLE_SIZE][RIPPLE_SIZE];

    float d[RIPPLE_SIZE][RIPPLE_SIZE];
    float h = 2/(RIPPLE_SIZE)-1;
    float c = 1;
    float dt = 1/(RIPPLE_SIZE);

    float A;
    float B;

    void ClculateTriangleNormal(int i, int j, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
public:
    //indexes of the center of the ripple
    int vertexX;
    int vertexY;
    glm::vec3 normals[RIPPLE_SIZE][RIPPLE_SIZE];

    WaterRipple();
    WaterRipple(int vertexX, int vertexY, Mesh* waterSurface, int waterX, int waterY);
    //~WaterRipple();
    void UpdateRipple();
};


#endif //DUCK_WATERRIPPLE_H
