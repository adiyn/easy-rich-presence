#include "src/connection.h"

int main(void)
{
    SetupConsole();
    
    atexit(RestoreConsole);

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    showLogo();
    printf("\n\n\n \tConnecting to discord pipe...\n");

    void* connect = EstablishConnection();

    run(connect);

    printf("\nAppuyez sur Entrée pour quitter...");
    getchar();

    return EXIT_SUCCESS; 
}