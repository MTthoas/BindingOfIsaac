#include "myUtils.h"
#include <time.h>
#include <stdlib.h>

int getRandomInt(int min, int max) {
    int random;

    srand(time(NULL));
    for(int i=0; i<100; i+=1) { 
        random = min + rand() %(max-1);
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