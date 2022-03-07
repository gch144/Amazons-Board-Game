#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../structs/structs.h"

void fillBoard(BOARD){  
    int inputHeight = -1;
    while(inputHeight<1){
        printf("Please input height of the board \n");
        scanf("%d", &inputHeight);
        if(inputHeight<1){
            printf("Height cannot be less than 1!\n");
        }
    }
    board->height = inputHeight;
    
    int inputWidth = -1;
    while(inputWidth<1){
        printf("Please input width of the board \n");
        scanf("%d", &inputWidth);
        if(inputWidth<1){
            printf("Width cannot be less than 1!\n");
        }
    }
    board->width = inputWidth;
    
    board->btable = malloc(sizeof(Cell) * board->height);
    srand(time(0)); 
    for (int row=0;row<board->height;row++){
        board->btable[row] = malloc(sizeof(Cell) * board->width);
        for(int cell=0;cell<board->width;cell++){
            //(rand() % 6); //random value between 0-5

            //this makes zeros appear more often
            int randomTreasure = (rand() % 15);
            if (randomTreasure>5){
                randomTreasure=0;
            }

            int randomArtifact = (rand() % 15);
            if (randomArtifact>3){
                randomArtifact=0;
            }
              
            board->btable[row][cell].treasure = randomTreasure;
            board->btable[row][cell].artifact = randomArtifact;
            board->btable[row][cell].occupation = 0;
        }
    }
}