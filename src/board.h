/**
*@file initialisation - closure.h
*@author Alexandre AZOR
*@brief Functions like initialisation or
*@version 0.1
* @date 2022-07-25

*/

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "main.h"
#include "check.h"

#define SEP_SIZE 2

enum Block_direction
{
    BLOCK_UP = 0,
    BLOCK_LEFT,
    BLOCK_DOWN,
    BLOCK_RIGHT
};

bool resolved(int map[], int puzzleSize);

void resize_window_board(SDL_Window *pWindow, int puzzleSize, int &block_width, int &block_height, int &window_width, int &window_height);

void move_block(int map[], int puzzleSize, int &iVoid, int &jVoid, int dir, SDL_Rect numbersRect[], int block_width, int block_height);

void shuffle_board(int map[], int puzzleSize, SDL_Rect numbersRect[], int block_width, int block_height);

void find_void(int map[], int puzzleSize, int &iVoid, int &jVoid);

int create_textures_board(SDL_Renderer *&pRenderer,
                          TTF_Font *pFont,
                          SDL_Texture *pNumbersTextures[],
                          int puzzleSize);

int create_rectangles_board(SDL_Texture *pNumbersTextures[],
                            SDL_Rect numbersRects[],
                            int puzzleSize,
                            int block_width,
                            int block_height);

int update_screen_board(SDL_Renderer *pRenderer,
                        SDL_Texture *pNumbersTextures[],
                        SDL_Rect numbersRects[],
                        SDL_Rect *blockRect,
                        int puzzleSize,
                        int map[],
                        int block_width,
                        int block_height);

void destroy_textures_board(SDL_Texture *pNumberTextures[], int puzzleSize);
#endif // BOARD_H_INCLUDED