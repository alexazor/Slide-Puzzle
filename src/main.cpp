#include "main.hpp"
#include "check.hpp"
#include "title.hpp"
#include "game.hpp"
#include "demo.hpp"

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
            Game::main(&application);
            break;

        case STATE_DEMO:
            Demo::main(&application);
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