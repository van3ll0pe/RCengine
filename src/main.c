#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include <SDL2/SDL.h>
#include "../include/macros.h"
#include "../include/screen.h"
#include "../include/wall.h"
#include "../include/player.h"
#include "../include/ray.h"
#include "../include/mathRadian.h"
#include "../include/map.h"

#include "../include/renderer.h"

int nbrWall;        //the number of wall




/**
 * @brief Function to parse the content of the file and set the number of wall and each wall position
 *         return 1 if there is an error | return 0 if success
 * @param buffer 
 * @param wall 
 * @return int 
 */
int parseMap(char *buffer, Wall **wall) {
    int i = 0;              //browse buffer
    int l = 0;              //browse wall
    int statePosition = 0;  //statePosition allow to determinate which position of the point

    nbrWall = 0;
    //get the number of wall in the first line
    for (i = 0; buffer[i] != '\n'; i++) {

        if (buffer[i] >= '0' && buffer[i] <= '9') {
            nbrWall = nbrWall * 10 + (buffer[i] - '0');
        }
    }

    //set the table of wall
    (*wall) = (Wall *)malloc(sizeof(Wall) * nbrWall);
    if ((*wall) == NULL) {
        printf("impossible to set wall memory\n");
        return (1);
    }

    for (l = 0; l < nbrWall; l++) {
        (*wall)[l].m_position.x1 = 0;
        (*wall)[l].m_position.y1 = 0;
        (*wall)[l].m_position.x2 = 0;
        (*wall)[l].m_position.y2 = 0;

        (*wall)[l].display = &wall_display;
    }
    

    //set the position of each wall
    //---------------------------------------------------------------------------------------------
    for (i = i+1, l = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ' ') {
            statePosition++;
        }

        else if (buffer[i] == '\n') {
            l++;
            statePosition = 0;
        }

        else if (buffer[i] >= '0' && buffer[i] <= '9') {

            if (statePosition == 0) { //x1
                
                (*wall)[l].m_position.x1 = ((*wall)[l].m_position.x1 * 10) + (buffer[i] - '0');

            } else if (statePosition == 1) { //y1
                
                (*wall)[l].m_position.y1 = ((*wall)[l].m_position.y1 * 10) + (buffer[i] - '0');

            } else if (statePosition == 2) { //x2

                (*wall)[l].m_position.x2 = ((*wall)[l].m_position.x2 * 10) + (buffer[i] - '0');

            } else if (statePosition == 3) { //y2
                
                (*wall)[l].m_position.y2 = ((*wall)[l].m_position.y2 * 10) + (buffer[i] - '0');

            }
        }
    }

    return (0);
}    //---------------------------------------------------------------------------------------------




/**
 * @brief Function to open the file map and call the parseMap function to edit the WALLS.
 *        Return 1 if there is an error | return 0 if success
 * 
 * @param wall 
 * @return int 
 */
int openFile(Wall **wall) {
    FILE        *file = NULL;               //the file to open
    struct stat file_specs;                 //the specs of the file
    char        *file_path = "data/map";    //the path of the file
    char        *buffer = NULL;             //the text of the file

    
    //open file
    file = fopen(file_path, "r");
    if (file == NULL) {
        printf("impossible to open file\n");
        return (1);
    }

    //get the size of the file to malloc the buffer
    stat(file_path, &file_specs);

    //set the buffer
    buffer = (char *)malloc(sizeof(char) * file_specs.st_size + 1);
    buffer[file_specs.st_size] = '\0';
    if (buffer == NULL) {
        printf("impossible to get size of buffer\n");
        return (1);
    }

    //all the content file in the buffer
    fread(buffer, file_specs.st_size, 1, file);

    if (parseMap(buffer, wall) == 1) {
        return (1);
    }


    fclose(file);
    free(buffer);

    return (0);
}


int main(int ac, char **av) {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return (EXIT_FAILURE);
    }

    Screen screen = screen_init();
    Wall *wall = NULL;
    Player player = player_init(250, 250);
    Map map;
    Rendering rendering;

    if (openFile(&wall) == 1) { //open file and set the wall variable
        return (EXIT_FAILURE);
    }


    if (screen.init_sdl(&screen) == 1) { //init all sdl element of screen
        return (EXIT_FAILURE);
    }

    map = map_init(&screen, wall);
    rendering = rendering_init(&screen, &player);

    while (screen.m_isRunning) { //main loop

        screen.adaptRender(&screen);
        screen.getEvent(&screen);

        screen.clear(&screen);
        map.clear(&screen, &map);
        
        for (int i = 0; i < nbrWall; i++) {
            wall[i].display(&screen, &wall[i], &map);
        }

        player.display(&screen, &player, &map);
        player.move(&screen, &player, wall);
        player.moveView(&player);

        for (int i=0; i < 66; i++) {
            player.m_ray[i].setPosition(&player, &player.m_ray[i]);
            player.m_ray[i].setEndPosition(wall, &player.m_ray[i]);

            player.m_ray[i].display(&screen, &player.m_ray[i], &map);
        }

        rendering.adapt(&screen, &rendering, &player);
        rendering.display(&screen, &rendering, &player);

        map.display(&screen, &map, &player);
        SDL_RenderPresent(screen.m_render);
        SDL_Delay(7);

    }
    
    SDL_Quit();
    return (EXIT_SUCCESS);
}