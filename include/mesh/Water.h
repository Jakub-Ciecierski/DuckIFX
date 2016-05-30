//
// Created by anna on 29.05.2016.
//

#ifndef DUCK_WATER_H
#define DUCK_WATER_H

#include "mesh_loader.h"
#include "WaterRipple.h"

class Water {
    RenderObject* renderObject;

    int x;
    int y;
    float unit;

    std::vector<WaterRipple> ripples;
    std::vector<std::vector<glm::vec3>> normals;
public:
    Water();
    Water(int x, int y, float unit, RenderObject* renderObject);
    ~Water();

    void NewRipple(int vertexX, int vertexY);
    void Update();
    void Render(const Program& program);

    const std::vector<std::vector<glm::vec3>>& getNormals();
};


#endif //DUCK_WATER_H
