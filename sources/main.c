#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<stdio.h>
#include <termios.h>          
#include <unistd.h>     
#include <stdlib.h>
#include <sys/select.h>
#include <stdbool.h>
#include <fcntl.h>

#include "Room.h"
#include "Player.h"
#include "menu.h"
#include "game.h"

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(double percentage) {

    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}


int main(int argc, char * argv[]) {
	//Menu
	bool condition = true, condition2 = true, etape = true;
	int c,c2;
	
	
	
	menu_init();

	while (condition) {
		c = 'p';

		if (etape == true && kbhit()) {
			c = getchar();
		}
		if (c == 'x') {
			condition = false;
		}

		switch (c) {

			case 'g':
				(void) argc;
				(void) argv;

				int stage = 0;
				int change = 0;

				for(int i = 0; i < 1; i++){


					Donjon * d = malloc(sizeof(Donjon));
		
					
					InitialisationGame(d, stage);			
					gestionGame(d,stage, &change);
					

					// free(d);

					stage++;
					// printf("CHANGE : %d", change);
					change = 0;

					system("clear");
					printf("\n\n\n\n\n\n\n\n\n");
					printf("		Changement d'étages ..\n\n");


					for(int i = 0; i < 20; i++){
						printProgress(i/20.0);
						#ifdef _WIN32 
						Sleep(100); 
						#else 
						usleep(100000); 
						#endif 
					}
					




				}
									
				condition = false;
				break;
				// menu_init();
			
			case 'i':
			while (condition2)
			{
			etape = false;
				c2 = 'p';
				menuCrudItem();
				if (kbhit()) {
					c2 = getchar();
				}
				switch (c2){
					case 'a':
						menuCreateItem();
						condition2 = false;
						break;
					case 'd':
						menuDeleteItem();
						condition2 = false;

						break;
					case 'm':
						menuModifyItem();
						condition2 = false;

						break;

				}
			}
			break;
				

			case 'r':
			 while (condition2)
			 {
				etape = false;
				c2 = 'p';
				menuCrudRoom();
				if (kbhit()) {
					c2 = getchar();
				}
				switch (c2){
					case 'a':
						menuCreateRoom();
						condition2 = false;
						break;
					case 'd':
						menuDeleteRoom();
						condition2 = false;
						break;
					case 'm':
						menuModifyRoom();
						condition2 = false;
						break;
				}
			 }
				break;

			case 'c':
				menuControl();
		}
	}
}