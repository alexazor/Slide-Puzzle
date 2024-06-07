/**
 * @file slide_puzzle.hpp
 * @author Alexandre AZOR
 * @brief Class containing variables used throughout the program
 * @version 0.2
 * @date 2024-06-06
 *
 *
 */

#ifndef SLIDE_PUZZLE_HPP_INCLUDED
#define SLIDE_PUZZLE_HPP_INCLUDED

#include <vector>
#include "main.hpp"

class Slide_Puzzle
{
public:
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
    TTF_Font *pFont;
    std::vector<SDL_Texture *> pNumbersTextures;
    std::vector<SDL_Rect> numbersRects;
    unsigned int puzzleSize;
    std::vector<int> map;
    unsigned int blockWidth;
    unsigned int blockHeight;
    unsigned int windowWidth = DEFAULT_WINDOW_WIDTH;
    unsigned int windowHeight = DEFAULT_WINDOW_HEIGHT;
    unsigned int iVoid;
    unsigned int jVoid;

    Program_State state = STATE_TITLE;

    Slide_Puzzle();
};

#endif // SLIDE_PUZZLE_HPP_INCLUDED