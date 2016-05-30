//
// Created by anna on 30.05.2016.
//

#include "WaterRipple.h"

WaterRipple::WaterRipple() {

}

WaterRipple::WaterRipple(int vertexX, int vertexY, Mesh* waterSurface, int waterX, int waterY)
        : vertexX(vertexX), vertexY(vertexY), waterSurface(waterSurface), waterX(waterX), waterY(waterY){
    //initialize d, ripple, prev_ripple, norlams matrixes : RIPPLE_SIZE x RIPPLE_SIZE
    float l;
    for (int i = 0; i < RIPPLE_SIZE; i++)
        for (int j = 0; j < RIPPLE_SIZE; j++) {
            //TODO: check correctness of value of l
            float distX = j/(RIPPLE_SIZE-1)*2;
            float distY = i/(RIPPLE_SIZE-1)*2;
            distX = (distX <= 1)? distX : 1-distX;
            distY = (distY <= 1)? distY : 1-distY;
            l = glm::min(distX, distY);
            d[i][j] = 0.95f * glm::min(1.0f, l / 0.2f);

            rippleHeights[i][j] = 0;
            prev_rippleHeights[i][j]=0;
            normals[i][j] = glm::vec3(0,0,1);
        }

    A = (c*c*dt*dt)/(h*h);
    B = 2 - 4*A;
}

void WaterRipple::UpdateRipple() {
    //here update A and B if dt/c/h will be changed during program execution

    float middleValues = 0;
    float tmp_rippleHeights[RIPPLE_SIZE][RIPPLE_SIZE];

    for (int i = 0; i < RIPPLE_SIZE; i++)
        for (int j = 0; j < RIPPLE_SIZE; j++) {
            float a1 = (i==RIPPLE_SIZE-1)? 0 : rippleHeights[i+1][j];
            float a2 = (i==0)? 0 : rippleHeights[i-1][j];
            float a3 = (j==RIPPLE_SIZE-1)? 0 : rippleHeights[i][j+1];
            float a4 = (j==0)? 0 : rippleHeights[i][j-1];
            middleValues = a1+a2+a3+a4;
            tmp_rippleHeights[i][j] = d[i][j]*(A*middleValues+B*rippleHeights[i][j]-prev_rippleHeights[i][j]);
        }

    //change arrays
    for (int i = 0; i < RIPPLE_SIZE; i++)
        for (int j = 0; j < RIPPLE_SIZE; j++) {
            prev_rippleHeights[i][j] = rippleHeights[i][j];
            rippleHeights[i][j] = tmp_rippleHeights[i][j];
        }

    //clear normals
    for (int i = 0; i < RIPPLE_SIZE; i++) {
        for (int j = 0; j < RIPPLE_SIZE; j++) {
            normals[i][j] = glm::vec3(0,1,0); //TODO: check if 0.0.1 can be later normalized
        }
    }
    //calculate normals for each triangle on the surface, number of squares per row = RIPPLE_SIZE-1
    std::vector<Vertex> vertices = waterSurface->getVertices();
    int startXindex = vertexX - RIPPLE_SIZE/2;
    int startYindex = vertexY - RIPPLE_SIZE/2;
    int index = (startYindex*waterX) + startXindex; //corresponding index in 1D array


    for (int i = 0; i<RIPPLE_SIZE-1; i++) {
        for (int j = 0; j<RIPPLE_SIZE-1; j++) {
            //vertexes in the currect square
            //TODO: get x and y position - check if correct
            //TODO: check if doesnt overextend
            glm::vec3 p1 = glm::vec3(0, 0, rippleHeights[i][j]);
            glm::vec3 p2 = glm::vec3(0, 0, rippleHeights[i][j+1]);
            glm::vec3 p3 = glm::vec3(0, 0, rippleHeights[i+1][j]);
            glm::vec3 p4 = glm::vec3(0, 0, rippleHeights[i+1][j+1]);
            //check if doesn't overextend
            if (startYindex + i>=0 && startXindex + j>=0 && startYindex + i<waterY && startXindex + j<waterX)
                p1 += vertices[(waterX*i)+index+j].Position;
            if (startYindex + i>=0 && startXindex + j + 1>=0 && startYindex + i<waterY && startXindex + j<waterX)
                p1 += vertices[(waterX*i)+index+j+1].Position;
            if (startYindex + i + 1>=0 && startXindex + j>=0 && startYindex + i<waterY && startXindex + j<waterX)
                p1 += vertices[(waterX*(i+1))+index+j].Position;
            if (startYindex + i + 1>=0 && startXindex + j + 1 >=0 && startYindex + i<waterY && startXindex + j<waterX)
                p1 += vertices[(waterX*(i+1))+index+j+1].Position;

            //upper triange normal calculations
            ClculateTriangleNormal(i, j, p1, p2, p3);
            //lower triange normal calculations
            ClculateTriangleNormal(i, j, p3, p2, p4);
        }
    }
}

void WaterRipple::ClculateTriangleNormal(int i, int j, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3){
    glm::vec3 V;
    glm::vec3 U;
    glm::vec3 normal;
    //base vectors calculations
    U= p2 - p1;
    V= p3 - p1;
    //cross product to get normal
    normal.x += (U.y * V.z) - (U.z * V.y);
    normal.y += (U.z * V.x) - (U.x * V.z);
    normal.z += (U.x * V.y) - (U.y * V.x);
    //add new normal to 3 vertexes of the triangle
    normals[i][j] += normal;
    normals[i][j + 1] += normal;
    normals[i + 1][j] += normal;
}







