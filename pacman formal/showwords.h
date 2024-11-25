#ifndef SHOWWORDS
#define SHOWWORDS

#include <stdio.h>
#include "custom_function.h"

void show_words(int a){
    switch(a){
        case 1:{
            printf("\n\t\t\tPACMAN GAME!\n\n");
            printf("press the key to choose gameplay mode\n");
            printf("press '1' for normal mode\n");
            printf("press '2' for infinite mode\n");
            printf("press 'p' to quit the game\n");
            printf("press '?' to check the game rule\n");
            break;
        }
        case 2:{
            printf("\n\t\t\tGAME RULE\n\n");
            printf("'C' stands for player(pacman). You can use 'w','a','s','d' to move UP, LEFT, DOWN, RIGHT. press 'p' to pause the game.\n");
            printf("'@' stands for ghosts. When pacman get catched by them or pacman runs into them, you will lose 1 HP.\n");
            printf("'#' stands for walls.\n");
            printf("'H' stands for healing. You will gain 1 HP after eating it.\n");
            printf("'.' stands for dots. Eating each one them will get 1 point.\n");
            printf("\n'$' stands for bigdots. Eating it allows you gain the [super buff] and get 3 points.\n");
            printf("During the super buff time, pacman will temporary become invincible.");
            printf("It also allows you to eat ghosts(they will turn to '!'). The effect will disappear after moving 30 steps.\n");
            printf("\nMode explaination:\n");
            printf("* NORMAL: Concludes 20 level. Each level requires different points to go to next level.\n");
            printf("* INFINITY: Each coures will come out randomly, It's endless gamemode unless you die or quit the game.\n");
            printf("\nTips:\n");
            printf("* Remember, pacman is always one step before ghosts' action,");
            printf("so DON'T stupidly move forward to them without super buff, or you will die.\n");
            printf("* You can AFK by pressing other keys or move confrontly the wall, but why would you do so?\n");
            printf("\n// press any key to go back to menu...\n");
            break;
        }
        case 3:{
            printf("\n\t\t\tGAME OVER\t\tfinal score : %d\n\n", total_score + score);
            printf("want to play again?\n");
            printf("YES [press '1']\n");
            printf("Back to menu [press '2']\n");
            printf("Quit the game [press 'p']\n");
            break;
        }
        case 4:{
            printf("\n\t\t\tPUASE\n\n");
            printf("continue?\n");
            printf("YES [press 'p']\n");
            printf("End game [press anykey]\n");
            break;
        }
        default: break;
    }
}

#endif

