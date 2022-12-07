#include "myUtils.h"
#include <time.h>
#include <stdlib.h>

int getRandomInt(int min, int max, int precision) {
    int random;

    srand(time(NULL));
    for(int i=0; i<precision; i+=1) { 
        random = min+1 + rand() %(max-1);
    }

    return random;
}

void refresh() {
    #ifdef _WIN32 
    Sleep(400); 
    #else 
    usleep(80000);
    //usleep(400000); 
    #endif
}

int* generateUniqueNumbers(int size, int limit) {
    if(size >= limit) { // combinaison unique impossible  
        return NULL;
    }

    int* res = malloc(sizeof(int) * size);
    int newNumber = 1;

    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0 ; i < size ; i += 1) { // génération des nombres

        while(1) { 
            newNumber = rand() % limit;
            if(isUnique(res, newNumber, size) == 1) {
                res[i] = newNumber;
                break;
            } else {
                continue;
            }
        }

    }
    return res;
}

int isUnique(int* res, int nb, int size) {
    for(int i = 0 ; i < size ; i += 1) {
        if(res[i] == nb) return 0;
    }
    return 1;
}

