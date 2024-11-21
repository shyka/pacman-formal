#ifndef SHOWWORDS
#define SHOWWORDS

#include <stdio.h>

void show_words(int a){
    switch(a){
        case 1:{
            printf("\t\t\tPACMAN GAME!\n\n");
            printf("press the key to choose gameplay mode\n");
            printf("press '1' for normal mode\n");
            printf("press '2' for infinite mode\n");
            printf("press 'p' to quit the game\n");
            printf("press '?' to check the game rule\n");
            break;
        }
        case 2:{
            printf("\n// press any key to go back to main screen...\n");
            break;
        }
        default: break;
    }
}

#endif

