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