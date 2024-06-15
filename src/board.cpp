#include "board.hpp"

Board::Board(int sizeOfPuzzle)
{
  this->blockWidth = (DEFAULT_WINDOW_WIDTH - sizeOfPuzzle * SEP_SIZE) / sizeOfPuzzle;
  this->blockHeight = (DEFAULT_WINDOW_HEIGHT - sizeOfPuzzle * SEP_SIZE) / sizeOfPuzzle;
  this->NUMBER_OF_BLOCKS = sizeOfPuzzle * sizeOfPuzzle;
  this->map = init_map();
  this->puzzleSize = sizeOfPuzzle;
  this->iVoid = sizeOfPuzzle - 1;
  this->jVoid = sizeOfPuzzle - 1;

  this->blockRect = SDL_Rect{0, 0, this->blockWidth, this->blockHeight};

  this->pNumbersTextures = std::vector<SDL_Texture *>(this->NUMBER_OF_BLOCKS - 1, nullptr);
  this->numbersRects = std::vector<SDL_Rect>(this->NUMBER_OF_BLOCKS - 1);
}

int Board::from_coordinates_to_index(const int i, const int j)
{
  return i * this->puzzleSize + j;
}

void Board::from_index_to_coordinates(const int index, int *pI, int *pJ)
{
  *pI = index / this->puzzleSize;
  *pJ = index % this->puzzleSize;
}

std::vector<int> Board::init_map()
{
  std::vector<int> map(this->NUMBER_OF_BLOCKS);

  for (int index = 0; index < this->NUMBER_OF_BLOCKS; index++)
    map[index] = index;

  return map;
}

void Board::shuffle()
{
  const int NUMBER_OF_MOVES = this->NUMBER_OF_BLOCKS * this->NUMBER_OF_BLOCKS;
  const int MAX_NUMBER_OF_STEPS = this->NUMBER_OF_BLOCKS * NUMBER_OF_MOVES;
  int numberOfSteps = 0;

  Block_Direction direction;
  Block_Direction prevDirection = Block_Direction::BLOCK_DOWN;

  while (this->is_resolved())
  {
    for (int i = 0; i < NUMBER_OF_MOVES; i++)
    {
      numberOfSteps++;
      direction = this->random_direction();

      if (direction != this->opposite_direction(direction))
      {
        prevDirection = direction;
        if (!this->move_block(direction))
          i--;
      }
      else
        i--;
    }

    if (numberOfSteps == MAX_NUMBER_OF_STEPS)
    {
      std::cout << "-shuffle- Maximum number of steps reached !" << std::endl;
      return;
    }
  }
}

bool Board::is_resolved()
{
  for (int number = 0; number < this->puzzleSize; number++)
    if (number != this->map[number])
      return false;

  return true;
}

bool Board::move_block(Block_Direction dir)
{
  int iBlock = iVoid;
  int jBlock = jVoid;
  int xDifBlock = 0;
  int yDifBlock = 0;
  int iDifVoid = 0;
  int jDifVoid = 0;

  this->move_block_set_differences(dir, &iBlock, &jBlock, &xDifBlock, &yDifBlock, &iDifVoid, &jDifVoid);

  if (iBlock == -1 || iBlock == this->puzzleSize || jBlock == -1 || jBlock == this->puzzleSize)
    return false;

  this->move_block_apply_differences(iBlock, jBlock, xDifBlock, yDifBlock, iDifVoid, jDifVoid);

  return true;
}

