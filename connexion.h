#ifndef CONNEXION_H
#define CONNEXION_H 
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004

static HANDLE stdoutHandle;
static DWORD outModeInit;

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Lmcons.h>

#pragma pack(push, 1)
typedef struct PacketHeader
{
	int opcode;
	int oplength;
} PacketHeader;
#pragma pack(pop)

#define DIS_APP_ID          "1143261501633867846" // public app id
#define DIS_PIPE_ADDR 		"\\\\.\\pipe\\discord-ipc-0" // where the pipe is in the ram (i think ?)
//silly colors
#define KRED          		"\x1B[31m"
#define KGRN  			    "\x1B[32m"
#define KNRM  		    	"\x1B[0m"

void SetupConsole();
void RestoreConsole();
HANDLE ConnexionDiscord();
void SendHandshake(HANDLE hPipe);
void UpdatePresence(HANDLE hPipe);
#endif
