//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_VBO_H
#define DUCK_VBO_H

#include <GL/gl.h>
#include <vector>

class VBO {
private:
    GLuint vboID;
    const std::vector<GLfloat>* vertices;

public:

    VBO(const std::vector<GLfloat>* vertices);
    ~VBO();

    /*
     * Default usage is GL_STATIC_DRAW
     */
    void bind(GLenum usage = GL_STATIC_DRAW);

    void unbind();
};


#endif //DUCK_VBO_H
