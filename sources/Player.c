#include<stdio.h>
#include <termios.h>          
#include <unistd.h>     
#include <stdlib.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <Player.h>

int kbhit(void) {
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, & oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, & newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, & oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

void gestionPosition(Player * player, Room * room, int keyboardEntry){

	player->positionX = 1;
	player->positionY = 1;

    if(keyboardEntry != 'e'){

        // system("clear");

		switch (keyboardEntry) {
				case 'z':
					if (room ->room[player->positionY - 1][player->positionX] != 'W' && room ->room[player->positionY - 1][player->positionX] != 'D') {
						room ->room[player->positionY][player->positionX] = ' ';
						player->positionY--;
						room ->room[player->positionY][player->positionX] = 'P';
						player->directionView = 'z';
					}
					break;
				case 's':
					if (room ->room[player->positionY + 1][player->positionX] != 'W' && room ->room[player->positionY + 1][player->positionX] != 'D') {
						room ->room[player->positionY][player->positionX] = ' ';
						player->positionY++;
						room ->room[player->positionY][player->positionX] = 'P';
						player->directionView = 's';
					}
					break;
				case 'q':
					if (room ->room[player->positionY][player->positionX - 2] != 'W' && room ->room[player->positionY][player->positionX - 2] != 'D') {
						room ->room[player->positionY][player->positionX] = ' ';
						player->positionX -= 2;
						room ->room[player->positionY][player->positionX] = 'P';
						player->directionView = 'q';
					}
					break;
				case 'd':
					if (room ->room[player->positionY][player->positionX + 2] != 'W' && room ->room[player->positionY][player->positionX + 2] != 'D') {
						room ->room[player->positionY][player->positionX] = ' ';
						player->positionX += 2;
						room ->room[player->positionY][player->positionX] = 'P';
						player->directionView = 'd';
					}
			}

    }
    

}