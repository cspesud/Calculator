#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

//сохранить числа в стек числа
void pushNumber(NumberStack* stack , NumberNode* node);
//брать числа из стека числа
NumberNode* popNumber(NumberStack* stack);
//сохранить операторы в очереди
void inQueueCompute(ComputeQueue* queue,ComputeNode* node);
//брать операторы из очереди
ComputeNode* dequeueCompute(ComputeQueue* queue);
//печать числа
void printBigNumber(BigInt* number);
//Освобождение памяти
void freeBigInt(BigInt* number);
//ударить 0
void clearHeadZero(BigInt* number);
//сравнить числа
int compareAbs(BigInt* leftValue,BigInt* rightValue);

BigInt* add(BigInt* leftValue,BigInt* rightValue);

BigInt* sub(BigInt* leftValue,BigInt* rightValue);



int main(int argc, const char * argv[]) {
    //создать стек числа, чтобы сохранить числа и результат.
    NumberStack *numbers = (NumberStack*)malloc(sizeof(NumberStack));
    numbers->size = 0;
    numbers->top = NULL;
    //создать очереди операций, чтобы сохранить операторы.
    ComputeQueue *computes = (ComputeQueue*)malloc(sizeof(ComputeQueue));
    computes->headCompute = NULL;
    computes->tailCompute = NULL;
    computes->size = 0;
    
    BigInt* readNumber = (BigInt*)malloc(sizeof(BigInt));
    readNumber->length = 0;
    readNumber->sign = 0;
    readNumber->head = NULL;
    readNumber->tail = NULL;
    
    for (char c=0 ; c!=EOF; c = getchar()){
        
        switch (c) {
            case '+':
            case '-':
            case '=':
      
                if (readNumber->head == NULL ){
                    
                    if((c == '+' || c == '-') && readNumber->sign == 0){
                        
                        readNumber->sign = ((c == '+') ? 1 : -1);
                        
                    }
                    else{
                        printf("empty stack.\n");
                        exit(1);
                    }
                    
                }
                else{
                    
                    //сохранить в стек числа, которые читали.
                    NumberNode* node = (NumberNode*)malloc(sizeof(NumberNode));
                    node->nextNode = NULL;
                    node->value = readNumber;
                    
                    clearHeadZero(readNumber);
                    pushNumber(numbers, node);
                   
                    //создать структуру.
                    readNumber = (BigInt*)malloc(sizeof(BigInt));
                    readNumber->length = 0;
                    readNumber->sign = 0;
                    readNumber->head =NULL;
                    readNumber->tail = NULL;
                    
                    //сохранить операторы в очереди операций
                    ComputeNode* computeN = (ComputeNode*)malloc(sizeof(ComputeNode));
                    computeN->nextCompute = NULL;
                    computeN->compute = c;
                    inQueueCompute(computes, computeN);
                    
                    
                    
                    
                    
                    ComputeNode* cn = computes->headCompute;
                    while (cn != NULL) {
                        
                        if (cn->compute == '='){
                            if (numbers->size > 0){
                                printBigNumber(numbers->top->value);
                                exit(0);
                            }else{
                                
                                  printf("empty stack.\n");
                            }
                            
                            dequeueCompute(computes);
                            
                        }
                        
                        else if (numbers->size>=2){
                            
                            NumberNode* rightNumNode = popNumber(numbers);
                            
                            NumberNode* leftNumNode = popNumber(numbers);
                            
                            //начинать выполнять
                            BigInt* result = NULL;
                            switch (cn->compute) {
                                case '+':
                                    
                                    if (leftNumNode->value->sign == -1 && rightNumNode->value->sign == -1){

                                        add(leftNumNode->value, rightNumNode->value);
                                        result->sign = -1;
                                    }else if (leftNumNode->value->sign != -1 && rightNumNode->value->sign != -1){
                                        
                                            result = add(leftNumNode->value, rightNumNode->value);
                                    }else{
                                        
                                        if (leftNumNode->value->sign == -1){
                                            result = sub(rightNumNode->value, leftNumNode->value);
                                        }else if (rightNumNode->value->sign == -1){
                                            result = sub(leftNumNode->value, rightNumNode->value);
                                        }
                                    }
                                    
                                    break;
                                case '-':
                                    
                                    if (leftNumNode->value->sign == -1 && rightNumNode->value->sign == -1){
                                        result = sub(rightNumNode->value, leftNumNode->value);
                                    }else if (leftNumNode->value->sign != -1 && rightNumNode->value->sign != -1){
                                        
                                        result = sub(leftNumNode->value, rightNumNode->value);
                                    }else{
                                        
                                        if (leftNumNode->value->sign == -1){
                                            result = add(rightNumNode->value, leftNumNode->value);
                                            result->sign = -1;
                                            
                                        }else if (rightNumNode->value->sign == -1){
                        
                                            result = add(leftNumNode->value, rightNumNode->value);
                                        }
                                        
                                    }
                                    
                                    break;
                            }
                            
                            //сравнить результат
                            NumberNode* nn = (NumberNode*)malloc(sizeof(NumberNode*));
                            nn->value = result;
                            nn->nextNode = NULL;
                            pushNumber(numbers, nn);
                           
                            dequeueCompute(computes);
                            //Освобождение памяти
                            freeBigInt(rightNumNode->value);
                            freeBigInt(leftNumNode->value);
                            free(rightNumNode);
                            free(leftNumNode);
                            
                        }else{
                            
                            break;
                        }
                        //брать операторы из очереди
                        cn = computes->headCompute;
                        
                    }
                    
                }
                
                break;
            default:
                
                if (c >= '0' && c<= '9'){
                    //создать unit, чтобы придать в структуру.
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
                break;
        }
        
    }
    
    
    return 0;
}



void pushNumber(NumberStack* stack, NumberNode* node){
    node->nextNode = stack->top;
    stack->top = node;
    stack->size ++;
}

NumberNode* popNumber(NumberStack* stack){
    
    if (stack->size == 0) { return NULL;}
    
    NumberNode* top = stack->top;
    stack->top = top->nextNode;
    stack->size --;
    return top;
}

void inQueueCompute(ComputeQueue* computes,ComputeNode* computeN){
    if (computes->size == 0){
        
        computes->headCompute = computeN;
        computes->tailCompute = computeN;
        computes->size = 1;
    }else{

        computes->tailCompute->nextCompute = computeN;
        computes->size ++;
        computes->tailCompute = computeN;
        
    }
    
}

ComputeNode* dequeueCompute(ComputeQueue* queue){
    
    if (queue->size == 0){ return  NULL;}
    
    ComputeNode* head = queue->headCompute;
    queue->headCompute = head->nextCompute;
    queue->size --;
    
    free(head);
    return NULL;
}


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
    
}

void clearHeadZero(BigInt* number){
    BigIntUnit* unit = number->head;
    while(unit != number->tail && unit != NULL){
        
        if (unit->value == 0){
            
            BigIntUnit* tmp = unit;
            unit = unit->nextUnit;
            number->head = unit;
            
            free(tmp);
            
        }else{
            break;
        }
        
    }
}

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

        if (result->head == NULL){
            result->tail = resultUnit;
            result->head = resultUnit;
            result->length = 1;
        }else{

            resultUnit->nextUnit = result->head;
            result->head->preUnit = resultUnit;
            result->head = resultUnit;
            result->length ++;
        }
        
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
        
        
        if (result->head == NULL){
            result->tail = resultUnit;
            result->head = resultUnit;
            result->length = 1;
        }else{
           
            resultUnit->nextUnit = result->head;
            result->head->preUnit = resultUnit;
            result->head = resultUnit;
            result->length ++;
        }
    
        if (leftUnit != NULL){ leftUnit = leftUnit->preUnit;}
        if (rightUnit != NULL){ rightUnit = rightUnit->preUnit;}
        
    }
    
    clearHeadZero(result);
    
    return result;
    
}
