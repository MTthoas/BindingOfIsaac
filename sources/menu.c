#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Player.h"
#include "menu.h"

void menu_init(void){
    system("clear");
    printf("------------ Binding Of Briatte --------------\n");
    printf("Press 1 to start the game\n");
    printf("Press 2 for the monster's CRUD\n");
    printf("Press 3 for the item's CRUD\n");
    printf("Press 4 for the room's CRUD\n");
    printf("Press 5 for the command's info\n");
    printf("-----------Dorian-Alexandre-Matthias----------\n");
}

void menuCrudMonster(void){
    system("clear");
		printf("------------ Binding Of Briatte --------------\n");
        printf("-------- You chose the monster's CRUD --------\n");
        printf("Press 1 to create a monster\n");
        printf("Press 2 to delete a monster\n");
        printf("Press 3 to modify a monster\n");
        //scanf("%d", &choix);
        // if (choix != 1 || choix != 2 || choix != 3){
        //     printf("------ Please enter a valid option  ------\n");
        //     scanf("%d", &choix);
        // }
        // return choix;

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
			printf("Choose the name of the monster to delete :\n");
            //deleteMonster();
}
void menuModifyMonster(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("------- You chose to modify a monster  -------\n");
            //modifyMonster();
}


void menuCrudItem(void){
    system("clear");
        printf("------------ Binding Of Briatte --------------\n");
        printf("-------- You chose the item's CRUD  --------\n");
        printf("Press 1 to create an item\n");
        printf("Press 2 to delete an item\n");
        printf("Press 3 to modify an item\n");
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


void menuCrudRoom(void){
    system("clear");
        printf("------------ Binding Of Briatte --------------\n");
        printf("-------- You chose the room's CRUD  --------\n");
        printf("Press 1 to create a room\n");
        printf("Press 2 to delete a room\n");
        printf("Press 3 to modify a room\n");
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

void menuCommand(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("--------------- Info Command  ----------------\n");
            printf("Use z,q,s,d to move\n");
            printf("Use 8,4,2,6 to attack\n");
            printf("Use c to go to the last page\n");
            printf("Use x to quit the game\n");            
}