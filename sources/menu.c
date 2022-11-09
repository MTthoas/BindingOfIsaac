#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
int choix;

int menu_init(void){
   printf("------------ Binding Of Briatte --------------\n");
    printf("Press 1 to start the game\n");
    printf("Press 2 for the monster's CRUD\n");
    printf("Press 3 for the item's CRUD\n");
    printf("Press 4 for the room's CRUD\n");
    printf("-----------Dorian-Alexandre-Matthias----------\n");

    scanf("%d", &choix);
    return choix;
}

int menuCrudMonster(void){
    system("clear");
		printf("------------ Binding Of Briatte --------------\n");
        printf("-------- You chose the monster's CRUD --------\n");
        printf("Press 1 to create a monster\n");
        printf("Press 2 to delete a monster\n");
        printf("Press 3 to modify a monster\n");
        scanf("%d", &choix);
        return;

}
void menuCreateMonster(void){
    system("clear");
			printf("------------ Binding Of Briatte --------------\n");
            printf("------- You chose to create a monster  -------\n");
            printf("Choose the name of the monster to create :\n");
            //monstre.name = malloc(sizeof(char) * 20);
            printf("Choose the hpMax of the monster to create :\n");
            //createMonster();
}
void menuDeleteMonster(void){
    system("clear");
			printf("------------ Binding Of Briatte --------------\n");
            printf("------- You chose to delete a monster  -------\n");
			printf("Choose the name of the monster to create :\n");
            //deleteMonster();
}
void menuModifyMonster(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("------- You chose to modify a monster  -------\n");
            //modifyMonster();
}


int menuCrudItem(void){
    system("clear");
        printf("------------ Binding Of Briatte --------------\n");
        printf("-------- You chose the item's CRUD  --------\n");
        printf("Press 1 to create an item\n");
        printf("Press 2 to delete an item\n");
        printf("Press 3 to modify an item\n");
        scanf("%d", &choix);
        return choix;
}
void menuCreateItem(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("-------- You chose to create an item  --------\n");
            //createItem();
}
void menuDeleteItem(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("-------- You chose to delete an item  --------\n");
            //deleteItem();
}
void menuModifyItem(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("-------- You chose to modify an item  --------\n");
            //modifyItem();
}


int menuCrudRoom(void){
    system("clear");
        printf("------------ Binding Of Briatte --------------\n");
        printf("-------- You chose the room's CRUD  --------\n");
        printf("Press 1 to create a room\n");
        printf("Press 2 to delete a room\n");
        printf("Press 3 to modify a room\n");
        scanf("%d", &choix);
        return choix;
}
void menuCreateRoom(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("-------- You chose to create a room  --------\n");
            //createRoom();
}
void menuDeleteRoom(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("-------- You chose to delete a room  --------\n");
            //deleteRoom();
}
void menuModifyRoom(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("-------- You chose to modify a room  --------\n");
            //modifyRoom();
}


void optionError(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("------ You didn't choose a valid option ------\n");
}