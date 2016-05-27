//
// Created by jakub on 5/26/16.
//

#include "render_object.h"
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
    program.use();

    // Model
    GLint transformLoc = glGetUniformLocation(program.getID(),
                                              MODEL_MATRIX_NAME.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

    mesh->draw(program);
}

void RenderObject::update(){
    ModelMatrix = mat4();

    ModelMatrix = translate(ModelMatrix, position);

    ModelMatrix = glm::rotate(ModelMatrix, rotation.x, vec3(1.0f, 0.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, rotation.y, vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, rotation.z, vec3(0.0f, 0.0f, 1.0f));

    ModelMatrix = glm::scale(ModelMatrix, scaleFactor);
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

Mesh *RenderObject::getMesh() {
    return mesh;
}

void RenderObject::scale(const glm::vec3 &scale) {
    this->scaleFactor = scale;
}

const glm::vec3 &RenderObject::getPosition() {
    return this->position;
}
