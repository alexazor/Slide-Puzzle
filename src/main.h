/**
 * @file constants.h
 * @author Alexandre AZOR
 * @brief Contants used throughout the whole program
 * @version 0.1
 * @date 2022-07-15
 *
 *
 */

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 629
#define WINDOW_HEIGHT 629

#define PUZZLE_SIZE_MIN 3
#define PUZZLE_SIZE_MAX 10
#define PUZZLE_SIZES PUZZLE_SIZE_MAX - PUZZLE_SIZE_MIN + 1

#define FPS 20
#define PAUSE 1000 / FPS

enum State
{
    STATE_TITLE,
    STATE_GAME,
    STATE_QUIT,
    STATE_ERROR
};
#endif // CONSTANTS_H_INCLUDED
