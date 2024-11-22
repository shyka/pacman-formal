#ifndef CUSTOM_FUNCTION
#define CUSTOM_FUNCTION

#include<stdio.h>

struct Level {
    char array[20][20];
};
char current_LevelMap[20][20];
struct Level map_N1 ={
    "####################",
    "#             $    #",
    "#                  #",
    "#        $         #",
    "#  #               #",
    "#           ..     #",
    "#           .      #",
    "#        ##        #",
    "#                  #",
    "#             #    #",
    "#     ......  #    #",
    "#   #              #",
    "###                #",
    "#   .     ..       #",
    "#                  #",
    "#     ......       #",
    "#                  #",
    "#     $            #",
    "#          ...     #",
    "####################"
};

int score = 0, heart = 3, level = 0;
char key1, key2, keyany;
enum selection1{NORMAL, INFINITE, QUIT, WRONG_KEY1, RULE_CHECK};
enum selection2{AGAIN, BACK_TO_MENU, ENDGAME, WRONG_KEY2};
enum MoveAction{UP, DOWN, RIGHT, LEFT};
enum MapItems {WALL = '#', GHOST = '@', DOT = '.', BIGDOT = '$', RECOVER = 'H'};


void MapRenew(void){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            printf("%2c ", current_LevelMap[i][j]);
            if(i == 0 && j == 19){
                printf("   score : %d", score);
            }
        }
        puts("");
    }
}

void charswap(char *a,char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}


void charreplace(char *a, char b){
    *a = b;
}

void stage_change(enum selection1 a, int b){
    switch(a){
        case NORMAL:{
            switch(b){
                case 1:{
                    for(int i = 0; i < 20; i++){
                        for(int j = 0; j < 20; j++){
                            current_LevelMap[i][j] = map_N1.array[i][j];
                        }
                    }
                }
                default: break;
            }
            break;
        }
        case INFINITE:{
            switch(b){
                case 1: break;
                default: break;
            }
            break;
        }
        default: break;
    }
}

#endif
