#ifndef INFINITYMODE
#define INFINITYMODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "custom_function.h"

void infinity_mode(void){
    
    //value initialization and map generation
    srand(time(NULL));
    step_count = 0;
    score = 0;
    total_score = 0;
    heart = 3;
    level = 1;
    wight_LevelUP = 0;
    wight_ghost_number = 0;
    wight_invincible_step = 0;
    invincible_buffer = 0;
    invincible_step_remain = 0;
    stage_change(INFINITE, level);
    C_spawn();
    GHOST_spawn(current_ghost_number);
    I_RNGitmes_spawn();
    puts("\n");
    MapRenew();
    
    //pacman moving
    char key;
    int step_checker_x = currentspot_x, step_checker_y = currentspot_y, key_a_buff = 0;
    enum MoveAction C_move_number, GHOST_move_number;
   
    while((key = getchar()) != ''){
        
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
        
        step_checker_x = currentspot_x; // renew step_checker
        step_checker_y = currentspot_y;
        switch(C_move_number){ // 根據輸入的鍵，決定pacman下一步的移動方向和行為
            case UP:{ // 上移
                step_count += 1; // 計算以移動的步數
                ghost_logic_function(&step_checker_y, &step_checker_x, UP); // detect '@' and execute its logic function
                step_checker_x = currentspot_x; // renew step_checker
                step_checker_y = currentspot_y;
                if(current_LevelMap[step_checker_y - 1][step_checker_x] != WALL
                   && current_LevelMap[step_checker_y - 1][step_checker_x] != GHOST){
                    //if next step don't encounter with WALL or GHOST, swap 'C' to next spot
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y - 1][currentspot_x]);
                    dot_logic_function(&step_checker_y, &step_checker_x); // detect '.' and execute its logic function
                    bigdot_logic_function(&step_checker_y, &step_checker_x); // detect '$' and execute its logic function
                    heal_logic_function(&step_checker_y, &step_checker_x); // detect 'H' and execute its logic function
                    poision_logic_function(&step_checker_y, &step_checker_x); // detect 'P' and execute its logic function
                    invincible_logic_function(&step_checker_y, &step_checker_x, UP); // execute its logic function when pacman has super buff
                    currentspot_y -= 1;
                    step_checker_x = currentspot_x; //renew step_cheker
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case DOWN:{ // 下移
                step_count += 1;
                ghost_logic_function(&step_checker_y, &step_checker_x, DOWN);
                step_checker_x = currentspot_x;
                step_checker_y = currentspot_y;
                if(current_LevelMap[step_checker_y + 1][step_checker_x] != WALL
                   && current_LevelMap[step_checker_y + 1][step_checker_x] != GHOST){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y + 1][currentspot_x]);
                    dot_logic_function(&step_checker_y, &step_checker_x);
                    bigdot_logic_function(&step_checker_y, &step_checker_x);
                    heal_logic_function(&step_checker_y, &step_checker_x);
                    poision_logic_function(&step_checker_y, &step_checker_x);
                    invincible_logic_function(&step_checker_y, &step_checker_x, DOWN);
                    currentspot_y += 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case RIGHT:{ //右移
                step_count += 1;
                ghost_logic_function(&step_checker_y, &step_checker_x, RIGHT);
                step_checker_x = currentspot_x;
                step_checker_y = currentspot_y;
                if(current_LevelMap[step_checker_y][step_checker_x + 1] != WALL
                   && current_LevelMap[step_checker_y][step_checker_x + 1] != GHOST){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y][currentspot_x + 1]);
                    dot_logic_function(&step_checker_y, &step_checker_x);
                    bigdot_logic_function(&step_checker_y, &step_checker_x);
                    heal_logic_function(&step_checker_y, &step_checker_x);
                    poision_logic_function(&step_checker_y, &step_checker_x);
                    invincible_logic_function(&step_checker_y, &step_checker_x, RIGHT);
                    currentspot_x += 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case LEFT:{ // 左移
                step_count += 1;
                ghost_logic_function(&step_checker_y, &step_checker_x, LEFT);
                step_checker_x = currentspot_x;
                step_checker_y = currentspot_y;
                if(current_LevelMap[step_checker_y][step_checker_x - 1] != WALL
                   && current_LevelMap[step_checker_y][step_checker_x - 1] != GHOST){
                    charswap(&current_LevelMap[currentspot_y][currentspot_x], &current_LevelMap[currentspot_y][currentspot_x - 1]);
                    dot_logic_function(&step_checker_y, &step_checker_x);
                    bigdot_logic_function(&step_checker_y, &step_checker_x);
                    heal_logic_function(&step_checker_y, &step_checker_x);
                    poision_logic_function(&step_checker_y, &step_checker_x);
                    invincible_logic_function(&step_checker_y, &step_checker_x, LEFT);
                    currentspot_x -= 1;
                    step_checker_x = currentspot_x;
                    step_checker_y = currentspot_y;
                }
                break;
            }
            case PAUSE:{
                char key_a;
                show_words(4);
                while((key_a = getchar()) == 'p'){
                    puts("");
                    goto that; // press 'p' to go back the game
                }
                key_a_buff = 1; // press any key then quit
                break;
            }
            default: break;
        }
        
        if(key_a_buff == 1){
            show_words(3);
            break;
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
                    if(current_LevelMap[current_ghost_spot_y[i] - 1][current_ghost_spot_x[i]] != WALL
                       && current_LevelMap[current_ghost_spot_y[i] - 1][current_ghost_spot_x[i]] != GHOST
                       && current_LevelMap[current_ghost_spot_y[i] - 1][current_ghost_spot_x[i]] != SGHOST){
                        //if next step don't encounter with WALL or GHOST, swap '@' to next spot
                        G_ghost_logic_function(&current_ghost_spot_y[i], &current_ghost_spot_x[i], UP); // execute its logic function if ghost move to pacman
                        step_checker_x = currentspot_x; // renew step_checker
                        step_checker_y = currentspot_y;
                        if(current_LevelMap[current_ghost_spot_y[i] - 1][current_ghost_spot_x[i]] != 'C'){
                            charswap(&current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i]],
                                     &current_LevelMap[current_ghost_spot_y[i] - 1][current_ghost_spot_x[i]]);
                            current_ghost_spot_y[i] -= 1;
                        }
                    }
                    break;
                }
                case DOWN:{ //下移
                    if(current_LevelMap[current_ghost_spot_y[i] + 1][current_ghost_spot_x[i]] != WALL
                       && current_LevelMap[current_ghost_spot_y[i] + 1][current_ghost_spot_x[i]] != GHOST
                       && current_LevelMap[current_ghost_spot_y[i] + 1][current_ghost_spot_x[i]] != SGHOST){
                        G_ghost_logic_function(&current_ghost_spot_y[i], &current_ghost_spot_x[i], DOWN);
                        step_checker_x = currentspot_x;
                        step_checker_y = currentspot_y;
                        if(current_LevelMap[current_ghost_spot_y[i] + 1][current_ghost_spot_x[i]] != 'C'){
                            charswap(&current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i]],
                                     &current_LevelMap[current_ghost_spot_y[i] + 1][current_ghost_spot_x[i]]);
                            current_ghost_spot_y[i] += 1;
                        }
                    }
                    break;
                }
                case RIGHT:{ //右移
                    if(current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] + 1] != WALL
                       && current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] + 1] != GHOST
                       && current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] + 1] != SGHOST){
                        G_ghost_logic_function(&current_ghost_spot_y[i], &current_ghost_spot_x[i], RIGHT);
                        step_checker_x = currentspot_x;
                        step_checker_y = currentspot_y;
                        if(current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] + 1] != 'C'){
                            charswap(&current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i]], &current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] + 1]);
                            current_ghost_spot_x[i] += 1;
                        }
                    }
                    break;
                }
                case LEFT:{ // 左移
                    if(current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] - 1] != WALL
                       && current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] - 1] != GHOST
                       && current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] - 1] != SGHOST){
                        G_ghost_logic_function(&current_ghost_spot_y[i], &current_ghost_spot_x[i], LEFT);
                        step_checker_x = currentspot_x;
                        step_checker_y = currentspot_y;
                        if(current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] - 1] != 'C'){
                            charswap(&current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i]], &current_LevelMap[current_ghost_spot_y[i]][current_ghost_spot_x[i] - 1]);
                            current_ghost_spot_x[i] -= 1;
                        }
                    }
                    break;
                }
                default: break;
            }
        }
        
        // 進入下一關的條件和血量歸零執行的程式
        if(score >= current_levelUP_score  && heart > 0){
            if(level % 3 == 0 && wight_ghost_number < 12 && wight_LevelUP < 60){ // 每隔三關所需的下一階段分數和鬼魂數量都會提升
                wight_LevelUP += 5;
                wight_ghost_number += 1;
            }
            if(level % 5 == 0 && wight_invincible_step < 40){ // 每隔五關無敵狀態持續時間（步數）會減少
                wight_invincible_step += 5;
            }
            level += 1;
            total_score += score;
            score = 0;
            invincible_buffer = 0;
            invincible_step_remain = 0;
            stage_change(INFINITE, level);
            C_spawn();
            GHOST_spawn(current_ghost_number);
            I_RNGitmes_spawn();
            MapRenew();
        }
        else if(heart <= 0){
            show_words(3);
            break;
        }
        else{
        that:
            MapRenew();
        }
    }
}


#endif
