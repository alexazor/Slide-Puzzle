#include "title.hpp"

void Title_Screen::main(Application *pApp)
{
    Title_Screen titleScreen(pApp);

    titleScreen.set_window_size();

    if (titleScreen.create_textures() < 0)
    {
        pApp->state = Program_State::STATE_ERROR;
        return;
    }

    if (titleScreen.create_rectangles() < 0)
    {
        titleScreen.destroy_textures();
        pApp->state = Program_State::STATE_ERROR;
        return;
    }

    titleScreen.resize_image();
    titleScreen.set_positions();

    SDL_SetRenderDrawBlendMode(titleScreen.pApp->pRenderer, SDL_BLENDMODE_BLEND);

    if (titleScreen.update_screen(Program_State::STATE_GAME, -1) < 0)
    {
        pApp->state = Program_State::STATE_ERROR;
        titleScreen.destroy_textures();
        return;
    }

    titleScreen.event_loop();
}

void Title_Screen::set_window_size()
{
    SDL_SetWindowSize(this->pApp->pWindow, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
}

int Title_Screen::create_textures()
{
    SDL_Colour foregroundColour = SDL_Colour{255, 255, 255, 255};
    SDL_Colour backgroundColour = SDL_Colour{0, 0, 0, 255};

    if (this->create_text_textures(foregroundColour, backgroundColour) < 0)
        return -1;

    if (this->create_puzzle_sizes_textures(foregroundColour, backgroundColour) < 0)
        return -1;

    if (this->create_image_texture() < 0)
        return -1;

    return 0;
}

int Title_Screen::create_text_textures(SDL_Colour foregroundColour, SDL_Colour backgroundColour)
{
    char textTitle[] = {"======Slide Puzzle======"};
    char textInstruction[] = {"Select the mode and choose the size"};
    char textMode[] = {"Click to change:"};
    char textGame[] = {"Game"};
    char textDemo[] = {"Demo"};
    //    char textPressP[] = {"P: Highlight the first misplaced block"};

    char *textsArray[] = {textTitle,
                          textInstruction,
                          textMode,
                          textGame,
                          textDemo}; /*,
                           textPressP};*/

    int i, j;

    for (i = 0; i < TITLE_TEXT_NBR_OF_ELEMENTS; i++)
    {
        if (CHECK::create_text_texture(this->pTextTextures[i], textsArray[i], foregroundColour, backgroundColour, *this->pApp) < 0)
        {
            this->destroy_text_textures(i);
            return -1;
        }
    }

    return 0;
}

int Title_Screen::create_puzzle_sizes_textures(SDL_Colour foregroundColour, SDL_Colour backgroundColour)
{
    int puzzleSizeInt, i, j;
    char puzzleSizeCharArray[TITLE_MAX_NUMBER_OF_DIGITS + 1];

    for (i = 0; i < PUZZLE_SIZES; i++)
    {
        puzzleSizeInt = i + PUZZLE_SIZE_MIN;
        std::sprintf(puzzleSizeCharArray, "%d", i + PUZZLE_SIZE_MIN);

        if (CHECK::create_text_texture(this->pPuzzleSizesTextures[i], puzzleSizeCharArray, foregroundColour, backgroundColour, *this->pApp) < 0)
        {
            this->destroy_text_textures(TITLE_TEXT_NBR_OF_ELEMENTS);

            this->destroy_puzzle_sizes_textures(i);

            return -1;
        }
    }

    return 0;
}

int Title_Screen::create_image_texture()
{
    char imgPath[] = {IMG_PATH};
    int j;

    if (CHECK::create_img_texture(this->pImgSDLTexture, imgPath, *this->pApp) < 0)
    {
        this->destroy_text_textures(TITLE_TEXT_NBR_OF_ELEMENTS);

        this->destroy_puzzle_sizes_textures(PUZZLE_SIZES);

        return -1;
    }

    return 0;
}

int Title_Screen::create_rectangles()
{
    if (create_text_rectangles() < 0)
        return -1;

    if (create_puzzle_sizes_rectangles() < 0)
        return -1;

    if (create_image_rectangle() < 0)
        return -1;

    return 0;
}

int Title_Screen::create_text_rectangles()
{
    for (int i = 0; i < TITLE_TEXT_NBR_OF_ELEMENTS; i++)
        if (CHECK::create_rect(this->pTextTextures[i], &this->textRects[i]) < 0)
            return -1;

    return 0;
}

int Title_Screen::create_puzzle_sizes_rectangles()
{
    for (int i = 0; i < PUZZLE_SIZES; i++)
        if (CHECK::create_rect(pPuzzleSizesTextures[i], &this->puzzleSizesRects[i]) < 0)
            return -1;

    return 0;
}

int Title_Screen::create_image_rectangle()
{
    if (CHECK::create_rect(pImgSDLTexture, &this->imgSDLRect) < 0)
        return -1;

    return 0;
}

void Title_Screen::resize_image()
{
    this->imgSDLRect.w = (3 * this->imgSDLRect.w) / 4;
    this->imgSDLRect.h = (3 * this->imgSDLRect.h) / 4;
}

void Title_Screen::set_positions()
{
    this->set_text_positions();
    this->set_puzzle_sizes_positions();
    this->set_image_positions();
}

void Title_Screen::set_text_positions()
{
    int space_width_modes = this->textRects[TITLE_GAME].w / 2;
    int textHeight = this->textRects[TITLE_TITLE].h;

    this->textRects[TITLE_TITLE].x = (DEFAULT_WINDOW_WIDTH - this->textRects[TITLE_TITLE].w) / 2;
    this->textRects[TITLE_TITLE].y = 0;

    this->textRects[TITLE_INSTRUCTION].x = (DEFAULT_WINDOW_WIDTH - this->textRects[TITLE_INSTRUCTION].w) / 2;
    this->textRects[TITLE_INSTRUCTION].y = 1.5 * textHeight;

    this->textRects[TITLE_MODE].x = (DEFAULT_WINDOW_WIDTH - this->textRects[TITLE_MODE].w - this->textRects[TITLE_GAME].w - this->textRects[TITLE_DEMO].w) / 2 - space_width_modes;
    this->textRects[TITLE_MODE].y = 3 * textHeight;

    this->textRects[TITLE_GAME].x = (DEFAULT_WINDOW_WIDTH + this->textRects[TITLE_MODE].w - this->textRects[TITLE_GAME].w - this->textRects[TITLE_DEMO].w) / 2;
    this->textRects[TITLE_GAME].y = 3 * textHeight;

    this->textRects[TITLE_DEMO].x = (DEFAULT_WINDOW_WIDTH + this->textRects[TITLE_MODE].w + this->textRects[TITLE_GAME].w - this->textRects[TITLE_DEMO].w) / 2 + space_width_modes;
    this->textRects[TITLE_DEMO].y = 3 * textHeight;

    /*this->textRects[TITLE_PRESS_P].x = (DEFAULT_WINDOW_WIDTH - this->textRects[TITLE_PRESS_P].w) / 2;
    this->textRects[TITLE_PRESS_P].y = DEFAULT_WINDOW_HEIGHT - 2 * textHeight;*/
}

void Title_Screen::set_puzzle_sizes_positions()
{
    int space_width_puzzle_sizes = DEFAULT_WINDOW_WIDTH / (1 + PUZZLE_SIZES) - this->puzzleSizesRects[0].w;

    for (int i = 0; i < PUZZLE_SIZES; i++)
    {
        this->puzzleSizesRects[i].x = space_width_puzzle_sizes + i * (this->puzzleSizesRects[0].w + space_width_puzzle_sizes);
        this->puzzleSizesRects[i].y = (DEFAULT_WINDOW_HEIGHT + imgSDLRect.h + this->puzzleSizesRects[i].h) / 2;
    }
}

void Title_Screen::set_image_positions()
{
    this->imgSDLRect.x = (DEFAULT_WINDOW_WIDTH - this->imgSDLRect.w) / 2;
    this->imgSDLRect.y = (DEFAULT_WINDOW_HEIGHT - this->imgSDLRect.h) / 2;
}

void Title_Screen::event_loop()
{
    int selectedSizeIndex = -1;

    SDL_Event events;
    Program_State futureState = Program_State::STATE_GAME;

    while (this->pApp->state == Program_State::STATE_TITLE)
    {
        this->handle_events(&events, &selectedSizeIndex, &futureState);

        if (this->update_screen(futureState, selectedSizeIndex) < 0)
        {
            this->pApp->state = Program_State::STATE_ERROR;
            this->destroy_textures();
            return;
        }

        SDL_Delay(PAUSE);
    }

    this->destroy_textures();
}

void Title_Screen::handle_events(SDL_Event *pEvents, int *pSelectedSizeIndex, Program_State *pFutureState)
{
    while (SDL_WaitEvent(pEvents))
    {
        switch (pEvents->type)
        {
        case SDL_QUIT:
            this->pApp->state = Program_State::STATE_QUIT;
            return;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (pEvents->button.button == SDL_BUTTON_LEFT)
                this->event_left_click(pEvents->button.x, pEvents->button.y, pFutureState);
            return;
            break;

        case SDL_MOUSEMOTION:
            this->event_mouse_motion(pEvents->motion.x, pEvents->motion.y, pSelectedSizeIndex);
            return;
            break;

        default:
            break;
        }
    }
}

void Title_Screen::event_left_click(Sint32 mouseX, Sint32 mouseY, Program_State *pFutureState)
{
    if (MOUSE::is_over_rectangle(this->textRects[TITLE_DEMO], mouseX, mouseY))
    {
        *pFutureState = Program_State::STATE_DEMO;
        return;
    }

    if (MOUSE::is_over_rectangle(this->textRects[TITLE_GAME], mouseX, mouseY))
    {
        *pFutureState = Program_State::STATE_GAME;
        return;
    }

    for (int sizeIndex = 0; sizeIndex < PUZZLE_SIZES; sizeIndex++)
        if (MOUSE::is_over_rectangle(this->puzzleSizesRects[sizeIndex], mouseX, mouseY))
        {
            this->pApp->puzzleSize = sizeIndex + PUZZLE_SIZE_MIN;
            this->pApp->state = *pFutureState;
            return;
        }
}

void Title_Screen::event_mouse_motion(Sint32 mouseX, Sint32 mouseY, int *pSelectedSizeIndex)
{
    *pSelectedSizeIndex = NO_SELECTED_SIZE;

    for (int sizeIndex = 0; sizeIndex < PUZZLE_SIZES; sizeIndex++)
        if (MOUSE::is_over_rectangle(puzzleSizesRects[sizeIndex], mouseX, mouseY))
        {
            *pSelectedSizeIndex = sizeIndex;
            return;
        }
}

int Title_Screen::update_screen(const Program_State futureState, int selectedSizeIndex)
{

    if (CHECK::colour_background_black(*this->pApp) < 0)
        return -1;

    if (this->render_text_textures() < 0)
        return -1;

    if (this->render_puzzle_sizes_textures() < 0)
        return -1;

    if (this->render_image_texture() < 0)
        return -1;

    if (this->render_selected_size_rectangle(selectedSizeIndex) < 0)
        return -1;

    if (this->render_future_state_rectangle(futureState) < 0)
        return -1;

    SDL_RenderPresent(this->pApp->pRenderer);

    return 0;
}

int Title_Screen::render_text_textures()
{
    for (int i = 0; i < TITLE_TEXT_NBR_OF_ELEMENTS; i++)
        if (CHECK::render_texture(this->pTextTextures[i], &this->textRects[i], *this->pApp) < 0)
            return -1;

    return 0;
}

int Title_Screen::render_puzzle_sizes_textures()
{
    for (int i = 0; i < PUZZLE_SIZES; i++)
        if (CHECK::render_texture(this->pPuzzleSizesTextures[i], &this->puzzleSizesRects[i], *this->pApp) < 0)
            return -1;

    return 0;
}

int Title_Screen::render_image_texture()
{
    if (CHECK::render_texture(this->pImgSDLTexture, &this->imgSDLRect, *this->pApp) < 0)
        return -1;

    return 0;
}

int Title_Screen::render_selected_size_rectangle(const int selectedSizeIndex)
{
    if (selectedSizeIndex == NO_SELECTED_SIZE)
        return 0;

    if (CHECK::render_transparent_green_rectangle(&this->puzzleSizesRects[selectedSizeIndex], *this->pApp) < 0)
        return -1;
    return 0;
}

int Title_Screen::render_future_state_rectangle(const int futureState)
{
    Title_Text textToHighlight;

    switch (futureState)
    {
    case Program_State::STATE_GAME:
        textToHighlight = Title_Text::TITLE_GAME;
        break;

    case Program_State::STATE_DEMO:
        textToHighlight = Title_Text::TITLE_DEMO;
        break;

    default:
        std::cout << "-futureState- variable does not have an acceptable value: " << futureState << std::endl;
        return -1;
        break;
    }

    if (CHECK::render_transparent_green_rectangle(&this->textRects[textToHighlight], *this->pApp) < 0)
        return -1;

    return 0;
}

void Title_Screen::destroy_textures()
{
    SDL_DestroyTexture(this->pImgSDLTexture);

    destroy_text_textures(TITLE_TEXT_NBR_OF_ELEMENTS);

    destroy_puzzle_sizes_textures(PUZZLE_SIZES);
}

void Title_Screen::destroy_text_textures(int maxIndex)
{
    for (int j = 0; j < maxIndex; j++)
        SDL_DestroyTexture(this->pTextTextures[j]);
}

void Title_Screen::destroy_puzzle_sizes_textures(int maxIndex)
{
    for (int j = 0; j < maxIndex; j++)
        SDL_DestroyTexture(this->pPuzzleSizesTextures[j]);
};
