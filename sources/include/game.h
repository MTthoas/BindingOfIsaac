/**
 * @file game.h
 * @author MTthoas
 * @brief Declaration fonctions du jeu
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef H_GAME
#define H_GAME

typedef Monster Monster;

int gestionRoom(Donjon * d, int numberOfRooms, int stage, int axeX, int axeY);
void gestionGame(Donjon * d, int stage, int * change, Monster * arrayMonster);

#endif