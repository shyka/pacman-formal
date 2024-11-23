#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "showwords.h"
#include "custom_function.h"
#include "normalmode.h"


int main(void) {
    while(1){
        system("stty raw");
        char key1, key2;
        
    here:
        show_words(1);
        while((key1 = getchar()) != 'p'){
            enum selection1 choose1;
            switch(key1){
                case'1': choose1 = NORMAL; break;
                case'2': choose1 = INFINITE; break;
                case'p':
                case'P': choose1 = QUIT; break;
                case'?': choose1 = RULE_CHECK; break;
                default: choose1 = WRONG_KEY1; break;
            }
            switch(choose1){
                case NORMAL:{
                    normal_mode();
                    goto there;
                    break;
                }
                case INFINITE:{
                    printf("infinite");
                    break;
                }
                case QUIT: break;
                case RULE_CHECK:{
                    char keyany;
                    show_words(2);
                    while((keyany = getchar()) != 'p'){
                        break;
                    }
                    goto here;
                    break;
                }
                case WRONG_KEY1:{
                    printf("\n^ WORNG KEY! please try other valid words ^\n");
                    goto here;
                    break;
                }
            }
        }
        
    there:
        show_words(3);
        while((key2 = getchar()) != 'p'){
            enum selection2 choose2;
            switch(key2){
                case'1': choose2 = AGAIN; break;
                case'2': choose2 = BACK_TO_MENU; break;
                case'p':
                case'P': choose2 = ENDGAME; break;
                default: choose2 = WRONG_KEY2; break;
            }
            switch(choose2){
                case AGAIN:{
                    normal_mode();
                    goto there;
                    break;
                }
                case BACK_TO_MENU:{
                    goto here;
                    break;
                }
                case QUIT: break;
                case WRONG_KEY2:{
                    printf("\n^ WORNG KEY! please try other valid words ^\n");
                    goto there;
                    break;
                }
            }
        }
        system("stty cook");
        break;
    }
}
