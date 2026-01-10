#ifndef CONNEXION_H
#define CONNEXION_H 

#include <windows.h>

#define DIS_APP_ID              "1143261501633867846" // public app id
#define DIS_PIPE_ADDR 			"\\\\.\\pipe\\discord-ipc-0" // where the ppipe is in the rap (i think ?)
//silly colors
#define KRED          			"\x1B[31m"
#define KGRN  					"\x1B[32m"
#define KNRM  					"\x1B[0m"

HANDLE ConnexionDiscord();
// connects to the discord pipe file

void SendHandshake(HANDLE hPipe);
// sends the handshake to discord
//@param: where to send it

#endif