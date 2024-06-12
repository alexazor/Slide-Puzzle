#include "board.hpp"

bool resolved(int map[], int puzzleSize)
{
  for (int index = 0; index < puzzleSize; index++)
    if (index != map[index])
      return false;

  return true;
}

void resize_window_board(SDL_Window *pWindow, int puzzleSize, int &block_width, int &block_height, int &window_width, int &window_height)
{
  block_width = (DEFAULT_WINDOW_WIDTH - puzzleSize * SEP_SIZE) / puzzleSize;
  block_height = (DEFAULT_WINDOW_HEIGHT - puzzleSize * SEP_SIZE) / puzzleSize;

  window_width = puzzleSize * (block_width + SEP_SIZE);
  window_height = puzzleSize * (block_height + SEP_SIZE);

  SDL_SetWindowSize(pWindow, window_width, window_height);
}

void move_block(int map[], int puzzleSize, int &iVoid, int &jVoid, int dir, SDL_Rect numbersRect[], int block_width, int block_height)
{
  int indexBlock, intermediate, numBlock;
  int indexVoid = iVoid * puzzleSize + jVoid;
  int iBlock = iVoid;
  int jBlock = jVoid;
  int xDifBlock = 0;
  int yDifBlock = 0;
  int iDifVoid = 0;
  int jDifVoid = 0;
  const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;

  switch (dir)
  {
  case BLOCK_UP:
    iBlock++;
    yDifBlock = -(block_height + SEP_SIZE);
    iDifVoid = 1;
    break;

  case BLOCK_LEFT:
    jBlock++;
    xDifBlock = -(block_width + SEP_SIZE);
    jDifVoid = 1;
    break;

  case BLOCK_DOWN:
    iBlock--;
    yDifBlock = block_height + SEP_SIZE;
    iDifVoid = -1;
    break;

  case BLOCK_RIGHT:
    jBlock--;
    xDifBlock = block_width + SEP_SIZE;
    jDifVoid = -1;
    break;

  default:
    SDL_Log("----->%d\n", dir);
    return;
    break;
  }

  if (0 <= iBlock && iBlock < puzzleSize && 0 <= jBlock && jBlock < puzzleSize)
  {
    indexBlock = iBlock * puzzleSize + jBlock;
    numBlock = map[indexBlock];

    numbersRect[numBlock].x += xDifBlock;
    numbersRect[numBlock].y += yDifBlock;

    iVoid += iDifVoid;
    jVoid += jDifVoid;

    intermediate = map[indexBlock];
    map[indexBlock] = map[indexVoid];
    map[indexVoid] = intermediate;
  }
}

void move_line(int map[], int puzzleSize, int iClick, int jClick, int &iVoid, int &jVoid, SDL_Rect numbersRect[], int block_width, int block_height)
{
  int dir = -1;
  bool validMove = false;

  if (iVoid == iClick)
  {
    if (jVoid < jClick)
      dir = BLOCK_LEFT;
    else
      dir = BLOCK_RIGHT;

    validMove = true;
  }
  if (jVoid == jClick)
  {
    if (iVoid < iClick)
      dir = BLOCK_UP;
    else
      dir = BLOCK_DOWN;

    validMove = true;
  }

  while (validMove && (iVoid != iClick || jVoid != jClick))
    move_block(map, puzzleSize, iVoid, jVoid, dir, numbersRect, block_width, block_height);
}

void shuffle_board(int map[], int puzzleSize, SDL_Rect numbersRect[], int block_width, int block_height)
{
  const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;
  int numberOfMoves = NUMBER_OF_BLOCS * NUMBER_OF_BLOCS;
  int iVoid = puzzleSize - 1;
  int jVoid = puzzleSize - 1;
  int index, direction;

  int prevDirection = BLOCK_DOWN;

  for (index = 0; index < NUMBER_OF_BLOCS; index++)
    map[index] = index;

  while (resolved(map, puzzleSize))
  {
    for (int i = 0; i < numberOfMoves; i++)
    {
      direction = rand() % 4;

      if ((direction + 2) % 4 != prevDirection)
      {
        prevDirection = direction;
        move_block(map, puzzleSize, iVoid, jVoid, direction, numbersRect, block_width, block_height);
      }
      else
        i--;
    }
  }
}

