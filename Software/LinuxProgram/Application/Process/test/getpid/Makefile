all:getpid getuid getgid

getpid:
	gcc -c getpid.c 
	gcc getpid.o -o getpid.bin

getuid:
	gcc -c getuid.c 
	gcc getuid.o -o getuid.bin

getgid:
	gcc -c getgid.c 
	gcc getgid.o -o getgid.bin

clean:
	rm *.o *.bin

test:
	./getpid.bin
	./getuid.bin
	./getgid.bin