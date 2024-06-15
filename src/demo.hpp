/**
*@file demo.hpp
*@author Alexandre AZOR
*@brief Functions for automatic solver
*@version 1.0
*@date 2024-06-15

*/

#ifndef DEMO_H_INCLUDED
#define DEMO_H_INCLUDED

#include "main.hpp"
#include "check.hpp"
#include "board.hpp"

#define FPS_DEMO 15
#define PAUSE_DEMO 1000 / FPS_DEMO

enum Demo_Phase
{
    PHASE_REGULAR = 0,
    PHASE_RIGHT_COLUMN,
    PHASE_TWO_LAST_LINES,
    PHASE_THREE_LAST_BLOCKS
};

class Demo
{
public:
    Board board;
    Application *pApp;

    Demo(Application *pApplication);

    static void main(Application *pApp);

private:
    void set_window_size();

    void set_positions();

    int create_textures();

    int create_rectangles();

    void event_loop();

    void handle_events(SDL_Event *pEvents);

    void next_move();

    int update_screen();

    void destroy_textures();
};
#endif // DEMO_H_INCLUDED