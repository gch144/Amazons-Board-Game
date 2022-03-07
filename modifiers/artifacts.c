#include "../structs/structs.h"

int removeArtifactFromCell(int row, int col, BOARD){//0 indexed
    int value = board->btable[row][col].artifact;
    board->btable[row][col].artifact = 0;
    return value;
}

int removeTreasuresAndArtifacts(int rowNum, int colNum, BOARD){//0 indexed
    board->btable[rowNum][colNum].treasure = 0;
    board->btable[rowNum][colNum].artifact = 0;
}