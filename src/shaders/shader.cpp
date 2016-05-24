//
// Created by jakub on 5/24/16.
//

#include <iostream>
#include <stdexcept>
#include "shader.h"

Shader::Shader(const GLchar* shaderSource){
    this->shaderSource = shaderSource;
}

Shader::~Shader() {

}

void Shader::compile() {
    id = createShader();

    glShaderSource(id, 1, &shaderSource, NULL);
    glCompileShader(id);

    // Check status;
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::string infoLogStr = infoLog;
        throw new std::invalid_argument("ERROR::SHADER::COMPILATION_FAILED\n"
                                        + infoLogStr);
    }
}

void Shader::deleteShader() {
    glDeleteShader(id);
}

GLuint Shader::getKey() {
    return id;
}
