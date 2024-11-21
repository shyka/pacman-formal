#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "showwords.h"
char key1, key2;
enum selection1{NORMAL, INFINITE, QUIT, WRONG_KEY, RULE_CHECK};

int main(void) {
    while(1){
        system("stty raw");
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
                default: choose1 = WRONG_KEY; break;
            }
            switch(choose1){
                case NORMAL:{
                    printf("normal");
                    break;
                }
                case INFINITE:{
                    printf("infinite");
                    break;
                }
                case QUIT: break;
                case RULE_CHECK:{
                    show_words(2);
                    while((key2 = getchar()) != 'p'){
                        break;
                    }
                    goto here;
                    break;
                }
                case WRONG_KEY:{
                    printf("\n^ WORNG KEY! please try other valid words ^\n\n");
                    goto here;
                    break;
                }
            }
        }
        system("stty cook");
        break;
    }
}
