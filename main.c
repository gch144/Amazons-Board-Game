#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//for sleep
#include "structs/structs.h"
#include "outputs/printBoard.h"
#include "outputs/endGame.h"
#include "utils/utils.h"
#include "movement/makeMovement.h"
#include "placement/makePlacement.h"
#include "placement/amazonsLeft.h"
#include "movement/switchToNextPlayer.h"
#include "validators/canMove.h"
#include "outputs/player.h"
#include "utils/fillBoard.h"
#include "utils/fillPlayers.h"


int main(){
    //board initialisation 
    Board board;

    //board filling
    fillBoard(&board);
    
    //players initialisation   
    PlayerList players;

    //players filling
    fillPlayers(&players);

    //placing amazons loop
    while(getTotalAmazonsLeft(players)){
        int uid = getPlayerIdWithMostAmazonsLeft(players);

        //getting player by id
        Player *player;
        for(int i=0;i<players.length;i++){
            if(players.list[i].id==uid){
                player=&players.list[i];
                break;
            }
        }

        clrscr();              
        printBoard(&board);
        makePlacement(player, 0, &board);
    }

    
    //game loop
    int currentPlayerId=1;
    while(canAnyPlayerMove(&players, &board)==1){
        clrscr();

        //getting player by id
        Player *player;
        for(int i=0;i<players.length;i++){
            if(players.list[i].id==currentPlayerId){
                player=&players.list[i];
                break;
            }
        }

        //ensuring that current player can move
        if(canPlayerMove(currentPlayerId, &board)==0){
            printf("\nPlayer %d - %s - can't move! Skipping to next player...\n", player->id, player->name);
            sleep(3);
            switchToNextPlayer(&currentPlayerId, players.length);
            continue;
        }

        printBoard(&board);

        makeMovement(player, 0, &board);

        switchToNextPlayer(&currentPlayerId, players.length);
    }

    //announce the winner
    endGame(&players);

    return 0;
}