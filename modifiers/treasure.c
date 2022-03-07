#include "../structs/structs.h"

int removeTreasureFromCell(int row, int col, BOARD){//0 indexed
    int value = board->btable[row][col].treasure;
    board->btable[row][col].treasure = 0;
    return value;
}

int addTreasureToPlayer(Player *player, int val){
    player->score+=val;
}