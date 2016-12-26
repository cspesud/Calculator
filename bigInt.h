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


void printBigNumber(BigInt* number);

void freeBigInt(BigInt* number);

void addUnitToHead(BigInt* number,BigIntUnit* unit);

void addUnitToTail(BigInt* number,BigIntUnit* unit);

void removeUnitFromTail(BigInt* number);

void clearHeadZero(BigInt* number);

