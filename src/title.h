/**
 * @file title.h
 * @author Alexandre AZOR
 * @brief Functions for the title page
 * @version 0.1
 * @date 2022-07-17
 *
 *
 */

#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "initialisation-closure.h"

Mode chose_mode(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, Mode mode);
void update_title_window(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *titleFont, TTF_Font *textFont);
#endif // TITLE_H_INCLUDED