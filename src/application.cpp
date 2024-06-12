#include "application.hpp"

Application::Application()
{
    SDL_SetWindowSize(this->pWindow, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
};