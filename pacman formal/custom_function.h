#ifndef CUSTOM_FUNCTION
#define CUSTOM_FUNCTION

#include<stdio.h>

struct Level {
    int ghost_number;
    char array[22][22];
};
int current_ghost_number;
int current_ghost_position_x[4];
int current_ghost_position_y[4];
char current_LevelMap[22][22];
struct Level map_N1 ={
    4,
    "####################",
    "#..................#",
    "#####          #####",
    "#                  #",
    "#  ##############  #",
    "#                  #",
    "#..................#",
    "#.  ###      ###  .#",
    "#.   . #      .   .#",
    "#.   .   .#   .   .#",
    "#.   .   #.   .   .#",
    "#.   .      # .   .#",
    "#.  ###      ###  .#",
    "#..................#",
    "#                  #",
    "#  ##############  #",
    "#                  #",
    "#####          #####",
    "#..................#",
    "####################"
};

int score = 0, heart = 3, level = 0;
int currentspot_x, currentspot_y, ghostspot_x, ghostspot_y;
enum selection1{NORMAL, INFINITE, QUIT, WRONG_KEY1, RULE_CHECK};
enum selection2{AGAIN, BACK_TO_MENU, ENDGAME, WRONG_KEY2};
enum MoveAction{UP, DOWN, RIGHT, LEFT, PAUSE};
enum MapItems {WALL = '#', GHOST = '@', DOT = '.', BIGDOT = '$', RECOVER = 'H'};


void MapRenew(void){ // renew current map information
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            printf("%2c ", current_LevelMap[i][j]);
            if(i == 0 && j == 19){
                printf("   score : %d", score);
            }
            if(i == 1 && j == 19){
                printf("   HP : %d", heart);
            }
        }
        puts("");
    }
}

void charswap(char *a,char *b){ // swap two char (a,b)
    char temp = *a;
    *a = *b;
    *b = temp;
}


void charreplace(char *a, char b){ // replace char a with char b
    *a = b;
}


void C_spawn(void){ // 隨機生成一開始遊玩的位置C（不會在‘＃’, '@'生成）
    while(1){
        currentspot_x = rand() % 20;
        currentspot_y = rand() % 20;
        if(current_LevelMap[currentspot_y][currentspot_x] != WALL && current_LevelMap[currentspot_y][currentspot_x] != GHOST){
            current_LevelMap[currentspot_y][currentspot_x] = 'C';
            break;
        }
    }
}


void GHOST_spawn(int a){ // 隨機生成一開始鬼魂的位置（不會在‘＃’, '@'生成), a變數表示生成鬼魂的數量
    for(int i = 0; i < a; i++){
        while(1){
            ghostspot_x = rand() % 20;
            ghostspot_y = rand() % 20;
            if(current_LevelMap[ghostspot_y][ghostspot_x] != WALL && current_LevelMap[ghostspot_y][ghostspot_x] != GHOST){
                current_LevelMap[ghostspot_y][ghostspot_x] = '@';
                current_ghost_position_x[i] = ghostspot_x;
                current_ghost_position_y[i] = ghostspot_y;
                break;
            }
        }
    }
}


void dot_logic_function(int *y, int *x){
    if(current_LevelMap[*y][*x] == DOT){
        charreplace(&current_LevelMap[*y][*x], ' ');
        score += 1;
    }
}


void ghost_logic_function(int *y, int *x, enum MoveAction action){
    switch(action){
        case UP:{
            if(current_LevelMap[*y - 1][*x] == GHOST){
                heart -= 1;
                charreplace(&current_LevelMap[*y][*x], ' ');
                C_spawn();
            }
            break;
        }
        case DOWN:{
            if(current_LevelMap[*y + 1][*x] == GHOST){
                heart -= 1;
                charreplace(&current_LevelMap[*y][*x], ' ');
                C_spawn();
            }
            break;
        }
        case RIGHT:{
            if(current_LevelMap[*y][*x + 1] == GHOST){
                heart -= 1;
                charreplace(&current_LevelMap[*y][*x], ' ');
                C_spawn();
            }
            break;
        }
        case LEFT:{
            if(current_LevelMap[*y][*x - 1] == GHOST){
                heart -= 1;
                charreplace(&current_LevelMap[*y][*x], ' ');
                C_spawn();
            }
            break;
        }
        default: break;
    }
}


void G_ghost_logic_function(int *y, int *x, enum MoveAction action){
    switch(action){
        case UP:{
            if(current_LevelMap[*y - 1][*x] == 'C'){
                heart -= 1;
                charreplace(&current_LevelMap[*y - 1][*x], ' ');
                C_spawn();
            }
            break;
        }
        case DOWN:{
            if(current_LevelMap[*y + 1][*x] == 'C'){
                heart -= 1;
                charreplace(&current_LevelMap[*y + 1][*x], ' ');
                C_spawn();
            }
            break;
        }
        case RIGHT:{
            if(current_LevelMap[*y][*x + 1] == 'C'){
                heart -= 1;
                charreplace(&current_LevelMap[*y][*x + 1], ' ');
                C_spawn();
            }
            break;
        }
        case LEFT:{
            if(current_LevelMap[*y][*x - 1] == 'C'){
                heart -= 1;
                charreplace(&current_LevelMap[*y][*x - 1], ' ');
                C_spawn();
            }
            break;
        }
        default: break;
    }
}


void stage_change(enum selection1 a, int b){
    switch(a){
        case NORMAL:{
            switch(b){
                case 1:{
                    current_ghost_number = map_N1.ghost_number;
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
