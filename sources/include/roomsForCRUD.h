/**
 * @file roomsForCRUD.h
 * @author TheGreat-Chain
 * @brief Structures and functions used by the rooms menu
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ROOMS_CRUD_H
#define ROOMS_CRUD_H


    /**
     * @brief Room used by the room menu in order to modify room.rtbob file.
     */
    typedef struct CRUD_Room CRUD_Room;
    struct CRUD_Room {
        int id;
        int lines;
        int columns;
        char** map; // array with the elements (doors, gaps, spikes, ...)

        CRUD_Room* next;
    };

    /**
     * @brief Create a CRUD_Room object with the given elements
     * 
     * @param lines 
     * @param columns should be x2 because of spaces
     * @param roomElements 
     * @return CRUD_Room* 
     */
    CRUD_Room* createCRUD_Room(int lines, int columns, char** roomElements);

    /**
     * @brief Create a CRUD_Room with only doors and walls
     * 
     * @param height 
     * @param width 
     * @return CRUD_Room* 
     */
    CRUD_Room* createEmptyCRUD_Room(int height, int width);

    /**
     * @brief Displays one room
     */
    void displayCRUD_Room(CRUD_Room*);

    /**
     * @brief Displays all the rooms of a list
     */
    void displayAllRooms(CRUD_Room*);

    /**
     * @brief Adds the given room to the rooms list
     * 
     * @param head first room of the list
     * @return int 1 if success, 0 otherwise
     */
    int addCRUD_Room(CRUD_Room* head, CRUD_Room* newROom);

    /**
     * @brief Removes the room with the given id from the list
     * 
     * @param head first room of the list
     * @param id id of the room to delete
     */
    void removeCRUD_Room(CRUD_Room** ptr_head, int id);

    /**
     * @brief Get the room corresponding the the given id
     * 
     * @param head first room of the list
     * @param id id of the room to get
     * 
     * @return CRUD_Room* id, NULL if not found
     */
    CRUD_Room* getCRUD_RoomById(CRUD_Room* head, int id);

    /**
     * @brief Duplicates a room
     * 
     * @return CRUD_Room 
     */
    CRUD_Room* duplicateCRUD_Room(CRUD_Room*);

    /**
     * @brief Desallocate memory allocated to one Room
     * 
     */
    void freeCRUD_Room(CRUD_Room*);

     /**
     * @brief Desallocate memory allocated to the all the rooms of a room list 
     * @param head first room of the list
     * @return 1 if success 0 otherwise
     */
    int freeAllRooms(CRUD_Room* head);

    /**
     * @brief Reorders the ids of rooms.
     * Use after a room deletion for example
     * @param head first room of the list
     */
    void arrangeRoomsIds(CRUD_Room* head);

    /**
     * @brief Returns the number of rooms in the rooms list 
     * @param head first room of the list
     * @return int number of rooms
     */
    int getRoomsListSize(CRUD_Room* head);


    

#endif