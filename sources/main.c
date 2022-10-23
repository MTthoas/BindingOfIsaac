/**
 * @file main.c
 * @author TheGreat-Chain
 * @brief Lancement du programme
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//#include <SDL2/SDL.h>
#include "include/fenetre.h"
#include "include/lectureFichiers.h"
#include "include/objets.h"

int main(int argc, char const *argv[]) {
    //int res = lancerInterfaceGraphique();
    ListeObjets* l = fichierToListeObjets(); 
    printf("Nombre d'objets : %d\n", l->nombreObjets);

    free(l->tabObjets);
    free(l);
    return EXIT_SUCCESS;
}
