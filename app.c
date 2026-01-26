#ifdef __linux__

#elif _WIN32
#include ".\src\connection.h"
int main ()
{
	// TODO : Simple terminal UI
	// TODO : Possibility to customize the status with a custom image, custom title...

    SetupConsole(); 
    
    bool showMessageBox = false;

    DWORD u_len = UNLEN+1;
    char username[UNLEN+1];
    void* connect = NULL;
    printf("Connecting to discord pipe...\n");
    
    int attempts = 10;
    do
    {
        connect = ConnectionDiscord();
        attempts--;
        Sleep(69); 
    } while (connect == NULL && attempts > 0);

    if (attempts == 0)
    {   
        char* userEnv = getenv("USERNAME");
        if (userEnv) strcpy(username, userEnv);
        else strcpy(username, "GhostUser");
        printf("%sConnection terminated. I'm sorry to interrupt you '%s%s%s'. \nIf you still even remember that name, But I'm afraid you've been misinformed.\nYou are not here to receive a gift, nor have you been called here by the individual you assume. \nAlthough, you have indeed been called. You have all been called here. \nInto a labyrinth of sounds and smells, misdirection and misfortune. \nA labyrinth with no exit, a maze with no prize. \nYou don't even realize that you are trapped.\n\n\t%sthis is a silly copypasta message, the program failed. (is discord running ?)%s\n\n", KGRN, KRED, username, KGRN, KRED, KNRM);
        RestoreConsole();
        return EXIT_FAILURE;
    }

    printf("Connection established..\n");
    SendHandshake(connect);
    Sleep(1000);
    UpdatePresence(connect);
    printf("\n\t\t\t\t%sdis-rpC is Online :3 press Enter to exit%s (WIP).\n", KGRN, KNRM);
    getchar();

    RestoreConsole();
    return EXIT_SUCCESS;
}

#endif