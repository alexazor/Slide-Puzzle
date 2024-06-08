#include "check.hpp"

void error_message()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());

    std::ofstream errorFile("Error.txt");
    errorFile << "[DEBUG] > " << SDL_GetError();
    errorFile.close();
}

int init_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        error_message();
        return -1;
    }

    return 0;
}

int init_TTF()
{
    if (TTF_Init() < 0)
    {
        SDL_Quit();
        error_message();
        return -1;
    }
    return 0;
}

int create_window(Slide_Puzzle &slidePuzzle)
{
    if (SDL_CreateWindowAndRenderer(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &slidePuzzle.pWindow, &slidePuzzle.pRenderer) < 0)
    {
        SDL_Quit();
        TTF_Quit();
        return -1;
    }
    else
    {
        SDL_SetWindowTitle(slidePuzzle.pWindow, "Slide-Puzzle");
        return 0;
    }
}

int init_program(Slide_Puzzle &slidePuzzle)
{
    if (init_SDL() < 0 || init_TTF() < 0 || create_window(slidePuzzle) < 0)
        return -1;
    else
    {
        slidePuzzle.pFont = TTF_OpenFont(FONT_PATH, FONT_SIZE);
        if (slidePuzzle.pFont == nullptr)
        {
            error_message();
            close_program(slidePuzzle);
            return -1;
        }
        else
            return 0;
    }
}

void close_program(Slide_Puzzle &slidePuzzle)
{
    if (slidePuzzle.pFont != nullptr)
        TTF_CloseFont(slidePuzzle.pFont);

    SDL_DestroyWindow(slidePuzzle.pWindow);
    SDL_DestroyRenderer(slidePuzzle.pRenderer);
    TTF_Quit();
    SDL_Quit();
}

int create_text_texture(SDL_Texture *pTextTexture, char *text, SDL_Colour fgColour, SDL_Colour bgColour, Slide_Puzzle &slidePuzzle)
{
    SDL_Surface *pTextSurface = TTF_RenderText_Shaded(slidePuzzle.pFont, text, fgColour, bgColour);

    if (pTextSurface == nullptr || surface_to_texture(pTextTexture, pTextSurface, slidePuzzle) < 0)
    {
        error_message();
        return -1;
    }

    return 0;
}

int create_img_texture(SDL_Texture *pImgTexture, char *imgPath, Slide_Puzzle &slidePuzzle)
{
    SDL_Surface *pImgSurface = IMG_Load(imgPath);
    if (pImgSurface == nullptr || surface_to_texture(pImgTexture, pImgSurface, slidePuzzle) < 0)
    {
        error_message();
        return -1;
    }

    return 0;
}

int surface_to_texture(SDL_Texture *pTexture, SDL_Surface *pSurface, Slide_Puzzle &slidePuzzle)
{
    pTexture = SDL_CreateTextureFromSurface(slidePuzzle.pRenderer, pSurface);
    SDL_FreeSurface(pSurface);

    if (pTexture == nullptr)
    {
        error_message();
        return -1;
    }

    return 0;
}