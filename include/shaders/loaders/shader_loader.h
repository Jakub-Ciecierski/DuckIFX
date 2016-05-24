//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_SHADER_LOADER_H
#define DUCK_SHADER_LOADER_H


#include <shaders/shader.h>

class ShaderLoader {
private:

public:

    ShaderLoader();

    ~ShaderLoader();

    static VertexShader LoadDefaultVertexShader();
    static FragmentShader LoadDefaultFragmentShader();
};


#endif //DUCK_SHADER_LOADER_H
