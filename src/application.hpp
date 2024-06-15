/**
 * @file application.hpp
 * @author Alexandre AZOR
 * @brief Class containing variables used throughout the program
 * @version 0.2
 * @date 2024-06-06
 *
 *
 */

#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include "main.hpp"

class Application
{
public:
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
    TTF_Font *pFont;
    int puzzleSize;

    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;

    Program_State state = Program_State::STATE_TITLE;

    Application();
};

#endif // APPLICATION_HPP_INCLUDED