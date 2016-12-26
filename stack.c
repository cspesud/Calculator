#include "stack.h"
#include <stdlib.h>


void pushNumber(NumberStack* stack , NumberNode* node){
    node->nextNode = stack->top;
    stack->top = node;
    stack->size ++;
}

void popNumber(NumberStack* stack){
    if (stack->size == 0) { return ;}
    
    NumberNode* top = stack->top;
    stack->top = top->nextNode;
    stack->size --;    
    freeBigInt(top->value);
    free(top);
}
