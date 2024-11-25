#ifndef CUSTOM_FUNCTION
#define CUSTOM_FUNCTION

#include<stdio.h>

struct Level {
    int ghost_number;
    int levelUP_score;
    char array[22][22];
};
int current_ghost_number;
int current_ghost_spot_x[8];
int current_ghost_spot_y[8];
char current_LevelMap[22][22];
struct Level map_N1 ={
    4, 40,
    "####################",
    "#..................#",
    "#####          #####",
    "#$                H#",
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
    "#H                $#",
    "#####          #####",
    "#..................#",
    "####################"
};
struct Level map_N2 ={
//    4, 40,
    "####################",
    "#H                 #",
    "#  ##    ##    ##  #",
    "#...     ##$    ...#",
    "#  ##############  #",
    "#......  ..  ......#",
    "#.  ###  ##  ###  .#",
    "#.  ###  ##  ###  .#",
    "#.   .        .   .#",
    "#..................#",
    "#.   .        .   .#",
    "#.  ###  ##  ###  .#",
    "#.  ###  ##  ###  .#",
    "#.                .#",
    "#......  ..  ......#",
    "#  ##############  #",
    "#...    $##     ...#",
    "#  ##    ##    ##  #",
    "#                 H#",
    "####################"
};
struct Level map_N3 ={
    4, 40,
    "####################",
    "#...#    ##    #...#",
    "#. ##    ##    ## .#",
    "#...     ##     ...#",
    "#  #####    #####  #",
    "#       ....       #",
    "#.  ### .... ###  .#",
    "#.  ###  ##  ###  .#",
    "#.   .        .   .#",
    "#$    ........     #",
    "#.   .        .   .#",
    "#.  ###  ##  ###  .#",
    "#.  ###  ##  ###  .#",
    "#.      ....      .#",
    "#       ....       #",
    "#  #####    #####  #",
    "#...     ##     ...#",
    "#. ##    ##    ## .#",
    "#...#    ##    #...#",
    "####################"
};
struct Level map_N4 ={
    5, 40,
    "####################",
    "# $##############$ #",
    "#  ##    ##    ##  #",
    "#...     ##     ...#",
    "#  ##  ######  ##  #",
    "#   ...  ..  ...   #",
    "#   ###..  ..###   #",
    "#   ###..##..###   #",
    "#    .        .    #",
    "#   .....  .....   #",
    "#    .   ##   .    #",
    "#   ###..##..###   #",
    "#   ###..##..###   #",
    "#   ...  ..  ...   #",
    "#......  ..  ......#",
    "#  ##  ######  ##  #",
    "#...     ##     ...#",
    "#  ##    ##    ##  #",
    "#  ##   H..    ##  #",
    "####################"
};

int score = 0, total_score = 0, heart = 3, level = 1, invincible_buffer = 0, invincible_step_remain = 0, Nmode = 0, Imode = 0;
int currentspot_x, currentspot_y, ghostspot_x, ghostspot_y, current_levelUP_score;
enum selection1{NORMAL, INFINITE, QUIT, WRONG_KEY1, RULE_CHECK};
enum selection2{AGAIN, BACK_TO_MENU, ENDGAME, WRONG_KEY2};
enum MoveAction{UP, DOWN, RIGHT, LEFT, PAUSE};
enum MapItems {WALL = '#', GHOST = '@', SGHOST = '!', DOT = '.', BIGDOT = '$', HEAL = 'H'};

