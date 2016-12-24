#ifndef structure_h
#define structure_h

#include <stdio.h>


typedef struct BigIntUnit{
    u_int8_t value;
    struct BigIntUnit *nextUnit;
    struct BigIntUnit *preUnit;
    
}BigIntUnit;


typedef struct BigInt{
    short sign ;
    long length;
    BigIntUnit *head;
    BigIntUnit *tail;

}BigInt;


typedef struct NumberNode{
    BigInt * value;
    struct NumberNode * nextNode;
    
}NumberNode;


typedef struct NumberStack {
    int size;
    NumberNode * top;
    
} NumberStack;



typedef struct ComputeNode{
    char compute;
    struct ComputeNode* nextCompute;
    
}ComputeNode;


typedef struct ComputeQueue{
    int size;
    ComputeNode *headCompute;
    ComputeNode *tailCompute;
    
}ComputeQueue;

#endif
