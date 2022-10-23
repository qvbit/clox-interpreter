//
// Created by nabee on 10/20/2022.
//

#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

typedef double Value;


// This is analogous to chunk but contains constant values for operators that have operands.
// the 'addConstant' function returns an index (i.e. the index into this array)
// which goes after the Opcode of the operator in 'code' (which itself in Chunk).
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif //CLOX_VALUE_H
