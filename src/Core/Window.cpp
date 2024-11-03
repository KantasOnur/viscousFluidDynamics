#include "Window.h"
#include "../Game.h"
#include "../Events/EventManager.h"

#include <iostream>
int Window::width_;
int Window::height_;

Window::Window(const int& width, const int& height)
{
    width_ = width;
    height_ = height;

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width_, height_, "Game", nullptr, nullptr);
    glfwMakeContextCurrent(window_);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW." << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwSetWindowSizeCallback(window_, windowResizeCallback);
}

Window::~Window()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Window::update() const
{
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

double Window::getTime()
{
    return glfwGetTime();
}

float Window::getDeltaTime()
{
    float current = getTime();
    float dt = current - lastTime_;
    lastTime_ = current;
    return dt;
}

bool Window::isOpen() const
{
    return !glfwWindowShouldClose(window_);
}


void Window::windowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    WindowResizeEvent e(width, height);
    EventManager::getInstance().triggerEvent(e);
}

void Window::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{

}