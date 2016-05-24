//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_SHADER_H
#define DUCK_SHADER_H

#include <GL/glew.h>

/*
 * compile function has to be called before using shader
 */
class Shader {
private:
    GLuint id;
    const GLchar*shaderSource;

protected:
    /*
     * Creates a shader: Vertex/Fragmet/Geometry
     */
    virtual GLuint createShader() = 0;

public:

    Shader(const GLchar* vertexShaderSource);
    virtual ~Shader();

    void compile();

    /*
     * Used after linking with the progam.
     */
    void deleteShader();

    GLuint getKey();
};


#endif //DUCK_SHADER_H
