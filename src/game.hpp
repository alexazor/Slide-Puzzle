/**
 * @file game.hpp
 * @author Alexandre AZOR
 * @brief Functions for the title page
 * @version 1.0
 * @date 2024-06-08
 *
 *
 */

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "board.hpp"
#include "mouse.hpp"

State game(SDL_Renderer *pRenderer, TTF_Font *pFont, int puzzleSize, int block_width, int block_height, int window_width, int window_height);

State event_loop_game(SDL_Renderer *pRenderer,
                      SDL_Texture *pNumbersTextures[],
                      SDL_Rect numbersRects[],
                      int puzzleSize,
                      int map[],
                      int block_width,
                      int block_height,
                      int window_width,
                      int window_height);

#endif // GAME_H_INCLUDED