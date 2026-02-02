#ifdef __linux__

#elif _WIN32
#include ".\src\connection.h"
int main ()
{
    char command = 'w';
    do 
    {
        SetupConsole();

        /* horrendous shit
        printf("\u0020\u0020\u2584\u2584\u2584\u2584\u2584\u2584\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u2584\u2584\u2584\u2584\u2584\u2584\u0020\u0020\u0020\u0020\u0020\u2584\u2584\u2584\u2584\u2584\u2584\u0020\u0020\u0020\u0020\u2584\u0020\u0020\u0020\u2584\u2584\u2584\u2584\u0020\n");
        printf("\u0020\u2588\u2580\u2588\u2588\u2580\u2580\u2588\u2588\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u2588\u2580\u2588\u2588\u2580\u2580\u2580\u2588\u2584\u0020\u0020\u2588\u2580\u2588\u2588\u2580\u2580\u2580\u2588\u2584\u0020\u0020\u2580\u2588\u2588\u2588\u2588\u2588\u2588\u2580\n");
        printf("\u0020\u0020\u0020\u2588\u2588\u0020\u0020\u0020\u2588\u2588\u0020\u2580\u2580\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u2588\u2588\u2584\u2584\u2584\u2588\u2580\u0020\u0020\u0020\u0020\u2588\u2588\u2584\u2584\u2584\u2588\u2580\u0020\u0020\u0020\u0020\u2588\u2588\n");
        printf("\u0020\u0020\u0020\u2588\u2588\u0020\u0020\u0020\u2588\u2588\u0020\u2588\u2588\u0020\u2584\u2588\u2588\u2580\u2588\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u2588\u2588\u2580\u2580\u2588\u2584\u0020\u0020\u0020\u0020\u0020\u2588\u2588\u2580\u2580\u2580\u0020\u0020\u0020\u0020\u0020\u0020\u2588\u2588\n");
        printf("\u0020\u2584\u0020\u2588\u2588\u0020\u0020\u0020\u2588\u2588\u0020\u2588\u2588\u0020\u2580\u2588\u2588\u2588\u2584\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u2584\u0020\u2588\u2588\u0020\u0020\u2588\u2588\u0020\u0020\u0020\u2584\u0020\u2588\u2588\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u2588\u2588\n");
        printf("\u0020\u2580\u2588\u2588\u2580\u2588\u2588\u2588\u2580\u0020\u2584\u2588\u2588\u2588\u2584\u2584\u2588\u2588\u2580\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u2580\u2588\u2588\u2580\u0020\u0020\u2580\u2588\u2588\u2580\u0020\u2580\u2588\u2588\u2580\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u2580\u2588\u2588\u2588\u2588\u2588\n");
        */
        
        //the normal printf statemnets
        printf("  ▄▄▄▄▄▄                   ▄▄▄▄▄▄     ▄▄▄▄▄▄    ▄   ▄▄▄▄▄ \n");
        printf(" █▀██▀▀██                 █▀██▀▀▀█▄  █▀██▀▀▀█▄  ▀████▄▄▀\n");
        printf("   ██   ██ ▀▀               ██▄▄▄█▀    ██▄▄▄█▀    ██\n");
        printf("   ██   ██ ██ ▄██▀█         ██▀▀█▄     ██▀▀▀     ██n");
        printf(" ▄ ██   ██ ██ ▀███▄       ▄ ██  ██   ▄ ██        ██▄n");
        printf(" ▀██▀███▀ ▄███▄▄██▀       ▀██▀  ▀██▀ ▀██▀         ▀█████▄\n");

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
    } while (command != 'q');
    return EXIT_SUCCESS;
}

#endif