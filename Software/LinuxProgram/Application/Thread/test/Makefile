all : pthread_create.1 pthread_create.2 pthread_join semaphore pv mutex

pthread_create.1:pthread_create.1.c
	gcc -c pthread_create.1.c 
	gcc pthread_create.1.o -o pthread_create.1.bin -lpthread

pthread_create.2:pthread_create.2.c
	gcc -c pthread_create.2.c 
	gcc pthread_create.2.o -o pthread_create.2.bin -lpthread

pthread_join:pthread_join.c
	gcc -c pthread_join.c 
	gcc pthread_join.o -o pthread_join.bin -lpthread

semaphore:semaphore.c
	gcc -c semaphore.c 
	gcc semaphore.o -o semaphore.bin -lpthread

pc_proble:pc_proble.c
	gcc -c pc_proble.c 
	gcc pc_proble.o -o pc_proble.bin -lpthread

mutex:mutex.c
	gcc -c mutex.c 
	gcc mutex.o -o mutex.bin -lpthread

clean:
	rm *.o *.bin