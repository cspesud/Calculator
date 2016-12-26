#include "read.h"


BigInt* readNumber(char firstDig){
    BigInt* readNumber = (BigInt*)malloc(sizeof(BigInt));
    readNumber->length = 0;
    readNumber->sign = 0;
    readNumber->head = NULL;
    readNumber->tail = NULL;
    
    for (char c = firstDig; c != '\n'; c =getchar()){
        
        if (c >= '0' && c<= '9'){
            BigIntUnit *unit = (BigIntUnit*)malloc(sizeof(BigIntUnit));
            unit->nextUnit = NULL;
            unit->preUnit = NULL;
            unit->value = c-'0';
            
            if (readNumber->length == 0){
                readNumber->head = unit;
                readNumber->tail = unit;
                readNumber->length = 1;
            }else{
                readNumber->tail->nextUnit = unit;
                unit->preUnit = readNumber->tail;
                readNumber->tail = unit;
                readNumber->length ++;
                
            }
        }
    }    
    clearHeadZero(readNumber);
    return readNumber;
}

void ignoreLine(){
    for (char tmp = getchar(); tmp != '\n'; tmp = getchar()) {}
}
