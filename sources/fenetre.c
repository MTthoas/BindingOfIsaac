/**
 * @file menuAccueil.c
 * @author TheGreat-Chain
 * @brief initialisation de l'interface graphique
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <SDL2/SDL.h>
#include "include/fenetre.h"

int lancerInterfaceGraphique()
{
    SDL_Window* window = NULL; 

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) != 0) { //gestion erreur
        SDL_Log("ERREUR : Initialisation de la SDL > %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("The Binding of Briatte", 
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            800, 600, 0);

    if(window == NULL) { //gestion erreur
        SDL_Log("ERREUR : Ouverture fenêtre > %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Delay(15 * 1000); // laisse la fenêtre ouverte pendant 5 secondes

    SDL_Quit();
    return EXIT_SUCCESS;
}