void find_void(int map[], int puzzleSize, int &iVoid, int &jVoid)
{
  for (int i = 0; i < puzzleSize; i++)
    for (int j = 0; j < puzzleSize; j++)
      if (map[i * puzzleSize + j] == puzzleSize * puzzleSize - 1)
      {
        iVoid = i;
        jVoid = j;
      }
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

int create_rectangles_board(SDL_Texture *pNumbersTextures[], SDL_Rect numbersRects[], int puzzleSize, int block_width, int block_height)
{
  int i, j, index;
  const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;

  char numbersChar[10];

  for (int i = 0; i < puzzleSize; i++)
  {
    for (int j = 0; j < puzzleSize; j++)
    {
      index = i * puzzleSize + j;

      if (SDL_QueryTexture(pNumbersTextures[index], nullptr, nullptr, &numbersRects[index].w, &numbersRects[index].h) < 0)
        RETURN_ERR

      numbersRects[index].x = j * (block_width + SEP_SIZE) + (block_width - numbersRects[index].w) / 2;
      numbersRects[index].y = i * (block_height + SEP_SIZE) + (block_height - numbersRects[index].h) / 2;
    }
  }
  return 0;
}

int update_screen_board(SDL_Renderer *pRenderer,
                        SDL_Texture *pNumbersTextures[],
                        SDL_Rect numbersRects[],
                        SDL_Rect *blockRect,
                        int puzzleSize,
                        int map[],
                        int block_width,
                        int block_height)
{
  int i, j, numBlock, blockIndex;
  bool knownNextBlockToPlace = false;

  const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;

  int numBlockToPlace = NUMBER_OF_BLOCS - 1;
  int iBlockToPlace = puzzleSize - 1;
  int jBlockToPlace = puzzleSize - 1;

  if (SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255) < 0 || SDL_RenderClear(pRenderer) < 0)
    RETURN_ERR

  for (i = 0; i < puzzleSize; i++)
  {

    blockRect->y = i * (block_height + SEP_SIZE);

    for (j = 0; j < puzzleSize; j++)
    {
      blockRect->x = j * (block_width + SEP_SIZE);

      blockIndex = i * puzzleSize + j;
      numBlock = map[blockIndex];

      if (numBlock < NUMBER_OF_BLOCS - 1)
      {
        if (SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255) < 0 || SDL_RenderFillRect(pRenderer, blockRect) < 0)
          RETURN_ERR

        if (SDL_RenderCopy(pRenderer, pNumbersTextures[numBlock], nullptr, &numbersRects[numBlock]) < 0)
          RETURN_ERR

        if (numBlock == blockIndex)
        {
          if (SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 127) < 0 || SDL_RenderFillRect(pRenderer, blockRect) < 0)
            RETURN_ERR
        }
        else
        {
          if (numBlock < numBlockToPlace)
          {
            numBlockToPlace = numBlock;
            iBlockToPlace = i;
            jBlockToPlace = j;
          }
        }
      }
    }
  }

  blockRect->x = jBlockToPlace * (block_width + SEP_SIZE);
  blockRect->y = iBlockToPlace * (block_height + SEP_SIZE);

  if (SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 127) < 0 || SDL_RenderFillRect(pRenderer, blockRect) < 0)
    RETURN_ERR

  SDL_RenderPresent(pRenderer);
  return 0;
}

void destroy_textures_board(SDL_Texture *pNumberTextures[], int puzzleSize)
{
  const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;

  for (int number = 0; number < NUMBER_OF_BLOCS; number++)
    SDL_DestroyTexture(pNumberTextures[number]);
}