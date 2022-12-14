/**
 * @file userInput.h
 * @author TheGreat-Chain
 * @brief functions to handle user inputs
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "./roomsForCRUD.h"


/**
 * @brief Fills 'string' with user input. Returns 1 if no problem, 0 otherwise.
 * 
 * @param string pointer to the string the user has to fill
 * @param size to allocate place in memory for the string parameter
 * @return int 
 */
int readInput(char* string, int size);

/**
 * @brief Converts user input into float
 * Returns a float, 0 if failure.
 * 
 * @return float
 */
float readFloat();

/**
 * @brief Converts user input into int
 * Returns a int, 0 if failure.
 * 
 * @return int
 */
int readInt();

/**
 * @brief Returns 1 if user types "y" or "Y" or "Yes".
 * Returns 0 if user types "n" or "N" or "No". 
 * 
 * @return int 
 */
int confirmation();

/**
 * @brief Lets the user type a name.
 * Fills the name string at the given address.
 * 
 */
void askName(char* name);

/**
 * @brief Lets the user type hpMax stat.
 * Fills hpMax string at the given address.
 * 
 */
void askHpMax(float* hpMax);

/**
 * @brief Lets the user type shield stat.
 * Fills shield string at the given address.
 */
void askShield(float* shield);

/**
 * @brief Lets the user type damage stat.
 * Fills the damage string at the given address.
 */
void askDamage(float* damage);

/**
 * @brief Lets the user decide if the item should provide piercing shot ability.
 * Fills ps string at the given address.
 */
void askPiercingShot(int* ps);

/**
 * @brief Lets the user decide if the item should provide spectral shot ability.
 * Fills ss string at the given address.
 * 
 */
void askSpectralShot(int* ss);

/**
 * @brief Lets the user decide if the item should provide flight ability.
 * Fills the flight string at the given address.
 * 
 */
void askFlight(int* flight);

/**
 * @brief Used to clear stdin
 */
void clearSTDIN();

/**
 * @brief Asks the user how many rooms does he want to load during the game
 */
void askNumberOfRooms(int* nRooms, int max);

/**
 * @brief Asks the user the dimensions for a room. 
 * 
 * @param lines 
 * @param columns 
 */
void askRoomDimensions(int* lines, int* columns);

void askRoomElement(char* element);

void askPosition(int* x, int* y, CRUD_Room* room);

void askNumberOfObstacles(int* nRooms);
#endif // USER_INPUT_H