//
// Created by jakub on 5/25/16.
//

#include <SOIL.h>
#include <GL/glew.h>
#include <stdexcept>
#include "texture_loader.h"

TextureLoader::TextureLoader(){

}

TextureLoader::~TextureLoader() {

}

GLuint TextureLoader::loadFromFile(std::string filepath) {
    GLuint id;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // TODO parametrize this:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    unsigned char* image = SOIL_load_image(filepath.c_str(),
                                           &width, &height, 0,
                                           SOIL_LOAD_RGB);
    if(image == NULL){
        std::string info = "NULL returned";
        throw new std::invalid_argument(info);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);

    glBindTexture(GL_TEXTURE_2D, 0);

    return id;
}

Texture TextureLoader::contructTexture(GLuint id, GLenum type){
    return Texture(id, type);
}

Texture TextureLoader::LoadContainer() {
    GLuint id = loadFromFile("res/textures/container.jpg");
    Texture texture = contructTexture(id, GL_TEXTURE_2D);

    return texture;
}
