//
// Created by anna on 29.05.2016.
//

#include "Water.h"

Water::Water() {

}

Water::~Water() {

}


Water::Water(int x, int y, float unit) : x(x), y(y), unit(unit) {
    MeshLoader meshLoader;
    mesh = meshLoader.LoadPlane(x, y, unit);

    //initialize normals : X x Y
    for (int i = 0; i < y; i++) {
        std::vector<glm::vec3> row;
        for (int j = 0; j < x; j++) {
            row.push_back(glm::vec3(0,1,0));
        }
        normals.push_back(row);
    }
}

void Water::Update() {
    //here update A and B if dt/c/h will be changed during program execution
    //clear normals
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            normals[i][j] = glm::vec3(0,0,1); //TODO: check if 0.0.1 can be later normalized
        }
    }
    //update ripples
    for (auto &r : ripples) {
        r.UpdateRipple();
    }
    //calculate global normals
    //get normals from all ripples and create global normal matrix
    for (auto &r : ripples) {
        int startXindex = r.vertexX - RIPPLE_SIZE/2;
        int startYindex = r.vertexY - RIPPLE_SIZE/2;

        for (int i = 0 ; i<RIPPLE_SIZE; i++)
            for (int j = 0; j<RIPPLE_SIZE; j++) {
                if (startYindex + i>=0 && startXindex + j>=0 && startYindex + i<y && startXindex + j<x)
                    normals[startYindex + i][startXindex + j] += r.normals[i][j];
            }
    }
}

void Water::Render(const Program& program){
    mesh.draw(program);
}

void Water::NewRipple(int vertexX, int vertexY) {
    ripples.push_back(WaterRipple(vertexX, vertexY, &mesh, x, y));
}

const std::vector<std::vector<glm::vec3>>& Water::getNormals(){
    return normals;
}



