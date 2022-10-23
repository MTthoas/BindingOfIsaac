/**
 * @file array.c
 * @author TheGreat-Chain
 * @brief Multiple functions to manipulate arrays et dynamic arrays
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "headers/array.h"

void clearIntArray(int *array, int size)
{
    for (int i = 0; i < size; i += 1) {
        array[i] = 0;
    }
}