//
// Created by jakub on 5/24/16.
//
#include <iostream>

#include "mesh_loader.h"
#include <textures/texture_loader.h>

using namespace std;

MeshLoader::MeshLoader(){

}

MeshLoader::~MeshLoader() {

}

Mesh MeshLoader::LoadTriangle() {
    vector<GLfloat> vertices = {
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f,   0.5f, 1.0f};
    vector<GLuint> indices = { 0, 1, 2 };

    TextureLoader textureLoader;
    Texture texture1 = textureLoader.LoadContainer();
    Texture texture2 = textureLoader.LoadAwesomeFace();

    std::vector<Texture> textures = {texture1, texture2};

    return Mesh(vertices, indices, textures);
}

Mesh MeshLoader::LoadSqaure(){
    vector<GLfloat> vertices = {
            0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };
    vector<GLuint> indices = {
            0, 1, 3,
            1, 2, 3
    };
    TextureLoader textureLoader;
    Texture texture1 = textureLoader.LoadContainer();
    Texture texture2 = textureLoader.LoadAwesomeFace();

    std::vector<Texture> textures = {texture1, texture2};

    return Mesh(vertices, indices, textures);
}

Mesh MeshLoader::LoadCube(){
    vector<GLfloat> vertices = {
            // Front
            1.0f,  1.0f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            1.0f,  0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            0.0f,  0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

            // Back
            1.0f,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            1.0f,  0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            0.0f,  0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            0.0f,  1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

            // Left
            0.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // 8
            0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 9
            0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // 10
            0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 11

            // Right
            1.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // 12
            1.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 13
            1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // 14
            1.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 15

            // Bottom
            1.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // 16
            1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 17
            0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // 18
            0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 19

            // Top
            1.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // 20
            1.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 21
            0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // 22
            0.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 23
    };
    vector<GLuint> indices = {
            0, 1, 3,    1, 2, 3,            // front
            7, 5, 4,    5, 6, 7,            // back
            8, 9, 11,    9, 10, 11,           // left
            12, 13, 15,    13, 14, 15,        // right
            16, 17, 19,    17, 18, 19,        // bottom
            20, 21, 23,    21, 22, 23,        // top
    };
    TextureLoader textureLoader;
    Texture texture1 = textureLoader.LoadContainer();
    Texture texture2 = textureLoader.LoadAwesomeFace();

    std::vector<Texture> textures = {texture1, texture2};

    return Mesh(vertices, indices, textures);
}


Mesh MeshLoader::LoadLamp(){
    vector<GLfloat> vertices = {
            // Front
            1.0f,  1.0f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            1.0f,  0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            0.0f,  0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

            // Back
            1.0f,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            1.0f,  0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            0.0f,  0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            0.0f,  1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

            // Left
            0.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // 8
            0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 9
            0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // 10
            0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 11

            // Right
            1.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // 12
            1.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 13
            1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // 14
            1.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 15

            // Bottom
            1.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // 16
            1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 17
            0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // 18
            0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 19

            // Top
            1.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // 20
            1.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 21
            0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // 22
            0.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 23
    };
    vector<GLuint> indices = {
            0, 1, 3,    1, 2, 3,            // front
            7, 5, 4,    5, 6, 7,            // back
            8, 9, 11,    9, 10, 11,           // left
            12, 13, 15,    13, 14, 15,        // right
            16, 17, 19,    17, 18, 19,        // bottom
            20, 21, 23,    21, 22, 23,        // top
    };
    TextureLoader textureLoader;
    Texture texture1 = textureLoader.LoadContainer();
    Texture texture2 = textureLoader.LoadAwesomeFace();

    std::vector<Texture> textures = {texture1, texture2};

    return Mesh(vertices, indices, textures);
}