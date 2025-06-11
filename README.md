    Properties:
    malloc.c - This file will contain mymalloc and myfree
    memgrind.c - This is the test file 

                                                –––––– NOTE!!!! ––––––
                                mymalloc.c contains all of the tests from the err.c file.
    
    All of the specific files have their own functions that are used to show we have a working library

    Our specific test plan
        - We first specify the requirements, which are to develop malloc and free. Malloc reserves memory, while free frees it. 
        - Requirements are not violated and have a working result
        - When successful, malloc() returns a pointer to the payload
        - We have created mymalloc and myfree which are two programs that check to show our requirements are successful. 

The Malloc Function
    Malloc is an array.
        "r" will contain a reserved marker showing that this region is malloced
        Adjacent are two blocks. Combined together, they create a number. 
              You get it by combining the first slot, which is multiplied by 255
                  And the second slot, which contains the remainer.
        This is what a malloced part of the array will look like -> | r | size/255 | size % 255 | m | m | m | ... |
        "m" shows that the specific region of array has been previously allocated, fixing the potential issue that 0 may create.
        In the array, 0 will be treated as empty and can the malloced without issue.
            Untouched party of array -> | 0 | 0 | 0 | ... |
        "f" represents that a free region is flagged.
            The freed parts of array will look like this: | f | size/255 | size % 255 | m | m | m | ... |

The Free Function
    Free is used to free all of the memory
        Finds the location of the pointer
        The spot has taken the memory and now will jump to the next taken or open slot
        Spot has been freed, next we will check the size
        Checks to see if next one is freed as well.
        At this point the memory has been freed. 

The Coallesce Function
    It searches for adjacent free blocks of memory and subsequently merges them.
    This is used after using the myfree function.   

For Testing:
    • For testing we are using err.c and other tests that we have created for the project. For err.c the three cases that we are 
    given have been tested to show the error, meaning the mymalloc.c functions are working correctly. 
    • For our first stress test, we use firsttest.c to test it out. We use a simple test in this sense to see if we are allocating and free ht memory. Firsttest.c works as expected.
    • For our second stress test, we use a similar format to firsttest.c, and it also works successfully. 

                                                –––––– NOTE!!!! ––––––
                                mymalloc.c contains all of the tests from the err.c file.

Average Times For Each Task
    err.c
        Case 1 - 0.000050 seconds.
        Case 2 - 0.000062 seconds.
        Case 3 - 0.000048 seconds.
    
    memgrind.c
        Case 4 - malloc() and immediately free() a 1-byte chunk, 120 times -  0.000098 seconds.
        Case 5 - malloc() to get 120 1-byte chunks, store  the pointers in an array, then use free() to
                 deallocate the chunks - 0.002010 seconds.
        Case 6 - Randomly choose between allocating a 1-byte chunk and storing the pointer in an array and 
                 reallocating one of the chunks in the array (if any) - 0.000008 seconds.

    Stress tests   
        Case 7 - malloc and free odd and difficult-to-code numbers 750 times in a row - 0.011087 seconds. 
        Case 8 - allocate 1000 bytes of memory 50 times in a row - 0.000093 seconds.