void Board::move_block_set_differences(Block_Direction dir, int *iBlock, int *jBlock, int *xDifBlock, int *yDifBlock, int *iDifVoid, int *jDifVoid)
{
  switch (dir)
  {
  case BLOCK_UP:
    (*iBlock)++;
    *yDifBlock = -(this->blockHeight + SEP_SIZE);
    *iDifVoid = 1;
    break;

  case BLOCK_LEFT:
    (*jBlock)++;
    *xDifBlock = -(this->blockWidth + SEP_SIZE);
    *jDifVoid = 1;
    break;

  case BLOCK_DOWN:
    (*iBlock)--;
    *yDifBlock = this->blockHeight + SEP_SIZE;
    *iDifVoid = -1;
    break;

  case BLOCK_RIGHT:
    (*jBlock)--;
    *xDifBlock = blockWidth + SEP_SIZE;
    *jDifVoid = -1;
    break;

  default:
    SDL_Log("-Board::move_block_set_differences- Unvalid direction ----->%d\n", dir);
    std::cout << "-Board::move_block_set_differences- Unvalid direction ----->" << dir << std::endl;
    break;
  }
}

void Board::move_block_apply_differences(const int iBlock, const int jBlock, const int xDifBlock, const int yDifBlock, const int iDifVoid, const int jDifVoid)
{
  int indexBlock = this->from_coordinates_to_index(iBlock, jBlock);
  int indexVoid = this->from_coordinates_to_index(this->iVoid, this->jVoid);
  int numBlock = this->map[indexBlock];

  this->numbersRects[numBlock].x += xDifBlock;
  this->numbersRects[numBlock].y += yDifBlock;

  this->iVoid += iDifVoid;
  this->jVoid += jDifVoid;

  this->map[indexBlock] = this->map[indexVoid];
  this->map[indexVoid] = numBlock;
}

void Board::move_line(int iClick, int jClick)
{
  if (!this->move_line_is_valid_move(iClick, jClick))
    return;

  Block_Direction dir = this->move_line_determine_direction(iClick, jClick);

  while (iClick != this->iVoid || jClick != this->jVoid)
    move_block(dir);
}

bool Board::move_line_is_valid_move(const int iClick, const int jClick)
{
  return (this->iVoid == iClick && this->jVoid != jClick) || (this->iVoid != iClick && this->jVoid == jClick);
}

Block_Direction Board::move_line_determine_direction(const int iClick, const int jClick)
{
  if (this->iVoid == iClick)
  {
    if (this->jVoid < jClick)
      return Block_Direction::BLOCK_LEFT;
    else
      return Block_Direction::BLOCK_RIGHT;
  }

  else // this->jVoid == jClick
  {
    if (this->iVoid < iClick)
      return Block_Direction::BLOCK_UP;
    else
      return Block_Direction::BLOCK_DOWN;
  }
}

int Board::create_textures(Application &application)
{
  SDL_Colour foregroundColour = SDL_Colour{255, 255, 255, 255};
  SDL_Colour backgroundColour = SDL_Colour{0, 0, 0, 255};

  char numbersChar[BOARD_MAX_NUMBER_OF_DIGITS + 1];

  for (int index = 0; index < this->NUMBER_OF_BLOCKS - 1; index++)
  {
    std::sprintf(numbersChar, "%d", index + 1);

    if (CHECK::create_text_texture(this->pNumbersTextures[index], numbersChar, foregroundColour, backgroundColour, application) < 0)
    {
      this->destroy_textures(index);
      return -1;
    }
  }

  return 0;
}

int Board::create_rectangles()
{
  for (int index = 0; index < this->NUMBER_OF_BLOCKS - 1; index++)
  {
    if (CHECK::create_rect(this->pNumbersTextures[index], &this->numbersRects[index]) < 0)
    {
      destroy_textures(NUMBER_OF_BLOCKS);
      return -1;
    }
  }

  return 0;
}

void Board::set_positions()
{
  int index;

  for (int i = 0; i < puzzleSize; i++)
  {
    for (int j = 0; j < puzzleSize; j++)
    {
      index = this->from_coordinates_to_index(i, j);
      this->numbersRects[index].x = j * (this->blockWidth + SEP_SIZE) + (this->blockWidth - this->numbersRects[index].w) / 2;
      this->numbersRects[index].y = i * (this->blockHeight + SEP_SIZE) + (this->blockHeight - this->numbersRects[index].h) / 2;
    }
  }
}

