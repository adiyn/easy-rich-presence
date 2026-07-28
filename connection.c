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

// windows API garbage
static HANDLE stdoutHandle;
static unsigned int oldCodePage;
static unsigned long outModeInit;

#pragma pack(push, 1) 
// stream must be continuous, no padding
typedef struct PacketHeader
{
	int opCode;
	int opLength;
} PacketHeader;
#pragma pack(pop)

void showLogo()
{ // print logo
    printf("\n\n\n");
    printf("\t%s                       ▄▄▄▄▄▄                   ▄▄▄▄▄▄     ▄▄▄▄▄▄    ▄   ▄▄▄▄▄                     %s\n", MAGHB, KNRM);
    printf("\t%s                      █▀██▀▀██                 █▀██▀▀▀█▄  █▀██▀▀▀█▄  ▀████▄▄▄█▀                    %s\n", MAGHB, KNRM);
    printf("\t%s                        ██   ██  ▀▀ ▄██▀█         ██▄▄▄█▀    ██▄▄▄█▀    ██                         %s\n", MAGHB, KNRM);
    printf("\t%s                        ██   ██  ██ ▀███▄         ██▀▀█▄     ██▀▀▀     ██                          %s\n", MAGHB, KNRM);
    printf("\t%s                      ▄ ██   ██  ██ ▄▄██        ▄ ██  ██   ▄ ██        ██▄                         %s\n", MAGHB, KNRM);
    printf("\t%s                     ▀▀▀▀▀▀▀▀▀  ▀▀▀             ▀▀▀▀  ▀▀▀▀ ▀▀▀▀▀        ▀▀▀▀▀▀                     %s\n", MAGHB, KNRM);
}

void SetupConsole(void)
{   // setup console for utf-8 and virtual terminal processing
    unsigned long outMode = 0x0;
    
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // save old console state
    oldCodePage = GetConsoleOutputCP();
    if(stdoutHandle == INVALID_HANDLE_VALUE) exit(GetLastError());
    if(!GetConsoleMode(stdoutHandle, &outMode)) exit(GetLastError());
    
    // set encoding to utf-8 
    SetConsoleOutputCP(CP_UTF8);

    // enable virtual terminal processing
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if(!SetConsoleMode(stdoutHandle, outMode)) exit(GetLastError());   
}

void RestoreConsole(void) {
    // Reset console 
    SetConsoleOutputCP(oldCodePage);
    SetConsoleMode(stdoutHandle, outModeInit);
}

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

// Store PIDs of processes with visible windows
static DWORD* g_visiblePids = NULL;
static int g_visibleCount = 0;
static int g_visibleCapacity = 0;

// windows API garbage
BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam)
{
    (void)lParam; 
    // unused
    if (!IsWindowVisible(hwnd)) return true; 
    // skip invisible windows
    
    char title[256];
    if (GetWindowTextA(hwnd, title, sizeof(title)) == 0) return true; 
    // skip windows with no title
    
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid); 
    // get PID of the process that owns the window
    
    for (int i = 0; i < g_visibleCount; i++) { 
        // check if PID is already recorded
        if (g_visiblePids[i] == pid) return true;
    }
    
    if (g_visibleCount >= g_visibleCapacity) {
        // double the capacity of the array if needed
        g_visibleCapacity = g_visibleCapacity == 0 ? 64 : g_visibleCapacity * 2;
        g_visiblePids = realloc(g_visiblePids, g_visibleCapacity * sizeof(DWORD));
    }
    g_visiblePids[g_visibleCount++] = pid;
    
    return true;
}

bool hasVisibleWindow(DWORD pid)
{
    for (int i = 0; i < g_visibleCount; i++) {
        if (g_visiblePids[i] == pid) return true;
        // check if the given PID has a visible window
    }
    return false;
}

char** getProcsNames(void)
{
    g_visibleCount = 0;
    EnumWindows(EnumWindowsCallback, 0);
    
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    // NOTE : CreateToolhelp32Snapshot works across 32/64 bit processes unlike EnumProcesses
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        // if the snapshot creation fails, print an error and return NULL
        fprintf(stderr, "CreateToolhelp32Snapshot failed\n");
        return NULL;
    }
    
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    int totalProcs = 0;
    if (Process32First(hSnapshot, &pe32)) {
        do {
            totalProcs++;
        } while (Process32Next(hSnapshot, &pe32));
    }
    
    char** procNames = malloc(sizeof(char*) * (totalProcs + 1));
    if (procNames == NULL) {
        fprintf(stderr, "go buy RAM smh (alloc error)\n");
        // what the hell is this error message
        CloseHandle(hSnapshot);
        return NULL;
    }
    
    pe32.dwSize = sizeof(PROCESSENTRY32);
    int count = 0;
    
    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (hasVisibleWindow(pe32.th32ProcessID) && !isToBeIgnored(pe32.szExeFile)) {
                int isDupe = 0;
                for (int j = 0; j < count; j++) {
                    if (_stricmp(procNames[j], pe32.szExeFile) == 0) {
                        isDupe = 1;
                        break;
                    }
                }
                if (!isDupe) {
                    procNames[count] = strdup(pe32.szExeFile);
                    count++;
                }
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    
    CloseHandle(hSnapshot);
    procNames[count] = NULL; // SEGVn't
    return procNames;
}

