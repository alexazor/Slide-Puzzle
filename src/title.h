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

#include "initialisation-closure.h"

Mode title(SDL_Window *pWindow, SDL_Renderer *pRenderer, TTF_Font *pFont);
#endif // TITLE_H_INCLUDED