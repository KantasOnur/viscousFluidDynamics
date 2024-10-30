#pragma once
#include <memory>
#include "Scene.h"
#include "Core/Window.h"

class Game
{
private:
    std::unique_ptr<Scene> scene_;
public:
    static std::unique_ptr<Window> window_;
    inline static float deltaTime_ = 0.0f;
    Game();
    void run();
};
