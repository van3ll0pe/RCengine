#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include "macros.h"
#include "screen.h"
#include "wall.h"
#include "player.h"

typedef struct Map Map;

//---------- PROTOTYPES -----------------------------
Map map_init(Screen *screen, Wall *wall);       //function to init the struct map
void map_display(Screen *screen, Map *map, Player *player);   //function to display the map on the screen
void map_clear(Screen *screen, Map *map);     //function to clear the texture
//---------------------------------------------------


struct Map {
    SDL_Texture *m_textureMap;   //the texture where all is draw (player, walls, rays)
    int         m_width;        //the width of the texture ''the width of the all the map''
    int         m_height;       //the height of the texture ''the height of the all the map''

    void (*display)(Screen *screen, Map *map, Player *player);    //pointer of function map_display
    void (*clear)(Screen *screen, Map *map);
};

#endif