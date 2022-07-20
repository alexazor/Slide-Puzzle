#include "title.h"

State title(SDL_Renderer *pRenderer, TTF_Font *pFont)
{
    SDL_Texture *pTextTextures[TITLE_TEXT_NBR_OF_ELEMENTS] = {nullptr};
    SDL_Texture *pPuzzleSizesTextures[NUMBER_OF_SIZES] = {nullptr};
    SDL_Texture *pImgSDLTexture = nullptr;

    SDL_Rect textRects[TITLE_TEXT_NBR_OF_ELEMENTS];
    SDL_Rect puzzleSizesRects[NUMBER_OF_SIZES];
    SDL_Rect imgSDLRect;
    SDL_Rect selectionRect = SDL_Rect{0, 0, 0, 0};

    SDL_Event events;
    State state = STATE_TITLE;

    if (create_textures_title(pRenderer, pFont, pTextTextures, pPuzzleSizesTextures, pImgSDLTexture) < 0)
        return STATE_ERROR;

    if (create_rectangles_title(pTextTextures, pPuzzleSizesTextures, pImgSDLTexture,
                                textRects, puzzleSizesRects, imgSDLRect) < 0)
        state = STATE_ERROR;

    while (state == STATE_TITLE)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                state = STATE_QUIT;
                break;

            default:
                break;
            }
        }

        if (update_screen_title(pRenderer,
                                pTextTextures, pPuzzleSizesTextures, pImgSDLTexture,
                                textRects, puzzleSizesRects, imgSDLRect, selectionRect) < 0)
            state = STATE_ERROR;
    }

    destroy_textures_title(pTextTextures, pPuzzleSizesTextures, pImgSDLTexture);
    return state;
}

int create_textures_title(SDL_Renderer *&pRenderer,
                          TTF_Font *pFont,
                          SDL_Texture *pTextTextures[],
                          SDL_Texture *pPuzzleSizesTextures[],
                          SDL_Texture *&pImgSDLTexture)
{
    SDL_Colour fgColour = SDL_Colour{255, 255, 255, 255};
    SDL_Colour bgColour = SDL_Colour{0, 0, 0, 255};

    char textTitle[] = {"======Slide Puzzle======"};
    char textInstruction[] = {"Select the mode and choose the size"};
    char textMode[] = {"Current mode: Game    Demo"};
    char textPressP[] = {"P: Highlight the first misplaced bloc"};
    char *textsArray[] = {textTitle,
                          textInstruction,
                          textMode,
                          textPressP};

    char imgPath[] = {IMG_PATH};

    int puzzleSizeInt, i, j;
    char puzzleSizeChar[10];

    for (i = 0; i < TITLE_TEXT_NBR_OF_ELEMENTS; i++)
    {
        if (create_text_texture(pTextTextures[i], pFont, textsArray[i], fgColour, bgColour, pRenderer) < 0)
        {
            for (j = 0; j < i; j++)
                SDL_DestroyTexture(pTextTextures[j]);
            return -1;
        }
    }

    for (i = 0; i <= PUZZLE_SIZE_MAX - PUZZLE_SIZE_MIN; i++)
    {
        puzzleSizeInt = i + PUZZLE_SIZE_MIN;
        std::sprintf(puzzleSizeChar, "%d", i + PUZZLE_SIZE_MIN);

        if (create_text_texture(pPuzzleSizesTextures[i], pFont, puzzleSizeChar, fgColour, bgColour, pRenderer) < 0)
        {
            for (j = 0; j < TITLE_TEXT_NBR_OF_ELEMENTS; j++)
                SDL_DestroyTexture(pTextTextures[j]);

            for (j = 0; j < i; j++)
                SDL_DestroyTexture(pPuzzleSizesTextures[j]);

            return -1;
        }
    }

    if (create_img_texture(pImgSDLTexture, imgPath, pRenderer) < 0)
    {
        for (j = 0; j < TITLE_TEXT_NBR_OF_ELEMENTS; j++)
            SDL_DestroyTexture(pTextTextures[j]);

        for (j = 0; j <= PUZZLE_SIZE_MAX - PUZZLE_SIZE_MIN; j++)
            SDL_DestroyTexture(pPuzzleSizesTextures[j]);

        return -1;
    }

    return 0;
}

