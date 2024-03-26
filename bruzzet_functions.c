#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INDEX 100   // maximum length of arrays

typedef struct
{
    int array[MAX_INDEX];
    int ptr;
} function;

void function_init(function *new) // initializes function array
{
    memset(new->array, 0, MAX_INDEX * sizeof(int));
    new->ptr = 0;
}

void increaseArray(function *array) // increases all ints in array with 1
{
    for(int a = 0; a < array->ptr; a++)
    {
        array->array[a]++;
    }
}

void increaseArraySelf(function *array) // increases all ints in array with 1 except last one
{
    for(int a = 0; a < (array->ptr - 1); a++)
    {
        array->array[a]++;
    }
}

void addFunction(function *array)
{
    array->ptr++;
}

int removeFunction(function *array) // reads final value and removes int in array
{
    int a = array->array[array->ptr];
    array->array[array->ptr] = 0;
    array->ptr--;
    return a;
}