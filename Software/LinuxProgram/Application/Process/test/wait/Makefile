all : wait waitpid

wait : wait.c
	gcc -c wait.c
	gcc wait.o -o wait.bin

waitpid : waitpid.c
	gcc -c waitpid.c
	gcc waitpid.o -o waitpid.bin

clean :
	rm *.o *.bin