int create_rectangles_title(SDL_Texture *pTextTextures[],
                            SDL_Texture *pPuzzleSizesTextures[],
                            SDL_Texture *&pImgSDLTexture,
                            SDL_Rect textRects[],
                            SDL_Rect puzzleSizesRects[],
                            SDL_Rect &imgSDLRect)
{
    int i;

    for (i = 0; i < TITLE_TEXT_NBR_OF_ELEMENTS; i++)
    {
        if (SDL_QueryTexture(pTextTextures[i], nullptr, nullptr, &textRects[i].w, &textRects[i].h) < 0)
        {
            error_message();
            return -1;
        }
    }

    for (i = 0; i <= PUZZLE_SIZE_MAX - PUZZLE_SIZE_MIN; i++)
    {
        if (SDL_QueryTexture(pPuzzleSizesTextures[i], nullptr, nullptr, &puzzleSizesRects[i].w, &puzzleSizesRects[i].h) < 0)
        {
            error_message();
            return -1;
        }
    }

    if (SDL_QueryTexture(pImgSDLTexture, nullptr, nullptr, &imgSDLRect.w, &imgSDLRect.h) < 0)
    {
        error_message();
        return -1;
    }
    imgSDLRect.w = (3 * imgSDLRect.w) / 4;
    imgSDLRect.h = (3 * imgSDLRect.h) / 4;

    for (i = 0; i < TITLE_TEXT_NBR_OF_ELEMENTS; i++)
    {
        textRects[i].x = WINDOW_WIDTH / 2 - textRects[i].w / 2;

        if (i != TITLE_PRESS_P)
            textRects[i].y = 1.5 * i * textRects[i].h;
        else
            textRects[i].y = WINDOW_HEIGHT - 2 * textRects[i].h;
    }

    int space_width = WINDOW_WIDTH / (1 + PUZZLE_SIZES) - puzzleSizesRects[0].w;
    for (i = 0; i < PUZZLE_SIZES; i++)
    {
        puzzleSizesRects[i].x = space_width + i * (puzzleSizesRects[0].w + space_width);
        puzzleSizesRects[i].y = (WINDOW_HEIGHT + imgSDLRect.h) / 2 + 0.5 * puzzleSizesRects[i].h;
    }

    imgSDLRect.x = (WINDOW_WIDTH - imgSDLRect.w) / 2;
    imgSDLRect.y = (WINDOW_HEIGHT - imgSDLRect.h) / 2;

    return 0;
}

int update_screen_title(SDL_Renderer *pRenderer,
                        SDL_Texture *pTextTextures[],
                        SDL_Texture *pPuzzleSizesTextures[],
                        SDL_Texture *&pImgSDLTexture,
                        SDL_Rect textRects[],
                        SDL_Rect puzzleSizesRects[],
                        SDL_Rect &imgSDLRect,
                        SDL_Rect &selectionRect)
{
    int i;
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    for (i = 0; i < TITLE_TEXT_NBR_OF_ELEMENTS; i++)
    {
        if (SDL_RenderCopy(pRenderer, pTextTextures[i], nullptr, &textRects[i]) < 0)
        {
            error_message();
            return -1;
        }
    }

    for (i = 0; i < PUZZLE_SIZES; i++)
    {
        if (SDL_RenderCopy(pRenderer, pPuzzleSizesTextures[i], nullptr, &puzzleSizesRects[i]) < 0)
        {
            error_message();
            return -1;
        }
    }

    if (SDL_RenderCopy(pRenderer, pImgSDLTexture, nullptr, &imgSDLRect) < 0)
    {
        error_message();
        return -1;
    }

    SDL_RenderPresent(pRenderer);
    return 0;
}

void destroy_textures_title(SDL_Texture *pTextTextures[],
                            SDL_Texture *pPuzzleSizesTextures[],
                            SDL_Texture *pImgSDLTexture)
{
    int j;

    SDL_DestroyTexture(pImgSDLTexture);

    for (j = 0; j < TITLE_TEXT_NBR_OF_ELEMENTS; j++)
        SDL_DestroyTexture(pTextTextures[j]);

    for (j = 0; j < PUZZLE_SIZES; j++)
        SDL_DestroyTexture(pPuzzleSizesTextures[j]);
}

// for( SDL_Texture: pTextTextures)