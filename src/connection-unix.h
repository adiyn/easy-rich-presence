#ifndef CONNEXION_H
#define CONNEXION_H 

// required libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>

#define DIS_PIPE_ADDR       "$XDG_RUNTIME_DIR/discord-ipc-0" // memory adress of pipe
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

#endif
