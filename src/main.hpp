/**
 * @file main.hpp
 * @author Alexandre AZOR
 * @brief Contants used throughout the whole program
 * @version 1.0
 * @date 2024-06-08
 *
 *
 */

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <cstdlib>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define DEFAULT_WINDOW_WIDTH 629
#define DEFAULT_WINDOW_HEIGHT 629

#define FPS 20
#define PAUSE 1000 / FPS

#define IMG_PATH "res/img/SDL_logo.png"
#define FONT_PATH "res/font/times.ttf" // times
#define FONT_SIZE 40

#define SEP_SIZE 2

enum Program_State
{
    STATE_TITLE,
    STATE_GAME,
    STATE_DEMO,
    STATE_QUIT,
    STATE_ERROR
};
#endif // MAIN_H_INCLUDED
