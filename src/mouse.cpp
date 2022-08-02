#include "mouse.h"

bool is_in_segement(int a, int l, int x)
{
    if (a <= x && x <= a + l)
        return true;
    else
        return false;
}

bool mouse_over_rectangle(SDL_Rect rect, Sint32 mouseX, Sint32 mouseY)
{
    return is_in_segement(rect.x, rect.w, mouseX) && is_in_segement(rect.y, rect.h, mouseY);
}

void get_block_position(Sint32 mouseX, Sint32 mouseY, int block_height, int block_width, int &i, int &j)
{
    j = mouseX / (block_width + SEP_SIZE);
    i = mouseY / (block_height + SEP_SIZE);
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