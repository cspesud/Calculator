#include "calculate.h"


int compareAbs(BigInt* leftValue,BigInt* rightValue){

    if (leftValue->length > rightValue->length){
        return 1;
    }else if (leftValue->length < rightValue ->length){
        return -1;
    }else {
        BigIntUnit* leftIntUnit = leftValue->head;
        BigIntUnit* rightIntUnit = rightValue->head;
        while (leftIntUnit != NULL && rightIntUnit != NULL) {
            
            if (leftIntUnit->value > rightIntUnit->value){
                return 1;
            }else if (leftIntUnit->value < rightIntUnit->value){
                return -1;
            }
            leftIntUnit = leftIntUnit->nextUnit;
            rightIntUnit = rightIntUnit->nextUnit;
        }
    }
    return 0;
}

BigInt* add(BigInt* leftValue,BigInt* rightValue){
    BigInt* result =  (BigInt*)malloc(sizeof(BigInt));
    result->length = 0;
    result->sign = 0;
    result->head = NULL;
    result->tail = NULL;
    int needAdd = 0;
    long maxLenght = leftValue->length > rightValue->length ? leftValue->length : rightValue->length;
    
    BigIntUnit* leftUnit = leftValue->tail;
    BigIntUnit* rightUnit = rightValue->tail;
    
    for (int i=0;i<maxLenght;i++){
        
        u_int8_t leftInt = 0;
        u_int8_t rightInt = 0;
        
        if (leftUnit != NULL){ leftInt = leftUnit->value;}
        if (rightUnit != NULL){ rightInt = rightUnit->value;}
        
        BigIntUnit* resultUnit = (BigIntUnit*)malloc(sizeof(BigIntUnit));
        resultUnit->nextUnit = NULL;
        resultUnit->preUnit = NULL;
        resultUnit->value = (leftInt +rightInt + needAdd) % 10;
        needAdd = (leftInt + rightInt + needAdd) / 10;
        addUnitToHead(result, resultUnit);

        if (leftUnit != NULL){ leftUnit = leftUnit->preUnit;}
        if (rightUnit != NULL){ rightUnit = rightUnit->preUnit;}
        
    }
    
    if (needAdd > 0){

        BigIntUnit* resultUnit = (BigIntUnit*)malloc(sizeof(BigIntUnit));
        resultUnit->nextUnit = NULL;
        resultUnit->preUnit = NULL;
        resultUnit->value = needAdd;        
        resultUnit->nextUnit = result->head;
        result->head->preUnit = resultUnit;
        result->head = resultUnit;
        result->length ++;
    }
    
    return result;
}

BigInt* sub(BigInt* leftValue,BigInt* rightValue){
    BigInt* result = (BigInt*)malloc(sizeof(BigInt));
    result->length = 0;
    result->sign = 0;
    result->head = NULL;
    result->tail = NULL;
    
    int needAdd = 0;

    int compareResult = compareAbs(leftValue, rightValue);
    if (compareResult == 0){
        BigIntUnit* unit = (BigIntUnit*)malloc(sizeof(BigIntUnit));;
        result->head = unit;
        result->tail = unit;
        result->length = 1;
        return result;
    }else if (compareResult < 0){
        result->sign = -1;
        BigInt* tmp = leftValue;
        leftValue = rightValue;
        rightValue = tmp;
}
    
    long maxLenght = leftValue->length;
    
    BigIntUnit* leftUnit = leftValue->tail;
    BigIntUnit* rightUnit = rightValue->tail;
    
    for (int i=0;i<maxLenght;i++){
        
        u_int8_t leftInt = 0;
        u_int8_t rightInt = 0;
        
        if (leftUnit != NULL){ leftInt = leftUnit->value;}
        if (rightUnit != NULL){ rightInt = rightUnit->value;}
        
        BigIntUnit* resultUnit = (BigIntUnit*)malloc(sizeof(BigIntUnit));
        resultUnit->nextUnit = NULL;
        resultUnit->preUnit = NULL;
        resultUnit->value = (10 + leftInt - needAdd - rightInt ) % 10;

        if(leftInt < needAdd + rightInt){
            needAdd = 1;
        }else {
            needAdd = 0;
        }
        
        addUnitToHead(result, resultUnit);
        
        if (leftUnit != NULL){ leftUnit = leftUnit->preUnit;}
        if (rightUnit != NULL){ rightUnit = rightUnit->preUnit;}
        
    }
    
    clearHeadZero(result);
    
    return result;
    
}


