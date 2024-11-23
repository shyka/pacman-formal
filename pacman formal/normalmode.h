#ifndef NORMALMODE
#define NORMALMODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "custom_function.h"

void normal_mode(void){
    
    //value initialization and map generation
    srand(time(NULL));
    score = 0;
    heart = 3;
    level = 1;
    stage_change(NORMAL, level);
    C_spawn();
    GHOST_spawn(current_ghost_number);
    puts("");
    MapRenew();
    
    //pacman moving
    char key;
    int step_checker_x = currentspot_x, step_checker_y = currentspot_y;
    enum MoveAction C_move_number, GHOST_move_number;
   
    while((key = getchar()) != 'p'){
        
        // 輸入'w''a''s''d'移動pacman
        printf("\n\n");
        switch(key){
            case 'a': C_move_number = LEFT; break;
            case 's': C_move_number = DOWN; break;
            case 'd': C_move_number = RIGHT; break;
            case 'w': C_move_number = UP; break;
            case 'p': C_move_number = PAUSE; break;
            default: C_move_number = 100; break;
        }
        
        switch(C_move_number){ // 根據輸入的鍵，決定pacman下一步的移動方向和行為
            case UP:{ // 上移
                ghost_logic_function(&step_checker_y, &step_checker_x, UP); // detect '@' and execute its logic function
                step_checker_x = currentspot_x; // renew step_checker
                step_checker_y = currentspot_y;
                if(current_LevelMap[step_checker_y - 1][step_checker_x] != WALL && current_LevelMap[step_checker_y - 1][step_checker_x] != GHOST){
                    //if next step don't encounter with WALL or GHOST, swap 'C' to next spot
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y - 1][currentspot_x]);
                    dot_logic_function(&step_checker_y, &step_checker_x); // detect '.' and execute its logic function
                    currentspot_y -= 1;
                    step_checker_x = currentspot_x; //renew step_cheker
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case DOWN:{ // 下移
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
            case RIGHT:{ //右移
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
            case LEFT:{ // 左移
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
            case PAUSE: break;
            default: break;
        }
        
        // 決定鬼魂的移動模式
        for(int i = 0; i < current_ghost_number; i++){
            int random_move_key = rand() % 4;
            switch(random_move_key){
                case 0: GHOST_move_number = LEFT; break;
                case 1: GHOST_move_number = DOWN; break;
                case 2: GHOST_move_number = RIGHT; break;
                case 3: GHOST_move_number = UP; break;
                default: GHOST_move_number = 100; break;
            }
            
            switch(GHOST_move_number){
                case UP:{ //上移
                    if(current_LevelMap[current_ghost_position_y[i] - 1][current_ghost_position_x[i]] != WALL && current_LevelMap[current_ghost_position_y[i] - 1][current_ghost_position_x[i]] != GHOST){
                        //if next step don't encounter with WALL or GHOST, swap '@' to next spot
                        G_ghost_logic_function(&current_ghost_position_y[i], &current_ghost_position_x[i], UP); // execute its logic function if ghost move to pacman
                        step_checker_x = currentspot_x; // renew step_checker
                        step_checker_y = currentspot_y;
                        charswap(&current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i]], &current_LevelMap[current_ghost_position_y[i] - 1][current_ghost_position_x[i]]);
                        current_ghost_position_y[i] -= 1;
                    }
                    break;
                }
                case DOWN:{ //下移
                    if(current_LevelMap[current_ghost_position_y[i] + 1][current_ghost_position_x[i]] != WALL && current_LevelMap[current_ghost_position_y[i] + 1][current_ghost_position_x[i]] != GHOST){
                        G_ghost_logic_function(&current_ghost_position_y[i], &current_ghost_position_x[i], DOWN); // execute its logic function if ghost move to pacman
                        step_checker_x = currentspot_x; // renew step_checker
                        step_checker_y = currentspot_y;
                        charswap(&current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i]], &current_LevelMap[current_ghost_position_y[i] + 1][current_ghost_position_x[i]]);
                        current_ghost_position_y[i] += 1;
                    }
                    break;
                }
                case RIGHT:{ //右移
                    if(current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i] + 1] != WALL && current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i] + 1] != GHOST){
                        G_ghost_logic_function(&current_ghost_position_y[i], &current_ghost_position_x[i], RIGHT); // execute its logic function if ghost move to pacman
                        step_checker_x = currentspot_x; // renew step_checker
                        step_checker_y = currentspot_y;
                        charswap(&current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i]], &current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i] + 1]);
                        current_ghost_position_x[i] += 1;
                    }
                    break;
                }
                case LEFT:{ // 左移
                    if(current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i] - 1] != WALL && current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i] - 1] != GHOST){
                        G_ghost_logic_function(&current_ghost_position_y[i], &current_ghost_position_x[i], LEFT); // execute its logic function if ghost move to pacman
                        step_checker_x = currentspot_x; // renew step_checker
                        step_checker_y = currentspot_y;
                        charswap(&current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i]], &current_LevelMap[current_ghost_position_y[i]][current_ghost_position_x[i] - 1]);
                        current_ghost_position_x[i] -= 1;
                    }
                    break;
                }
                default: break;
            }
        }
        MapRenew();
    }
}


#endif
