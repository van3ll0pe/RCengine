#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "screen.h"
#include "wall.h"
#include "macros.h"
#include "mathRadian.h"
#include "ray.h"
#include "map.h"

typedef struct Player Player;

//-----PROTOTYPES-------------------
Player player_init(int x, int y);       //the function to init the player
void player_move(Screen *screen, Player *player, Wall *wall);   //the function to move the player and check collision
void player_moveView(Player *player);                           //the function to move the view player on the left of right
void player_display(Screen *screen, Player *player, Map *map);            //the function to display the player
//----------------------------------



struct Player {
    SDL_Rect m_position;  //the position of the player and his size
    Ray *m_ray;             //all rays of the player/the view

    void (*move)(Screen *screen, Player *player, Wall *wall);   //pointer of function player_move
    void (*display)(Screen *screen, Player *player, Map *map);            //pointer of function player_display
    void (*moveView)(Player *player);                           //pointer of function player_moveView
};

#endif


