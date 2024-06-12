/**
 * @file check.hpp
 * @author Alexandre AZOR
 * @brief Functions like initialisation or font opening are checked.
 *        If an error is detected, the program is closed.
 *        Also contains the closing functions
 * @version 1.0
 * @date 2024-06-07
 *
 *
 */

#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED

#include <iostream>
#include <fstream>
#include "main.hpp"
#include "application.hpp"

void error_message(); // Logs the error message from SDL

int init_SDL();
int init_TTF();
int create_window(Application &application);
int init_program(Application &application);

void close_program(Application &application);

namespace CHECK
{
    int create_text_texture(SDL_Texture *&pTextTexture, char *text, SDL_Colour fgColour, SDL_Colour bgColour, Application &application);

    int create_img_texture(SDL_Texture *&pImgTexture, char *imgPath, Application &application);

    int surface_to_texture(SDL_Texture *&pTexture, SDL_Surface *pSurface, Application &application);

    int create_rect(SDL_Texture *pTexture, SDL_Rect *pRect);

    int colour_background(Uint8 red, Uint8 green, Uint8 blue, Application &application);

    int colour_background_black(Application &application);

    int colour_background_white(Application &application);

    int render_texture(SDL_Texture *pTexture, SDL_Rect *pRect, Application &application);

    int render_transparent_rectangle(SDL_Rect *pRect, Uint8 red, Uint8 green, Uint8 blue, Application &application);

    int render_transparent_green_rectangle(SDL_Rect *pRect, Application &application);

} // namespace CHECK

#endif // CHECK_H_INCLUDED