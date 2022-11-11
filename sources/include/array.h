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

#endif // ARRAY_H