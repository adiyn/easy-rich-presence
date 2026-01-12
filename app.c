#define CloseWindow Win32CloseWindow
#define ShowCursor  Win32ShowCursor
#define Rectangle   Win32Rectangle
#define PlaySound   Win32PlaySound
#define LoadImage   Win32LoadImage
#define DrawText    Win32DrawText
#define DrawTextEx  Win32DrawTextEx

#define WIN32_LEAN_AND_MEAN
#define NOGDI             
#define NOUSER            

#include <windows.h>
#include <Lmcons.h>

#undef CloseWindow
#undef ShowCursor
#undef Rectangle
#undef PlaySound
#undef LoadImage
#undef DrawText
#undef DrawTextEx

#include ".\src\raylib.h"
#define RAYGUI_IMPLEMENTATION
#include ".\src\raygui.h"
#include ".\src\connexion.h"

int main ()
{
	// TODO : basic raylib UI (the purple one :3)
	// TODO : dropdown menu to choose which app to display the status of
	// TODO : fetch statuses like "is the window focused " "what is user doing on the app"...
	// TODO : when app is closed, minimise to tray, to not pollute when alt tabbing
	// TODO : add possibility to customize the status with a custom image ? or just text xd
    SetupConsole(); 
    Rectangle window = {0,0, 500, 500};
    GuiWindowBox(window, "TestWindow");
    
    DWORD u_len = UNLEN+1;
    char username[u_len];
    void* connect = NULL;
    printf("Connexion au pipe Discord...\n");
    
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
        GuiMessageBox(window, "Error", "error", NULL);
        printf("%sConnection terminated. I'm sorry to interrupt you '%s%s%s'. \nIf you still even remember that name, But I'm afraid \nyou've been misinformed. You are not here to receive a gift,\nnor have you been called here by the individual you assume, \nalthough, you have indeed been called. You have all been called here, \ninto a labyrinth of sounds and smells, misdirection and misfortune. \nA labyrinth with no exit, a maze with no prize. \nYou don't even realize that you are trapped.\n\n\t%sthis is a silly copypasta message, the program failed. (is discord running ?)%s\n\n", KGRN, KRED, username, KGRN, KRED, KNRM);
        RestoreConsole();
        return EXIT_FAILURE;
    }

    printf("Connexion reussie.\n");
    SendHandshake(connect);
    Sleep(1000);
    UpdatePresence(connect);
    printf("\n%RPC Online :3 press Enter to exit (WIP).%s\n", KGRN, KNRM);
    getchar();

    RestoreConsole();
    return EXIT_SUCCESS;
}