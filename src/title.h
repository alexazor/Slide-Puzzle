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
#include "mouse.h"

State title(SDL_Renderer *pRenderer, TTF_Font *pFont, int &puzzleSize);

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

State event_loop_title(SDL_Renderer *pRenderer,
                       SDL_Texture *pTextTextures[],
                       SDL_Texture *pPuzzleSizesTextures[],
                       SDL_Texture *&pImgSDLTexture,
                       SDL_Rect textRects[],
                       SDL_Rect puzzleSizesRects[],
                       SDL_Rect &imgSDLRect,
                       int &puzzleSize);

int update_screen_title(SDL_Renderer *pRenderer,
                        SDL_Texture *pTextTextures[],
                        SDL_Texture *pPuzzleSizesTextures[],
                        SDL_Texture *pImgSDLTexture,
                        SDL_Rect textRects[],
                        SDL_Rect puzzleSizesRects[],
                        SDL_Rect imgSDLRect,
                        State futureState,
                        int selectedSizeindex);

void destroy_textures_title(SDL_Texture *pTextTextures[],
                            SDL_Texture *pPuzzleSizesTextures[],
                            SDL_Texture *pImgSDLTexture);

enum Title_Text
{
    TITLE_TITLE = 0,
    TITLE_INSTRUCTION,
    TITLE_MODE,
    TITLE_GAME,
    TITLE_DEMO,
    TITLE_PRESS_P,
    TITLE_TEXT_NBR_OF_ELEMENTS
};

#endif // TITLE_H_INCLUDED