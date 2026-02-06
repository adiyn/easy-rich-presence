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

#include "src/connection.h"

#pragma pack(push, 1) // discord needs a continuous stream of bytes, so we need to pack the struct
typedef struct PacketHeader
{
	int opCode;
	int opLength;
} PacketHeader;
#pragma pack(pop)

void SetupConsole(void) {   
    unsigned long outMode = 0x0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // save old console state
    oldCodePage = GetConsoleOutputCP();
    if(stdoutHandle == INVALID_HANDLE_VALUE) exit(GetLastError());
    if(!GetConsoleMode(stdoutHandle, &outMode)) exit(GetLastError());
    
    // set encoding to utf-8 
    SetConsoleOutputCP(65001);

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

// windows api garbage
char** getProcsNames(DWORD processID, char* buffer, size_t bufferSize)
{
    char** procNames = malloc(sizeof(char*) * 42); // #JFA

    if (procNames == NULL) {
        fprintf(stderr, "lol u need more ram\n");
        return NULL;
    }

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL) {
        fprintf(stderr, "processn't %ld\n", processID);
        free(procNames);
        return NULL;
    }

    HMODULE hMod;
    DWORD cbNeeded;

    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
        GetModuleBaseNameA(hProcess, hMod, buffer, bufferSize);
        procNames[0] = strdup(buffer); // store name
    } else {
        fprintf(stderr, "process enumeration failed :( %ld\n", processID);
        free(procNames);
        CloseHandle(hProcess);
        return NULL;
    }

    CloseHandle(hProcess);
    return procNames;
}

char* appNameToAssetName(const char* appName) {
    size_t j = 0;
    char* assetName = NULL;
    for (size_t i = 0; appName[i] != '\0' && j < MAX_BUFFER_SIZE - 1; i++) {
        if (strcmp(appName, "Discord.exe") == 0) {
            assetName = "edge";
            break;
        }
        else if (strcmp(appName, "chrome.exe") == 0) {
            assetName = "chrome";
            break;
        }
        else if (strcmp(appName, "Firefox.exe") == 0) {
            assetName = "firefox";
            break;
        }
        else {
            assetName = "sleepy";
        }
    }
    return assetName;
}

void showRunning(char** procs) {
    printf("Running apps :\n");
    for (int i = 0; i < 9 && procs[i] != NULL; i++) {
        printf("\t\t@ [%d] %s\n", i + 1, procs[i]);
    }
}

void UpdatePresence(HANDLE hPipe, const char* message, const char* state, const char* appName)
{
    char json_buffer[MAX_BUFFER_SIZE];
    int APP_PID = GetCurrentProcessId();
    
    sprintf(json_buffer, 
        "{\"cmd\": \"SET_ACTIVITY\","
        "\"args\": {"
            "\"pid\": %d,"
            "\"activity\": {"
                "\"details\": \"%s\","
                "\"state\": \"%s\","
                "\"assets\": {"
                    "\"large_image\": \"%s\","
                    "\"large_text\": \"%s\""
                "}"
            "}"
        "},"
        "\"nonce\": \"%d\"}", 
        APP_PID, message, state, appNameToAssetName(appName), appName, 69);
	int json_len = strlen(json_buffer);

    PacketHeader header;
    header.opCode = 1;
    header.opLength = json_len;
    unsigned long bytesWritten;
	
    // more windows api garbage
    WriteFile(hPipe, &header, sizeof(PacketHeader), &bytesWritten, NULL);
    WriteFile(hPipe, json_buffer, json_len, &bytesWritten, NULL);

    printf(" \tPayload Sent : %s%s%s\n", KGRN, json_buffer, KNRM);
}

// even more windows api garbage
HANDLE ConnectionDiscord()
{
	HANDLE hipe = CreateFileA(DIS_PIPE_ADDR, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if (hipe == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    return hipe;
}

void* EstablishConnection()
{
    void* connect = NULL;
    int attempts = 10;
    
    do
    {
        connect = ConnectionDiscord();
        attempts--;
        Sleep(69); // hmm... magic.
    } while (connect == NULL && attempts > 0);

    if (attempts == 0)
    {   
        char username[UNLEN+1];
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
        return NULL;
    }
    
    printf(" \tConnection established. %s\n", KNRM);
    SendHandshake(connect);
    Sleep(911); // Jsclatt ???
    printf("\n\n\n \tdis-rpC is %sOnline%s %s(WIP).%s\n", KGRN, KNRM, KRED, KNRM);
    return connect;
}

void run(HANDLE connect) {
    char message[MAX_BUFFER_SIZE];
    char state[MAX_BUFFER_SIZE];
    char command = '0';
    char** procs = getProcsNames(GetCurrentProcessId(), message, MAX_BUFFER_SIZE);
    showRunning(procs);

    while (command != 'q') {
        printf("\tchoose app to display in presence (q to quit / n for next page / p for previous) : ");
        scanf(" %c", &command);
        if (command == 'n' || command == 'p') {
            printf("pagination not implemented yet, sorry :(\n");
        }
        else if (command >= '1' && command <= '9') {
            int index = command - '1';
            if (procs[index] != NULL) {
                sprintf(message, "Using %s", procs[index]);
                sprintf(state, "PID : %ld", GetCurrentProcessId());
                UpdatePresence(connect, message, state, procs[index]);
            }
        }
        else {
            continue; 
        }
    }
}

#endif