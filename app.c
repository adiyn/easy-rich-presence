/////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
/////////////////////////////////////////////////////////////////////////////////////////

// TODO

/////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
/////////////////////////////////////////////////////////////////////////////////////////
#include "connection.h"

bool use_sdl = false;

int main(int argc, char *argv[])
{
    SetupConsole();
    showLogo();
    if (use_sdl) {
        showSdlTestWindow();
    }
    void* connect = NULL;
    printf("\n\n\n \tConnecting to discord pipe...\n");
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    connect = EstablishConnection();
    if (connect == NULL) {
        RestoreConsole(); 
        return EXIT_FAILURE;
    }
    run(connect);
    getchar();
    return EXIT_SUCCESS;
}

#endif