char* appNameToAssetName(const char* appName) 
{
    char* assetName = NULL;
    if (_stricmp(appName, "firefox.exe") == 0) {
        assetName = "firefox";
    } else if (_stricmp(appName, "chrome.exe") == 0) {
        assetName = "chrome";
    } else if (_stricmp(appName, "code.exe") == 0) {
        assetName = "vscode";
    } else if (_stricmp(appName, "msedge.exe") == 0) {
        assetName = "edge";
    } else if (_stricmp(appName, "discord.exe") == 0) {
        assetName = "discord";
    } else if (_stricmp(appName, "w64devkit.exe") == 0) {
        assetName = "w64devkit";
    } else if (_stricmp(appName, "minecraft.exe") == 0) {
        assetName = "minecraft";
    } else if (_stricmp(appName, "hytale.exe") == 0) {
        assetName = "hytale";
    } else {
        assetName = "default";
    }
    return assetName;
}

void showRunning(char** procs)
{
    // print the list of running applications with visible windows
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

void UpdatePresence(HANDLE hPipe, const char* details, const char* subtitle, const char* appName)
{
    // update the Discord Rich Presence with the given details, subtitle, and application name
    char json_buffer[MAX_BUFFER_SIZE];
    int APP_PID = GetCurrentProcessId();
    
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
        APP_PID, subtitle, details, appNameToAssetName(appName), appName, rand()%68+1);
    
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

HANDLE Connect()
{
    // establish a connection to the Discord IPC pipe
	HANDLE hipe = CreateFileA(DIS_PIPE_ADDR, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if (hipe == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    return hipe;
}

HANDLE EstablishConnection()
{
    // attempt to establish a connection to Discord's IPC pipe, retrying up to 10 times if necessary
    void* connect = NULL;
    int attempts = 10;
    
    do
    {
        connect = Connect();
        attempts--;
        Sleep(69);
    } while (connect == NULL && attempts > 0);

    if (attempts == 0)
    {   
        // silly FNAF copypasta error message
        char username[UNLEN+1];
        char* userEnv = getenv("USERNAME");
        if (userEnv) strcpy(username, userEnv);
        else strcpy(username, "GhostUser");
        printf(" \t%sConnection terminated. I'm sorry to interrupt you '%s'%s,\n", KGRN, username, KNRM);
        printf("\t%sif you still even remember that name.%s\n", KRED, KNRM);
        printf("\t%sIf you still even remember that name. But I'm afraid you've been misinformed.%s\n", KRED, KNRM);
        printf("\tYou are not here to receive a gift, nor have you been called here by the individual you assume.\n");
        printf("\tAlthough, you have indeed been called. You have all been called here.\n");
        printf("\tInto a labyrinth of sounds and smells, misdirection and misfortune.\n");
        printf("\tA labyrinth with no exit, a maze with no prize. You don't even realize that you are trapped.\n\n");
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
    // do i have to explain ?
    if (process != NULL) {
        printf("\n\t%sConnected to : %s%s%s\n", MAGHB, KGRN, process, KNRM);
    }
}

void freeProcs(char** procs)
{
    // SayonaRAM... get it...? haha...
    if (procs == NULL) return;
    for (int i = 0; procs[i] != NULL; i++) {
        free(procs[i]);
    }
    free(procs);
}

void clearConsole () {
    printf("\033[2J\033[1;1H");
}

void run(HANDLE connect)
{
    // main loop for the application, allowing the user to select a process
    // to show in their Discord Rich Presence, refresh the list of processes,
    // clear the presence, or quit the application
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
        procs = getProcsNames();
        procCount = 0;
        for (int i = 0; procs[i] != NULL; i++) procCount++;
        showConnectionStatus(chosenApp);
        printf("\n\t%sSelect a process : [1-9 A-F] | [r]efresh | [c]lear | [q]uit%s\n\n", MAGHB, KNRM);
        showRunning(procs);
        printf("\t> ");
        scanf(" %c", &command);
        
        if (command == 'r') {
            printf("\n\t%sRefreshing...%s\n\n", KGRN, KNRM);
            Sleep(200);
        } else if (command == 'c') {
            chosenApp = NULL;
            cleared = true;
            printf("\n\t%sClearing presence...%s\n\n", KGRN, KNRM);
            Sleep(200);
        } else if ((command >= '1' && command <= '9') || (command == '0' && procCount > 9) || ((command >= 'A' && command <= 'F') || (command >= 'a' && command <= 'f'))) {
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
    freeProcs(procs);
}

#endif