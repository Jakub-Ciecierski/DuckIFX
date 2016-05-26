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

// Maximum number of textures
extern const int MAX_TEX_COUNT;

/*
 * This names must correspond to texture samplers names in fragment shader
 */
extern const std::string TEX_UNI_NAMES[];

extern const std::string MODEL_MATRIX_NAME;
extern const std::string VIEW_MATRIX_NAME;
extern const std::string PROJECTION_MATRIX_NAME;

extern const std::string LIGHT_POSITION_NAME;
extern const std::string OBJECT_COLOR_NAME;
extern const std::string LIGHT_COLOR_NAME;
extern const std::string VIEW_POSITION_NAME;

#endif //DUCK_MESH_DATA_H
