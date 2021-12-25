#include "../include/map.h"

Wall wall_init(int x1, int y1, int x2, int y2) {
    Wall wall;

    wall.m_position.x1 = x1;
    wall.m_position.y1 = y1;
    wall.m_position.x2 = x2;
    wall.m_position.y2 = y2;

    wall.display = &wall_display;

    return (wall);
}

void wall_display(Screen *screen, Wall *wall, Map *map) {
    SDL_SetRenderTarget(screen->m_render, map->m_textureMap);

    SDL_SetRenderDrawColor(screen->m_render, 255, 255, 255, 255);
    SDL_RenderDrawLine(screen->m_render, wall->m_position.x1, wall->m_position.y1, wall->m_position.x2, wall->m_position.y2);

    SDL_SetRenderTarget(screen->m_render, NULL);
}