/////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
/////////////////////////////////////////////////////////////////////////////////////////

// TODO

/////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
/////////////////////////////////////////////////////////////////////////////////////////
#include ".\src\connection.h"

int main ()
{
    SetupConsole();

    system("cls");
    printf("\n\n\n");
    printf("\t%s                       ▄▄▄▄▄▄                   ▄▄▄▄▄▄     ▄▄▄▄▄▄    ▄   ▄▄▄▄▄                     %s\n", MAGHB, KNRM); // giggity
    printf("\t%s                      █▀██▀▀██                 █▀██▀▀▀█▄  █▀██▀▀▀█▄  ▀████▄▄▀                      %s\n", MAGHB, KNRM);
    printf("\t%s                        ██   ██ ▀▀ ▄██▀█         ██▄▄▄█▀    ██▄▄▄█▀    ██                          %s\n", MAGHB, KNRM);
    printf("\t%s                        ██   ██ ██ ▀███▄         ██▀▀█▄     ██▀▀▀     ██                           %s\n", MAGHB, KNRM);
    printf("\t%s                      ▄ ██   ██ ██ ▄▄██▀       ▄ ██  ██   ▄ ██        ██▄                          %s\n", MAGHB, KNRM);
    printf("\t%s                      ▀▀▀▀▀▀▀▀ ▀▀▀▀            ▀▀▀▀  ▀▀▀▀ ▀▀▀▀▀         ▀▀▀▀▀▀                     %s\n", MAGHB, KNRM);

    char username[UNLEN+1];
    void* connect = NULL;
    printf("\n\n\n \tConnecting to discord pipe...\n");
    
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