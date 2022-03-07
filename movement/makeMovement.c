#include <stdio.h>
#include "../structs/structs.h"
#include "../validators/misc.h"
#include "../validators/isMovementValid.h"
#include "throwObject.h"
#include "../validators/getCoords.h"
#include "../utils/utils.h"
#include "../outputs/printBoard.h"
#include "../modifiers/treasure.h"
#include "../modifiers/occupation.h"
#include "../modifiers/artifacts.h"

void makeMovement(Player *player, int status, BOARD){
    //instruction message  
    switch(status){
        case 0:
            printf("\nPlayer %d - %s - it's your turn! Please enter coordinates of amazon that you want to move: ", player->id, player->name); 
            break;
        case 1:
            printf("\nincorrect! - please enter correct coordinates: ");
            break;
        case 2:
            printf("\nyou are trying to move amazon of another player! - please enter correct coordinates: ");
            break;
        case 3:
            printf("\nincorrect movement, try again - enter coordinates of amazon that you want to move: ");
            break;
        case 4:
            printf("\nPlayer %d - %s - you got one more move! Please enter coordinates of amazon that you want to move: ", player->id, player->name);
            break;
    }

    //get coordinates from
    int fromRowNum, fromColNum;//1 indexed
    getCoords(&fromRowNum, &fromColNum, board->width, board->height);//1 indexed
    if (fromRowNum==-1 || fromColNum==-1){//1 indexed
        return makeMovement(player, 1, board);
    }
    
    //switching from coordinates to 0 indexed
    fromRowNum--;
    fromColNum--;

    //check if player wants to move his amazon (not sbdys)
    if(isPlayerOwner(fromColNum, fromRowNum, player->id, board)==0){
        return makeMovement(player, 2, board);
    }

    int toRowNum, toColNum;//1 indexed
    printf("\nplease enter coordinates to move amazon to: ");
    getCoords(&toRowNum, &toColNum, board->width, board->height);//1 indexed
    if (toRowNum==-1 || toColNum==-1){//1 indexed
        return makeMovement(player, 0, board);
    }
    
    toRowNum--;
    toColNum--;
    

    //checking if cell player want to move to is valid
    if(isCellFree(toRowNum, toColNum, board)==0){
        return makeMovement(player, 0, board);
    }

    //incorrect movement
    if(isMovementValid(fromColNum, fromRowNum, toColNum, toRowNum, board)==0){
        return makeMovement(player, 3, board);
    }

    //move player from cell to cell
    occupy(toRowNum, toColNum, player->id, board);
    removeOccupation(fromRowNum, fromColNum, board);

    //handle treasures
    int treasureValue = removeTreasureFromCell(toRowNum, toColNum, board);//removes treasure from board and returns value of treasure 
    addTreasureToPlayer(player, treasureValue);
    //printPlayer(player);


    //handle artifacts
    clrscr();//
    printBoard(board);

    int artifact = removeArtifactFromCell(toRowNum, toColNum, board);//removes artifact from board and returns value of artifact 

    switch(artifact){
        case 0://none
            throwObject(0, toRowNum, toColNum, board, player,0);//first arg: 0-arrow, 1-spear
            break;
        case 1://horse (shoot an arrow and move again)
            //TODO
            throwObject(0, toRowNum, toColNum, board, player,0);//first arg: 0-arrow, 1-spear
            clrscr();//
            printBoard(board);
            return makeMovement(player, 4, board);
            break;
        case 2://broken arrow
            //nothing to do here
            break;
        case 3://spear
            throwObject(1, toRowNum, toColNum, board, player,0);//first arg: 0-arrow, 1-spear
            break;
    }
}
