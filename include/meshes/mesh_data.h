//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_MESH_DATA_H
#define DUCK_MESH_DATA_H

#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
#include <string>

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture{
    GLuint id;
    GLenum type;

    Texture(){}
    Texture(GLuint id,
            GLenum type) : id(id), type(type){}
};

#endif //DUCK_MESH_DATA_H
