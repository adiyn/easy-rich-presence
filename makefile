CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wundef -Wpointer-arith -Wshadow -Wwrite-strings -Wconversion -I"./src"

ifeq ($(OS),Windows_NT)
    TARGET = dis-rpC.exe
    CONN_SRC = connection_win32.c
    CLEAN_CMD = rm -f *.o *.exe
    POST_BUILD = @echo "you're good to go"
else
    TARGET = dis-rpC
    CONN_SRC = connection_linux.c
    CLEAN_CMD = rm -f *.o $(TARGET)
    POST_BUILD = @echo "you're good to go"
endif

OBJ = app.o $(CONN_SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	$(POST_BUILD)

app.o: app.c ./src/connection.h
	$(CC) $(CFLAGS) -c app.c

%.o: %.c ./src/connection.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(CLEAN_CMD)