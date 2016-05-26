//
// Created by jakub on 5/24/16.
//

#include <GL/glew.h>
#include "vao.h"

VAO::VAO(){
    glGenVertexArrays(1, &id);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &id);
}

void VAO::bindBuffers(VBO &vbo, EBO &ebo){
    this->bind();

    vbo.bind();
    ebo.bind();

    const GLuint DATA_PER_POSITION = 3;
    const GLuint DATA_PER_NORMAL = 3;
    const GLuint DATA_PER_COLOR = 3;
    const GLuint DATA_PER_TEXTURE = 2;
    const GLuint STRIDE =
            (DATA_PER_POSITION + DATA_PER_NORMAL +
                    DATA_PER_COLOR + DATA_PER_TEXTURE) *
                    sizeof(GLfloat);

    // Position
    glVertexAttribPointer(0, DATA_PER_POSITION, GL_FLOAT, GL_FALSE,
                          STRIDE, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, DATA_PER_NORMAL, GL_FLOAT, GL_FALSE,
                          STRIDE, (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Color
    glVertexAttribPointer(2, DATA_PER_COLOR, GL_FLOAT, GL_FALSE,
                          STRIDE, (GLvoid*)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // Texture
    glVertexAttribPointer(3, DATA_PER_TEXTURE, GL_FLOAT, GL_FALSE,
                          STRIDE, (GLvoid*)(9*sizeof(GLfloat)));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->unbind();
}

void VAO::bind() {
    glBindVertexArray(id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}
