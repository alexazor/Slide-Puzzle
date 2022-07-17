#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <iostream>
#include "initialisation.h"

void bidon(int *&pA)
{
    *pA = 7;
}

int main(int argc, char *argv[])
{
    std::cout << "Hello world !" << std::endl;

    int a = 1;
    int *pA = &a;

    bidon(pA);

    std::cout << a << std::endl;

    return EXIT_SUCCESS;
}