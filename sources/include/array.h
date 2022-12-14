/**
 * @file array.h
 * @author TheGreat-Chain
 * @brief Multiple functions to manipulate arrays et dynamic arrays
 * @version 0.1
 * @date 2022-10-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARRAY_H

    #define ARRAY_H

    /**
     * @brief Replaces every element of the array of integers with zeros.  
     * {1,2,3} -> {0,0,0}
     * 
     * @param array array to clear
     * @param size size of the array
     */
    void clearIntArray(int* array, int size);

    /**
     * @brief Prints in the console the content of 2D array
     * 
     * @param array 
     * @param lines 
     * @param columns 
     */
    void displayCharArray2D(char** array, int lines, int columns);

    void freeCharArray2D(char** array, int lines, int columns);

    char** duplicateCharArray2D(char** array, int lines, int columns);

    char** createCharArray2D(int lines, int columns);

#endif // ARRAY_H