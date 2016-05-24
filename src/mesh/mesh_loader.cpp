//
// Created by jakub on 5/24/16.
//
#include <iostream>
#include "mesh_loader.h"

using namespace std;

MeshLoader::MeshLoader(){

}

MeshLoader::~MeshLoader() {

}

Mesh MeshLoader::LoadTriangle() {
    /*
    vector<GLfloat> vertices = {-0.5f, -0.5f, 0.0f,
                                0.5f, -0.5f, 0.0f,
                                0.0f, 0.5f, 0.0f};
                                */
    vector<GLfloat> vertices = {-0.7f, -0.7f, 0.0f,
                                0.7f, -0.7f, 0.0f,
                                0.0f, 0.7f, 0.0f};
    vector<GLuint> indices = { 0, 1, 2 };

    return Mesh(vertices, indices);
}

Mesh MeshLoader::LoadSqaure(){
    vector<GLfloat> vertices = {
            0.5f,  0.5f, 0.0f,  // Top Right
            0.5f, -0.5f, 0.0f,  // Bottom Right
            -0.5f, -0.5f, 0.0f,  // Bottom Left
            -0.5f,  0.5f, 0.0f   // Top Left
    };
    vector<GLuint> indices = {
            0, 1, 3,
            1, 2, 3
    };

    return Mesh(vertices, indices);
}