BigInt* mul(BigInt* leftValue,BigInt* rightValue){
        BigInt* result = (BigInt*)calloc(1,sizeof(BigInt));
    
    if ((leftValue->length == 1 && leftValue->tail->value == 0) ||
        (rightValue->length == 1 && rightValue->tail->value == 0)) {
        addUnitToHead(result, (BigIntUnit*)calloc(1, sizeof(BigIntUnit)));
    }else{
        
        int i = 0;
        
        for (BigIntUnit* runit = rightValue->tail ; runit != NULL; runit = runit->preUnit){
            
            u_int8_t rInt = runit->value;
            u_int8_t needAdd = 0;
            BigInt* tmpResult = (BigInt*)calloc(1,sizeof(BigInt));
            
            for (int j=0;j<i;j++){
                BigIntUnit* zeroUnit = (BigIntUnit*)calloc(1, sizeof(BigIntUnit));
                addUnitToHead(tmpResult, zeroUnit);
            }
            
            for (BigIntUnit* lunit = leftValue->tail ; lunit != NULL; lunit = lunit->preUnit){
                
                u_int8_t lInt = lunit->value;
                u_int8_t cInt = (lInt * rInt + needAdd) % 10;
                needAdd = (lInt * rInt + needAdd) / 10;
                BigIntUnit* cUnit = (BigIntUnit*)calloc(1, sizeof(BigIntUnit));
                cUnit->value = cInt;
                addUnitToHead(tmpResult, cUnit);
                
            }

            BigIntUnit* cUnit = (BigIntUnit*)calloc(1, sizeof(BigIntUnit));
            cUnit->value = needAdd;
            addUnitToHead(tmpResult, cUnit);
            
            BigInt* tmp = result;
            result = add(result, tmpResult);
            freeBigInt(tmp);
            
            freeBigInt(tmpResult);
            i++;
            
        }
        
        
    }
    
    clearHeadZero(result);
    
    return result;
}

BigInt* divide(BigInt* leftValue,BigInt* rightValue){
    BigInt* result = (BigInt*)calloc(1,sizeof(BigInt));
    int cmpFlag = compareAbs(leftValue, rightValue) ;

    if ((leftValue->length == 1 && leftValue->tail->value == 0) || cmpFlag == -1){
        addUnitToHead(result, (BigIntUnit*)calloc(1, sizeof(BigIntUnit)));
        
    }else if (rightValue->length == 1 && rightValue->tail->value == 0) {

        printf("you should not divide by zero\n");
        freeBigInt(result);
        return NULL;
    }else if (cmpFlag == 0){

        BigIntUnit* unit = (BigIntUnit*)calloc(1, sizeof(BigIntUnit));
        unit->value = 1;
        addUnitToHead(result, unit);
    }else{
        
        BigInt* subValue = leftValue;
        long maxLength = leftValue->length - rightValue->length +1;

        for (int j=0;j<maxLength-1;j++){
            addUnitToTail(rightValue, (BigIntUnit*)calloc(1, sizeof(BigIntUnit)));
        }

        for (long i=maxLength;i>0;i--){
            int cInt = 0;
            while(compareAbs(subValue, rightValue)>=0){
                BigInt* tmp = subValue;
                subValue = sub(subValue, rightValue);

                if (tmp != leftValue){
                    freeBigInt(tmp);
                }
                cInt ++;
            }

            BigIntUnit* cUnit = (BigIntUnit*)calloc(1, sizeof(BigIntUnit));
            cUnit->value = cInt;
            addUnitToTail(result, cUnit);

            if (i != 1){
                removeUnitFromTail(rightValue);
            }
            
        }
        
        
    }
    
    clearHeadZero(result);
    return result;
}

BigInt* calculate(char compute,BigInt* leftValue,BigInt* rightValue){
    BigInt* result = NULL;
        
    switch (compute) {
        case '+':
            if (leftValue->sign == -1 && rightValue->sign == -1){
                add(leftValue, rightValue);
                result->sign = -1;
            }else if (leftValue->sign != -1 && rightValue->sign != -1){
                result = add(leftValue, rightValue);
            }else{
         
                if (leftValue->sign == -1){
                    result = sub(rightValue, leftValue);
                }else if (rightValue->sign == -1){
                    result = sub(leftValue, rightValue);
                }
            }
            
            break;
        case '-':
            if (leftValue->sign == -1 && rightValue->sign == -1){
                result = sub(rightValue, leftValue);
            }else if (leftValue->sign != -1 && rightValue->sign != -1){
          
                result = sub(leftValue, rightValue);
            }else{
                
                if (leftValue->sign == -1){
                    result = add(rightValue, leftValue);
                    result->sign = -1;
                    
                }else if (rightValue->sign == -1){
                    
                    result = add(leftValue, rightValue);
                }
                
            }
            
            break;
        case '*':
            result = mul(leftValue, rightValue);
            
            if (leftValue->sign ==  rightValue->sign ){
                result->sign = 0 ;
            }else{
                result->sign = -1 ;
            }
            break;
        case '/':
            result = divide(leftValue, rightValue);
            
            if (leftValue->sign ==  rightValue->sign ){
                result->sign = 0 ;
            }else{
                result->sign = -1 ;
            }
            break;
            
        default:
            break;
    }
    
    return result;
}

