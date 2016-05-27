//
// Created by jakub on 5/26/16.
//

#include <glm/detail/type_vec.hpp>
#include <lighting/light_source.h>

LightSource::LightSource(){
    followedRenderObject = NULL;
    followedCamera = NULL;

    setFollow(true);
}

LightSource::LightSource(RenderObject *renderObject) :
        followedRenderObject(renderObject){
    followedCamera = NULL;
    setFollow(true);
}

LightSource::~LightSource() {

}

void LightSource::setRenderObject(RenderObject* object){
    this->followedRenderObject = object;
    this->followedCamera = NULL;
}

void LightSource::setCamera(Camera *camera) {
    this->followedCamera = camera;
    this->followedRenderObject = NULL;
}


void LightSource::setFollow(bool value) {
    isFollow = value;
}

void LightSource::setPosition(const glm::vec3 &position) {
    if(!isFollow){
        this->position = position;
    }
}

void LightSource::setLight(const Light& light){
    this->light = light;
}

const glm::vec3 &LightSource::getPosition() {
    if(isFollow && followedRenderObject != NULL){
        return followedRenderObject->getPosition();
    }else if(isFollow && followedCamera != NULL){
        return followedCamera->getPosition();
    }else{
        return this->position;
    }
}

void LightSource::use(const Program& program) {
    program.use();

    bind(program);

    GLint lightAmbientLoc  = glGetUniformLocation(program.getID(),
                                                  LIGHT_AMBIENT_NAME.c_str());
    GLint lightDiffuseLoc  = glGetUniformLocation(program.getID(),
                                                  LIGHT_DIFFUSE_NAME.c_str());
    GLint lightSpecularLoc = glGetUniformLocation(program.getID(),
                                                  LIGHT_SPECULAR_NAME.c_str());

    GLint lightAttenConstLoc
            = glGetUniformLocation(program.getID(),
                                   LIGHT_ATTENUATION_CONST_NAME.c_str());
    GLint lightAttenLinLoc
            = glGetUniformLocation(program.getID(),
                                   LIGHT_ATTENUATION_LINEAR_NAME.c_str());
    GLint lightAttenQuadLoc
            = glGetUniformLocation(program.getID(),
                                   LIGHT_ATTENUATION_QUAD_NAME.c_str());

    glUniform3f(lightAmbientLoc,
                light.ambient.x, light.ambient.y, light.ambient.z);
    glUniform3f(lightDiffuseLoc,
                light.diffuse.x, light.diffuse.y, light.diffuse.z);
    glUniform3f(lightSpecularLoc,
                light.specular.x, light.specular.y, light.specular.z);

    glUniform1f(lightAttenConstLoc, light.constant);
    glUniform1f(lightAttenLinLoc, light.linear);
    glUniform1f(lightAttenQuadLoc, light.quadratic);
}

void LightSource::render(const Program &program) {
    if(followedRenderObject == NULL) return;

    followedRenderObject->render(program);
}
