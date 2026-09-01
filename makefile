CC = gcc
CFLAGS = -Wall -Wextra -Werror -I"./src"
OBJ = app.o connection.o

ifeq ($(OS),Windows_NT) # bleh
	TARGET = dis-rpC.exe
	POST_BUILD = @echo "you're good to go"
else # :D
	TARGET = dis-rpC
	POST_BUILD = @echo "you're goot to go"
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	$(POST_BUILD)

app.o: app.c
	$(CC) $(CFLAGS) -c app.c

connection.o: connection.c ./src/connection.h
	$(CC) $(CFLAGS) -c connection.c

clean:
	rm -f *.o $(TARGET)