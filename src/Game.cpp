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

        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        

 
        scene_->render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window_->update();
        //std::cout << 1 / window_->getDeltaTime() << std::endl;
    }
}
