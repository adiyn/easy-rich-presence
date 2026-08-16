/***
DisRPC is an RPC tool made in C !
₍ᐢ. .ᐢ₎ ₊˚⊹ by @adiyn
***/

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "./src/connection.h"

HANDLE stdoutHandle;
unsigned int oldCodePage;
unsigned long outModeInit;

const AppAssetMap APP_MAP[] = {
    { "firefox.exe",    "firefox"   },
    { "chrome.exe",     "chrome"    },
    { "code.exe",       "vscode"    },
    { "msedge.exe",     "edge"      },
    { "discord.exe",    "discord"   },
    { "w64devkit.exe",  "w64devkit" },
    { "minecraft.exe",  "minecraft" },
    { "hytale.exe",     "hytale"    },
    { "qobuz.exe",      "qobuz"     },
};
const size_t APP_MAP_COUNT = sizeof(APP_MAP) / sizeof(APP_MAP[0]);

/// @brief shows the logo on the terminal
void showLogo()
{
    printf("\n\n\n");
    printf("\t%s                       ▄▄▄▄▄▄                   ▄▄▄▄▄▄     ▄▄▄▄▄▄    ▄   ▄▄▄▄▄                     %s\n", MAGHB, KNRM);
    printf("\t%s                      █▀██▀▀██                 █▀██▀▀▀█▄  █▀██▀▀▀█▄  ▀████▄▄▄█▀                    %s\n", MAGHB, KNRM);
    printf("\t%s                        ██   ██  ▀▀ ▄██▀█         ██▄▄▄█▀    ██▄▄▄█▀    ██                         %s\n", MAGHB, KNRM);
    printf("\t%s                        ██   ██  ██ ▀███▄         ██▀▀█▄     ██▀▀▀     ██                          %s\n", MAGHB, KNRM);
    printf("\t%s                      ▄ ██   ██  ██ ▄▄██        ▄ ██  ██   ▄ ██        ██▄                         %s\n", MAGHB, KNRM);
    printf("\t%s                     ▀▀▀▀▀▀▀▀▀  ▀▀▀             ▀▀▀▀  ▀▀▀▀ ▀▀▀▀▀        ▀▀▀▀▀▀                     %s\n", MAGHB, KNRM);
}

/// @brief enables virtual terminal processing to be able to use ASCII escape codes for example
void SetupConsole()
{   
    unsigned long outMode = 0x0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    oldCodePage = GetConsoleOutputCP();
    GetConsoleMode(stdoutHandle, &outModeInit);
    if(stdoutHandle == INVALID_HANDLE_VALUE) exit(GetLastError());
    if(!GetConsoleMode(stdoutHandle, &outMode)) exit(GetLastError());
    SetConsoleOutputCP(CP_UTF8);
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if(!SetConsoleMode(stdoutHandle, outMode)) exit(GetLastError());   
}

/// @brief restores the console to a void state
void RestoreConsole() {
    SetConsoleOutputCP(oldCodePage);
    SetConsoleMode(stdoutHandle, outModeInit);
}

/// @brief opens a connection to the pipe by sending a json handshake with my discord app id
/// @param hPipe the HANDLE to the discord ipc pipe
void SendHandshake(HANDLE hPipe)
{
    char json_buffer[MAX_BUFFER_SIZE];
    sprintf(json_buffer, "{\"v\": 1, \"client_id\": \"%s\"}", DIS_APP_ID);
    int json_len = strlen(json_buffer);

    PacketHeader header;
    header.opCode = 0;
    header.opLength = json_len;

    unsigned long bytesWritten;
    WriteFile(hPipe, &header, sizeof(PacketHeader), &bytesWritten, NULL);
    WriteFile(hPipe, json_buffer, json_len, &bytesWritten, NULL);

    printf(" \tHandshank request sent ! %s(Opcode: %d, Len: %d)%s\n", KGRN, header.opCode, header.opLength, KNRM);
    printf(" \tRequest: %s%s%s\n", KGRN, json_buffer, KNRM);
}

/// @brief determines whether an app is to be ignored or not by checkign if it's in the ignored list
/// @param name the name of the app
/// @return whether app is to be ignored
bool isToBeIgnored(const char* name)
{
    const char* ignored[] = {
        "dis-rpC.exe", "app.exe", NULL
    };
    
    for (int i = 0; ignored[i] != NULL; i++) {
        if (_stricmp(name, ignored[i]) == 0) return true;
    }
    return false;
}

