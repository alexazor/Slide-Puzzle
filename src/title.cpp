#include "title.h"

State title(SDL_Renderer *pRenderer, TTF_Font *pFont, int &puzzleSize)
{
    SDL_Texture *pTextTextures[TITLE_TEXT_NBR_OF_ELEMENTS] = {nullptr};
    SDL_Texture *pPuzzleSizesTextures[PUZZLE_SIZES] = {nullptr};
    SDL_Texture *pImgSDLTexture = nullptr;

    SDL_Rect textRects[TITLE_TEXT_NBR_OF_ELEMENTS];
    SDL_Rect puzzleSizesRects[PUZZLE_SIZES];
    SDL_Rect imgSDLRect;

    if (create_textures_title(pRenderer, pFont, pTextTextures, pPuzzleSizesTextures, pImgSDLTexture) < 0)
        return STATE_ERROR;

    if (create_rectangles_title(pTextTextures, pPuzzleSizesTextures, pImgSDLTexture,
                                textRects, puzzleSizesRects, imgSDLRect) < 0)
    {
        destroy_textures_title(pTextTextures, pPuzzleSizesTextures, pImgSDLTexture);
        return STATE_ERROR;
    }

    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);

    return event_loop_title(pRenderer,
                            pTextTextures, pPuzzleSizesTextures, pImgSDLTexture,
                            textRects, puzzleSizesRects, imgSDLRect, puzzleSize);
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
    char textMode[] = {"Click to change:"};
    char textGame[] = {"Game"};
    char textDemo[] = {"Demo"};
    char textPressP[] = {"P: Highlight the first misplaced bloc"};
    char *textsArray[] = {textTitle,
                          textInstruction,
                          textMode,
                          textGame,
                          textDemo,
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
            error_message();
            return -1;
        }
    }

    for (i = 0; i < PUZZLE_SIZES; i++)
    {
        puzzleSizeInt = i + PUZZLE_SIZE_MIN;
        std::sprintf(puzzleSizeChar, "%d", i + PUZZLE_SIZE_MIN);

        if (create_text_texture(pPuzzleSizesTextures[i], pFont, puzzleSizeChar, fgColour, bgColour, pRenderer) < 0)
        {
            for (j = 0; j < TITLE_TEXT_NBR_OF_ELEMENTS; j++)
                SDL_DestroyTexture(pTextTextures[j]);

            for (j = 0; j < i; j++)
                SDL_DestroyTexture(pPuzzleSizesTextures[j]);

            error_message();
            return -1;
        }
    }

    if (create_img_texture(pImgSDLTexture, imgPath, pRenderer) < 0)
    {
        for (j = 0; j < TITLE_TEXT_NBR_OF_ELEMENTS; j++)
            SDL_DestroyTexture(pTextTextures[j]);

        for (j = 0; j <= PUZZLE_SIZE_MAX - PUZZLE_SIZE_MIN; j++)
            SDL_DestroyTexture(pPuzzleSizesTextures[j]);

        error_message();
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
    int i, space_width_puzzle_sizes, space_width_modes, textHeight;

    // Creation of the SDL_Rects
    //---Creation of the SDL_Rects for the text textures
    for (i = 0; i < TITLE_TEXT_NBR_OF_ELEMENTS; i++)
        if (SDL_QueryTexture(pTextTextures[i], nullptr, nullptr, &textRects[i].w, &textRects[i].h) < 0)
            RETURN_ERR

    //---Creation of the SDL_Rects for the puzzle size textures
    for (i = 0; i <= PUZZLE_SIZE_MAX - PUZZLE_SIZE_MIN; i++)
        if (SDL_QueryTexture(pPuzzleSizesTextures[i], nullptr, nullptr, &puzzleSizesRects[i].w, &puzzleSizesRects[i].h) < 0)
            RETURN_ERR

    //---Creation of the SDL_Rects for the SDL image textures
    if (SDL_QueryTexture(pImgSDLTexture, nullptr, nullptr, &imgSDLRect.w, &imgSDLRect.h) < 0)
        RETURN_ERR

    // Resize image
    imgSDLRect.w = (3 * imgSDLRect.w) / 4;
    imgSDLRect.h = (3 * imgSDLRect.h) / 4;

    // Positions of the SDL_Rect
    //---Positions for the text textures
    space_width_modes = textRects[TITLE_GAME].w / 2;
    textHeight = textRects[TITLE_TITLE].h;

    textRects[TITLE_TITLE].x = (WINDOW_WIDTH - textRects[TITLE_TITLE].w) / 2;
    textRects[TITLE_TITLE].y = 0;

    textRects[TITLE_INSTRUCTION].x = (WINDOW_WIDTH - textRects[TITLE_INSTRUCTION].w) / 2;
    textRects[TITLE_INSTRUCTION].y = 1.5 * textHeight;

    textRects[TITLE_MODE].x = (WINDOW_WIDTH - textRects[TITLE_MODE].w - textRects[TITLE_GAME].w - textRects[TITLE_DEMO].w) / 2 - space_width_modes;
    textRects[TITLE_MODE].y = 3 * textHeight;

    textRects[TITLE_GAME].x = (WINDOW_WIDTH + textRects[TITLE_MODE].w - textRects[TITLE_GAME].w - textRects[TITLE_DEMO].w) / 2;
    textRects[TITLE_GAME].y = 3 * textHeight;

    textRects[TITLE_DEMO].x = (WINDOW_WIDTH + textRects[TITLE_MODE].w + textRects[TITLE_GAME].w - textRects[TITLE_DEMO].w) / 2 + space_width_modes;
    textRects[TITLE_DEMO].y = 3 * textHeight;

    textRects[TITLE_PRESS_P].x = (WINDOW_WIDTH - textRects[TITLE_PRESS_P].w) / 2;
    textRects[TITLE_PRESS_P].y = WINDOW_HEIGHT - 2 * textHeight;

    //---Position for the puzzle size textures
    space_width_puzzle_sizes = WINDOW_WIDTH / (1 + PUZZLE_SIZES) - puzzleSizesRects[0].w;
    for (i = 0; i < PUZZLE_SIZES; i++)
    {
        puzzleSizesRects[i].x = space_width_puzzle_sizes + i * (puzzleSizesRects[0].w + space_width_puzzle_sizes);
        puzzleSizesRects[i].y = (WINDOW_HEIGHT + imgSDLRect.h) / 2 + 0.5 * puzzleSizesRects[i].h;
    }

    //---Position of the image
    imgSDLRect.x = (WINDOW_WIDTH - imgSDLRect.w) / 2;
    imgSDLRect.y = (WINDOW_HEIGHT - imgSDLRect.h) / 2;

    return 0;
}

