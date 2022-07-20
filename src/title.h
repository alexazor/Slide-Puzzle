/**
 * @file title.h
 * @author Alexandre AZOR
 * @brief Functions for the title page
 * @version 0.2
 * @date 2022-07-17
 *
 *
 */

#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

#include "check.h"

#define NUMBER_OF_SIZES PUZZLE_SIZE_MAX - PUZZLE_SIZE_MIN + 1

State title(SDL_Renderer *pRenderer, TTF_Font *pFont);

int create_textures_title(SDL_Renderer *&pRenderer,
                          TTF_Font *pFont,
                          SDL_Texture *pTextTextures[],
                          SDL_Texture *pPuzzleSizesTextures[],
                          SDL_Texture *&pImgSDLTexture);

int create_rectangles_title(SDL_Texture *pTextTextures[],
                            SDL_Texture *pPuzzleSizesTextures[],
                            SDL_Texture *&pImgSDLTexture,
                            SDL_Rect textRects[],
                            SDL_Rect puzzleSizesRects[],
                            SDL_Rect &imgSDLRect);

int update_screen_title(SDL_Renderer *pRenderer,
                        SDL_Texture *pTextTextures[],
                        SDL_Texture *pPuzzleSizesTextures[],
                        SDL_Texture *&pImgSDLTexture,
                        SDL_Rect textRects[],
                        SDL_Rect puzzleSizesRects[],
                        SDL_Rect &imgSDLRect,
                        SDL_Rect &selectionRect);

void destroy_textures_title(SDL_Texture *pTextTextures[],
                            SDL_Texture *pPuzzleSizesTextures[],
                            SDL_Texture *pImgSDLTexture);

enum Title_Text
{
    TITLE_TITLE = 0,
    TITLE_INSTRUCTION,
    TITLE_MODE,
    TITLE_PRESS_P,
    TITLE_TEXT_NBR_OF_ELEMENTS
};

#endif // TITLE_H_INCLUDED