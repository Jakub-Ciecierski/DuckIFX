//
// Created by jakub on 5/27/16.
//

#include "light_global.h"

LightGlobal::LightGlobal() : LightSource(){

}

LightGlobal::LightGlobal(RenderObject *renderObject) :
        LightSource(renderObject){

}

LightGlobal::~LightGlobal() {

}

void LightGlobal::bind(const Program &program) {
    const glm::vec3& pos = getPosition();
    // Light Position
    GLint lightPosLoc = glGetUniformLocation(program.getID(),
                                             LIGHT_POSITION_NAME.c_str());
    glUniform3f(lightPosLoc, pos.x, pos.y, pos.z);
}
