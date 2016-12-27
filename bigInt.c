#include "bigInt.h"
#include <stdlib.h>


void printBigNumber(BigInt* number){
    if (number->head != NULL && number->sign<0){ printf("-");}
    BigIntUnit* unit = number->head;
    while(unit != NULL){
        printf("%d",unit->value);
        unit = unit->nextUnit;
    }
    printf("\n");
}

void freeBigInt(BigInt* number){
    BigIntUnit* unit = number->head;
    while(unit!=NULL){
        BigIntUnit* tmp = unit;
        unit = unit->nextUnit;
        free(tmp);
    }
    
    free (number);
    
}

void addUnitToHead(BigInt* number,BigIntUnit* unit){
    if (number == NULL || unit == NULL) { return;}
    if (number->head == NULL){
        number->tail = unit;
        number->head = unit;
        number->length = 1;
    }else{
        unit->nextUnit = number->head;
        number->head->preUnit = unit;
        number->head = unit;
        number->length ++;
    }
}


void addUnitToTail(BigInt* number,BigIntUnit* unit)
{
    if (number == NULL || unit == NULL) { return;}
    if (number->head == NULL){
        number->tail = unit;
        number->head = unit;
        number->length = 1;
    }else{
        unit->preUnit = number->tail;
        number->tail->nextUnit = unit;
        number->tail = unit;
        number->length ++;
    }
}


void removeUnitFromTail(BigInt* number){
    if (number->length<1) { return;}
    BigIntUnit* tailUnit = number->tail;
    number->tail = tailUnit->preUnit;
    number->tail->nextUnit = NULL;
    number->length--;
    free(tailUnit);
}

void clearHeadZero(BigInt* number){
    BigIntUnit* unit = number->head;
    while(unit != number->tail && unit != NULL){
        if (unit->value == 0){            
            BigIntUnit* tmp = unit;
            unit = unit->nextUnit;
            number->head = unit;
            unit->preUnit = NULL;
            number->length--;
            free(tmp);
            
        }else{
            break;
        }
        
    }
}
