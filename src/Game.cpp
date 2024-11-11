#include "Game.h"
#include <iostream>

std::unique_ptr<Window> Game::window_;

Game::Game()
{
    window_ = std::make_unique<Window>(640, 480);
    scene_ = std::make_unique<Scene>(*window_);
}

void Game::run()
{

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    while (window_->isOpen())
    { 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene_->render();
        window_->update();
    }
}
