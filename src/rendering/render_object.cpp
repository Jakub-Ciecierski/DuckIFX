//
// Created by jakub on 5/26/16.
//

#include "render_object.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

RenderObject::RenderObject(ObjectID id, std::string name,
                           Mesh* mesh) :
        Object(id, name), mesh(mesh){
    initVectors();
}

RenderObject::~RenderObject(){

}

void RenderObject::initVectors(){
    scaleFactor = vec3(1.0f, 1.0f, 1.0f);
}

void RenderObject::render(const Program& program){
    GLint transformLoc = glGetUniformLocation(program.getID(),
                                              MODEL_MATRIX_NAME.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(Model));

    mesh->draw(program);
}

void RenderObject::update(){
    Model = mat4();

    Model = translate(Model, position);

    Model = glm::rotate(Model, rotation.x, vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, rotation.y, vec3(0.0f, 1.0f, 0.0f));
    Model = glm::rotate(Model, rotation.z, vec3(0.0f, 0.0f, 1.0f));

    Model = glm::scale(Model, scaleFactor);
}

void RenderObject::moveTo(const glm::vec3 &position) {
    this->position = position;
}

void RenderObject::move(const glm::vec3 &position) {
    this->position += position;
}

void RenderObject::rotateTo(const glm::vec3 &rotate) {
    this->rotation = rotate;
}

void RenderObject::rotate(const glm::vec3 &rotate) {
    this->rotation += rotate;
}

void RenderObject::scale(const glm::vec3 &scale) {
    this->scaleFactor = scale;
}
