/////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
/////////////////////////////////////////////////////////////////////////////////////////

// TODO

/////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
/////////////////////////////////////////////////////////////////////////////////////////
#include "connection.h"

#ifndef DISRPC_USE_SDL
#define DISRPC_USE_SDL 0
#endif

#if DISRPC_USE_SDL
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

static void showSdlTestWindow(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL init failed: %s\n", SDL_GetError());
        return;
    }

    SDL_Window* window = SDL_CreateWindow("dis-rpC SDL test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 900, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_ShowWindow(window);

    const Uint32 startTime = SDL_GetTicks();
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        if (SDL_GetTicks() - startTime > 3000u) {
            running = false;
        }

        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
#else
static void showSdlTestWindow(void)
{
    printf("SDL test window disabled; rebuild with -DDISRPC_USE_SDL=1 and an SDL2 library to enable it.\n");
}
#endif

int main ()
{
    SetupConsole();
    showLogo();
    showSdlTestWindow();

    void* connect = NULL;
    printf("\n\n\n \tConnecting to discord pipe...\n");
    
    setbuf(stdout, NULL);
    setbuf(stderr, NULL); // disable buffering for stderr and stdout to ensure immediate output
    connect = EstablishConnection();
    if (connect == NULL) {
        printf("Connection failure :c\n");
        return EXIT_FAILURE;
        RestoreConsole();
    }
    run(connect);
    getchar();
    return EXIT_SUCCESS;
}

#endif