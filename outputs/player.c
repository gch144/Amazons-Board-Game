#include <stdio.h>
#include "../structs/structs.h"

void printPlayer(Player *player){
    printf("Player %d - %s | score: %d | amazons not placed: %d\n", player->id, player->name, player->score, player->amazonsNotPlaced);
}

void listPlayers(PlayerList *Players){
    for(int i=0;i<Players->length;i++){
        //printf("Player %d - %s | score: %d | amazons not placed: %d\n", p[i].id, p[i].name, p[i].score, p[i].amazonsNotPlaced);
        printPlayer(&Players->list[i]);
    }
}