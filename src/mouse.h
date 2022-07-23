/**
 * @file mouse.h
 * @author Alexandre AZOR
 * @brief Functions for the mouse
 * @version 0.1
 * @date 2022-07-23
 */

#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "main.h"

bool is_in_segement(int a, int l, int x);
bool mouse_over_rectangle(SDL_Rect rect, Sint32 mouseX, Sint32 mouseY);

#endif // MOUSE_H_INCLUDED