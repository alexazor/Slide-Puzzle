#include "check.h"

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
    else
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
    else
        return 0;
}

int create_window(SDL_Window *&pWindow, SDL_Renderer *&pRenderer)
{
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_Quit();
        TTF_Quit();
        return -1;
    }
    else
    {
        SDL_SetWindowTitle(pWindow, "Slide-Puzzle");
        return 0;
    }
}

int init_program(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *&pFont)
{
    if (init_SDL() < 0 || init_TTF() < 0 || create_window(pWindow, pRenderer) < 0)
        return -1;
    else
    {
        pFont = TTF_OpenFont(FONT_PATH, FONT_SIZE);
        if (pFont == nullptr)
        {
            error_message();
            close_program(pWindow, pRenderer, nullptr);
            return -1;
        }
        else
            return 0;
    }
}

void close_program(SDL_Window *pWindow, SDL_Renderer *pRenderer, TTF_Font *pFont)
{
    if (pFont != nullptr)
        TTF_CloseFont(pFont);

    SDL_DestroyWindow(pWindow);
    SDL_DestroyRenderer(pRenderer);
    TTF_Quit();
    SDL_Quit();
}

int create_text_texture(SDL_Texture *&pTextTexture, TTF_Font *pFont, char *text, SDL_Colour fgColour, SDL_Colour bgColour, SDL_Renderer *pRenderer)
{
    SDL_Surface *pTextSurface = TTF_RenderText_Shaded(pFont, text, fgColour, bgColour);

    if (pTextSurface == nullptr || surface_to_texture(pTextTexture, pTextSurface, pRenderer))
    {
        error_message();
        return -1;
    }
    else
        return 0;
}

int create_img_texture(SDL_Texture *&pImgTexture, char *imgPath, SDL_Renderer *pRenderer)
{
    SDL_Surface *pImgSurface = IMG_Load(imgPath);
    if (pImgSurface == nullptr || surface_to_texture(pImgTexture, pImgSurface, pRenderer) < 0)
    {
        error_message();
        return -1;
    }
    return 0;
}

int surface_to_texture(SDL_Texture *&pTexture, SDL_Surface *pSurface, SDL_Renderer *pRenderer)
{
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    SDL_FreeSurface(pSurface);

    if (pTexture == nullptr)
    {
        error_message();
        return -1;
    }
    else
        return 0;
}