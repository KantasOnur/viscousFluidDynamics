#include "Game.h"
#include <windows.h>


extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 1;
    _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main(void)
{
    Game game;
    game.run();
    return 0;
}