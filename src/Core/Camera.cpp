#define GLM_ENABLE_EXPERIMENTAL
#include "Camera.h"
#include <iostream>
#include "../Game.h"
#include <glm/gtx/string_cast.hpp>
#include "../Events/EventManager.h"

Camera::Camera(const Window& window, float fov, glm::vec3 position, glm::vec3 up, glm::vec3 front)
    : fov_(fov), position_(position), up_(up), front_(front), window_(&window)
{
    yaw_ = glm::degrees(atan2(front_.z, front_.x));
    pitch_ = glm::degrees(atan2(front_.y, sqrt(front_.x * front_.x + front_.z * front_.z)));


    viewM_ = glm::lookAt(position_, position_ + front_, up_);
    updateProjectionMatrix(window_->getAspectRatio());


    EventHandler<WindowResizeEvent> windowResizeHandler = [this](const WindowResizeEvent& event) {this->updateProjectionMatrix(event.width / event.height);};
    EventManager::getInstance().sub(std::make_unique<EventHandlerWrapper<WindowResizeEvent>>(windowResizeHandler));
}


void Camera::updateProjectionMatrix(const float& aspectRatio)
{
    projM_ = glm::perspective(fov_, aspectRatio, 0.1f, 100.0f);
}