/// @brief enumerates through apps with a visible window
/// @param hwnd window handle
/// @param lParam app defined parameter
/// @return true/false whether to continue the enumeration
static BOOL CALLBACK EnumWindowsFilter(HWND hwnd, LPARAM lParam)
{
    AppList* list = (AppList*)lParam;

    if (!IsWindowVisible(hwnd)) return true;
    LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
    if (exStyle & WS_EX_TOOLWINDOW) return true;
    if (GetWindowTextLengthA(hwnd) == 0) return true;
    RECT rc;
    if (GetWindowRect(hwnd, &rc)) {
        if ((rc.right - rc.left) <= 0 || (rc.bottom - rc.top) <= 0) return true;
    }
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid == 0) return true;

    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProc) return true;

    char fullPath[MAX_PATH];
    DWORD size = sizeof(fullPath);
    if (QueryFullProcessImageNameA(hProc, 0, fullPath, &size)) {
        char* exeName = strrchr(fullPath, '\\');
        exeName = exeName ? exeName + 1 : fullPath;

        if (!isToBeIgnored(exeName)) {
            bool isDupe = false;
            for (int i = 0; i < list->count; i++) {
                if (_stricmp(list->names[i], exeName) == 0) {
                    isDupe = true;
                    break;
                }
            }
            if (!isDupe) {
                if (list->count >= list->capacity) {
                    list->capacity = (list->capacity == 0) ? 16 : list->capacity * 2;
                    list->names = realloc(list->names, sizeof(char*) * list->capacity);
                }
                list->names[list->count++] = _strdup(exeName);
            }
        }
    }
    CloseHandle(hProc);
    return TRUE;
}

/// @brief returns a list of process names
/// @return a deduplicated list of proc names that have a visible window
char** getProcsNames(void)
{
    AppList list = { .names = NULL, .count = 0, .capacity = 0 };
    EnumWindows(EnumWindowsFilter, (LPARAM)&list);

    list.names = realloc(list.names, sizeof(char*) * (list.count + 1));
    list.names[list.count] = NULL;
    return list.names;
}

/// @brief links the appName to the corresponding assetName
/// @param appName the detected app name as a string
/// @return the assetName
const char* appNameToAssetName(const char* appName) 
{
    if (!appName) return "default";

    for (size_t i = 0; i < APP_MAP_COUNT; i++) {
        if (_stricmp(appName, APP_MAP[i].exe) == 0) {
            return APP_MAP[i].asset;
        }
    }
    return "default";
}

/// @brief prints the currently running apps on the user's machine
/// @param procs the list of the currently running procvesses with their names
void showRunning(char** procs)
{
    printf("\tRunning apps :\n");
    int i;
    for (i = 0; i < 15 && procs[i] != NULL; i++) {
        if (i >= 9) {
            printf("\t\t@ [%c] %s\n", 'A' + i - 9, procs[i]);
        }
        else {
            printf("\t\t@ [%d] %s\n", i+1, procs[i]);
        }
    }
}


/// @brief writes into the ipc pipe the json formatted payload with all the information to be updated
/// @param hPipe the HANDLE to the discord ipc pipe
/// @param details discord RPC stuff
/// @param subtitle discord RPC stuff
/// @param appName discord RPC stuff
void UpdatePresence(HANDLE hPipe, const char* details, const char* subtitle, const char* appName)
{
    char json_buffer[MAX_BUFFER_SIZE];
    int APP_PID = GetCurrentProcessId();
    int nonce = rand()%'z';

    sprintf(json_buffer, 
        "{"
            "\"cmd\":\"SET_ACTIVITY\","
            "\"args\":{"
                "\"pid\":%d,"
                "\"activity\":{"
                    "\"state\":\"%s\","
                    "\"details\":\"%s\","
                    "\"assets\":{"
                        "\"large_image\":\"%s\","
                        "\"large_text\":\"%s\""
                    "},"
                    "\"buttons\":[{"
                        "\"label\":\"dis-rpC\","
                        "\"url\":\"https://codeberg.org/adiyn/dis-rpC\""
                    "}]"
                "}"
            "},"
            "\"nonce\":%d"
        "}",
        APP_PID, subtitle, details, appNameToAssetName(appName), appName, nonce);
    
    int json_len = strlen(json_buffer);
    
    PacketHeader header;
    header.opCode = 1;
    header.opLength = json_len;
	
    unsigned long bytesWritten;
    WriteFile(hPipe, &header, sizeof(PacketHeader), &bytesWritten, NULL);
    WriteFile(hPipe, json_buffer, json_len, &bytesWritten, NULL);

    char response[MAX_BUFFER_SIZE];
    unsigned long bytesRead = 0;
    ReadFile(hPipe, response, MAX_BUFFER_SIZE, &bytesRead, NULL);

    printf(" \tPayload Sent : %s%s%s\n", KGRN, json_buffer, KNRM);
}

