CC = gcc
CFLAGS = -Wall -Wextra -I./src
OBJ = app.o connection.o

all: app

app: $(OBJ)
	$(CC) $(CFLAGS) -o dis-rpC.exe $(OBJ) -lPsapi

app.o: app.c
	$(CC) $(CFLAGS) -c app.c

connection.o: connection.c ./src/connection.h
	$(CC) $(CFLAGS) -c connection.c

clean:
	rm -f *.o *.exe