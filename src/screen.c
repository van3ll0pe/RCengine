#include "../include/screen.h"


/**
 * FUNCTION TO INIT THE STRUCTURE SCREEN 
 * 
 *  RETURN A SCREEN 
 */
Screen screen_init() {
    Screen var;

    var.m_isRunning     = 1;
    var.m_widthWindow   = 900;
    var.m_heightWindow  = 600;
    var.m_ratioScreenBegin   = var.m_widthWindow / var.m_heightWindow;
    var.m_titleWindow   = "RAYCASTING ENGINE";
    var.m_window        = NULL;
    var.m_render        = NULL;


    var.init_sdl    = &screen_init_sdl;
    var.getEvent    = &screen_getEvent;
    var.adaptRender = &screen_adaptRender;
    var.destroy     = &screen_destroy;
    var.clear       = &screen_clear;

    return (var);
}


/**
 *  FUNCTION TO INIT SDL_WINDOW AND SDL_RENDERER of the structure
 * 
 */
int screen_init_sdl(Screen *var) {

    var->m_window = SDL_CreateWindow(var->m_titleWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, var->m_widthWindow, var->m_heightWindow, SDL_WINDOW_RESIZABLE);
    if (var->m_window == NULL) {
        printf("probleme creation fenetre\n");
        return (EXIT_FAILURE);
    }

    var->m_render = SDL_CreateRenderer(var->m_window, -1, SDL_RENDERER_ACCELERATED);
    if (var->m_render == NULL) {
        printf("probleme creation renderer\n");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}


/**
 * FUNCTION which destroy WINDOW and RENDERER of the Structure 
 * 
 */
void screen_destroy(Screen *var) {
    SDL_DestroyRenderer(var->m_render);
    SDL_DestroyWindow(var->m_window);
}

/**
 * FUNCTION get the window size and apply the same size to the main render
 * 
 * 
 */
void screen_adaptRender(Screen *var) {
    //get the window size into widthWindow and heightWindow
    SDL_GetWindowSize(var->m_window, &var->m_widthWindow, &var->m_heightWindow);

    //set the render size at the window size
    SDL_RenderSetLogicalSize(var->m_render, var->m_widthWindow, var->m_heightWindow);

}

/**
 * FUNCTION clear the screen in black
 * 
 * 
 */
void screen_clear(Screen *var) {
    //set the black color of the renderer
    SDL_SetRenderDrawColor(var->m_render, 0, 0, 0, 255);
    //apply the color to all renderer
    SDL_RenderClear(var->m_render);

}

/**
 * FUNCTION get all event on the program
 * 
 * 
 */
void screen_getEvent(Screen *var) {
    while (SDL_PollEvent(&var->m_event)) {
        if (var->m_event.type == SDL_QUIT) {
            var->m_isRunning = 0;
        }
    }
}