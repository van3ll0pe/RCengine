#ifndef WALL_H
#define WALL_H

#include <SDL2/SDL.h>
#include "screen.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Map Map;

typedef struct Wall Wall;
typedef struct Pos Pos;

//----PROTOTYPES-------
Wall wall_init(int x1, int y1, int x2, int y2);         //function to init a Wall variable
void wall_display(Screen *screen, Wall *wall, Map *map);           //function to display the wall on the screen
//---------------------

//the position of the wall
struct Pos {
    int x1;
    int y1;

    int x2;
    int y2;
};

//the main structure
struct Wall {
    Pos m_position;

    void (*display)(Screen *screen, Wall *wall, Map *map); //pointer of function wall_display
};

#endif