#include <stdio.h>
#include "../structs/structs.h"


void endGame(PlayerList *p){
    int most=0;
    int pid;
    for(int i=0;i<p->length;i++){
        if (p->list[i].score>most){
            most=p->list[i].score;
            pid = p->list[i].id;
        }
    }

    for(int i=0;i<p->length;i++){
        if (p->list[i].id==pid){
            printf("\n++++++++++ THE END ++++++++++\n");
            printf("Winner:%s\n", p->list[i].name);
            printf("Score:%d\n", p->list[i].score);
        }
    }
}