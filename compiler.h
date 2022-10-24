//
// Created by nabee on 10/23/2022.
//

#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "vm.h"
#include "object.h"

bool compile(const char* source, Chunk* chunk);

#endif //CLOX_COMPILER_H
