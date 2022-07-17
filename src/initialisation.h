/**
 * @file initialisation.h
 * @author Alexandre AZOR
 * @brief Functions to initialise the SDL library and create a window
 * @version 0.1
 * @date 2022-07-16
 *
 *
 */

#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"

void error_message(); // Logs the error message from SDL
int init_SDL();       // Initialise the SDL and SDL_TTF libraries
int init_TTF();       // Initialise the SDL and SDL_TTF libraries
int create_window(SDL_Window *&pWindow, SDL_Renderer *&pRenderer);
int init_program(SDL_Window *&pWindow, SDL_Renderer *&pRenderer); // Initialise the SDL and SDL_TTF libraries

#endif // INITIALISATION_H_INCLUDED