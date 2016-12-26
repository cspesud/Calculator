#include <stdio.h>
#include "stack.h"



int compareAbs(BigInt* leftValue,BigInt* rightValue);

BigInt* calculate(char compute,BigInt* leftValue,BigInt* rightValue);

BigInt* add(BigInt* leftValue,BigInt* rightValue);

BigInt* sub(BigInt* leftValue,BigInt* rightValue);

BigInt* mul(BigInt* leftValue,BigInt* rightValue);

BigInt* divide(BigInt* leftValue,BigInt* rightValue);
