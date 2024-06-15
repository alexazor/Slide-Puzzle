/**
*@file board.hpp
*@author Alexandre AZOR
*@brief Functions for block movements
*@version 1.0
* @date 2024-06-12

*/

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "main.hpp"
#include "check.hpp"
#include <vector>

#define BOARD_MAX_NUMBER_OF_DIGITS 3

enum Block_Direction
{
    BLOCK_UP = 0,
    BLOCK_LEFT,
    BLOCK_DOWN,
    BLOCK_RIGHT
};

class Board
{
public:
    std::vector<SDL_Texture *> pNumbersTextures;
    std::vector<SDL_Rect> numbersRects;
    SDL_Rect blockRect;
    int blockWidth;
    int blockHeight;
    std::vector<int> map;
    int puzzleSize;
    int iVoid;
    int jVoid;
    int NUMBER_OF_BLOCKS;

    Board() {}
    Board(int sizeOfPuzzle);

    void shuffle();

    int create_textures(Application &application);

    int create_rectangles();

    void set_positions();

    int render_textures(Application &application);

    void destroy_textures(int numberOfBlocksToDestroy);

    void move_line(const int iClick, const int jClick);

    bool move_block(Block_Direction dir);

    static Block_Direction random_direction();

private:
    int from_coordinates_to_index(const int i, const int j);

    void from_index_to_coordinates(const int index, int *pI, int *pJ);

    std::vector<int> init_map();

    bool is_resolved();

    void move_block_set_differences(Block_Direction dir, int *iBlock, int *jBlock, int *xDifBlock, int *yDifBlock, int *iDifVoid, int *jDifVoid);

    void move_block_apply_differences(const int iBlock, const int jBlock, const int xDifBlock, const int yDifBlock, const int iDifVoid, const int jDifVoid);

    bool move_line_is_valid_move(const int iClick, const int jClick);

    Block_Direction move_line_determine_direction(const int iClick, const int jClick);

    Block_Direction opposite_direction(const Block_Direction dir);

    int render_numbers_textures(Application &application, int *pIndexBlockToPlace);

    int render_number_texture(Application &application, int *pIndexBlockToPlace, const int numBlock, const int indexBlock);

    int render_highlight_rectangle(Application &application, const int iBlockToPlace, const int jBlockToPlace);
};
#endif // BOARD_H_INCLUDED