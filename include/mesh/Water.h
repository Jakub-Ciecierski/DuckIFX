//
// Created by anna on 29.05.2016.
//

#ifndef DUCK_WATER_H
#define DUCK_WATER_H

#include "mesh_loader.h"
#include "WaterRipple.h"

class Water {
    Mesh mesh;
    int x;
    int y;
    float unit;


    std::vector<WaterRipple> ripples;
    std::vector<std::vector<glm::vec3>> normals;
public:
    Water();
    Water(int x, int y, float unit);
    ~Water();

    void NewRipple(int vertexX, int vertexY);
    void Update();

    const std::vector<std::vector<glm::vec3>>& getNormals();
};


#endif //DUCK_WATER_H
