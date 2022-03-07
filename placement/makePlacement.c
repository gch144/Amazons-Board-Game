#include <stdio.h>
#include "../structs/structs.h"
#include "../validators/getCoords.h"
#include "../validators/misc.h"
#include "../modifiers/occupation.h"
#include "../modifiers/artifacts.h"

void makePlacement(Player *player, int status, BOARD){
    //instruction message
    switch(status){
        case 0:
            printf("\nPlayer %d - %s - it's your turn! Please enter coordinates of the cell you want to place amazon: ", player->id, player->name);
            break;
        case 1:
            printf("\nincorrect! - please enter correct coordinates: ");
            break;
        case 2:
            printf("\nthis cell is already occupied! - please enter correct coordinates: ");
            break;
    }

    //get coordinates
    int rowNum, colNum;//1 indexed
    getCoords(&rowNum, &colNum, board->width, board->height);//1 indexed
    //printf("col: %d, row: %d\n", colNum, rowNum);
    
    if (rowNum==-1 || colNum==-1){//1 indexed
        return makePlacement(player, 1, board);
    }
    
    //switching index from 1 to 0
    rowNum--;
    colNum--;

    //occupy coordinates
    if(isCellFree(rowNum, colNum, board)==1){
        //remove treasures and artifacts
        removeTreasuresAndArtifacts(rowNum, colNum, board);

        //occupy the cell with players id
        occupy(rowNum, colNum, player->id, board);

        //reduce players amazons left
        player->amazonsNotPlaced--;
    } else {
        //this cell is occupied
        return makePlacement(player, 2, board);
    }
}