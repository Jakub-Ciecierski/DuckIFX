//
// Created by jakub on 5/27/16.
//

#include "program_loader.h"

ProgramLoader::ProgramLoader(){

}

ProgramLoader::~ProgramLoader() {

}

Program* ProgramLoader::loadAllLightProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/light_all_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/light_all_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program* ProgramLoader::loadAnisotropicLightProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/anis_light_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/anis_light_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program* ProgramLoader::loadCubemapProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/cubemap_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/cubemap_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program* ProgramLoader::loadBumpMappingProgram(){
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/bump_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/bump_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program *ProgramLoader::loadLampProgram() {
    VertexShader vertexShaderLight =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/lamp_vert.glsl");
    FragmentShader fragmentShaderLight =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/lamp_frag.glsl");
    vertexShaderLight.compile();
    fragmentShaderLight.compile();

    Program* programLamp = new Program(vertexShaderLight, fragmentShaderLight);

    return programLamp;
}
