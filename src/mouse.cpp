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
