/**
 * @file constants.h
 * @author Alexandre AZOR
 * @brief Contants used throughout the whole program
 * @version 0.1
 * @date 2022-07-15
 *
 *
 */

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define WINDOW_WIDTH 629
#define WINDOW_HEIGHT 629
#define MINIMUM_SIZE 3
#define MAXIMUM_SIZE 10
#define FPS 20
#define PAUSE 1000 / FPS

enum Mode
{
    MODE_TITLE,
    MODE_GAME,
    MODE_QUIT
};

#endif // CONSTANTS_H_INCLUDED