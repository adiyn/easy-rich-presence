CC = gcc

# DISRPC_USE_SDL: 0 disabled, 1 enabled, default is 0
DISRPC_USE_SDL ?= 0

CFLAGS = -Wall -Wextra -I./src
LDFLAGS = 
LDLIBS = -lPsapi
SDL_DLL ?= ./src/SDL2.dll

ifeq ($(DISRPC_USE_SDL),1)
	CFLAGS += -I"./src" -DDISRPC_USE_SDL=1
	LDFLAGS += -L"./src"
	LDLIBS += -lmingw32 -lSDL2main -lSDL2
endif

OBJ = app.o connection.o

all: app

app: $(OBJ)
	$(CC) $(CFLAGS) -o dis-rpC.exe $(OBJ) $(LDFLAGS) $(LDLIBS)
	if exist "$(SDL_DLL)" copy /Y "$(SDL_DLL)" . >nul

app.o: app.c
	$(CC) $(CFLAGS) -c app.c

connection.o: connection.c ./src/connection.h
	$(CC) $(CFLAGS) -c connection.c

clean:
	rm -f *.o *.exe













# windows is fucking garbage