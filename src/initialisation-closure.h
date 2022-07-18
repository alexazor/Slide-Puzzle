/**
 * @file initialisation-closure.h
 * @author Alexandre AZOR
 * @brief Contains functions for the initialisation (like SDL_init), the closure (like SDL_quit) and
 * @version 0.1
 * @date 2022-07-16
 *
 *
 */

#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

#include <iostream>
#include <fstream>
#include "constants.h"

#define FONT_PATH "res/font/times.ttf"
#define FONT_SIZE 40

void error_message(); // Logs the error message from SDL

int init_SDL();
int init_TTF();
int create_window(SDL_Window *&pWindow, SDL_Renderer *&pRenderer);
int init_program(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *&pFont);

void close_program(SDL_Window *pWindow, SDL_Renderer *pRenderer, TTF_Font *pFont);

int create_text_surface(SDL_Surface *&textSurface, TTF_Font *pFont, char *text, SDL_Colour fgColour, SDL_Colour bgColour);
#endif // INITIALISATION_H_INCLUDED