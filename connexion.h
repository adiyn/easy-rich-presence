#ifndef CONNEXION_H
#define CONNEXION_H

#include <windows.h>

#define DIS_APP_ID "1143261501633867846" // public app id

HANDLE ConnexionDiscord();
// connects to the discord pipe file

void SendHandshake(HANDLE hPipe);
// sends the handshake to discord
//@param: where to send it

#endif