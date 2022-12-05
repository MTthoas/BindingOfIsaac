#ifndef MY_UTILS
#define MY_UTILS

#ifdef _WIN32 
#include <Windows.h>  
#else
#include <unistd.h>
#endif 

/**
 * @brief get a random integer
 * 
 * @param min minimum
 * @param max maximum of the wanted number
 * @param precision The higher the precision, better the "randomness"
 * @return int 
 */
int getRandomInt(int min, int max, int precision);
void refresh(void);


/**
 * @brief Get an array with x numbers that are all unique
 * 
 * @param number 
 * @param zero 
 * @return int* array of unique numbers
 */
int* generateUniqueNumbers(int size, int limit); // renvoie null si impossible à cause de la taille

/**
 * @brief Checks if a number is unique inside an array
 * 
 * @param res 
 * @param newNumber 
 * @param size 
 * @return int 1 if unique, 0 else
 */
int isUnique(int* res, int newNumber, int size); 

#endif