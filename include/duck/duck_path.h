//
// Created by jakub on 5/30/16.
//

#ifndef DUCK_DUCKPATH_H
#define DUCK_DUCKPATH_H


#include <render_object.h>
#include "../../src/duck/bspline.h"

class DuckPath {
private:
    RenderObject* duck;

    float xMin;
    float xMax;
    float zMin;
    float zMax;
    float y;

    BSpline* bspline;

    void generateNextBSpline();
    float randomFloat(float min, float max);
public:

    DuckPath(RenderObject* duck,
             float xMin, float xMax,
             float zMin, float zMax, float y);

    ~DuckPath();

    glm::vec3 computePosition(float dt);

};


#endif //DUCK_DUCKPATH_H
