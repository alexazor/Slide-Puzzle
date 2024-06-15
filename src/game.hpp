/**
 * @file game.hpp
 * @author Alexandre AZOR
 * @brief Functions for the actual game
 * @version 1.0
 * @date 2024-06-12
 *
 *
 */

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "main.hpp"
#include "application.hpp"
#include "board.hpp"
#include "check.hpp"
#include "mouse.hpp"

class Game
{
public:
    Board board;
    Application *pApp;

    Game(Application *pApplication);

    static void main(Application *pApp);

private:
    void set_window_size();

    void set_positions();

    int create_textures();

    int create_rectangles();

    void event_loop();

    void handle_events(SDL_Event *pEvents);

    void event_left_click(Sint32 mouseX, Sint32 mouseY);

    int update_screen();

    void destroy_textures();
};

#endif // GAME_H_INCLUDED