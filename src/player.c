#include "../include/player.h"

/**
 * @brief function to init a player
 * 
 * @param x 
 * @param y 
 * @return Player 
 */
Player player_init(int x, int y) {
    Player player;

    player.m_position.x = x;
    player.m_position.y = y;
    player.m_position.h = 5;
    player.m_position.w = 5;

    player.display  = &player_display;
    player.move     = &player_move;
    player.moveView = &player_moveView;

    player.m_ray = (Ray *)malloc(sizeof(Ray) * 66);
    for (int i = 0; i < 66; i++) {
        player.m_ray[i] = ray_init(&player, degree_to_radian(i));
        printf("le cos : %lf - le sin : %lf\n", cosf(degree_to_radian(i*10)), sinf(degree_to_radian(i)));
    }

    return (player);
}

/**
 * @brief Function to display the player on the screen
 * 
 * @param screen 
 * @param player 
 */
void player_display(Screen *screen, Player *player, Map *map) {

        SDL_SetRenderTarget(screen->m_render, map->m_textureMap);

        SDL_SetRenderDrawColor(screen->m_render, 255, 0, 0, 255);

        SDL_RenderFillRect(screen->m_render, &player->m_position);

        SDL_SetRenderTarget(screen->m_render, NULL);
}


/**
 * @brief Function to move the player on the screen with the arrow keypad and check collision of each side of the rect player with each wall
 * 
 * @param screen 
 * @param player 
 * @param wall 
 */
void player_move(Screen *screen, Player *player, Wall *wall) {

    const Uint8 *stateKeyboard;
    
    int tmpX = player->m_position.x;   //new position of player x
    int tmpY = player->m_position.y;   //new position of player y

    float t = 0;                //the t value to check collision
    float u = 0;                //the u value to check collision
    float denominator = 0;      //the denominateur of each calcul

    int x1 = 0; //the player
    int y1 = 0; //the player
    int x2 = 0; //the player
    int y2 = 0; //the player
    int x3 = 0; //the wall
    int y3 = 0; //the wall
    int x4 = 0; //the wall
    int y4 = 0; //the wall

    //get the future position with event keyboard arrow

    stateKeyboard = SDL_GetKeyboardState(NULL);

    if (stateKeyboard[SDL_SCANCODE_UP]) { //up the player on the screen
        tmpY--;
    }

    if (stateKeyboard[SDL_SCANCODE_DOWN]) {//down the player on the screen
        tmpY++;
    }
    if (stateKeyboard[SDL_SCANCODE_RIGHT]) {//right the player on the screen
        tmpX++;
    }      
    if (stateKeyboard[SDL_SCANCODE_LEFT]) {//left the player on the screen
         tmpX--;
    }


    //check collision

    for (int l = 0; l < nbrWall; l++) {

        x3 = wall[l].m_position.x1;
        y3 = wall[l].m_position.y1;
        x4 = wall[l].m_position.x2;
        y4 = wall[l].m_position.y2;


        for (int i = 0; i < 4; i++) { //check collision of each side of the player rectangle

            if (i == 0) { //face du dessus

                x1 = tmpX;
                y1 = tmpY;
                x2 = tmpX + player->m_position.w;
                y2 = tmpY;

            } else if (i == 1) { //face dessous

                x1 = tmpX;
                y1 = tmpY + player->m_position.h;
                x2 = tmpX + player->m_position.w;
                y2 = tmpY + player->m_position.h;

            } else if (i == 2) { //face côté droit

                x1 = tmpX + player->m_position.w; 
                y1 = tmpY;
                x2 = tmpX + player->m_position.w;
                y2 = tmpY + player->m_position.h;

            } else if (i == 3) { //face côté gauche

                x1 = tmpX; 
                y1 = tmpY;
                x2 = tmpX;
                y2 = tmpY + player->m_position.h;

            }

            denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

            t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
            u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / denominator;

            if (t >= 0 && t <= 1 && u >= 0 && u <= 1) { //collision true
                tmpX = player->m_position.x;
                tmpY = player->m_position.y;
            }
        }
    }
    player->m_position.x = tmpX;
    player->m_position.y = tmpY;
}


void player_moveView(Player *player) {

   //the rotation for all angle
    float rotation;
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    if (keyboardState[SDL_SCANCODE_Q]) {
        rotation -= 1;
    } else if (keyboardState[SDL_SCANCODE_D]) {
        rotation += 1;
    }

    rotation= degree_to_radian(rotation);

    for (int i = 0; i < 66; i++) {

        player->m_ray[i].m_angle = player->m_ray[i].m_angle + rotation;
        player->m_ray[i].m_direction.x = cosf(player->m_ray[i].m_angle);
        player->m_ray[i].m_direction.y = sinf(player->m_ray[i].m_angle);
    }
}