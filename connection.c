/***
DisRPC is an RPC tool made in C with ❤ by @adiyn
***/

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "src/connection.h"

#pragma pack(push, 1)
typedef struct PacketHeader
{
	int opcode;
	int oplength;
} PacketHeader;
#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#include ".\src\connection.h"
static HANDLE stdoutHandle;
static unsigned int oldCodePage;
static unsigned long outModeInit;

#pragma pack(push, 1)
typedef struct PacketHeader
{
	int opcode;
	int oplength;
} PacketHeader;
#pragma pack(pop)

void SetupConsole(void) {   
    unsigned long outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE) exit(GetLastError());
    if(!GetConsoleMode(stdoutHandle, &outMode)) exit(GetLastError());
    
    oldCodePage = GetConsoleOutputCP();
    SetConsoleOutputCP(65001);

    outModeInit = outMode;
    
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(stdoutHandle, outMode)) exit(GetLastError());   
}

void RestoreConsole(void) {
    // Reset color
    printf("\x1b[0m");  
    
    SetConsoleOutputCP(oldCodePage);
    
    SetConsoleMode(stdoutHandle, outModeInit);
}

void SendHandshake(HANDLE hPipe)
{
    char json_buffer[512];
    // Init payload
    sprintf(json_buffer, "{\"v\": 1, \"client_id\": \"%s\"}", DIS_APP_ID);
    int json_len = strlen(json_buffer);

    // Init header
    PacketHeader header;
    header.opcode = 0;
    header.oplength = json_len;
    unsigned long bytesWritten;
    
    // Send
    WriteFile(hPipe, &header, sizeof(PacketHeader), &bytesWritten, NULL);
    WriteFile(hPipe, json_buffer, json_len, &bytesWritten, NULL);

    printf("Handshank request sent ! (Opcode: %d, Len: %d)\n", header.opcode, header.oplength);
    printf("Payload: %s\n", json_buffer);
}

void UpdatePresence(HANDLE hPipe)
{
    char json_buffer[1024];
    int APP_PID = GetCurrentProcessId();

    sprintf(json_buffer, 
        "{"
            "\"cmd\": \"SET_ACTIVITY\"," 
            "\"args\": {"
                "\"pid\": %d,"
                "\"activity\": {"
                    "\"details\": \"test\","
                    "\"state\": \"CCCCCC\""
                "}"
            "},"
            "\"nonce\": \"1\""
        "}",
        APP_PID
    );
	int json_len = strlen(json_buffer);

    PacketHeader header;
    header.opcode = 1;
    header.oplength = json_len;
    unsigned long bytesWritten;
	
    WriteFile(hPipe, &header, sizeof(PacketHeader), &bytesWritten, NULL);
    WriteFile(hPipe, json_buffer, json_len, &bytesWritten, NULL);
}

HANDLE ConnectionDiscord()
{
	HANDLE hipe = CreateFileA(DIS_PIPE_ADDR, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if (hipe == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    return hipe;
}

void get_procs()
{
    
}

#endif
#endif