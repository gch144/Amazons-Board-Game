#ifndef FILEINPUT_H
#define FILEINPUT_H

int mapFileToBoardState(Board *board, char fileName[256]);
int mapFileToPlayerState(PlayerList *Players, char fileName[256]);

#endif // !FILEINPUT_H