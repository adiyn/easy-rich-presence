#ifndef CONNEXION_H
#define CONNEXION_H 

#ifdef __linux__

// required libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>

#define DIS_PIPE_ADDR       "$XDG_RUNTIME_DIR/discord-ipc-0" // adress of pipe ??? maybe....
#define DIS_APP_ID          "1143261501633867846" // public app id
#define KRED                "\x1B[31m" // red
#define KGRN                "\x1B[32m" // green
#define MAGHB               "\e[0;105m" // special purble
#define KNRM                "\x1B[0m" // no

/* connect to discord
*/
void* ConnectionDiscord();
/* send handshank request
@param : pipetastic!!
*/
void SendHandshake(void* hPipe);
/*
update rpc presence
@param : piperliscious...
*/
void UpdatePresence(void* hPipe);

#elif _WIN32

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <lmcons.h>
#include <tchar.h>
#include <psapi.h>

#define DIS_PIPE_ADDR       "\\\\.\\pipe\\discord-ipc-0" // memory adress of pipe
#define DIS_APP_ID          "1143261501633867846" // public app id
#define KRED                "\x1B[31m" // red
#define KGRN                "\x1B[32m" // green
#define MAGHB               "\e[0;105m" // special purble
#define KNRM                "\x1B[0m" // no
#define MAX_BUFFER_SIZE 512

static HANDLE stdoutHandle;
static unsigned int oldCodePage;
static unsigned long outModeInit;

// connect to discord
void* ConnectionDiscord();
// send handshank request
void SendHandshake(void* hPipe);
// update rpc presence 
void UpdatePresence(void* hPipe);
// allows ansi escape codes
void SetupConsole();
// reverts changes made to console
void RestoreConsole();
// returns a list of the names of running apps "{"Firefox (sigma)", "Discord", "CheatEngine", "Edge (stinky)", "Chrome (stinky)", ...}"
char** getApps();

#endif
#endif
