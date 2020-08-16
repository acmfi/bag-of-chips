#include "display.h"
#include "SDL2/SDL.h"
#include <stdio.h>

#define MAX_SCALE_FACTOR 25

int init_window(int scale_factor) {

    if (scale_factor < 1 || scale_factor > MAX_SCALE_FACTOR) {
	return 1; // Wrong scale factor, no window will be created
    }
    
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
			      "bag-of-chips: CHIP-8 Emulator",
			      SDL_WINDOWPOS_CENTERED, // initial x position
			      SDL_WINDOWPOS_CENTERED, // initial y position
			      64 * scale_factor, // width
			      32 * scale_factor, // height
			      SDL_WINDOW_OPENGL                 
			      );

    // Check if the window has been created
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 2;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
	printf("Could not create renderer: %s\n", SDL_GetError());
	return 3;
    }

    // draws a white background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // draws a red diagonal line
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 64 * MAX_SCALE_FACTOR; ++i)
        SDL_RenderDrawPoint(renderer, i, i);
    SDL_RenderPresent(renderer);

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}

void cls();

void draw(int VX, int VY, int N);
