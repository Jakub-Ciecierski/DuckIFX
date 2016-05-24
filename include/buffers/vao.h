//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_VAO_H
#define DUCK_VAO_H


#include <GL/gl.h>
#include "vbo.h"
#include "ebo.h"

class VAO {
private:
    GLuint id;

    const GLuint DATA_PER_VERTEX = 3;
    const GLuint STRIDE = DATA_PER_VERTEX * sizeof(GLfloat);
public:

    VAO();

    ~VAO();

    void bindBuffers(VBO &vbo, EBO &ebo);

    void bind();
    void unbind();
};


#endif //DUCK_VAO_H
