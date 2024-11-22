#ifndef NORMALMODE
#define NORMALMODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "custom_function.h"

void normal_mode(void){
    int currentspot_x, currentspot_y;
    srand(time(NULL));
    
    level = 1;
    stage_change(NORMAL, level);
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
            default: move_number = 100; break;
        }
        switch(move_number){
            case UP:{
                if(current_LevelMap[step_checker_y - 1][step_checker_x] != WALL){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y - 1][currentspot_x]);
                    if(current_LevelMap[step_checker_y][step_checker_x] == DOT){
                        charreplace(&current_LevelMap[step_checker_y][step_checker_x], ' ');
                        score += 1;
                    }
                    currentspot_y -= 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case DOWN:{
                if(current_LevelMap[step_checker_y + 1][step_checker_x] != WALL){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y + 1][currentspot_x]);
                    if(current_LevelMap[step_checker_y][step_checker_x] == DOT){
                        charreplace(&current_LevelMap[step_checker_y][step_checker_x], ' ');
                        score += 1;
                    }
                    currentspot_y += 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case RIGHT:{
                if(current_LevelMap[step_checker_y][step_checker_x + 1] != WALL){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y][currentspot_x + 1]);
                    if(current_LevelMap[step_checker_y][step_checker_x] == DOT){
                        charreplace(&current_LevelMap[step_checker_y][step_checker_x], ' ');
                        score += 1;
                    }
                    currentspot_x += 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case LEFT:{
                if(current_LevelMap[step_checker_y][step_checker_x - 1] != WALL){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y][currentspot_x - 1]);
                    if(current_LevelMap[step_checker_y][step_checker_x] == DOT){
                        charreplace(&current_LevelMap[step_checker_y][step_checker_x], ' ');
                        score += 1;
                    }
                    currentspot_x -= 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            default: break;
        }
        MapRenew();
    }
}


#endif
