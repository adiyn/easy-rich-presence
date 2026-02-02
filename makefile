CC = gcc
CFLAGS = -L./src -Wall -Wextra
OBJ = app.o connection.o

all: app

app: $(OBJ)
	$(CC) -o app $(OBJ)

app.o: app.c
	$(CC) $(CFLAGS) -c app.c

connection.o: connection.c ./src/connection.h
	$(CC) $(CFLAGS) -c connection.c

clean:
	rm -f *.o app