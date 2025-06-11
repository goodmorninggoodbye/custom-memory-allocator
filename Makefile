memgrind: memgrind.c mymalloc.c
	gcc -o memgrind memgrind.c mymalloc.c -I.