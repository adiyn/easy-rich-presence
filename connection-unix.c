#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#include ".\src\connection-unix.h"
#include <unistd.h>

static void* stdoutHandle;
static unsigned long outModeInit;

#pragma pack(push, 1)
typedef struct PacketHeader
{
	int opcode;
	int oplength;
} PacketHeader;
#pragma pack(pop)