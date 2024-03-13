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

int main(int argc, char *argv[])
{
    puts("Bruzzet interpreter by DanielKwinkel");

    if(argc == 1)
    {
        puts("Specify filename please!\n(stopped)");
        exit(1);
    }

    FILE *pt = fopen(argv[1], "r");
    int command; // current char
    int commandCounter = 0;
    int a;

    int stack[MAX_INDEX];
    int stackp;

    function io;
    function math;
    function stackf;
    function cf;

    function_init(&io); function_init(&math); function_init(&stackf); function_init(&cf);

    printf("Program name: %s\n\n", argv[1]);

    while(!feof(pt))
    {
        command = fgetc(pt);
        commandCounter++;
        switch(command)
        {
            case '(': // io
                addFunction(&io);
                increaseArraySelf(&io);
                increaseArray(&math);
                increaseArray(&stackf);
                increaseArray(&cf);
                break;
            case '[': // math
                addFunction(&math);
                increaseArraySelf(&math);
                increaseArray(&io);
                increaseArray(&stackf);
                increaseArray(&cf);
                break;
            case '<': // stackf
                addFunction(&stackf);
                increaseArraySelf(&stackf);
                increaseArray(&io);
                increaseArray(&math);
                increaseArray(&cf);
                break;
            case '{': // cf
                addFunction(&cf);
                increaseArraySelf(&cf);
                increaseArray(&io);
                increaseArray(&math);
                increaseArray(&stackf);
                break;

            // Esolang functions

            case ')': // io
                increaseArraySelf(&io);
                a = removeFunction(&io);
                switch(a)
                {
                    case 1:
                        stackp++;
                        scanf("%d", &stack[stackp]);
                        break;
                    case 2:
                        stackp++;
                        stack[stackp] = getc(stdin);
                        break;
                    case 3:
                        printf("%d", stack[stackp]);
                        stack[stackp] = 0;
                        stackp--;
                        break;
                    case 4:
                        printf("%c", stack[stackp]);
                        stack[stackp] = 0;
                        stackp--;
                        break;
                    default:
                        printf("\nUnknown command: %d spaces between () at character %d\n(stopped)", a, commandCounter);
                        exit(1);
                }
                increaseArray(&math);
                increaseArray(&stackf);
                increaseArray(&cf);
                break;
            case ']': // math
                increaseArraySelf(&math);
                a = removeFunction(&math);
                switch(a)
                {
                    case 1:
                        stack[stackp - 1] += stack[stackp];
                        stack[stackp] = 0;
                        stackp--;
                        break;
                    case 2:
                        stack[stackp - 1] -= stack[stackp];
                        stack[stackp] = 0;
                        stackp--;
                        break;
                    case 3:
                        stack[stackp - 1] *= stack[stackp];
                        stack[stackp] = 0;
                        stackp--;
                        break;
                    case 4:
                        stack[stackp - 1] /= stack[stackp];
                        stack[stackp] = 0;
                        stackp--;
                        break;
                    default:
                        printf("\nUnknown command: %d spaces between [] at character %d\n(stopped)", a, commandCounter);
                        exit(1);
                }
                increaseArray(&io);
                increaseArray(&stackf);
                increaseArray(&cf);
                break;
            case '>': // stackf
                increaseArraySelf(&stackf);
                a = removeFunction(&stackf);
                switch(a)
                {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        stack[stackp] = 0;
                        stackp--;
                        break;
                    case 6:
                        memset(stack, 0, MAX_INDEX * sizeof(int));
                        break;
                    default:
                        printf("\nUnknown command: %d spaces between <> at character %d\n(stopped)", a, commandCounter);
                        exit(1);
                }
                increaseArray(&io);
                increaseArray(&math);
                increaseArray(&cf);
                break;
            case '}': // cf
                increaseArraySelf(&cf);
                a = removeFunction(&cf);
                switch(a)
                {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    default:
                        printf("\nUnknown command: %d spaces between {} at character %d\n(stopped)", a, commandCounter);
                        exit(1);
                }
                increaseArray(&io);
                increaseArray(&math);
                increaseArray(&stackf);
                break;
            default:
                break;
        }
    }

    fclose(pt);
    return 0;
}