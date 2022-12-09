#include "myUtils.h"
#include <time.h>
#include <stdlib.h>


int getRandomInt(int min, int max) {
    int result = 0, low = 0, high = 0;

    // to include max 
    if (min < max)
    {
        low = min;
        high = max + 1; 
    } else {
        low = max + 1; 
        high = min;
    }

    srand(time(NULL));
    result = (rand() % (high - low)) + low;
    return result;
}

void refresh() {
    #ifdef _WIN32 
    Sleep(400); 
    #else 
    usleep(80000);
    //usleep(400000); 
    #endif
}

void wait(int microseconds) {
    #ifdef _WIN32 
    Sleep(microseconds/1000); 
    #else 
    usleep(microseconds);
    #endif
}

void shuffle(int *array, size_t n)
{
    srand(time(NULL));
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }

}

int* generateUniqueNumbers(int size)
{
    int* array=malloc(sizeof(int)*size);

    for(int i=0 ; i < size ; i+=1) {
        array[i] = i;
    }    

    shuffle(array, size);
    return array;
}

int isUnique(int* res, int nb, int size) {
    for(int i = 0 ; i < size ; i += 1) {
        if(res[i] == nb) return 0;
    }
    return 1;
}

