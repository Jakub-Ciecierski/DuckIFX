//
// Created by jakub on 5/24/16.
//

#include <GL/glew.h>
#include <shaders/vertex_shader.h>
#include <shaders/fragment_shader.h>
#include "shader_loader.h"

ShaderLoader::ShaderLoader(){

}

ShaderLoader::~ShaderLoader() {

}

VertexShader ShaderLoader::LoadDefaultVertexShader() {
    const GLchar* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 position;\n"
            "void main()\n"
            "{\n"
            "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
            "}\0";

    return VertexShader(vertexShaderSource);
}

FragmentShader ShaderLoader::LoadDefaultFragmentShader() {
    const GLchar* fragmentShaderSource = "#version 330 core\n"
            "out vec4 color;\n"
            "void main()\n"
            "{\n"
            "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

    return FragmentShader(fragmentShaderSource);
}
