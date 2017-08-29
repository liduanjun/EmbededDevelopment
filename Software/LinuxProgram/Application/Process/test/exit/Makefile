all:exit atexit

exit:
	gcc -c exit.c
	gcc exit.o -o exit.bin

atexit:
	gcc -c atexit.c
	gcc atexit.o -o atexit.bin

clean:
	rm *.o *.bin