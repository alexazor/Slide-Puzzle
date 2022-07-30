#include "board.h"

void resize_window_board(SDL_Window *pWindow, int puzzleSize, int &bloc_width, int &bloc_height, int &window_width, int &window_height)
{
  bloc_width = (DEFAULT_WINDOW_WIDTH - puzzleSize * SEP_SIZE) / puzzleSize;
  bloc_height = (DEFAULT_WINDOW_HEIGHT - puzzleSize * SEP_SIZE) / puzzleSize;

  window_width = puzzleSize * (bloc_width + SEP_SIZE);
  window_height = puzzleSize * (bloc_height + SEP_SIZE);

  SDL_SetWindowSize(pWindow, window_width, window_height);
}

void shuffle_board(int map[], int puzzleSize)
{
  const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;
  int numberOfMoves = NUMBER_OF_BLOCS * NUMBER_OF_BLOCS;

  for (int index = 0; index < NUMBER_OF_BLOCS; index++)
    map[index] = index;
}

int create_textures_board(SDL_Renderer *&pRenderer,
                          TTF_Font *pFont,
                          SDL_Texture *pNumbersTextures[],
                          int puzzleSize)
{
  SDL_Colour fgColour = SDL_Colour{255, 255, 255, 255};
  SDL_Colour bgColour = SDL_Colour{0, 0, 0, 255};

  const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;
  int j;

  char numbersChar[10];

  for (int number = 0; number < NUMBER_OF_BLOCS; number++)
  {
    std::sprintf(numbersChar, "%d", number + 1);

    if (create_text_texture(pNumbersTextures[number], pFont, numbersChar, fgColour, bgColour, pRenderer) < 0)
    {

      for (j = 0; j < number; j++)
        SDL_DestroyTexture(pNumbersTextures[j]);

      error_message();
      return -1;
    }
  }

  return 0;
}

int create_rectangles_board(SDL_Texture *pNumbersTextures[], SDL_Rect numbersRects[], int puzzleSize, int bloc_width, int bloc_height)
{
  int i, j, index;

  char numbersChar[10];

  for (int i = 0; i < puzzleSize; i++)
  {
    for (int j = 0; j < puzzleSize; j++)
    {
      index = i * puzzleSize + j;

      if (SDL_QueryTexture(pNumbersTextures[index], nullptr, nullptr, &numbersRects[index].w, &numbersRects[index].h) < 0)
        RETURN_ERR

      numbersRects[index].x = j * (bloc_width + SEP_SIZE) + (bloc_width - numbersRects[index].w) / 2;
      numbersRects[index].y = i * (bloc_height + SEP_SIZE) + (bloc_height - numbersRects[index].h) / 2;
    }
  }
  return 0;
}

int update_screen_board(SDL_Renderer *pRenderer,
                        SDL_Texture *pNumbersTextures[],
                        SDL_Rect numbersRects[],
                        SDL_Rect *blocRect,
                        int blocToPlace,
                        int puzzleSize,
                        int map[],
                        int bloc_width,
                        int bloc_height)
{
  int i, j, blocIndex, mapIndex;
  const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;

  if (SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255) < 0 || SDL_RenderClear(pRenderer) < 0)
    RETURN_ERR

  for (i = 0; i < puzzleSize; i++)
  {
    for (j = 0; j < puzzleSize; j++)
    {
      blocRect->x = j * (bloc_width + SEP_SIZE);
      blocRect->y = i * (bloc_height + SEP_SIZE);

      mapIndex = i * puzzleSize + j;
      blocIndex = map[mapIndex];

      if (blocIndex < NUMBER_OF_BLOCS - 1)
      {
        if (SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255) < 0 || SDL_RenderFillRect(pRenderer, blocRect) < 0)
          RETURN_ERR

        if (SDL_RenderCopy(pRenderer, pNumbersTextures[blocIndex], nullptr, &numbersRects[blocIndex]) < 0)
          RETURN_ERR

        if (blocIndex == blocToPlace)
          if (SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 127) < 0 || SDL_RenderFillRect(pRenderer, &blocRect[blocIndex]) < 0)
            RETURN_ERR
      }
    }
  }

  SDL_RenderPresent(pRenderer);
  return 0;
}

void destroy_textures_board(SDL_Texture *pNumberTextures[], int puzzleSize)
{
  const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;

  for (int number = 0; number < NUMBER_OF_BLOCS; number++)
    SDL_DestroyTexture(pNumberTextures[number]);
}