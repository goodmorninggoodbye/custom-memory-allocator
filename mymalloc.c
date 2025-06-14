#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stddef.h>
#include <string.h>

#include "mymalloc.h"

////////////////////////////////////////////////////////////
#define memorySIZE 4096
static char memory[memorySIZE];

////////////////////////////////////////////////////////////

// Prints it - for testing
void printStuff(){
    int i = 0;
    // memorySIZE
    while (i < memorySIZE){
        // if (memory[i] == 0 && memory[i + 1] == 0 && memory[i + 2] == 0){
        //     break;
        // }
        printf("%d%s", memory[i], " ");
        i++;
    }
    printf("\n\n");
    return;
}


////////////////////////////////////////////////////////////


// Malloc is an array.

// r will be a reserved marker showing that this region is malloced
// s will be a number, standing for the size of the array
    // what a malloced part of the array will look like -> | r | size of the array | m | m | m | ... |
// 0 for empty
    // untouched party of array -> | 0 | 0 | 0 | ... |
// f for free region
    // freed parts of array -> | f | f | f | ... |

void coallesce(void *ptr){
    int i = 0;
    int adjacentSize;

    int tempSize;

    //coallesces
    while (i < memorySIZE){
            int q = memory[i + 1];
            int d = memory[i + 2];
        switch (memory[i]){
        // spot has taken memory array, jumps to next taken or open slot.
            case 'r': 
                tempSize = (q * 255) + d;
                i = i + tempSize + 3;
                continue;        
        // spot has freed memory array. check size of it
            case 'f': 
                tempSize = (q * 255) + d;
                //checks to see if next one is freed as well.
                if ((memory[i + tempSize + 3]) == 'f'){
                    //the second freed block size
                    q = memory[i + tempSize + 4];
                    d = memory[i + tempSize + 5];
                    int willAdd = (q * 255) + d;
                    tempSize = tempSize + willAdd + 3;
                    //updating the size of f
                    memory[i + 1] = (tempSize / 255);
                    memory[i + 2] = (tempSize % 255);

                    // making the next block size indicator f
                    continue;
                } else {
                    i = i + tempSize + 3;
                }
            default:
                // printStuff();
                return;
        }
    }
}

void *mymalloc(size_t size, char *file, int line){
    int i = 0;
    int tempSize;
// divide size by 255 into first slot
// modulo size by 255 into second slot

    //goes until it finds an open space.
    while (i < memorySIZE){
        int q = memory[i + 1];
        int d = memory[i + 2];
        switch (memory[i]){
        // spot has taken memory array, jumps to next taken or open slot.
            case 'r': 
                tempSize = (q * 255) + d;
                i = i + tempSize + 3;
                continue;
        
        // spot has freed memory array. check size of it
            case 'f': 
                tempSize = (q * 255) + d;
                // not enough space
                if (size > tempSize){
                    i = i + tempSize + 3;
                    continue;
                } else {
                    memory[i] = 'r';
                    int newFreeSize = tempSize - size;
                    memory[i + 1] = (size / 255);
                    memory[i + 2] = (size % 255);
                    i = i + 3;
                    while (i < size){
                        memory[i] = 'j';
                        i++;
                    }
                    memory[i + 1] = (newFreeSize / 255);
                    memory[i + 2] = (newFreeSize % 255);
                    // printStuff();
                    return &memory[i];
                    break;
                }
            default:
                if (i + size + 2 > memorySIZE){
                    printf("\n");
                    puts("ERROR! Not enough space. ");
                    printf("File: %s, line: %d", file, line);
                    printf("\n");
                    return NULL;
                }
                memory[i] = 'r';
                memory[i + 1] = (size / 255);
                memory[i + 2] = (size % 255);
                int j = 0;
                int anchor = i + 3;
                while (j < size){
                    memory[i + 3] = 'm';
                    i++;
                    j++;
                }
                // printStuff();
                return &memory[anchor];
                break;
        }
    }
    //returns the first part of your block, m
}

//frees and coallsces all of it as well
void myfree(void *ptr, char *file, int line){
    char *mem = ptr - 3;

    int *d = ptr - 1;
    int *q = ptr - 2;
    int size = (*q * 255) + *d;

    switch (*mem){
        case 'r':
            *mem = 'f';
            break;
        case 'f':
            printf("\n");
            puts("ERROR! Trying to free something already freed.");
            printf("File: %s, line: %d", file, line);
            printf("\n\n");
            return;
        case 0:
            printf("\n");
            puts("ERROR! Have you tried to free something that hasn't been malloced yet? ");
            printf("File: %s, line: %d", file, line);
            printf("\n\n");
            return;
        default:
            printf("\n");
            puts("ERROR! Not the start of the allocated payload. ");
            printf("File: %s, line: %d", file, line);
            printf("\n\n");
            return;
    }
    return coallesce(ptr);
}
