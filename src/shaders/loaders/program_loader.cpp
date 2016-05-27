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

Program *ProgramLoader::loadGlobalLightProgram() {
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/light_global_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/light_global_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program *ProgramLoader::loadGlobalAttenuationLightProgram() {
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/light_global_attenuation_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/light_global_attenuation_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program *ProgramLoader::loadDirectionalLightProgram() {
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/light_dir_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/light_dir_frag.glsl");

    vertexShader.compile();
    fragmentShader.compile();

    Program* programGlobalLight = new Program(vertexShader, fragmentShader);
    return programGlobalLight;
}

Program *ProgramLoader::loadFlashlightProgram() {
    VertexShader vertexShader =
            shaderLoader.loadVertexShader
                    ("res/shaders/lighting/light_flashlight_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/light_flashlight_frag.glsl");

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
