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

#define DIS_PIPE_ADDR       "\\\\.\\pipe\\discord-ipc-0" // memory adress of pipe
#define DIS_APP_ID          "1143261501633867846" // public app id
#define KRED                "\x1B[31m" // red
#define KGRN                "\x1B[32m" // green
#define MAGHB               "\e[0;105m" // special purble
#define KNRM                "\x1B[0m" // no

void* ConnectionDiscord();
// connect to discord
void SendHandshake(void* hPipe);
// send handshank request
void UpdatePresence(void* hPipe);
// update rpc presence 
void SetupConsole();
// allows ansi escape codes
void RestoreConsole();
// reverts changes made to console

#endif
#endif
