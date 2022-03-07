#include "../structs/structs.h"

int getTotalAmazonsLeft(PlayerList p){
    int total = 0;
    for(int i=0;i<p.length;i++){
        total+=p.list[i].amazonsNotPlaced;
    }
    return total;
}

int getPlayerIdWithMostAmazonsLeft(PlayerList p){
    int id;
    int most = 0;

    for(int i=0;i<p.length;i++){
        if(p.list[i].amazonsNotPlaced>most){
            most=p.list[i].amazonsNotPlaced;
            id=p.list[i].id;
        }
    }
    return id;
}