#ifndef CONNEXION_H
#define CONNEXION_H 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DIS_PIPE_ADDR       "1143261501633867846" 
#define KRED                "\x1B[31m"
#define KGRN                "\x1B[32m"
#define KNRM                "\x1B[0m"

void* ConnexionDiscord();
void SendHandshake(void* hPipe);
void UpdatePresence(void* hPipe);
void SetupConsole();
void RestoreConsole();

#endif
