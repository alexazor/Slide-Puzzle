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

int create_window(Application &application)
{
    if (SDL_CreateWindowAndRenderer(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &application.pWindow, &application.pRenderer) < 0)
    {
        SDL_Quit();
        TTF_Quit();
        return -1;
    }
    else
    {
        SDL_SetWindowTitle(application.pWindow, "Slide-Puzzle");
        return 0;
    }
}

int init_program(Application &application)
{
    if (init_SDL() < 0 || init_TTF() < 0 || create_window(application) < 0)
        return -1;
    else
    {
        application.pFont = TTF_OpenFont(FONT_PATH, FONT_SIZE);
        if (application.pFont == nullptr)
        {
            error_message();
            close_program(application);
            return -1;
        }
        else
            return 0;
    }
}

void close_program(Application &application)
{
    if (application.pFont != nullptr)
        TTF_CloseFont(application.pFont);

    SDL_DestroyWindow(application.pWindow);
    SDL_DestroyRenderer(application.pRenderer);
    TTF_Quit();
    SDL_Quit();
}

namespace CHECK
{
    int create_text_texture(SDL_Texture *&pTextTexture, char *text, SDL_Colour fgColour, SDL_Colour bgColour, Application &application)
    {
        SDL_Surface *pTextSurface = TTF_RenderText_Shaded(application.pFont, text, fgColour, bgColour);

        if (pTextSurface == nullptr || surface_to_texture(pTextTexture, pTextSurface, application) < 0)
        {
            error_message();
            return -1;
        }

        return 0;
    }

    int create_img_texture(SDL_Texture *&pImgTexture, char *imgPath, Application &application)
    {
        SDL_Surface *pImgSurface = IMG_Load(imgPath);
        if (pImgSurface == nullptr || surface_to_texture(pImgTexture, pImgSurface, application) < 0)
        {
            error_message();
            return -1;
        }

        return 0;
    }

    int surface_to_texture(SDL_Texture *&pTexture, SDL_Surface *pSurface, Application &application)
    {
        pTexture = SDL_CreateTextureFromSurface(application.pRenderer, pSurface);
        SDL_FreeSurface(pSurface);

        if (pTexture == nullptr)
        {
            error_message();
            return -1;
        }

        return 0;
    }

    int create_rect(SDL_Texture *pTexture, SDL_Rect *pRect)
    {
        if (SDL_QueryTexture(pTexture, nullptr, nullptr, &pRect->w, &pRect->h) < 0)
        {
            error_message();
            return -1;
        }

        return 0;
    }

    int colour_background(Uint8 red, Uint8 green, Uint8 blue, Application &application)
    {
        if (SDL_SetRenderDrawColor(application.pRenderer, red, green, blue, 255) < 0 || SDL_RenderClear(application.pRenderer) < 0)
        {
            error_message();
            return -1;
        }

        return 0;
    }

    int colour_background_black(Application &application)
    {
        return colour_background(0, 0, 0, application);
    }

    int colour_background_white(Application &application)
    {
        return colour_background(255, 255, 255, application);
    }

    int render_texture(SDL_Texture *pTexture, SDL_Rect *pRect, Application &application)
    {
        if (SDL_RenderCopy(application.pRenderer, pTexture, nullptr, pRect) < 0)
        {
            error_message();
            return -1;
        }

        return 0;
    }

    int render_transparent_rectangle(SDL_Rect *pRect, Uint8 red, Uint8 green, Uint8 blue, Application &application)
    {
        if (SDL_SetRenderDrawColor(application.pRenderer, red, green, blue, 127) < 0 || SDL_RenderFillRect(application.pRenderer, pRect) < 0)
        {
            error_message();
            return -1;
        }

        return 0;
    }

    int render_transparent_green_rectangle(SDL_Rect *pRect, Application &application)
    {
        return render_transparent_rectangle(pRect, 0, 255, 0, application);
    }
} // namespace CHECK
