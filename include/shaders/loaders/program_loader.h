//
// Created by jakub on 5/27/16.
//

#ifndef DUCK_PROGRAM_LOADER_H
#define DUCK_PROGRAM_LOADER_H

#include <shaders/program.h>
#include <shaders/loaders/shader_loader.h>

/*
 * Loads specific shaders compiled into Programs from resources
 */
class ProgramLoader {
private:
    ShaderLoader shaderLoader;
public:

    ProgramLoader();

    ~ProgramLoader();

    Program* loadCubemapProgram();
    Program* loadAllLightProgram();
    Program* loadBumpMappingProgram();
    Program* loadGlobalLightProgram();
    Program* loadGlobalAttenuationLightProgram();

    Program* loadDirectionalLightProgram();
    Program* loadFlashlightProgram();

    Program* loadLampProgram();

};


#endif //DUCK_PROGRAM_LOADER_H
