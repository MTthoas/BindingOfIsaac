#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include "parseRoom.h"


#define LARGEUR_TILE 24 // hauteur et largeur des tiles.
#define HAUTEUR_TILE 16

#define NOMBRE_BLOCS_LARGEUR 15 // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 13



int main(int argc, char * argv[]) {

    (void) argc;
    (void) argv;

    // int ** matrix;


    // matrix = FetchRoom();
    // printf("Matrix is : \n");
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         printf("%d", matrix[i][j]);
    //         printf("\t");
    //     }
    //     printf("\n");
    // }



    Room(3);
  
    printf("\n");
    // for(int i = 0; i<2; i++){
    //     printf("%d", tab[i]);
    // }


    return 0;

  
}