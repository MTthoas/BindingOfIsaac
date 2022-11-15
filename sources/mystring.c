#include "include/mystring.h"

#include <string.h>
#include <stdlib.h>

char* duplicateString(char* string) {
    if(string == NULL) {
        return NULL;
    }
    int size = strlen(string);
    char* newStr = malloc(sizeof(char) * (size + 1));

    return strcpy(newStr, string);
}

void uppercase(char string[255]) {
    int i = 0;
    char c = string[i];
    char ecart = 'a' - 'A';

    while(c != '\0') {
        c = string[i];
        if(c >= 'a' && c <= 'z') {
            string[i] = c - ecart;
        }
        i += 1;
    }
}

void uppercaseSingle(char string) {
    char c = string;
    char ecart = 'a' - 'A';

        if(c >= 'a' && c <= 'z') {
            string = c - ecart;
        }
        
    
}