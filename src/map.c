#include "../include/map.h"

Map map_init(Screen *screen, Wall *wall) {
    
    Map map;
    map.m_textureMap = NULL;
    map.m_height = 0;
    map.m_width = 0;
    
    for (int i = 0; i < nbrWall; i++) {
        if (map.m_width < wall[i].m_position.x1) {
            map.m_width = wall[i].m_position.x1;
        }

        if (map.m_width < wall[i].m_position.x2) {
            map.m_width = wall[i].m_position.x2;
        }

        if (map.m_height < wall[i].m_position.y1) {
            map.m_height = wall[i].m_position.y1;
        }

        if (map.m_height < wall[i].m_position.y2) {
            map.m_height = wall[i].m_position.y2;
        }
    }

    map.m_width++; //+1 pour que la ligne la plus loin soit inclue dans la map et pas à la bordure (afin de voir la ligne)
    map.m_height++; //+1 pour que la ligne la plus loin soit inclue dans la map et pas à la bordure (afin de voir la ligne)

    map.m_textureMap = SDL_CreateTexture(screen->m_render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, map.m_width, map.m_height);
    if (map.m_textureMap == NULL) {
        printf("problème texture\n");
    }

    map.display = &map_display;
    map.clear  = &map_clear;

    return (map);
}

void map_display(Screen *screen, Map *map, Player *player) {
    SDL_Rect dst_display; //the area to display on the screen
    SDL_Rect src_display; //the area of the texture to display
    SDL_Rect limit_map; //the limit map allow to delimitate visualy the map on the screen                                        

    dst_display.x = 1;
    dst_display.y = 1; //(screen->m_heightWindow - (screen->m_heightWindow / 2)) / 2
    dst_display.w = screen->m_widthWindow / 3;
    dst_display.h = screen->m_heightWindow / 3;

    //connaître le début d'affichage de X position
    if (player->m_position.x < ((screen->m_widthWindow / 3)/2)) {
        src_display.x = 0;
    }
    else if (player->m_position.x > (map->m_width - ((screen->m_widthWindow / 3)/2))) { 
        src_display.x = (map->m_width - (screen->m_widthWindow / 3));
    } else {
        src_display.x = player->m_position.x - ((screen->m_widthWindow / 3)/2);
    }

    //connaître le début d'affichage de Y position sur l'écran
    if (player->m_position.y < ((screen->m_heightWindow / 3)/2)) {
        src_display.y = 0;
    }
    else if (player->m_position.y > (map->m_height - ((screen->m_heightWindow / 3)/2))) { 
        src_display.y = (map->m_height - (screen->m_heightWindow / 3));
    }
    else {
        src_display.y = player->m_position.y - ((screen->m_heightWindow / 3)/2);
    }
    
 
    src_display.w = screen->m_widthWindow / 3;
    src_display.h = screen->m_heightWindow / 3;



    SDL_RenderCopy(screen->m_render, map->m_textureMap, &src_display, &dst_display);
    
    //le cadre vert qui délimite la map. Il y a +3 pour ne pas passer sur l'affichage de la map
    limit_map.h = (screen->m_heightWindow / 3)+3;
    limit_map.w = (screen->m_widthWindow / 3)+3;
    limit_map.x = 0;
    limit_map.y = 0;

    SDL_SetRenderDrawColor(screen->m_render, 0, 255, 0, 255);
    SDL_RenderDrawRect(screen->m_render, &limit_map);
    return;
}

void map_clear(Screen *screen, Map *map) {

    SDL_SetRenderTarget(screen->m_render, map->m_textureMap);
    SDL_SetRenderDrawColor(screen->m_render, 0, 0, 0, 255);
    //apply the color to all renderer
    SDL_RenderClear(screen->m_render);
    SDL_SetRenderTarget(screen->m_render, NULL);
}