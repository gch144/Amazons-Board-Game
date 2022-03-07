int switchToNextPlayer(int *pid, int maxlen){
    if((*pid)<maxlen){
        //printf("++\n");
        (*pid)++;
    } else {
        //printf("reset to 1\n");
        (*pid)=1;
    }
}