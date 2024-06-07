/**
 * @file MAIN.h
 * @author Alexandre AZOR
 * @brief Contants used throughout the whole program
 * @version 0.2
 * @date 2022-07-15
 *
 *
 */

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
// #include <time.h>

#define DEFAULT_WINDOW_WIDTH 629
#define DEFAULT_WINDOW_HEIGHT 629

#define PUZZLE_SIZE_MIN 2
#define PUZZLE_SIZE_MAX 10
#define PUZZLE_SIZES PUZZLE_SIZE_MAX - PUZZLE_SIZE_MIN + 1

#define FPS 20
#define PAUSE 1000 / FPS

enum Program_State
{
    STATE_TITLE,
    STATE_GAME,
    STATE_DEMO,
    STATE_QUIT,
    STATE_ERROR
};
#endif // MAIN_H_INCLUDED
