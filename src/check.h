/**
 * @file check.h
 * @author Alexandre AZOR
 * @brief Functions like initialisation or font opening are checked.
 *        If an error is detected, the program is closed.
 *        Also contains the closing functions
 * @version 0.2
 * @date 2022-06-07
 *
 *
 */

#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED

#include <iostream>
#include <fstream>
#include "main.hpp"
#include "slide_puzzle.hpp"

#define IMG_PATH "../res/img/SDL_logo.png"
#define FONT_PATH "../res/font/times.ttf"
#define FONT_SIZE 40

void error_message(); // Logs the error message from SDL

int init_SDL();
int init_TTF();
int create_window(Slide_Puzzle &slidePuzzle);
int init_program(Slide_Puzzle &slidePuzzle);

void close_program(Slide_Puzzle &slidePuzzle);

int create_text_texture(SDL_Texture *&pTextTexture, char *text, SDL_Colour fgColour, SDL_Colour bgColour, Slide_Puzzle &slidePuzzle);
int create_img_texture(SDL_Texture *&pImgTexture, char *imgPath, Slide_Puzzle &slidePuzzle);
int surface_to_texture(SDL_Texture *&pTexture, SDL_Surface *pSurface, Slide_Puzzle &slidePuzzle);

#endif // CHECK_H_INCLUDED