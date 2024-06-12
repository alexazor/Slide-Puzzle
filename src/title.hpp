/**
 * @file title.hpp
 * @author Alexandre AZOR
 * @brief Functions for the title page
 * @version 0.2
 * @date 2022-07-17
 *
 *
 */

#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

#include "main.hpp"
#include "check.hpp"
#include "mouse.hpp"

#define PUZZLE_SIZE_MIN 2
#define PUZZLE_SIZE_MAX 10
#define PUZZLE_SIZES PUZZLE_SIZE_MAX - PUZZLE_SIZE_MIN + 1

#define MAX_NUMBER_OF_DIGITS 2

#define NO_SELECTED_SIZE -1

enum Title_Text
{
    TITLE_TITLE = 0,
    TITLE_INSTRUCTION,
    TITLE_MODE,
    TITLE_GAME,
    TITLE_DEMO,
    //    TITLE_PRESS_P,
    TITLE_TEXT_NBR_OF_ELEMENTS
};

class Title_Screen
{
public:
    SDL_Texture *pTextTextures[Title_Text::TITLE_TEXT_NBR_OF_ELEMENTS] = {nullptr};
    SDL_Texture *pPuzzleSizesTextures[PUZZLE_SIZES] = {nullptr};
    SDL_Texture *pImgSDLTexture = nullptr;

    SDL_Rect textRects[Title_Text::TITLE_TEXT_NBR_OF_ELEMENTS];
    SDL_Rect puzzleSizesRects[PUZZLE_SIZES];
    SDL_Rect imgSDLRect;

    Application *pApp = nullptr;

    Title_Screen(Application *pApplication)
    {
        pApp = pApplication;
    };

    static void main(Application *pApp);

private:
    void set_window_size();

    int create_textures();

    int create_text_textures(SDL_Colour foregroundColour, SDL_Colour backgroundColour);

    int create_puzzle_sizes_textures(SDL_Colour foregroundColour, SDL_Colour backgroundColour);

    int create_image_texture();

    int create_rectangles();

    int create_text_rectangles();

    int create_puzzle_sizes_rectangles();

    int create_image_rectangle();

    void resize_image();

    void set_positions();

    void set_text_positions();

    void set_puzzle_sizes_positions();

    void set_image_positions();

    void event_loop();

    void handle_events(SDL_Event *pEvents, int *pSelectedSizeIndex, Program_State *pFutureState);

    void event_left_click(Sint32 mouseX, Sint32 mouseY, Program_State *pFutureState);

    void event_mouse_motion(Sint32 mouseX, Sint32 mouseY, int *pSelectedSizeIndex);

    int update_screen(const Program_State futureState, const int selectedSizeIndex);

    int render_text_textures();

    int render_puzzle_sizes_textures();

    int render_image_texture();

    int render_selected_size_rectangle(const int selectedSizeIndex);

    int render_future_state_rectangle(const int futureState);

    void destroy_textures();

    void destroy_text_textures(int maxIndex);

    void destroy_puzzle_sizes_textures(int maxIndex);
};

#endif // TITLE_H_INCLUDED