void MapRenew(void){ // renew current map information
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            printf("%2c ", current_LevelMap[i][j]);
            if(i == 0 && j == 19){
                printf("   score : %d", score + total_score);
            }
            if(i == 1 && j == 19){
                printf("   HP : %d", heart);
            }
            if(i == 2 && j == 19){
                printf("   remain ghost : %d", current_ghost_number);
            }
            if(i == 5 && j == 19 && invincible_buffer == 1){
                printf("   super buff : %d steps remain", invincible_step_remain);
            }
            if(i == 16 && j == 19 && Nmode == 1){
                printf("   MODE : NORMAL");
            }
            if(i == 16 && j == 19 && Imode == 1){
                printf("   MODE : INFINITY");
            }
            if(i == 17 && j == 19 && Nmode == 1){
                printf("   LEVEL : %d", level);
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
        if(current_LevelMap[currentspot_y][currentspot_x] != WALL
           && current_LevelMap[currentspot_y][currentspot_x] != GHOST
           && current_LevelMap[currentspot_y][currentspot_x] != DOT
           && current_LevelMap[currentspot_y][currentspot_x] != BIGDOT){
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
            if(current_LevelMap[ghostspot_y][ghostspot_x] != 'C'
               && current_LevelMap[ghostspot_y][ghostspot_x] != WALL
               && current_LevelMap[ghostspot_y][ghostspot_x] != GHOST
               && current_LevelMap[ghostspot_y][ghostspot_x] != DOT
               && current_LevelMap[ghostspot_y][ghostspot_x] != BIGDOT){
                current_LevelMap[ghostspot_y][ghostspot_x] = '@';
                current_ghost_spot_x[i] = ghostspot_x;
                current_ghost_spot_y[i] = ghostspot_y;
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


void bigdot_logic_function(int *y, int *x){
    if(current_LevelMap[*y][*x] == BIGDOT){
        charreplace(&current_LevelMap[*y][*x], ' ');
        invincible_buffer = 1;
        invincible_step_remain = 31;
        score += 3;
    }
}


void heal_logic_function(int *y, int *x){
    if(current_LevelMap[*y][*x] == HEAL){
        charreplace(&current_LevelMap[*y][*x], ' ');
        heart += 1;
    }
}


void invincible_logic_function(int *y, int *x, enum MoveAction action){
    if(invincible_buffer == 1){
        for(int i = 0; i < current_ghost_number; i++){
            charreplace(&current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i]], '!');
        }
        if(current_LevelMap[*y][*x] == '!'){
            charreplace(&current_LevelMap[*y][*x], ' ');
            int target_sghostspot_x = 0, target_sghostspot_y = 0, checker = 0;
            switch(action){
                case UP: target_sghostspot_x = *x; target_sghostspot_y = *y - 1; charreplace(&current_LevelMap[*y - 1][*x], 'C'); break;
                case DOWN: target_sghostspot_x = *x; target_sghostspot_y = *y + 1; charreplace(&current_LevelMap[*y + 1][*x], 'C');break;
                case RIGHT: target_sghostspot_x = *x + 1; target_sghostspot_y = *y; charreplace(&current_LevelMap[*y][*x + 1], 'C');break;
                case LEFT: target_sghostspot_x = *x - 1; target_sghostspot_y = *y; charreplace(&current_LevelMap[*y][*x - 1], 'C');break;
                default: break;
            }
            for(int i = 0; i < current_ghost_number; i++){
                if(current_ghost_spot_x[i] == target_sghostspot_x && current_ghost_spot_y[i] == target_sghostspot_y){
                    checker = i;
                    break;
                }
            }
            for(int i = checker; i < current_ghost_number - 1; i++){
                current_ghost_spot_x[i] = current_ghost_spot_x[i + 1];
                current_ghost_spot_y[i] = current_ghost_spot_y[i + 1];
            }
            current_ghost_number -= 1;
            score += 2;
        }
    }
    if(invincible_step_remain > 0){
        invincible_step_remain -= 1;
        if(invincible_step_remain <= 0){
            invincible_buffer = 0;
            for(int i = 0; i < current_ghost_number; i++){
                charreplace(&current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i]], '@');
            }
        }
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
    if(invincible_buffer == 0){
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
}


void stage_change(enum selection1 a, int b){
    switch(a){
        case NORMAL:{
            switch(b){
                case 1:{
                    current_ghost_number = map_N1.ghost_number;
                    current_levelUP_score = map_N1.levelUP_score;
                    for(int i = 0; i < 20; i++){
                        for(int j = 0; j < 20; j++){
                            current_LevelMap[i][j] = map_N1.array[i][j];
                        }
                    }
                    break;
                }
                case 2:{
                    current_ghost_number = map_N2.ghost_number;
                    current_levelUP_score = map_N2.levelUP_score;
                    for(int i = 0; i < 20; i++){
                        for(int j = 0; j < 20; j++){
                            current_LevelMap[i][j] = map_N2.array[i][j];
                        }
                    }
                    break;
                }
                case 3:{
                    current_ghost_number = map_N3.ghost_number;
                    current_levelUP_score = map_N3.levelUP_score;
                    for(int i = 0; i < 20; i++){
                        for(int j = 0; j < 20; j++){
                            current_LevelMap[i][j] = map_N3.array[i][j];
                        }
                    }
                    break;
                }
                case 4:{
                    current_ghost_number = map_N4.ghost_number;
                    current_levelUP_score = map_N4.levelUP_score;
                    for(int i = 0; i < 20; i++){
                        for(int j = 0; j < 20; j++){
                            current_LevelMap[i][j] = map_N4.array[i][j];
                        }
                    }
                    break;
                }
                default: break;
            }
            Nmode = 1;
            Imode = 0;
            break;
        }
        case INFINITE:{
            switch(b){
                case 1: break;
                default: break;
            }
            Nmode = 0;
            Imode = 1;
            break;
        }
        default: break;
    }
}


#endif
