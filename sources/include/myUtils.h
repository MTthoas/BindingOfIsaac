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
 * @param max maximum included
 * @return int 
 */
int getRandomInt(int min, int max);
void refresh(void);

/**
 * @brief Cross-platform way to wait for x microseconds
 * 
 * @param microseconds 
 */
void wait(int microseconds);

/**
 * @brief Get an array with x numbers that are all unique. From 0 to size.
 * 
 * @param size of the wanted array
 * @return int* array of unique numbers
 */
int* generateUniqueNumbers(int size);

/**
 * @brief shuffle an array of int
 * 
 * @param array 
 * @param n 
 */
void shuffle(int *array, size_t n);

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