State event_loop_title(SDL_Renderer *pRenderer,
                       SDL_Texture *pTextTextures[],
                       SDL_Texture *pPuzzleSizesTextures[],
                       SDL_Texture *&pImgSDLTexture,
                       SDL_Rect textRects[],
                       SDL_Rect puzzleSizesRects[],
                       SDL_Rect &imgSDLRect,
                       int &puzzleSize)
{
    const int X_GAME = textRects[TITLE_MODE].x + (50 * textRects[TITLE_MODE].w) / 100;
    const int X_DEMO = X_GAME + (30 * textRects[TITLE_MODE].w) / 100;
    int selectedSizeIndex, sizeIndex;

    SDL_Event events;
    State state = STATE_TITLE;
    State futureState = STATE_GAME;

    int size;

    while (state == STATE_TITLE)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                state = STATE_QUIT;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT)
                {
                    if (mouse_over_rectangle(textRects[TITLE_DEMO], events.button.x, events.button.y))
                        futureState = STATE_DEMO;
                    if (mouse_over_rectangle(textRects[TITLE_GAME], events.button.x, events.button.y))
                        futureState = STATE_GAME;

                    for (size = 0; size < PUZZLE_SIZES; size++)
                        if (mouse_over_rectangle(puzzleSizesRects[size], events.button.x, events.button.y))
                        {
                            state = futureState;
                            puzzleSize = size + PUZZLE_SIZE_MIN;
                        }
                }
                break;

            case SDL_MOUSEMOTION:
                selectedSizeIndex = -1;
                for (sizeIndex = 0; sizeIndex < PUZZLE_SIZES; sizeIndex++)
                    if (mouse_over_rectangle(puzzleSizesRects[sizeIndex], events.motion.x, events.motion.y))
                        selectedSizeIndex = sizeIndex;
                break;

            default:
                break;
            }
        }

        if (update_screen_title(pRenderer,
                                pTextTextures, pPuzzleSizesTextures, pImgSDLTexture,
                                textRects, puzzleSizesRects, imgSDLRect,
                                futureState, selectedSizeIndex) < 0)
            state = STATE_ERROR;
    }

    destroy_textures_title(pTextTextures, pPuzzleSizesTextures, pImgSDLTexture);
    return state;
}

int update_screen_title(SDL_Renderer *pRenderer,
                        SDL_Texture *pTextTextures[],
                        SDL_Texture *pPuzzleSizesTextures[],
                        SDL_Texture *pImgSDLTexture,
                        SDL_Rect textRects[],
                        SDL_Rect puzzleSizesRects[],
                        SDL_Rect imgSDLRect,
                        State futureState,
                        int selectedSizeIndex)
{
    int i;

    if (SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255) < 0 || SDL_RenderClear(pRenderer) < 0)
        RETURN_ERR

    for (i = 0; i < TITLE_TEXT_NBR_OF_ELEMENTS; i++)
        if (SDL_RenderCopy(pRenderer, pTextTextures[i], nullptr, &textRects[i]) < 0)
            RETURN_ERR

    for (i = 0; i < PUZZLE_SIZES; i++)
    {
        if (SDL_RenderCopy(pRenderer, pPuzzleSizesTextures[i], nullptr, &puzzleSizesRects[i]) < 0)
            RETURN_ERR

        if (i == selectedSizeIndex)
            if (SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 127) < 0 || SDL_RenderFillRect(pRenderer, &puzzleSizesRects[i]) < 0)
                RETURN_ERR
    }

    if (SDL_RenderCopy(pRenderer, pImgSDLTexture, nullptr, &imgSDLRect) < 0)
        RETURN_ERR

    if (futureState == STATE_GAME)
    {
        if (SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 127) < 0 || SDL_RenderFillRect(pRenderer, &textRects[TITLE_GAME]) < 0)
            RETURN_ERR
    }

    else
    {
        if (SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 127) < 0 || SDL_RenderFillRect(pRenderer, &textRects[TITLE_DEMO]) < 0)
            RETURN_ERR
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