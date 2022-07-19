/**
 * @file initialisation-closure.h
 * @author Alexandre AZOR
 * @brief Functions like initialisation or font opening are checked.
 *        If an error is detected, the program is closed.
 *        Also contains the closing functions
 * @version 0.1
 * @date 2022-07-16
 *
 *
 */

#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED

#include <iostream>
#include <fstream>
#include "main.h"

#define IMG_PATH "res/img/SDL_logo.png"
#define FONT_PATH "res/font/times.ttf"
#define FONT_SIZE 40

void error_message(); // Logs the error message from SDL

int init_SDL();
int init_TTF();
int create_window(SDL_Window *&pWindow, SDL_Renderer *&pRenderer);
int init_program(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *&pFont);

void close_program(SDL_Window *pWindow, SDL_Renderer *pRenderer, TTF_Font *pFont);

int create_text_texture(SDL_Texture *&pTextTexture, TTF_Font *pFont, char *text, SDL_Colour fgColour, SDL_Colour bgColour, SDL_Renderer *pRenderer);
int create_img_texture(SDL_Texture *&pImgTexture, char *imgPath, SDL_Renderer *pRenderer);
int surface_to_texture(SDL_Texture *&pTexture, SDL_Surface *pSurface, SDL_Renderer *pRenderer);
#endif // CHECK_H_INCLUDED