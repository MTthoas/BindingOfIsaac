#ifndef MY_UTILS
#define MY_UTILS

#ifdef _WIN32 
#include <Windows.h>  
#else
#include <unistd.h>
#endif 

int getRandomInt(int min, int max);
void refresh(void);

#endif