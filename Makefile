CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi
OBJ = main.o gameMap.o carMove.o buffer.o newSleep.o linkedlist.o
EXEC = traffic

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c main.h
	$(CC) -c main.c $(CFLAGS)

gameMap.o : gameMap.c gameMap.h
	$(CC) -c gameMap.c $(CFLAGS)

carMove.o : carMove.c carMove.h
	$(CC) -c carMove.c $(CFLAGS)

buffer.o : buffer.c buffer.h 
	$(CC) -c buffer.c $(CFLAGS)

newSleep.o : newSleep.c newSleep.h 
	$(CC) -c newSleep.c $(CFLAGS)

linkedlist.o : linkedlist.c linkedlist.h 
	$(CC) -c linkedlist.c $(CFLAGS)

clean: 
	rm -f $(EXEC) $(OBJ)