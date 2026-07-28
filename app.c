/////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
/////////////////////////////////////////////////////////////////////////////////////////

// TODO

/////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
/////////////////////////////////////////////////////////////////////////////////////////
#include "connection.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

bool use_sdl = false;

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


int main(int argc, char *argv[])
{
    // "-sdl" ?
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-sdl") == 0) {
            use_sdl = true;
            break;
        }
    }

    SetupConsole();
    showLogo();
    
    if (use_sdl) {
        showSdlTestWindow();
    }

    void* connect = NULL;
    printf("\n\n\n \tConnecting to discord pipe...\n");
    
    setbuf(stdout, NULL);
    setbuf(stderr, NULL); // disable buffering for stderr and stdout to ensure immediate output
    connect = EstablishConnection();
    if (connect == NULL) {
        printf("Connection failure :c\n");
        RestoreConsole(); 
        return EXIT_FAILURE;
    }
    run(connect);
    getchar();
    return EXIT_SUCCESS;
}

#endif