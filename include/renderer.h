#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "screen.h"
#include "player.h"

typedef struct Rendering Rendering;

//--------- PROTOTYPES -------------------------
Rendering rendering_init(Screen *screen, Player *player); //function to init 
void rendering_display(Screen *screen, Rendering *rendering, Player *player); //function to display the rendering on the texture
void rendering_adapt(Screen *screen, Rendering *rendering, Player *player);     //function to adapt all rectangle rendering in while size of screen
//----------------------------------------------


struct Rendering{
    SDL_Rect  *m_renderRay;         //the renderRay is a rect in fonction to the Ray
    int        m_nbrRenderRay;      //the number of renderRay - is the same as the number of rays
    SDL_Texture *m_renderTexture;   //the texture to draw the Rectangle of renderRay

    void (*display)(Screen *screen, Rendering *rendering, Player *player);  //pointer of function rendering_display
    void (*adapt)(Screen *screen, Rendering *rendering, Player *player);    //pointer of function rendering_adapt
};

#endif