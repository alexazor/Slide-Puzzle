#include "mouse.hpp"

namespace MOUSE
{
    bool is_in_segement(int leftBoundary, int length, int x)
    {
        return leftBoundary <= x && x <= leftBoundary + length;
    }

    bool is_over_rectangle(SDL_Rect rect, Sint32 mouseX, Sint32 mouseY)
    {
        return is_in_segement(rect.x, rect.w, mouseX) && is_in_segement(rect.y, rect.h, mouseY);
    }

    void get_block_coordinates(Sint32 mouseX, Sint32 mouseY, int block_height, int block_width, int &i, int &j)
    {
        j = mouseX / (block_width + SEP_SIZE);
        i = mouseY / (block_height + SEP_SIZE);
    }

} // namespace MOUSE