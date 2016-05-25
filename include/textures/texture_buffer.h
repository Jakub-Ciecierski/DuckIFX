//
// Created by jakub on 5/25/16.
//

#ifndef DUCK_TEXTURE_H
#define DUCK_TEXTURE_H


#include <GL/gl.h>
#include <string>

class TextureBuffer {
private:
    GLuint id;

    void create(std::string filepath);
public:

    TextureBuffer(std::string filepath);

    ~TextureBuffer();

    void bind();
};


#endif //DUCK_TEXTURE_H
