//
// Created by jakub on 5/24/16.
//

#include "vertex_shader.h"

VertexShader::VertexShader(const GLchar* shaderSource) :
        Shader(shaderSource){

}

VertexShader::~VertexShader() {

}

GLuint VertexShader::createShader() {
    return glCreateShader(GL_VERTEX_SHADER);
}
