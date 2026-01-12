#ifndef CONNEXION_H
#define CONNEXION_H 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DIS_PIPE_ADDR       "\\\\.\\pipe\\discord-ipc-0" // memory adress of pipe
#define DIS_APP_ID          "1143261501633867846" // public app id
#define KRED                "\x1B[31m" // red
#define KGRN                "\x1B[32m" // green
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
