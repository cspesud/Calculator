#include <stdio.h>
#include "bigInt.h"


typedef struct NumberNode{
    BigInt * value;
    struct NumberNode * nextNode;
}NumberNode;


typedef struct NumberStack {
    int size;
    NumberNode * top;    
} NumberStack;


void pushNumber(NumberStack* stack , NumberNode* node);

void popNumber(NumberStack* stack);
