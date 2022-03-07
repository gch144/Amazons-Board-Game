#include <stdlib.h>

//clear the screen
void clrscr(){
    #ifdef OS_Windows
    //system("cls");
    #else
    //system("clear");
    #endif    
}