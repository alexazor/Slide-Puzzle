/**
 * @file initialisation-closure.h
 * @author Alexandre AZOR
 * @brief Contains functions for the initialisation (SDL_init, TTF_init, creation of window) and for the closure (SDL_quit, TTF_quit, etc...)
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

int init_SDL(); // Initialise the SDL and SDL_TTF libraries
int init_TTF(); // Initialise the SDL and SDL_TTF libraries
int create_window(SDL_Window *&pWindow, SDL_Renderer *&pRenderer);
int init_program(SDL_Window *&pWindow, SDL_Renderer *&pRenderer); // Initialise the SDL and SDL_TTF libraries

void close_program(SDL_Window *&pWindow, SDL_Renderer *&pRenderer);

int open_font(TTF_Font *&pFont, char *filePath, int ptSize, Mode mode);

int create_text_surface(SDL_Surface *&textSurface, TTF_Font *font, char *text, SDL_Colour fgColour, SDL_Colour bgColour, TTF_Text_Type textType);
int create_text_surface(SDL_Surface *&textSurface, TTF_Font *font, char *text, SDL_Colour fgColour, TTF_Text_Type textType);
#endif // INITIALISATION_H_INCLUDED