/// @brief connects to the discord ipc pipe
/// @return the HANDLE connected to the ipc pipe
HANDLE Connect()
{
	HANDLE hipe = CreateFileA(DIS_PIPE_ADDR, GENERIC_READ
        | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if (hipe == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    return hipe;
}

/// @brief attempts 10 times at most to connect to the ipc pipe
/// @return the HANDLE connected to discord ipc pipe
HANDLE EstablishConnection()
{
    HANDLE connect = NULL;
    int attempts = 10;
    
    do
    {
        connect = Connect();
        attempts--;
        Sleep(69);
    } while (connect == NULL && attempts > 0);

    if (attempts == 0)
    {   
        char username[UNLEN+1];
        char* userEnv = getenv("USERNAME");
        if (userEnv) strcpy(username, userEnv);
        else strcpy(username, "GhostUser");
        printf(" \t%sConnection terminated. I'm sorry to interrupt you '%s'%s,\n", KGRN, username, KNRM);
        printf("\t%sif you still even remember that name.%s\n", KRED, KNRM);
        printf("\t%sIf you still even remember that name. But I'm afraid you've been misinformed.%s\n", KRED, KNRM);
        printf("\t%sYou are not here to receive a gift, nor have you been called here by the individual you assume.%s\n", KRED, KNRM);
        printf("\t%sAlthough, you have indeed been called. You have all been called here.%s\n", KRED, KNRM);
        printf("\t%sInto a labyrinth of sounds and smells, misdirection and misfortune.%s\n", KRED, KNRM);
        printf("\t%sA labyrinth with no exit, a maze with no prize. You don't even realize that you are trapped.%s\n\n", KRED, KNRM);
        printf(" \t%sthis is a silly copypasta message, the program failed. (is discord running ?)%s\n\n", KRED, KNRM);
        return NULL;
    }
    
    printf(" \tConnection established. %s\n", KNRM);
    SendHandshake(connect);
    Sleep(911); // Jschlatt ???
    printf("\n\n\n \tdis-rpC is %sOnline%s %s(WIP).%s\n\n", KGRN, KNRM, KRED, KNRM);
    return connect;
}

void showConnectionStatus(char* process)
{
    if (process != NULL) {
        printf("\n\t%sConnected to : %s%s%s\n", MAGHB, KGRN, process, KNRM);
    }
}

/// @brief frees the memory
/// @param procs 
void freeProcs(char** procs)
{
    if (procs == NULL) return;
    for (int i = 0; procs[i] != NULL; i++) {
        free(procs[i]);
    }
    free(procs);
}

void clearConsole () {
    printf("\033[2J\033[1;1H");
}

/// @brief main loop for the application, allowing the user to select a process
// to show in their Discord Rich Presence, refresh the list of processes,
// clear the presence, or quit the application
/// @param connect the HANDLE connected to the discord ipc pipe
void run(HANDLE connect)
{
    char details[MAX_BUFFER_SIZE];
    char state[MAX_BUFFER_SIZE];
    char command = 'N';
    char** procs = getProcsNames();
    char* chosenApp = NULL;
    int procCount = 0;
    bool cleared = false;
    
    for (int i = 0; procs[i] != NULL; i++) procCount++;
    
    while (command != 'q')
    {
        if (cleared) {
            UpdatePresence(connect, "Zzz...", "", "");
            cleared = false;
        }
        clearConsole();
        showLogo();
        if (!use_sdl) {
            printf("\tCLI mode enabled (based); quit & re-run with the '-sdl' argument to use the GUI\n");
        }
        freeProcs(procs);
        procs = getProcsNames();
        procCount = 0;
        for (int i = 0; procs[i] != NULL; i++) procCount++;
        showConnectionStatus(chosenApp);
        printf("\n\t%sSelect a process : [1-9 A-F] | [r]efresh | [c]lear | [q]uit%s\n\n", MAGHB, KNRM);
        showRunning(procs);
        printf("\t> ");
        command = getch();
        
        if (command == 'r' || command == 'R') {
            printf("\n\t%sRefreshing...%s\n\n", KGRN, KNRM);
            Sleep(200);
        } else if (command == 'c' || command == 'C') {
            chosenApp = NULL;
            cleared = true;
            printf("\n\t%sClearing presence...%s\n\n", KGRN, KNRM);
            Sleep(200);
        } else if ((command >= '1' && command <= '9')
         || (command == '0' && procCount > 9)
          || ((command >= 'A' && command <= 'F')
           || (command >= 'a' && command <= 'f'))) {
            int index = -1;
            
            if (command >= '1' && command <= '9') {
                index = command - '1';
            } else if (command == '0') {
                index = 9;
            } else if (command >= 'A' && command <= 'F') {
                index = command - 'A' + 9;
            } else if (command >= 'a' && command <= 'f') {
                index = command - 'a' + 9;
            }
            
            if (index >= 0 && index < procCount && procs[index] != NULL) {
                chosenApp = procs[index];
                sprintf(details, "Zzz...");
                sprintf(state, "Using %s", appNameToAssetName(chosenApp));
                UpdatePresence(connect, details, state, chosenApp);
                Sleep(500);
            }
        }
    }
    printf("\n\t%sbabaiii :3%s\n\n", KGRN, KNRM);
    clearConsole();
    freeProcs(procs);
    exit(EXIT_SUCCESS);
}
#endif