#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "../structs/structs.h"

void fillPlayers(PlayerList *Players){
    int inputPlayersLength = -1;
    while(inputPlayersLength<1){
        printf("How many players want to play the game? \n");
        scanf("%d", &inputPlayersLength);
        if(inputPlayersLength<1){
            printf("Amount of players cannot be less than 1!\n");
        }
    }
    Players->length = inputPlayersLength;
    Players->list = malloc(sizeof(Player)*Players->length);

    
    int numOfAmazons = -1;
    while(numOfAmazons<1){
        printf("How many amazons should each player have? \n");
        scanf("%d", &numOfAmazons);
        if(numOfAmazons<1){
            printf("Number of amazons per player cannot be less than 1!\n");
        }
    }

    for(int p=0;p<Players->length;p++){
            Players->list[p].id = p+1;
            Players->list[p].score = 0;
            Players->list[p].amazonsNotPlaced = numOfAmazons;

            clrscr();
            printf("Please enter a name for Player %d: ", Players->list[p].id);
            scanf("%s", Players->list[p].name);
    }
}