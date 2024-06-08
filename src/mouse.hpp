/**
 * @file mouse.hpp
 * @author Alexandre AZOR
 * @brief Functions for the mouse
 * @version 1.0
 * @date 2024-06-08
 */

#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "main.hpp"
#include "board.hpp"

bool is_in_segement(int a, int l, int x);
bool mouse_over_rectangle(SDL_Rect rect, Sint32 mouseX, Sint32 mouseY);
void get_block_position(Sint32 mouseX, Sint32 mouseY, int block_height, int block_width, int &i, int &j);
void move_line(int map[], int puzzleSize, int iClick, int jClick, int &iVoid, int &jVoid, SDL_Rect numbersRect[], int block_width, int block_height);
#endif // MOUSE_H_INCLUDED