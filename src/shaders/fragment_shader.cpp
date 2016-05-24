//
// Created by jakub on 5/24/16.
//

#include "fragment_shader.h"

FragmentShader::FragmentShader(const GLchar* shaderSource) :
        Shader(shaderSource){

}

FragmentShader::~FragmentShader() {

}

GLuint FragmentShader::createShader() {
    return glCreateShader(GL_FRAGMENT_SHADER);
}

