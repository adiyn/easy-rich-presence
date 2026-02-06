#ifndef CONNEXION_H
#define CONNEXION_H 
#define DIS_APP_ID          "1143261501633867846" // me public app id
#define KRED                "\x1B[31m" // red
#define KGRN                "\x1B[32m" // green
#define MAGHB               "\e[0;105m" // special purble
#define KNRM                "\x1B[0m" // no

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// required libraries
#include <unistd.h>
#include <sys/socket.h>

#define DIS_PIPE_ADDR       "$XDG_RUNTIME_DIR/discord-ipc-0" // adress of pipe ??? maybe....

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <lmcons.h>
#include <tchar.h>
#include <psapi.h>

#define DIS_PIPE_ADDR       "\\\\.\\pipe\\discord-ipc-0" // memory adress of pipe
#define MAX_BUFFER_SIZE 1024

static HANDLE stdoutHandle;
static unsigned int oldCodePage;
static unsigned long outModeInit;

// send handshake request
void SendHandshake(HANDLE hPipe);
// update rpc presence 
void UpdatePresence(HANDLE hPipe, const char* message, const char* state, const char* appName);
// allows ansi escape codes
void SetupConsole(void);
// reverts changes made to console
void RestoreConsole(void);
// returns a list of the names of running apps "{"Firefox (sigma)", "Discord", "CheatEngine", "Edge (stinky)", "Chrome (stinky)", ...}"
char** getProcsNames(DWORD processID, char* buffer, size_t bufferSize);
// connect to discord
void* ConnectionDiscord(void);
// establishes connection to discord and returns a handle to the pipe
void* EstablishConnection(void);
// run app
void run(HANDLE connect);

#endif
#endif
