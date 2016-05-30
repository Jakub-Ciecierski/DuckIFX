//
// Created by jakub on 5/30/16.
//

#include <iostream>
#include "duck_path.h"

using namespace std;
using namespace glm;

DuckPath::DuckPath(RenderObject* duck,
                   float xMin, float xMax,
                   float zMin, float zMax,
                   float y){
    this->duck = duck;

    this->xMin = xMin;
    this->xMax = xMax;

    this->zMin = zMin;
    this->zMax = zMax;

    this->y = y;

    bspline = NULL;

    generateNextBSpline();
}

DuckPath::~DuckPath() {

}

glm::vec3 DuckPath::computePosition(float dt) {
    glm::vec3 pos = bspline->computeBSpline(dt);
    duck->rotate(glm::vec3(0.0f, dt, 0.0f));
    if(bspline->t >= bspline->t_max){
        cout << "Generating new BSpline" << endl;
        generateNextBSpline();
    }

    return pos;
}

void DuckPath::generateNextBSpline() {
    vector<vec3> controlPoints;
    controlPoints.push_back(duck->getPosition());

    int count = 6;
    for(int i = 1; i < count; i++){
        float x = randomFloat(xMin, xMax);
        float y = this->y;
        float z = randomFloat(zMin, zMax);

        controlPoints.push_back(vec3(x, y, z));
    }

    if(bspline != NULL){
        delete bspline;
    }

    bspline = new BSpline(controlPoints);

}

float DuckPath::randomFloat(float min, float max){
    float random = ((float) rand()) / (float) RAND_MAX;
    float range = max - min;
    return (random*range) + min;
}