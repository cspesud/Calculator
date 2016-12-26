#include <stdio.h>
#include <stdlib.h>
#include "read.h"



int main(int argc, const char * argv[]) {
    
    NumberStack *numbers = (NumberStack*)malloc(sizeof(NumberStack));
    numbers->size = 0;
    numbers->top = NULL;
    char tmp;
    for (char c= getchar() ; c!='q'; c = getchar()){
        
        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '=':
                
                tmp = getchar() ;
                if ((tmp >= '0' && tmp <= '9') && c == '-'){
                    NumberNode* node = (NumberNode*)calloc(1, sizeof(NumberNode));
                    node->value = readNumber(tmp);
                    node->value->sign = -1;
                    pushNumber(numbers, node);
                    continue;
                }
                
                if (tmp != '\n') { ignoreLine(); continue; }
                if (numbers->size >0  && c == '='){
                    printBigNumber(numbers->top->value);
                }else if (numbers->size >= 2){
                    BigInt* rightValue = numbers->top->value;
                    BigInt* leftValue = numbers->top->nextNode->value;
                    BigInt* result = calculate(c, leftValue, rightValue);

                    if (result == NULL) {
                        continue;
                    }
                    NumberNode* node = (NumberNode*)calloc(1, sizeof(NumberNode));
                    node->value = result;
                    popNumber(numbers);
                    popNumber(numbers);
                    pushNumber(numbers, node);
                    }else{
                    printf("empty stack\n");
                }
                break;
            default:

                if (c >= '0' && c<= '9'){
                    NumberNode* node = (NumberNode*)calloc(1, sizeof(NumberNode));
                    node->value = readNumber(c);
                    pushNumber(numbers, node);
                }
                break;
        }
        }        
    return 0;
}

