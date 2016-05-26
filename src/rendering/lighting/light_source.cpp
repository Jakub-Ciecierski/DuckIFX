//
// Created by jakub on 5/26/16.
//

#include "light_source.h"

LightSource::LightSource(){
    renderObject = NULL;

    setFollowObject(false);

    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

LightSource::LightSource(RenderObject *renderObject) :
        renderObject(renderObject){
    setFollowObject(true);

    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

LightSource::~LightSource() {

}

void LightSource::setFollowObject(bool value) {
    followObject = value;
}

void LightSource::setColor(const glm::vec3 &color) {
    this->lightColor = color;
}


void LightSource::setPosition(const glm::vec3 &position) {
    if(!followObject){
        this->position = position;
    }
}

void LightSource::use(const Program& program) {
    program.use();

    GLint lightColorLoc =
            glGetUniformLocation(program.getID(), LIGHT_COLOR_NAME.c_str());
    glUniform3f(lightColorLoc,
                lightColor.x, lightColor.y, lightColor.z);
}

void LightSource::render(const Program &program) {
    if(renderObject == NULL) return;

    renderObject->render(program);
}

