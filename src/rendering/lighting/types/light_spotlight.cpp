//
// Created by jakub on 5/27/16.
//


#include <lighting/types/light_spotlight.h>

LightSpotlight::LightSpotlight() : LightDirectional(){

}

LightSpotlight::LightSpotlight(RenderObject *object) :
        LightDirectional(object){

}

LightSpotlight::~LightSpotlight() {

}

void LightSpotlight::bind(const Program &program) {
    const glm::vec3& pos = getPosition();
    const glm::vec3 dir = getDirection();

    // Light Direction
    GLint lightDirLoc = glGetUniformLocation(program.getID(),
                                             LIGHT_DIRECTION_NAME.c_str());
    glUniform3f(lightDirLoc, dir.x, dir.y, dir.z);

    // Light Position
    GLint lightPosLoc = glGetUniformLocation(program.getID(),
                                             LIGHT_POSITION_NAME.c_str());
    glUniform3f(lightPosLoc, pos.x, pos.y, pos.z);

    // Light Cutoff
    GLint lightCutoffLoc = glGetUniformLocation(program.getID(),
                                                LIGHT_FLASHLIGHT_CUTOFF_NAME.c_str());
    glUniform1f(lightCutoffLoc, glm::cos(glm::radians(light.cutOff)));


    GLint lightOuterCutoffLoc = glGetUniformLocation(program.getID(),
                                                     LIGHT_FLASHLIGHT_OUTER_CUTOFF_NAME.c_str());
    glUniform1f(lightOuterCutoffLoc, glm::cos(glm::radians(light.outerCutOff)));
}