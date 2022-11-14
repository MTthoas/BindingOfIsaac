#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/Player.h"
#include "./include/menu.h"
#include "./include/cheminsFichiers.h"
#include "./include/lectureFichiers.h"
#include "./include/objets.h"
#include "./include/mystring.h"
#include "./include/userInput.h"

void printGameBanner() {
    printf("=================================================\n");
    printf("=========== THE BINDING OF BRIATTE ==============\n");
    printf("=================================================\n");
}

void menu_init(void){
    system("clear");
    printGameBanner();
    printf("Press G to start the game\n");
    printf("Press I for the ITEMS menu\n");
    printf("Press R for the ROOMS menu\n");
    printf("Press C for the controls information\n");
    printf("----------- Dorian-Alexandre-Matthias ----------\n");
}


void menuCrudItem(void){
    system("clear");
        printGameBanner();
        printf("-------- ITEMS MENU  --------\n");
        printf("Press S to see your current items\n");
        printf("Press A to add an item\n");
        printf("Press D to delete an item\n");
        printf("Press M to modify an item\n");
}

void menuSeeItems(void) {
    system("clear");
    printGameBanner();
    printf("-------- Your items --------\n");

    FILE* fichier = fopen(CHEMIN_FICHIER_OBJETS, "r");
    afficherFichier(fichier);
    fclose(fichier);
    
    printf("\nPress ENTER to continue ...\n");
    getchar();
    return;
}

void menuCreateItem(void){
    system("clear");
    printGameBanner();
    printf("-------- Creating item  --------\n");

    ListeObjets* items = fichierObjetsToListeObjets();
    if(items == NULL) {
        printf("Couldn't open %s\n.", CHEMIN_FICHIER_OBJETS);
        printf("Press ENTER to continue\n");
        getchar();
        return;
    }

    char name[20];
    askName(name);

    float hpMax;
    askHpMax(&hpMax);

    float shield;
    askShield(&shield);
    
    float damage;
    askDamage(&damage);
    
    int piercingShot;
    askPiercingShot(&piercingShot);
    
    int spectralShot;
    askSpectralShot(&spectralShot);
    
    int flight;
    askFlight(&flight);

    Objet* newItem = createObjet(duplicateString(name), hpMax, shield, damage, piercingShot, spectralShot, flight);
    
    int res = addObjet(items, newItem);
    if(res == 0) {
        printf("Could not add the item.\n");
        freeListeObjets(items);
        freeObjet(newItem);
        printf("Press ENTER to continue\n");
        getchar();
    }

    printf("New item : ");
    displayObjet(newItem);
    printf("Do you want to add it ?\n");
    int success = confirmation();
    if(success) {
        listeToFichierObjets(items);
        printf("New item added.\n");
    }     

    printf("\nPress ENTER to continue\n");
    getchar();
}

void menuDeleteItem(void){
    system("clear");
    printGameBanner();
    printf("-------- Deleting item  --------\n");
    
    ListeObjets* items = fichierObjetsToListeObjets();
    if(items == NULL) {
        printf("Couldn't open %s\n.", CHEMIN_FICHIER_OBJETS);
        printf("Press ENTER to continue\n");
        getchar();
        menuCrudItem();
    }

    int id;
    int success = 0;
    displayListeObjets(items);
    printf("Enter the id of the item you want to delete (see above) : \n");
    do {
        id = readInt();
        printf("id = %d. Is it correct ? (y/n) \n", id);
        success = confirmation();
    } while(!success);

    removeObjet(items, id);
    listeToFichierObjets(items);
    freeListeObjets(items);

    printf("Item deleted.\n");
    printf("\nPress ENTER to continue\n");
    getchar();
}

void menuModifyItem(void){
    system("clear");
    printGameBanner();
    printf("-------- You chose to modify an item  --------\n");

    ListeObjets* items = fichierObjetsToListeObjets();
    if(items == NULL) {
        printf("Couldn't open %s\n.", CHEMIN_FICHIER_OBJETS);
        printf("Press ENTER to continue\n");
        getchar();
        return;
    }

    int id;
    int success = 0;
    displayListeObjets(items);
    do {
        printf("Enter the id of the item you want to update (see above) : \n");
        id = readInt();
        printf("You selected the id %d. Is it correct ? (y/n) \n", id);
        success = confirmation();
    } while(!success);

    Objet* item = getObjetById(items, id);
    if(item == NULL) {
        printf("Couldn't get the item of id : %d\n", id);
        printf("Press ENTER to continue\n");
        getchar();
        return;
    }

    success = 0;
    
    printf("Current item's name : %s.\nDo you want to modify the item's name (y/n) ?\n", item->name);
    success = confirmation();
    if(success) {
        char name[20];
        askName(name);
        item->name = duplicateString(name);
    }
    
    printf("Current item's HP MAX : %f.\nDo you want to modify the item's HP MAX (y/n) ?\n", item->hpMax);
    success = confirmation();
    if(success) {
        float hpMax;
        askHpMax(&hpMax);
        item->hpMax = hpMax;
    }

    printf("Current item's SHIELD: %f.\nDo you want to modify the item's SHIELD (y/n) ?\n", item->shield);
    success = confirmation();
    if(success) {
        float shield;
        askShield(&shield);
        item->shield = shield;
    }

    printf("Current item's DAMAGE: %f.\nDo you want to modify the item's DAMAGE (y/n) ?\n", item->damage);
    success = confirmation();
    if(success) {
        float damage;
        askDamage(&damage);
        item->damage = damage;
    }

    printf("Current item's PIERCING SHOT : %s.\nDo you want to modify the item's PIERCING SHOT (y/n) ?\n", 
        (item->piercingShot) ? "true" : "false");
    success = confirmation();
    if(success) {
        int ps;
        askPiercingShot(&ps);
        item->piercingShot = ps;
    }

    printf("Current item's SPECTRAL SHOT : %s.\nDo you want to modify the item's SPECTRAL SHOT (y/n) ?\n", 
        (item->spectralShot) ? "true" : "false");
    success = confirmation();
    if(success) {
        int ss;
        askSpectralShot(&ss);
        item->spectralShot= ss;
    }

    printf("Current item's FLIGHT : %s.\nDo you want to modify the item's FLIGHT (y/n) ?\n", 
        (item->flight) ? "true" : "false");
    success = confirmation();
    if(success) {
        int flight;
        askFlight(&flight);
        item->flight= flight;
    }

    printf("The item's stat now :\n");
    displayObjet(item);

    listeToFichierObjets(items);
    freeListeObjets(items);
    printf("\nPress ENTER to continue\n");
    getchar();
}


void menuCrudRoom(void){
    system("clear");
        printGameBanner();
        printf("-------- You chose the room's CRUD  --------\n");
        printf("Press a to add a room\n");
        printf("Press d to delete a room\n");
        printf("Press m to modify a room\n");
}
void menuCreateRoom(void){
    system("clear");
            printGameBanner();
            printf("-------- You chose to create a room  --------\n");
            //createRoom();
}
void menuDeleteRoom(void){
    system("clear");
            printGameBanner();
            printf("-------- You chose to delete a room  --------\n");
            //deleteRoom();
}
void menuModifyRoom(void){
    system("clear");
            printGameBanner();
            printf("-------- You chose to modify a room  --------\n");
            //modifyRoom();
}

void menuControl(void){
    system("clear");
            printGameBanner();
            printf("--------------- Info control  ----------------\n");
            printf("Use z,q,s,d to move\n");
            printf("Use 8,4,5,6 to attack\n");
            printf("Use x to quit the game\n");

        printf("\nPress ENTER to continue ...\n");
        getchar();
        return;
}