#include "../include/player.h"

/**
 * @brief function to init the structure ray
 * 
 * @param player 
 * @return Ray 
 */
 Ray ray_init(Player *player, float angle) {
     Ray ray;

     ray.m_position.x = player->m_position.x + 2;
     ray.m_position.y = player->m_position.y + 2;

     ray.m_angle = angle;

     ray.m_direction.x = cosf(angle);
     ray.m_direction.y = sinf(angle);

     ray.m_endPosition.x = ray.m_position.x + ray.m_direction.x * 1;
     ray.m_endPosition.y = ray.m_position.y + ray.m_direction.y * 1;

     ray.display = &ray_display;
     ray.setPosition = &ray_setPosition;
     ray.setEndPosition = &ray_setEndPosition;

     return (ray);
 }


/**
 * @brief function to display the ray on the screen
 * 
 * @param screen 
 * @param ray 
 */
 void ray_display(Screen *screen, Ray *ray, Map *map) {
     SDL_SetRenderTarget(screen->m_render, map->m_textureMap);
     SDL_SetRenderDrawColor(screen->m_render, 255, 255, 0, 255);
     SDL_RenderDrawLine(screen->m_render, ray->m_position.x, ray->m_position.y, ray->m_endPosition.x, ray->m_endPosition.y);
     SDL_SetRenderTarget(screen->m_render, NULL);

 }



/**
 * @brief Function to set the new position of the ray
 * 
 * @param player 
 * @param ray 
 */
 void ray_setPosition(Player *player, Ray *ray) {
     ray->m_position.x = player->m_position.x + 2;
     ray->m_position.y = player->m_position.y + 2;
 }



/**
 * @brief function to calculate the new end Position of the ray
 * 
 * @param wall 
 * @param player 
 */
 void ray_setEndPosition(Wall *wall, Ray *ray) {

    int x1 = ray->m_position.x; //the player
    int y1 = ray->m_position.y; //the player
    float x2 = ray->m_position.x + ray->m_direction.x; //the player
    float y2 = ray->m_position.y + ray->m_direction.y; //the player

    int x3 = 0; //the wall
    int y3 = 0; //the wall
    int x4 = 0; //the wall
    int y4 = 0; //the wall

    float t = 0;                //the t value to check collision
    float u = 0;                //the u value to check collision
    float denominator = 0;      //the denominateur of each calcul

    float closest = -1;            //the indicator to get the closest wall collision
    int closestCollision_x;        //the temporary closest position of the collision X 
    int closestCollision_y;        //the temporary closest position of the collision y

    for (int i = 0; i < nbrWall; i++) { //browse every wall

        x3 = wall[i].m_position.x1;
        y3 = wall[i].m_position.y1;
        x4 = wall[i].m_position.x2;
        y4 = wall[i].m_position.y2;

        denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);


        t = (((x1 - x3) * (y3 - y4)) - ((y1 - y3) * (x3 - x4))) / denominator;
        u = (((x1 - x3) * (y1 - y2)) - ((y1 - y3) * (x1 - x2))) / denominator;


        if (t >= 0 && u <= 1 && u >= 0) { //c'est inversé car le personnage possède les premières coordonnées et les murs les dernières

            closestCollision_x = x3 + (u * (x4 - x3));
            closestCollision_y = y3 + (u * (y4 - y3));
            
            if (closest == -1) {
                closest = distance_points(x1, y1, closestCollision_x, closestCollision_y);
                ray->m_endPosition.x = closestCollision_x;
                ray->m_endPosition.y = closestCollision_y;
            } else if (closest > distance_points(x1, y1, closestCollision_x, closestCollision_y)) {
                closest = distance_points(x1, y1, closestCollision_x, closestCollision_y);
                ray->m_endPosition.x = closestCollision_x;
                ray->m_endPosition.y = closestCollision_y;
            }
            
        }

    }
 }