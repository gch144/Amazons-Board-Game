#include <stdio.h>
#include "../structs/structs.h"

int saveStateToFile(BOARD, PlayerList *Players, char fileName[256]){
    FILE *fptr;
    fptr = fopen(fileName,"w");
    
    //1st line with board dimensions
    fprintf(fptr,"%d %d\n",board->height, board->width);
    
    //board
    for(int row=0;row<board->height;row++){
        for(int cell=0;cell<board->width;cell++){
            fprintf(fptr, "%d%d%d", board->btable[row][cell].treasure, board->btable[row][cell].artifact, board->btable[row][cell].occupation);
            fprintf(fptr, " ");
        }
        fprintf(fptr, "\n");
    }
    
    //players
    for(int i=0;i<Players->length;i++){
        fprintf(fptr, "%s %d %d\n", Players->list[i].name, Players->list[i].id, Players->list[i].score);
    }
    
    fclose(fptr); 
    return 0;
}