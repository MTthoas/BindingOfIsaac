/**
 * @file menu.c
 * @author  Nairod36
 * @brief Fonctions du menu
 * @version 0.1
 * @date 2022-11-5
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Player.h"
#include "menu.h"

void menu_init(void){
    system("clear");
    printf("------------ Binding Of Briatte --------------\n");
    printf("Press g to start the game\n");
    printf("Press i for the item's CRUD\n");
    printf("Press r for the room's CRUD\n");
    printf("Press c for the control's info\n");
    printf("-----------Dorian-Alexandre-Matthias----------\n");
}


void menuCrudItem(void){
    system("clear");
        printf("------------ Binding Of Briatte --------------\n");
        printf("-------- You chose the item's CRUD  --------\n");
        printf("Press a to add an item\n");
        printf("Press d to delete an item\n");
        printf("Press m to modify an item\n");
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
        printf("Press a to add a room\n");
        printf("Press d to delete a room\n");
        printf("Press m to modify a room\n");
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

void menuControl(void){
    system("clear");
            printf("------------ Binding Of Briatte --------------\n");
            printf("--------------- Info control  ----------------\n");
            printf("Use z,q,s,d to move\n");
            printf("Use 8,4,5,6 to attack\n");
            printf("Use x to quit the game\n");            
}