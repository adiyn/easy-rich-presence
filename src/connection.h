#ifndef CONNEXION_H
#define CONNEXION_H 
#define DIS_APP_ID                          "1143261501633867846"
#define KGRN                                "\x1B[32m"
#define MAGHB                               "\e[0;105m"
#define KNRM                                "\x1B[0m"
#define KRED                                "\x1B[31m"                 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// required libraries
#include <unistd.h>
#include <sys/socket.h>

#define DIS_PIPE_ADDR                       "$XDG_RUNTIME_DIR/discord-ipc-0"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <lmcons.h>
#include <tchar.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <conio.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#define DIS_PIPE_ADDR                       "\\\\.\\pipe\\discord-ipc-0"
#define MAX_BUFFER_SIZE                     4096


#pragma pack(push, 1) 
typedef struct PacketHeader
{
	uint32_t opCode;
	uint32_t opLength;
} PacketHeader;
#pragma pack(pop)

typedef struct {
    char** names;
    int count;
    int capacity;
} AppList;

typedef struct {
    const char* exe;
    const char* asset;
} AppAssetMap;

extern HANDLE stdoutHandle;
extern uint8_t oldCodePage;
extern DWORD outModeInit;
extern const AppAssetMap APP_MAP[];
extern const size_t APP_MAP_COUNT;

void showLogo(void);
void SetupConsole(void);
void RestoreConsole(void);
void SendHandshake(HANDLE hPipe);
bool isToBeIgnored(const char* name);
bool hasVisibleWindow(DWORD pid);
char** getProcsNames(void);
const char* appNameToAssetName(const char* appName);
void showRunning(char** procs);
void UpdatePresence(HANDLE hPipe, const char* details, const char* subtitle, const char* appName);
void* ConnectionDiscord(void);
void* EstablishConnection(void);
bool Disconnect(HANDLE hPipe);
void freeProcs(char** procs);
bool processCommand(HANDLE hPipe, char details[], char subtitle[], char command, char chosenApp[], size_t chosenAppLen, int procCount, char** procs, bool reset);
void run(HANDLE hPipe);
#endif
#endif