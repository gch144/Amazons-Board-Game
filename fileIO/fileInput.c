#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../structs/structs.h"
#include <sys/types.h>


/**
 * @brief getline implementation by Antti Haapala - https://stackoverflow.com/a/47229318/8144868 - it is needed when compiling to .exe file
 * @param lineptr 
 * @param n 
 * @param stream 
 * @return ssize_t 
 */
ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    size_t pos;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL) {
        return -1;
    }

    c = getc(stream);
    if (c == EOF) {
        return -1;
    }

    if (*lineptr == NULL) {
        *lineptr = malloc(128);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = 128;
    }

    pos = 0;
    while(c != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n + (*n >> 2);
            if (new_size < 128) {
                new_size = 128;
            }
            char *new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        ((unsigned char *)(*lineptr))[pos ++] = c;
        if (c == '\n') {
            break;
        }
        c = getc(stream);
    }

    (*lineptr)[pos] = '\0';
    return pos;
}

int mapFileToBoardState(BOARD, char fileName[256]){
    FILE *fptr;
    fptr = fopen(fileName,"r");
    
    int height, width;
    
    fscanf(fptr,"%d", &height);
    fscanf(fptr,"%d", &width);
    
    if(width<1 || height<1 || width>256 || height>256){
        printf("incorrect dimensions of the board\n");
        return 2;
    }
    
    board->height = height;
    board->width = width;
    
    board->btable = malloc(sizeof(Player) * board->height);
    
    fseek(fptr, 0, SEEK_SET);
    
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    int lineIndex=0;
    int row=0;
    while ((read = getline(&line, &len, fptr)) != -1) {
        if(lineIndex==0){
            lineIndex++;
            continue;
        }
        if(lineIndex==board->height+1){
            break;
        }
        
        board->btable[row] = malloc(sizeof(Player) * board->width);
        
        int expectedLineLength = board->width*3 + board->width-1;
        
        int charIndex=0;
        for(int cell=0;cell<board->width;cell++){
            int treasure = line[charIndex+0]-'0';
            int artifact = line[charIndex+1]-'0';
            int occupation = line[charIndex+2]-'0';
            
            if(treasure>5 || treasure <0 || artifact>3 || artifact <0 || occupation>9 || occupation <0){
                printf("incorrect cell value\n");
                return 2;
            }
            
            board->btable[row][cell].treasure = treasure;
            board->btable[row][cell].artifact = artifact;
            board->btable[row][cell].occupation = occupation;
            
            charIndex+=4;
        }
        
        lineIndex++;
        row++;
    }
    fclose(fptr); 
    return 0;
}

int mapFileToPlayerState(PlayerList *Players, char fileName[256]){
    FILE *fptr;
    fptr = fopen(fileName,"a+");
    
    int height;
    
    fscanf(fptr,"%d", &height);
    
    if(height<1 || height>256){
        printf("incorrect dimensions of the board\n");
        return 2;
    }
    
    fseek(fptr, 0, SEEK_SET);
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    Players->length = 8;//max number of players
    Players->list = malloc(sizeof(Player)*Players->length);
    
    int amountOfPlayers = 0; 
    int lineIndex=0;
    int ourPlayerIsPresent = 0;
    int lastPlayerId;
    while ((read = getline(&line, &len, fptr)) != -1) {
        if(lineIndex<height){
            lineIndex++;
            continue;
        }
        if(lineIndex==height+8){
            break;
        }
        printf("line index:%d %d\n", lineIndex, line[0]);
        //parse line
        char playerName[15];
        fscanf(fptr,"%s", playerName);
        
        
        int playerId;
        fscanf(fptr,"%d", &playerId);
        
        int numberOfPoints;
        fscanf(fptr,"%d", &numberOfPoints);
        
        if(playerId>8 || playerId<0){
            printf("incorrect player id - %d\n", playerId);
            return 2;
        }
        
        if(numberOfPoints<0){
            printf("incorrect number of points - %d\n", numberOfPoints);
            return 2;
        }
        
        if(strcmp(playerName, PLAYER_NICKNAME)==0){
            //our player is present
            ourPlayerIsPresent=1;
        }
        
        strcpy(Players->list[amountOfPlayers].name, playerName);
        Players->list[amountOfPlayers].id = playerId;
        Players->list[amountOfPlayers].score = numberOfPoints;
        //temporary
        Players->list[amountOfPlayers].amazonsNotPlaced = 0;
        
        lastPlayerId = playerId;
        
        
        
        amountOfPlayers++;
        lineIndex++;
    }
    Players->length = amountOfPlayers;

    if(ourPlayerIsPresent==0){
//        fprintf(fptr, "\n%s %d %d", PLAYER_NICKNAME, lastPlayerId+1, 0);
        Players->length = (amountOfPlayers + 1);
        strcpy(Players->list[amountOfPlayers].name, PLAYER_NICKNAME);
        Players->list[amountOfPlayers].id = (lastPlayerId + 1);
        Players->list[amountOfPlayers].score = 0;
        Players->list[amountOfPlayers].amazonsNotPlaced = 0;
    }
    
    fclose(fptr); 
    return 0;
}