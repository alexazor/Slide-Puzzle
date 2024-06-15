#include "game.hpp"

void Game::main(Application *pApp)
{
    Game game = Game(pApp);

    game.set_window_size();

    if (game.create_textures() < 0)
    {
        pApp->state = Program_State::STATE_ERROR;
        return;
    }

    if (game.create_rectangles() < 0)
    {
        game.destroy_textures();
        pApp->state = Program_State::STATE_ERROR;
        return;
    }

    game.set_positions();

    game.board.shuffle();

    SDL_SetRenderDrawBlendMode(game.pApp->pRenderer, SDL_BLENDMODE_BLEND);

    if (game.update_screen() < 0)
    {
        pApp->state = Program_State::STATE_ERROR;
        game.destroy_textures();
        return;
    }

    game.event_loop();
}

Game::Game(Application *pApplication)
{
    this->pApp = pApplication;
    this->board = Board(pApplication->puzzleSize);
}

void Game::set_window_size()
{
    int window_width = this->pApp->puzzleSize * (this->board.blockWidth + SEP_SIZE);
    int window_height = this->pApp->puzzleSize * (this->board.blockHeight + SEP_SIZE);

    SDL_SetWindowSize(this->pApp->pWindow, window_width, window_height);
}

int Game::create_textures()
{
    return this->board.create_textures(*this->pApp);
}

int Game::create_rectangles()
{
    return this->board.create_rectangles();
}

void Game::set_positions()
{
    this->board.set_positions();
}

void Game::event_loop()
{
    SDL_Event events;

    while (this->pApp->state == STATE_GAME)
    {
        this->handle_events(&events);

        if (this->update_screen() < 0)
        {
            this->pApp->state = STATE_ERROR;
            this->destroy_textures();

            return;
        }
        SDL_Delay(PAUSE);
    }

    this->destroy_textures();
}

void Game::handle_events(SDL_Event *pEvents)
{
    while (SDL_WaitEvent(pEvents))
    {
        switch (pEvents->type)
        {
        case SDL_QUIT:
            this->pApp->state = Program_State::STATE_QUIT;
            return;
            break;

        case SDL_KEYDOWN:
            if (pEvents->key.keysym.sym == SDLK_ESCAPE)
            {
                this->pApp->state = Program_State::STATE_TITLE;
                return;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (pEvents->button.button == SDL_BUTTON_LEFT)
            {
                event_left_click(pEvents->button.x, pEvents->button.y);
                return;
            }
            break;

        default:
            break;
        }
    }
}

void Game::event_left_click(Sint32 mouseX, Sint32 mouseY)
{
    int iClick, jClick;

    MOUSE::get_block_coordinates(mouseX, mouseY, this->board.blockHeight, this->board.blockWidth, &iClick, &jClick);
    this->board.move_line(iClick, jClick);
}

int Game::update_screen()
{
    if (CHECK::colour_background_white(*this->pApp) < 0)
        return -1;

    if (this->board.render_textures(*this->pApp) < 0)
        return -1;

    SDL_RenderPresent(this->pApp->pRenderer);

    return 0;
}

void Game::destroy_textures()
{
    this->board.destroy_textures(this->board.NUMBER_OF_BLOCKS - 1);
}