//
// Created by anna on 29.05.2016.
//

#ifndef DUCK_WATER_H
#define DUCK_WATER_H

#include "mesh_loader.h"
#include "WaterRipple.h"

class Water {
    RenderObject* renderObject;

    //between 0-100, probability per frame of ripple occuring on the water surface
    int rippleFrequency;
    int x;
    int y;
    float unit;

    std::vector<WaterRipple> ripples;
    std::vector<std::vector<float>> heights;
    std::vector<std::vector<glm::vec3>> normals;

    void ClculateTriangleNormal(int i, int j, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
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
