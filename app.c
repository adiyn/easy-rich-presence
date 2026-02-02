#ifdef __linux__

/////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
/////////////////////////////////////////////////////////////////////////////////////////
#include ".\src\connection.h"
int main ()
{
    SetupConsole();

    system("cls");
    printf("\n\n\n");
    printf("%s                       ▄▄▄▄▄▄                   ▄▄▄▄▄▄     ▄▄▄▄▄▄    ▄   ▄▄▄▄▄ %s\n", MAGHB, KNRM); // giggity
    printf("%s                      █▀██▀▀██                 █▀██▀▀▀█▄  █▀██▀▀▀█▄  ▀████▄▄▀  %s\n", MAGHB, KNRM);
    printf("%s                        ██   ██ ▀▀ ▄██▀█         ██▄▄▄█▀    ██▄▄▄█▀    ██      %s\n", MAGHB, KNRM);
    printf("%s                        ██   ██ ██ ▀███▄         ██▀▀█▄     ██▀▀▀     ██       %s\n", MAGHB, KNRM);
    printf("%s                      ▄ ██   ██ ██ ▄▄██▀       ▄ ██  ██   ▄ ██        ██▄      %s\n", MAGHB, KNRM);
    printf("%s                      ▀▀▀▀▀▀▀▀ ▀▀▀▀            ▀▀▀▀  ▀▀▀▀ ▀▀▀▀▀         ▀▀▀▀▀▀ %s\n", MAGHB, KNRM);

    char username[UNLEN+1];
    void* connect = NULL;
    printf("\n\n\n \tConnecting to discord pipe...\n");

    int attempts = 10;
    do
    {
        connect = ConnectionDiscord();
        attempts--;
        Sleep(69); // hmm...
    } while (connect == NULL && attempts > 0);

    if (attempts == 0)
    {   
        char* userEnv = getenv("USERNAME");
        if (userEnv) strcpy(username, userEnv);
        else strcpy(username, "GhostUser");
        printf(" \t%sConnection terminated. I'm sorry to interrupt you '%s%s%s', if you still even remember that name. \n", KGRN, KRED, username, KGRN);
        printf(" \tIf you still even remember that name. But I'm afraid you've been misinformed.\n");
        printf(" \tYou are not here to receive a gift, nor have you been called here by the individual you assume. \n");
        printf(" \tAlthough, you have indeed been called. You have all been called here. \n");
        printf(" \tInto a labyrinth of sounds and smells, misdirection and misfortune. \n");
        printf(" \tA labyrinth with no exit, a maze with no prize. You don't even realize that you are trapped.\n");
        printf("\n \t%sthis is a silly copypasta message, the program failed. (is discord running ?)%s\n\n", KRED, KNRM);
        RestoreConsole();
        return EXIT_FAILURE;
    }

    printf(" \tConnection established. %s\n", KNRM);
    SendHandshake(connect);
    Sleep(911); // ehe~ (sorry)
    UpdatePresence(connect);
    printf("\n\n\n \t%sdis-rpC is Online, press 'enter' to exit %s(WIP).%s\n", KGRN, KRED, KNRM);
    getchar();

    RestoreConsole();
    return EXIT_SUCCESS;
}

#endif