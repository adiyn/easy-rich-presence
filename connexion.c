#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define APPID "114326150163386784"

// note for self : pragma tells the compiler sth
// and here it just tells him to push in packs of 1 byte
#pragma pack(push, 1)
struct PacketHeader {
	int opcode; // 0 is handshake and 1 is frame
	int oplenght; // json size
}
#pragma pack(pop)
//

//TODO : connexion function to discord 
