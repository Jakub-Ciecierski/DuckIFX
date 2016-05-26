//
// Created by jakub on 5/26/16.
//

#include <glm/detail/type_vec.hpp>
#include <lighting/light_source.h>
#include <iostream>

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

void LightSource::setLight(const Light& light){
    this->light = light;
}

const glm::vec3 &LightSource::getPosition() {
    if(followObject && renderObject != NULL){
        return renderObject->getPosition();
    }else{
        return this->position;
    }
}

void LightSource::use(const Program& program) {
    program.use();

    const glm::vec3& pos = getPosition();
    // Light Position
    GLint lightPosLoc = glGetUniformLocation(program.getID(),
                                             LIGHT_POSITION_NAME.c_str());
    glUniform3f(lightPosLoc, pos.x, pos.y, pos.z);

    GLint lightAmbientLoc  = glGetUniformLocation(program.getID(),
                                                  LIGHT_AMBIENT_NAME.c_str());
    GLint lightDiffuseLoc  = glGetUniformLocation(program.getID(),
                                                  LIGHT_DIFFUSE_NAME.c_str());
    GLint lightSpecularLoc = glGetUniformLocation(program.getID(),
                                                  LIGHT_SPECULAR_NAME.c_str());

    glUniform3f(lightAmbientLoc,
                light.ambient.x, light.ambient.y, light.ambient.z);
    glUniform3f(lightDiffuseLoc,
                light.diffuse.x, light.diffuse.y, light.diffuse.z);
    glUniform3f(lightSpecularLoc,
                light.specular.x, light.specular.y, light.specular.z);
}

void LightSource::render(const Program &program) {
    if(renderObject == NULL) return;

    renderObject->render(program);
}
