#include "Camera.hpp"
#include <iostream>

namespace gps {
    int firstMouse = 1;
    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, cameraUp));
        this->cameraUpDirection = glm::cross(cameraRightDirection, cameraFrontDirection);
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        glm::vec3 moveVector = glm::vec3(0.0f);
        if (direction == MOVE_FORWARD) {
            moveVector = 1.0f * this->cameraFrontDirection * speed;
        }
        else if (direction == MOVE_BACKWARD) {
            moveVector = -this->cameraFrontDirection * speed;
        }
        else if (direction == MOVE_RIGHT) {
            moveVector = 1.0f * this->cameraRightDirection * speed;
        }
        else if (direction == MOVE_LEFT) {
            moveVector = -cameraRightDirection * speed;
        }
        else if (direction == MOVE_UP) {
            moveVector = cameraUpDirection * speed;
        }
        else if (direction == MOVE_DOWN) {
            moveVector = -1.0f * this->cameraUpDirection * speed;
        }


        cameraPosition += moveVector;
        cameraTarget += moveVector;
    }


    void Camera::rotate(float pitch, float yaw) {
        glm::mat4 yrotation = glm::rotate(glm::radians(yaw), cameraRightDirection);
        glm::mat4 zrotation = glm::rotate(glm::radians(pitch), cameraUpDirection);
        this->cameraFrontDirection = glm::normalize(glm::vec3(glm::vec4(cameraFrontDirection, 0) * yrotation * zrotation));
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, cameraUpDirection));
        this->cameraTarget = cameraPosition + cameraFrontDirection;
    }
}