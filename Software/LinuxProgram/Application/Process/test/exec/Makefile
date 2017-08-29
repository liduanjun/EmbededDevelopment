all:execl execlp execle myexec execv execvp execve execvpe

execl:execl.c
	gcc -c execl.c
	gcc execl.o -o execl.bin

execlp:execlp.c
	gcc -c execlp.c
	gcc execlp.o -o execlp.bin

execle:execle.c
	gcc -c execle.c
	gcc execle.o -o execle.bin

myexec:myexec.c
	gcc -c myexec.c
	gcc myexec.o -o myexec.bin

execv:execv.c
	gcc -c execv.c
	gcc execv.o -o execv.bin

execvp:execvp.c
	gcc -c execvp.c
	gcc execvp.o -o execvp.bin

execve:execve.c
	gcc -c execve.c
	gcc execve.o -o execve.bin

execvpe:execvpe.c
	gcc -c execvpe.c
	gcc execvpe.o -o execvpe.bin

clean:
	rm execl.bin execlp.bin execle.bin myexec.bin execv.bin execvp.bin execve.bin execvpe.bin
	rm execl.o execlp.o execle.o myexec.o execv.o execvp.o execve.o execvpe.o