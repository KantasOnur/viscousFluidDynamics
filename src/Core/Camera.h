#pragma once
#include <glm/glm.hpp>
#include "Window.h"
class Camera
{
private:
    glm::vec3 position_, front_, up_, right_;
    glm::mat4 projM_, viewM_;
    float pitch_, yaw_;
    float fov_, aspectRatio_;
    const Window* window_;
    void updateProjectionMatrix(const float& aspectRatio);
public:
    explicit Camera(const Window& window, float fov = 45.0f, glm::vec3 position = { 0.0f, 0.0f, 10.0f }, glm::vec3 up = { 0.0f, 1.0f, 0.0f }, glm::vec3 front = { 0.0f, 0.0f, -1.0f });
    ~Camera() = default;

    glm::mat4 getProjection() const { return projM_; }
    glm::mat4 getView() const { return viewM_; }
    glm::vec3 getPosition() const { return position_; }
};

