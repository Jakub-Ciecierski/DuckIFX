//
// Created by jakub on 5/25/16.
//

#ifndef DUCK_TEXTURE_LOADER_H
#define DUCK_TEXTURE_LOADER_H


#include <meshes/mesh_data.h>
#include "texture_buffer.h"

/*
 * Class loads textures saved in resource files
 */
class TextureLoader {
private:
    GLuint loadFromFile(std::string filepath);
    Texture contructTexture(GLuint id, GLenum Type);

public:

    TextureLoader();

    ~TextureLoader();

    Texture LoadContainer();
};


#endif //DUCK_TEXTURE_LOADER_H
