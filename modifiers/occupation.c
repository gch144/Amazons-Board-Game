#include "../structs/structs.h"

int occupy(int rowNum, int colNum, int playerId, BOARD){//0 indexed
    board->btable[rowNum][colNum].occupation = playerId;
}

int removeOccupation(int rowNum, int colNum, BOARD){//0 indexed
    board->btable[rowNum][colNum].occupation = 0;
}