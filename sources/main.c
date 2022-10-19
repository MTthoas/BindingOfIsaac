#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include "Room.h"

int main(int argc, char * argv[]) {

    (void) argc;
    (void) argv;

    Room* room = newRoom(4);
    printRoom(*room);
    
    printf("\n");


    return 0;

  
}