VERSION ?= $(shell git describe --tags --always 2>/dev/null || echo "unknown")

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

release: $(TARGET)
	@echo "release $(VERSION)"
	rm -rf dist dis-rpC-$(VERSION)-win64.zip
	mkdir -p dist
	cp -f $(TARGET) dist/
	if [ -f "$(SDL_DLL)" ]; then cp -f "$(SDL_DLL)" dist/; fi
	cp -f readme.md dist/ 2>/dev/null || cp -f README.md dist/ 2>/dev/null || true
	cp -f LICENCE dist/ 2>/dev/null || cp -f LICENSE dist/ 2>/dev/null || true