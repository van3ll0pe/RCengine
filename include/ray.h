#ifndef RAY_H
#define RAY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "screen.h"
#include "macros.h"

typedef struct Wall wall;
typedef struct Player Player;

typedef struct Ray Ray;     //the main struct
typedef struct PosRay PosRay;     //the struct with only two int for the position and direction
typedef struct Direction Direction;

//----PROTOTYPES---------------------------------------
Ray ray_init(Player *player, float angle);     //function to init the Ray structure
void ray_display(Screen *screen, Ray *ray, Map *map);     //function to display the ray
void ray_setPosition(Player *player, Ray *ray); //function to set the starting position of the ray when the player move
void ray_setEndPosition(Wall *wall, Ray *ray);  //function to calculate the end position of the ray when there is a wall
//-----------------------------------------------------

struct PosRay {
    int x;
    int y;
};

struct Direction {
    float x;
    float y;
};


struct Ray {
    PosRay     m_position;         //the starting position of the ray
    Direction     m_direction;        //the direction where it looks
    PosRay     m_endPosition;      //the end point (to draw the line until the wall)
    float      m_angle;            //the angle of the ray from the player position

    void    (*display)(Screen *screen, Ray *ray, Map *map);       //pointer of function ray_display
    void    (*setPosition)(Player *player, Ray *ray);   //pointer of function ray_setPosition
    void    (*setEndPosition)(Wall *wall, Ray *ray);  //pointer of function ray_setEndPosition
};

#endif