int Board::render_textures(Application &application)
{
  int indexBlockToPlace = this->NUMBER_OF_BLOCKS;
  int indexVoid = from_coordinates_to_index(this->iVoid, this->jVoid);
  int iBlockToPlace, jBlockToPlace;

  if (render_numbers_textures(application, &indexBlockToPlace) < 0)
    return -1;

  this->from_index_to_coordinates(indexBlockToPlace, &iBlockToPlace, &jBlockToPlace);

  if (indexBlockToPlace != indexVoid)
    return render_highlight_rectangle(application, iBlockToPlace, jBlockToPlace);

  return 0;
}

int Board::render_numbers_textures(Application &application, int *pIndexBlockToPlace)
{
  int numBlock, indexBlock;

  for (int i = 0; i < this->puzzleSize; i++)
  {
    this->blockRect.y = i * (this->blockHeight + SEP_SIZE);

    for (int j = 0; j < this->puzzleSize; j++)
    {
      this->blockRect.x = j * (this->blockWidth + SEP_SIZE);

      indexBlock = this->from_coordinates_to_index(i, j);
      numBlock = map[indexBlock];

      if (this->render_number_texture(application, pIndexBlockToPlace, numBlock, indexBlock) < 0)
        return -1;
    }
  }

  return 0;
}

int Board::render_number_texture(Application &application, int *pIndexBlockToPlace, const int numBlock, const int indexBlock)
{
  int numBlockToPlace = this->map[*pIndexBlockToPlace];

  if (numBlock == this->NUMBER_OF_BLOCKS - 1)
    return 0;

  if (CHECK::render_opaque_black_rectangle(&this->blockRect, application) < 0)
    return -1;

  if (CHECK::render_texture(pNumbersTextures[numBlock], &numbersRects[numBlock], application) < 0)
    return -1;

  if (numBlock == indexBlock)
  {
    if (CHECK::render_transparent_blue_rectangle(&this->blockRect, application) < 0)
      return -1;
  }

  else if (numBlock < numBlockToPlace)
    *pIndexBlockToPlace = indexBlock;

  return 0;
}

int Board::render_highlight_rectangle(Application &application, const int iBlockToPlace, const int jBlockToPlace)
{
  this->blockRect.x = jBlockToPlace * (this->blockWidth + SEP_SIZE);
  this->blockRect.y = iBlockToPlace * (this->blockHeight + SEP_SIZE);

  if (CHECK::render_transparent_green_rectangle(&this->blockRect, application) < 0)
    return -1;

  return 0;
}

void Board::destroy_textures(int numberOfBlocksToDestroy)
{
  for (int number = 0; number < numberOfBlocksToDestroy; number++)
    SDL_DestroyTexture(this->pNumbersTextures[number]);
}

Block_Direction Board::random_direction()
{
  int randInt = rand() % 4;

  switch (randInt)
  {
  case 0:
    return Block_Direction::BLOCK_UP;
    break;

  case 1:
    return Block_Direction::BLOCK_LEFT;
    break;

  case 2:
    return Block_Direction::BLOCK_DOWN;
    break;

  case 3:
    return Block_Direction::BLOCK_RIGHT;
    break;

  default:
    std::cout << "-random_direction- Unvalid random value: " << randInt << std::endl;
    return Block_Direction::BLOCK_UP;
    break;
  }
}

Block_Direction Board::opposite_direction(const Block_Direction dir)
{
  switch (dir)
  {
  case Block_Direction::BLOCK_UP:
    return Block_Direction::BLOCK_DOWN;
    break;

  case Block_Direction::BLOCK_LEFT:
    return Block_Direction::BLOCK_RIGHT;
    break;

  case Block_Direction::BLOCK_DOWN:
    return Block_Direction::BLOCK_UP;
    break;

  case Block_Direction::BLOCK_RIGHT:
    return Block_Direction::BLOCK_LEFT;
    break;

  default:
    SDL_Log("[opposite_direction]\nUnvalid direction ----->%d\n", dir);
    return Block_Direction::BLOCK_DOWN;
    break;
  }
}