#include "demo.hpp"

void Demo::main(Application *pApp)
{
    Demo demo = Demo(pApp);

    demo.set_window_size();

    if (demo.create_textures() < 0)
    {
        pApp->state = Program_State::STATE_ERROR;
        return;
    }

    if (demo.create_rectangles() < 0)
    {
        demo.destroy_textures();
        pApp->state = Program_State::STATE_ERROR;
        return;
    }

    demo.set_positions();

    demo.board.shuffle();

    SDL_SetRenderDrawBlendMode(demo.pApp->pRenderer, SDL_BLENDMODE_BLEND);

    if (demo.update_screen() < 0)
    {
        pApp->state = Program_State::STATE_ERROR;
        demo.destroy_textures();
        return;
    }

    demo.event_loop();
}

Demo::Demo(Application *pApplication)
{
    this->pApp = pApplication;
    this->board = Board(pApplication->puzzleSize);
}

void Demo::set_window_size()
{
    int window_width = this->pApp->puzzleSize * (this->board.blockWidth + SEP_SIZE);
    int window_height = this->pApp->puzzleSize * (this->board.blockHeight + SEP_SIZE);

    SDL_SetWindowSize(this->pApp->pWindow, window_width, window_height);
}

int Demo::create_textures()
{
    return this->board.create_textures(*this->pApp);
}

int Demo::create_rectangles()
{
    return this->board.create_rectangles();
}

void Demo::set_positions()
{
    this->board.set_positions();
}

void Demo::event_loop()
{
    SDL_Event events;

    while (this->pApp->state == STATE_DEMO)
    {
        this->handle_events(&events);

        this->next_move();

        if (this->update_screen() < 0)
        {
            this->pApp->state = STATE_ERROR;
            this->destroy_textures();

            return;
        }
        SDL_Delay(PAUSE_DEMO);
    }

    this->destroy_textures();
}

void Demo::handle_events(SDL_Event *pEvents)
{
    while (SDL_PollEvent(pEvents))
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

        default:
            break;
        }
    }
}

void Demo::next_move()
{
    Block_Direction direction = Board::random_direction();

    while (!this->board.move_block(direction))
        direction = Board::random_direction();
}

int Demo::update_screen()
{
    if (CHECK::colour_background_red(*this->pApp) < 0)
        return -1;

    if (this->board.render_textures(*this->pApp) < 0)
        return -1;

    SDL_RenderPresent(this->pApp->pRenderer);

    return 0;
}

void Demo::destroy_textures()
{
    this->board.destroy_textures(this->board.NUMBER_OF_BLOCKS - 1);
}