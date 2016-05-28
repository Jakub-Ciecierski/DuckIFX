//
// Created by jakub on 5/25/16.
//

#ifndef DUCK_TEXTURE_LOADER_H
#define DUCK_TEXTURE_LOADER_H


#include <mesh/mesh_data.h>

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

    Texture loadTexture(std::string filepath,
                        TextureTypes type,
                        GLenum glType = GL_TEXTURE_2D);

    Texture LoadContainer();
    Texture LoadContainerDiffuse();
    Texture LoadContainerSpecular();

    Texture LoadAwesomeFace();
};


#endif //DUCK_TEXTURE_LOADER_H
