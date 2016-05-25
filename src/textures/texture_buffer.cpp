//
// Created by jakub on 5/25/16.
//

#include <SOIL.h>
#include <GL/glew.h>
#include "texture_buffer.h"

using namespace std;

TextureBuffer::TextureBuffer(string filepath){
    create(filepath);
}

TextureBuffer::~TextureBuffer() {

}

void TextureBuffer::create(string filepath) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // TODO parametrize this:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureBuffer::bind() {

}
