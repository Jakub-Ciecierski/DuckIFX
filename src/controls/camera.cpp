//
// Created by jakub on 5/26/16.
//

#include "camera.h"

using namespace glm;

Camera::Camera(int* width, int* height,
               float FOV, float near, float far) :
        width(width), height(height),
        FOV(FOV), near(near), far(far){
    WorldUp = vec3(0.0f, 1.0f, 0.0f);
    position = vec3(1.0f, 1.0f, 1.0f);
    update();
}

Camera::~Camera() {

}

void Camera::moveTo(const glm::vec3 &position) {
    this->position = position;
}

void Camera::moveForward(float speedBoost) {
    position += direction * speedBoost;
}

void Camera::moveBackward(float speedBoost) {
    position -= direction * speedBoost;
}

void Camera::moveLeft(float speedBoost) {
    position -= right * speedBoost;
}

void Camera::moveRight(float speedBoost) {
    position += right * speedBoost;
}

void Camera::moveUp(float speedBoost) {
    position += up * speedBoost;
}

void Camera::moveDown(float speedBoost) {
    position -= up * speedBoost;
}

void Camera::rotate(const glm::vec3 &rotation) {
    this->rotation += rotation;
}

void Camera::rotateTo(const glm::vec3 &rotation) {
    this->rotation = rotation;
}

void Camera::update() {
    ProjectionMatrix = glm::perspective(FOV,
                                        (float)(*width)/(float)(*height),
                                        near, far);

    direction.x = cos(glm::radians(rotation.x))
                  * cos(glm::radians(rotation.y));
    direction.y = sin(glm::radians(rotation.y));
    direction.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));

    direction = glm::normalize(direction);
    right = glm::normalize(glm::cross(direction, this->WorldUp));
    up    = glm::normalize(glm::cross(right, direction));

    ViewMatrix = glm::lookAt(position, position + direction, up);
}

const glm::mat4 &Camera::getViewMatrix() {
    return this->ViewMatrix;
}

const glm::mat4 &Camera::getProjectionMatrix() {
    return this->ProjectionMatrix;
}
