//
// Created by jakub on 5/27/16.
//

#include <lighting/types/light_point.h>

LightPoint::LightPoint() : LightSource(){

}

LightPoint::LightPoint(RenderObject *renderObject) :
        LightSource(renderObject){

}

LightPoint::~LightPoint() {

}

void LightPoint::bind(const Program &program) {
    const glm::vec3& pos = getPosition();
    // Light Position
    GLint lightPosLoc = glGetUniformLocation(program.getID(),
                                             LIGHT_POSITION_NAME.c_str());
    glUniform3f(lightPosLoc, pos.x, pos.y, pos.z);
}
