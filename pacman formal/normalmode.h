#ifndef NORMALMODE
#define NORMALMODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "custom_function.h"

void normal_mode(void){
    srand(time(NULL));
    score = 0;
    heart = 3;
    level = 1;
    stage_change(NORMAL, level);
    for(int i = 0; i < 4; i++){
        while(1){
            ghostspot_x = rand() % 20;
            ghostspot_y = rand() % 20;
            if(current_LevelMap[ghostspot_y][ghostspot_x] != WALL && current_LevelMap[ghostspot_y][ghostspot_x] != GHOST){
                current_LevelMap[ghostspot_y][ghostspot_y] = '@'; // 隨機生成一開始鬼魂的位置（不會在‘＃’, '@'生成）
                break;
            }
        }
    }
    while(1){
        currentspot_x = rand() % 20;
        currentspot_y = rand() % 20;
        if(current_LevelMap[currentspot_y][currentspot_x] != WALL && current_LevelMap[currentspot_y][currentspot_x] != GHOST){
            current_LevelMap[currentspot_y][currentspot_x] = 'C'; // 隨機生成一開始遊玩的位置C（不會在‘＃’, '@'生成）
            break;
        }
    }
    puts("");
    MapRenew();
    
    //pacman moving
    char key;
    int step_checker_x = currentspot_x, step_checker_y = currentspot_y;
    enum MoveAction move_number;
   
    while((key = getchar()) != 'p'){
        printf("\n\n");
        switch(key){
            case 'a': move_number = LEFT; break;
            case 's': move_number = DOWN; break;
            case 'd': move_number = RIGHT; break;
            case 'w': move_number = UP; break;
            case 'p': move_number = PAUSE; break;
            default: move_number = 100; break;
        }
        
        switch(move_number){
            case UP:{
                ghost_logic_function(&step_checker_y, &step_checker_x, UP); // detect '@' and execute its logic function
                step_checker_x = currentspot_x;
                step_checker_y = currentspot_y;
                if(current_LevelMap[step_checker_y - 1][step_checker_x] != WALL && current_LevelMap[step_checker_y - 1][step_checker_x] != GHOST){
                    //if next step don't encounter with WALL or GHOST, swap 'C' to next spot
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y - 1][currentspot_x]);
                    dot_logic_function(&step_checker_y, &step_checker_x); // detect '.' and execute its logic function
                    currentspot_y -= 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case DOWN:{
                ghost_logic_function(&step_checker_y, &step_checker_x, DOWN);
                step_checker_x = currentspot_x;
                step_checker_y = currentspot_y;
                if(current_LevelMap[step_checker_y + 1][step_checker_x] != WALL && current_LevelMap[step_checker_y + 1][step_checker_x] != GHOST){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y + 1][currentspot_x]);
                    dot_logic_function(&step_checker_y, &step_checker_x);
                    currentspot_y += 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case RIGHT:{
                ghost_logic_function(&step_checker_y, &step_checker_x, RIGHT);
                step_checker_x = currentspot_x;
                step_checker_y = currentspot_y;
                if(current_LevelMap[step_checker_y][step_checker_x + 1] != WALL && current_LevelMap[step_checker_y][step_checker_x + 1] != GHOST){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y][currentspot_x + 1]);
                    dot_logic_function(&step_checker_y, &step_checker_x);
                    currentspot_x += 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case LEFT:{
                ghost_logic_function(&step_checker_y, &step_checker_x, LEFT);
                step_checker_x = currentspot_x;
                step_checker_y = currentspot_y;
                if(current_LevelMap[step_checker_y][step_checker_x - 1] != WALL && current_LevelMap[step_checker_y][step_checker_x - 1] != GHOST){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y][currentspot_x - 1]);
                    dot_logic_function(&step_checker_y, &step_checker_x);
                    currentspot_x -= 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case PAUSE:{
                break;
            }
            default: break;
        }
        MapRenew();
    }
}


#endif
