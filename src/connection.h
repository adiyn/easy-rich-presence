#ifndef CONNEXION_H
#define CONNEXION_H 
#define DIS_APP_ID          "1143261501633867846"           // me public app id
#define KRED                "\x1B[31m"                      // red
#define KGRN                "\x1B[32m"                      // green
#define MAGHB               "\e[0;105m"                     // special purble
#define KNRM                "\x1B[0m"                       // no

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// required libraries
#include <unistd.h>
#include <sys/socket.h>

#define DIS_PIPE_ADDR       "$XDG_RUNTIME_DIR/discord-ipc-0" // memory adress of pipe

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <lmcons.h>
#include <tchar.h>
#include <psapi.h>
#include <tlhelp32.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#define DIS_PIPE_ADDR       "\\\\.\\pipe\\discord-ipc-0" // memory adress of pipe
#define MAX_BUFFER_SIZE 4096

// shows the logo
void showLogo(void);
// allows ansi escape codes
void SetupConsole(void);
// reverts changes made to console
void RestoreConsole(void);
// send handshake request
void SendHandshake(HANDLE hPipe);
// checks if the app should be ignored (just dis-rpC itself)
bool isToBeIgnored(const char* name);
// checks if a process has a visible window
bool hasVisibleWindow(DWORD pid);
// returns a list of apps with visible windows {"Firefox.exe", "Code.exe", ...}
char** getProcsNames(void);
// converts app name to asset name (for example "Firefox.exe" -> "firefox")
char* appNameToAssetName(const char* appName);
// shows the list of running apps
void showRunning(char** procs);
// update rpc presence 
void UpdatePresence(HANDLE hPipe, const char* details, const char* subtitle, const char* appName);
// connect to discord
void* ConnectionDiscord(void);
// establishes connection to discord and returns a handle to the pipe
void* EstablishConnection(void);
// frees the memory allocated for the list of process names
void freeProcs(char** procs);
// run app
void run(HANDLE connect);
#endif
#endif