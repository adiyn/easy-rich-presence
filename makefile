CC = gcc
CFLAGS = -Wall -Wextra -I./src -luser32 -lws2_32 -lshlwapi -lwinmm -lole32 -loleaut32
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