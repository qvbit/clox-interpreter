//
// Created by nabee on 10/23/2022.
//

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;  // VM gets an array of chunks
    // ip always points to next instruction, not the one currently being handled.
    uint8_t* ip;  // Byte pointer poitnting right into the middle of the bytecode array (faster way to do it vs e.g. int index).
    Value stack[STACK_MAX];  // Stack keeps track of values we need e.g. operands in an arithmetic expression.
    Value* stackTop;  // Use direct pointer to keep track of top of stack.
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpreter(const char* source);
void push(Value value);
Value pop();

#endif //CLOX_VM_H
