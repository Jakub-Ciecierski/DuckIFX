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

    glVertexAttribPointer(0, DATA_PER_VERTEX, GL_FLOAT, GL_FALSE,
                          STRIDE, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->unbind();
}

void VAO::bind() {
    glBindVertexArray(id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}
