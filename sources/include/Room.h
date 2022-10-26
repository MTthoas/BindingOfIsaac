#ifndef H_ROOM
#define H_ROOM

struct Room {
    char** room;
    int** roomInt;
    int number;
    int width;
    int height;
};

typedef struct Room Room;

Room* newRoom(int number);
void printRoom(Room room);

#endif