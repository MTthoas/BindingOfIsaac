#ifndef H_PROOM
#define H_ROOM

struct Room {
    char** room;
    int number;
    int width;
    int height;
};

typedef struct Room Room;

Room* newRoom(int number);
void printRoom(Room room);

#endif