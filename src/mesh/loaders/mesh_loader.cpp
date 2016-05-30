//
// Created by jakub on 5/24/16.
//
#include <iostream>

#include "mesh_loader.h"
#include <textures/texture_loader.h>

using namespace std;
using namespace glm;

MeshLoader::MeshLoader(){

}

MeshLoader::~MeshLoader() {

}
/*
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
*/


Mesh MeshLoader::LoadCubemap(){
    // Position, Normal, TexCoord
    vector<Vertex> vertices = {
            // Front
            Vertex{vec3(1.0f,  1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f,  -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f,  -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f,  1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            // Back
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},

            // Left
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Right
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Bottom
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Top
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
    };

    vector<GLuint> indices = {
            3, 1, 0,    3, 2, 1,            // front
            4, 5, 7,    5, 6, 7,            // back

            8, 9, 11,    9, 10, 11,           // left
            15, 13, 12,    15, 14, 13,        // right

            16, 17, 19,    17, 18, 19,        // bottom
            23, 21, 20,    23, 22, 21,        // top
    };
    TextureLoader textureLoader;
    Texture textureDiffuse = textureLoader.LoadExampleCubemap();

    std::vector<Texture> textures = {textureDiffuse};

    Mesh mesh(vertices, indices, textures);

    Material material;
    material.shininess = 32.0f;
    mesh.setMaterial(material);

    return mesh;
}

Mesh MeshLoader::LoadCube(){
    // Position, Normal, TexCoord
    vector<Vertex> vertices = {
            // Front
            Vertex{vec3(1.0f,  1.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f,  0.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f,  0.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f,  1.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            // Back
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 0.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},

            // Left
            Vertex{vec3(0.0f, 1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(0.0f, 0.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.0f, 0.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f, 1.0f, 0.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Right
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 0.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(1.0f, 0.0f, 0.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(1.0f, 1.0f, 0.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Bottom
            Vertex{vec3(1.0f, 0.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 0.0f, 0.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.0f, 0.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Top
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 1.0f, 0.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f, 1.0f, 0.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
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
    Texture textureDiffuse = textureLoader.LoadContainerDiffuse();
    Texture textureSpecular = textureLoader.LoadContainerSpecular();

    std::vector<Texture> textures = {textureDiffuse, textureSpecular};

    Mesh mesh(vertices, indices, textures, GL_TRIANGLES);

    Material material;
    material.shininess = 32.0f;
    mesh.setMaterial(material);

    return mesh;
}

Mesh MeshLoader::LoadLamp(){
    vector<Vertex> vertices = {
            // Front
            Vertex{vec3(1.0f,  1.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f,  0.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f,  0.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f,  1.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            // Back
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 0.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},

            // Left
            Vertex{vec3(0.0f, 1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(0.0f, 0.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.0f, 0.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f, 1.0f, 0.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Right
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 0.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(1.0f, 0.0f, 0.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(1.0f, 1.0f, 0.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Bottom
            Vertex{vec3(1.0f, 0.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 0.0f, 0.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.0f, 0.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(1.0f, 0.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Top
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 1.0f, 0.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f, 1.0f, 0.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
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

    std::vector<Texture> textures;

    return Mesh(vertices, indices, textures, GL_TRIANGLES);
}

Mesh MeshLoader::LoadPlane(int x, int y, float unit) {
    float offsetX;
    float offsetZ;
    offsetX = (unit * x) / 2;
    offsetZ = (unit * y) / 2;

    vector<Vertex> vertices;
    for (int j = 0; j<y; j++) {
        for (int i = 0; i < x; i++) {
            vertices.push_back(Vertex{vec3(i*unit - offsetX,
                                           0.0f, j*unit - offsetZ),
                                      vec3(0.0f, 1.0f, 0.0f),
                                      vec2(1-((j*unit)/((y-1)*unit)), (i*unit)/(unit*(x-1)) )});
        }
    }
    vector<GLuint> indices;
    //GL TRIANGLE STRIP
    /*for (int j = 0; j<y-1; j++) {
        for (int i = 0; i < x; i++) {
            indices.push_back(j * y + i);
            indices.push_back((j+1) * y + i);
        }
        indices.push_back((j+1) * y + (x-1));
        indices.push_back((j+1) * y);
    }*/
    //GL TRIANGLES
    for (int j = 0; j<y-1; j++) {
        for (int i = 0; i < x-1; i++) {
            //upper triangle
            indices.push_back(j * y + i);
            indices.push_back((j + 1) * y + i);
            indices.push_back(j * y + i+1);
            //lowe triangle
            indices.push_back(j * y + i+1);
            indices.push_back((j + 1) * y + i);
            indices.push_back((j + 1) * y + i+1);
        }
    }

    return Mesh(vertices, indices, GL_TRIANGLE_STRIP);
}