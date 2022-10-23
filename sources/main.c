#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include "Room.h"

#define SIZE_RECT 32

void update_map(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

void update_perso(SDL_Renderer *renderer, SDL_Rect perso) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &perso);
	SDL_RenderDrawRect(renderer, &perso);
}

int main(int argc, char * argv[]) {

    (void) argc;
    (void) argv;

    // Room* room = newRoom(4);
    // printRoom(*room);
    
    SDL_Window *window;
	SDL_Event event;
	SDL_Renderer *renderer;
	int quit=0;
	
	SDL_Rect perso;
	perso.x = 32;
	perso.y = 32;
	perso.w = SIZE_RECT;
	perso.h = SIZE_RECT;
	
	SDL_Surface *surface_rect;
	surface_rect = SDL_CreateRGBSurfaceWithFormat(0, SIZE_RECT, SIZE_RECT, 32, 
		SDL_PIXELFORMAT_RGBA32);
	if (surface_rect == NULL) {
		SDL_Log("Problem create rgb surface : %s", SDL_GetError());
		exit(1);
	}
	

	if (SDL_VideoInit(NULL) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL video: %s\n",
                SDL_GetError());
        exit(1);
	}
	
	window = SDL_CreateWindow("Fenetre",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480, SDL_WINDOW_SHOWN);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &perso);
	SDL_RenderDrawRect(renderer, &perso);
	
	SDL_RenderPresent(renderer);
	
	while ( !quit ) {
		if ( SDL_PollEvent(&event) ) {
			switch (event.type) {
				case SDL_QUIT:
					quit=1;
					break;
					
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_a:
							perso.x -=32;
							update_map(renderer);
							update_perso(renderer, perso);
							SDL_RenderPresent(renderer);
							break;
						case SDLK_d:
							perso.x +=32;
							update_map(renderer);
							update_perso(renderer, perso);
							SDL_RenderPresent(renderer);
							break;
						case SDLK_s:
							perso.y +=32;
							update_map(renderer);
							update_perso(renderer, perso);
							SDL_RenderPresent(renderer);
							break;
						case SDLK_w:
							perso.y -=32;
							update_map(renderer);
							update_perso(renderer, perso);
							SDL_RenderPresent(renderer);
							break;
				}//end switch event.key.keysym.sym
				break;
			}//end switch event.type
		}//end if PollEvent
	}//end while quit
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;


    return 0;

  
}