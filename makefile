CC = gcc
CFLAGS = -Wall -Wextra -I"./src" -I"./src/include"
OBJ = app.o connection.o

ifeq ($(OS),Windows_NT) # bleh
	TARGET = dis-rpC.exe
	LDFLAGS = -L"./src" -L"./src/lib"
	LDLIBS = -lPsapi -lmingw32 -lSDL2main -lSDL2
	SDL_DLL = ./SDL2.dll
	POST_BUILD = @echo "you good to og"
else # :D
	TARGET = dis-rpC
	LDFLAGS = 
	LDLIBS = -lSDL2
	POST_BUILD = @echo "have fun, ig"
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS) $(LDLIBS)
	$(POST_BUILD)

app.o: app.c
	$(CC) $(CFLAGS) -c app.c

connection.o: connection.c ./src/connection.h
	$(CC) $(CFLAGS) -c connection.c

clean:
	rm -f *.o $(TARGET)