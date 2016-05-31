//
// Created by anna on 29.05.2016.
//

#include <render_object.h>
#include "Water.h"
#include <time.h>

Water::Water() {

}

Water::~Water() {

}


Water::Water(int x, int y,
             float unit, RenderObject* renderObject)
        : x(x), y(y), unit(unit), renderObject(renderObject), rippleFrequency(2) {
    //initialize normals : X x Y
    for (int i = 0; i < y; i++) {
        std::vector<glm::vec3> row_n;
        std::vector<float> row_h;
        for (int j = 0; j < x; j++) {
            row_n.push_back(glm::vec3(0,1,0));
            row_h.push_back(0);
        }
        normals.push_back(row_n);
        heights.push_back(row_h);
    }
    srand (time(NULL));
}

void Water::Update() {
    renderObject->update();

    //simulate falling droplets
    int probability = rand() & 1000 + 1;
    if (probability<=rippleFrequency) {
        int posX = rand() % (x - 1);
        int posY = rand() % (y - 1);
        NewRipple(posX, posY);
    }

    //here update A and B if dt/c/h will be changed during program execution
    //clear normals and heights
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            normals[i][j] = glm::vec3(0,1,0); //TODO: check if 0.0.1 can be later normalized
            heights[i][j] = 0;
        }
    }
    //memset(&heights, 0, sizeof(float) * x * y);
    //update ripples
    for (auto &r : ripples) {
        r.UpdateRipple();
    }

    //get heights from all ripples
    for (auto &r : ripples) {
        int startXindex = r.vertexX - RIPPLE_SIZE/2;
        int startYindex = r.vertexY - RIPPLE_SIZE/2;

        for (int i = 0 ; i<RIPPLE_SIZE; i++)
            for (int j = 0; j<RIPPLE_SIZE; j++) {
                if (startYindex + i>=0 && startXindex + j>=0 && startYindex + i<y && startXindex + j<x){
                    heights[startYindex + i][startXindex + j] += r.rippleHeights[i][j];
                }
            }
    }
    //calculate global normals
    //calculate normals for each triangle on the surface, number of squares per row = x-1/y-1
    std::vector<Vertex> vertices = renderObject->getModel()->getMesh(0)->getVertices();
    for (int i = 0; i<y-1; i++) {
        for (int j = 0; j<x-1; j++) {
            //vertexes in the currect square
            glm::vec3 p1 = glm::vec3(0, heights[i][j], 0);
            glm::vec3 p2 = glm::vec3(0, heights[i][j+1], 0);
            glm::vec3 p3 = glm::vec3(0, heights[i+1][j], 0);
            glm::vec3 p4 = glm::vec3(0, heights[i+1][j+1], 0);
            p1 += vertices[(x*i)+j].Position;
            p2 += vertices[(x*i)+j+1].Position;
            p3 += vertices[(x*(i+1))+j].Position;
            p4 += vertices[(x*(i+1))+j+1].Position;

            //upper triange normal calculations
            ClculateTriangleNormal(i, j, p1, p2, p3);
            //lower triange normal calculations
            ClculateTriangleNormal(i, j, p3, p2, p4);
        }
    }


    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            normals[i][j] = glm::normalize(normals[i][j]);
        }
    }
}

void Water::Render(const Program& program){
    renderObject->render(program);
}

void Water::NewRipple(int vertexX, int vertexY) {
    ripples.push_back(WaterRipple(vertexX, vertexY, x, y));
}

const std::vector<std::vector<glm::vec3>>& Water::getNormals(){
    return normals;
}

void Water::ClculateTriangleNormal(int i, int j, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3){
    glm::vec3 V;
    glm::vec3 U;
    glm::vec3 normal;
    //base vectors calculations
    U= p2 - p1;
    V= p3 - p1;
    //cross product to get normal
    normal = glm::cross(U, V);
    /*normal.x += (U.y * V.z) - (U.z * V.y);
    normal.y += (U.z * V.x) - (U.x * V.z);
    normal.z += (U.x * V.y) - (U.y * V.x);*/
    //add new normal to 3 vertexes of the triangle
    normals[i][j] += normal;
    normals[i][j + 1] += normal;
    normals[i + 1][j] += normal;


    // NORMALS HACKS
    if(normals[i][j].y == 0 && normals[i][j].x == 0 && normals[i][j].z == 0){
        normals[i][j].x = 0;
        normals[i][j].y = 1;
        normals[i][j].z = 0;
    }
    if(isnan(normals[i][j].x) || isnan(normals[i][j].y) || isnan(normals[i][j].z)){
        normals[i][j].x = 0;
        normals[i][j].y = 1;
        normals[i][j].z = 0;
    }
}


