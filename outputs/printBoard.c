#include <stdio.h>
#include "../structs/structs.h"

void printBoard(BOARD){
    //top row with column names
    printf("    ");
    for(int cell='A';cell<'A'+board->width;cell++){
            printf(" %c ", cell);
            printf(" ");
        }
    printf("\n");

    for (int row=0;row<board->height;row++){
        //row numbers
        if (row<9){
            printf(" %d  ", row+1);
        } else {
            printf(" %d ", row+1);
        }
        

        for(int cell=0;cell<board->width;cell++){
            printf("%d%d%d", board->btable[row][cell].treasure, board->btable[row][cell].artifact, board->btable[row][cell].occupation);
            printf(" ");
        }
        printf("\n");
    }
}