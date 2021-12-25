#include "../include/renderer.h"

Rendering rendering_init(Screen *screen, Player *player) {
    int besideRest = (screen->m_widthWindow % 66) / 2; //le reste sur les côtés de l'écran
    Rendering rendering;

    rendering.m_nbrRenderRay = 66; //the number of rectangle because there are 66 rays in the view of player



    rendering.m_renderRay = (SDL_Rect *)malloc(sizeof(SDL_Rect) * rendering.m_nbrRenderRay);

    for (int i = 0; i < rendering.m_nbrRenderRay; i++) {
        rendering.m_renderRay[i].y = 0;
        rendering.m_renderRay[i].x = (i * (screen->m_widthWindow / rendering.m_nbrRenderRay)) + besideRest;
        rendering.m_renderRay[i].h = screen->m_heightWindow;
        rendering.m_renderRay[i].w = screen->m_widthWindow / rendering.m_nbrRenderRay;
    }

    rendering.display = &rendering_display;
    rendering.adapt = &rendering_adapt;

    return (rendering);
}

void rendering_display(Screen *screen, Rendering *rendering, Player *player) {
    float distance = 0;       //the distance between player and collision line with ray to set the color of the rectangle
    int color = 0;              //the color for each wall depends of the ray distance

    for (int i = 0; i < rendering->m_nbrRenderRay; i++) { 
        distance = sqrt( pow((player->m_ray[i].m_position.x - player->m_ray[i].m_endPosition.x),2) + pow((player->m_ray[i].m_position.y - player->m_ray[i].m_endPosition.y), 2) );
        color = 255 - distance;

        if (color < 0) {
            color = 0;
        }
        SDL_SetRenderDrawColor(screen->m_render, color, color, color, 255);
        SDL_RenderFillRect(screen->m_render, &rendering->m_renderRay[i]);
    }
}

void rendering_adapt(Screen *screen, Rendering *rendering, Player *player) {
   int besideRest = (screen->m_widthWindow % 66) / 2; //le reste sur les côtés de l'écran
   int besideRest2 = 0;                                //le reste sur les côtés haut/bas de l'écran
   float distance = 0;       //the distance between player and collision line with ray to set the color of the rectangle
   float distanceDelta =  sqrt( pow((player->m_ray[32].m_position.x - player->m_ray[32].m_endPosition.x),2) + pow((player->m_ray[32].m_position.y - player->m_ray[32].m_endPosition.y), 2) );



   for (int i = 0; i < rendering->m_nbrRenderRay; i++) {
       distance = sqrt( pow((player->m_ray[i].m_position.x - player->m_ray[i].m_endPosition.x),2) + pow((player->m_ray[i].m_position.y - player->m_ray[i].m_endPosition.y), 2) );
       
       if ((screen->m_heightWindow - distance) >= 0) {
            rendering->m_renderRay[i].h = (screen->m_heightWindow - distance);
        } else {
            rendering->m_renderRay[i].h = 0;
        }
        besideRest2 = (screen->m_heightWindow - rendering->m_renderRay[i].h) / 2;
        rendering->m_renderRay[i].y = besideRest2;

       rendering->m_renderRay[i].x = (i * (screen->m_widthWindow / rendering->m_nbrRenderRay)) + besideRest;
       rendering->m_renderRay[i].w = screen->m_widthWindow / rendering->m_nbrRenderRay;
       
   } 

}
