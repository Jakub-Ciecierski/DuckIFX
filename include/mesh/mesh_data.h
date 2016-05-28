//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_MESH_DATA_H
#define DUCK_MESH_DATA_H

#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
#include <string>

/**
 * Provides all the data used by Meshes and Lights.
 * Provides uniform global strings for shader binding.
 * TODO Separate the Mesh, Light and shader data.
 */

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

enum TextureTypes{
    DIFFUSE, SPECULAR
};

struct Texture{
    GLuint id;
    TextureTypes texType;
    GLenum type;

    std::string path; // physical path on the disk of the texture

    Texture(){}
    Texture(GLuint id,
            GLenum type) : id(id), type(type){}
};

struct Material{
    float shininess;
};

struct Light{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // Attenuation
    float constant;
    float linear;
    float quadratic;

    // FlashLight cutOff angle, in degrees
    float cutOff;
    float outerCutOff;
};

// Maximum number of textures
extern const int MAX_TEX_COUNT;

/*
 * These names must correspond to texture samplers names in fragment shader
 */
extern const std::string TEX_UNI_NAMES[];

extern const std::string MODEL_MATRIX_NAME;
extern const std::string VIEW_MATRIX_NAME;
extern const std::string PROJECTION_MATRIX_NAME;

extern const std::string VIEW_POSITION_NAME;

extern const std::string MATERIAL_AMBIENT_NAME;
extern const std::string MATERIAL_DIFFUSE_NAME;
extern const std::string MATERIAL_SPECULAR_NAME;
extern const std::string MATERIAL_SHININESS_NAME;

#endif //DUCK_MESH_DATA_H
