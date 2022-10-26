//
// Created by nabee on 10/24/2022.
//
#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"
#include "table.h"

// Exists just to type cast from Obj* to specfic Obj<Type>*
#define ALLOCATE_OBJ(type, objectType) \
(type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(NULL, 0, size);
    object->type = type;

    // Insert new object at head of VM's LL of objects.
    object->next = vm.objects;
    vm.objects = object;

    return object;
}

static ObjString* allocateString(char* chars, int length,
                                 uint32_t hash) {
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->hash = hash;
    string->chars = chars;
    tableSet(&vm.strings, string, NIL_VAL);
    return string;
}

static uint32_t hashString(const char* key, int length) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++) {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }
    return hash;
}

// Used for cases when we want to dynamically allocate string and dont have problems freeing the string taken
// from somewhere else (e.g. from string concatenation that isnt needed by other parts of the program).
ObjString* takeString(char* chars, int length) {
    uint32_t hash = hashString(chars, length);

    // Deduplicate. Free passed in string if it already exists in seen set
    ObjString* interned = tableFindString(&vm.strings, chars, length,
                                          hash);
    if (interned != NULL) {
        FREE_ARRAY(char, chars, length + 1);
        return interned;
    }

    return allocateString(chars, length, hash);
}

// Copy string used for case when string is from source code. Dont want to free string from source code
ObjString* copyString(const char* chars, int length) {
    uint32_t hash = hashString(chars, length);

    // Deduplicate string
    ObjString* interned = tableFindString(&vm.strings, chars, length,
                                          hash);
    if (interned != NULL) return interned;

    char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length, hash);
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
            break;
    }
}