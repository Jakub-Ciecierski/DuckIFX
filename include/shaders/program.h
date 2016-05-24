//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_PROGRAM_H
#define DUCK_PROGRAM_H

#include "fragment_shader.h"
#include "vertex_shader.h"

class Program {
private:
    GLuint id;

    void linkShaders(VertexShader &vertexShader, FragmentShader &fragmentShader);
public:

    Program();
    Program(VertexShader& vertexShader, FragmentShader& fragmentShader);

    ~Program();

    void use() const;
};


#endif //DUCK_PROGRAM_H
