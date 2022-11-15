/**
 * @file main.c
 * @author Nairod36
 * @brief  Main du programme
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#include<stdio.h>
#include <stdlib.h>
#include "Room.h"
#include "menu.h"
#include "firstMenu.h"

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"


int main(int argc, char * argv[]) {
	(void) argc;
	(void) argv;
	
	Donjon * d = malloc(sizeof(Donjon));
	
	InitialisationGame(d);
	InitialisationGameByStagesOptions(d);
	menu_init();
	firstMenu(d);
}