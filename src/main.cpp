#include "main.hpp"
#include "check.hpp"
#include "title.hpp"
// #include "game.hpp"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Application application;

    if (init_program(application) < 0)
        return EXIT_FAILURE;

    while (true)
    {
        switch (application.state)
        {
        case STATE_TITLE:
            Title_Screen::main(&application);
            break;

        case STATE_GAME:
            SDL_Log("Oops! -Game- tot implemented yet!");
            close_program(application);
            return EXIT_SUCCESS;
            /*resize_window_board(pWindow, puzzleSize, block_width, block_height, window_width, window_height);
            state = game(pRenderer, pFont, puzzleSize, block_width, block_height, window_width, window_height);*/
            break;

        case STATE_DEMO:
            SDL_Log("Oops! -Demo- not implemented yet!");
            close_program(application);
            return EXIT_SUCCESS;
            break;

        case STATE_QUIT:
            close_program(application);
            return EXIT_SUCCESS;
            break;

        case STATE_ERROR:
            close_program(application);
            return EXIT_FAILURE;
            break;

        default:
            SDL_Log("Unknown state!");
            close_program(application);
            return EXIT_FAILURE;
            break;
        }
    }
    return EXIT_FAILURE;
}