
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

#ifdef __linux__
#include "src/connection-unix.h"

static void* stdoutHandle;
static unsigned long outModeInit;

#pragma pack(push, 1)
typedef struct PacketHeader
{
	int opcode;
	int oplength;
} PacketHeader;
#pragma pack(pop)

// todo : redo everything

void SendHandshake(void* hPipe)
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
    // Send em

    // todo : replace writefile with socket() and connect() from sys/socket.h ?
    WriteFile(hPipe, &header, sizeof(PacketHeader), &bytesWritten, NULL);
    WriteFile(hPipe, json_buffer, json_len, &bytesWritten, NULL);

    printf("Handshank request sent ! (Opcode: %d, Len: %d)\n", header.opcode, header.oplength);
    printf("Payload: %s\n", json_buffer);
}

void UpdatePresence(void* hPipe)
{
    char json_buffer[1024];
    int APP_PID = GetCurrentProcessId(); // change that

    sprintf(json_buffer, 
        "{"
            "\"cmd\": \"SET_ACTIVITY\"," 
            "\"args\": {"
                "\"pid\": %d,"
                "\"activity\": {"
                    "\"details\": \"test\","
                    "\"state\": \"linux > windaube\""
                "}"
            "},"
            "\"nonce\": \"1\"" // my "unique ID", required by discord
        "}", 
        APP_PID
    );
	int json_len = strlen(json_buffer);

    PacketHeader header;
    header.opcode = 1;
    header.oplength = json_len;
    unsigned long bytesWritten;

	// todo : replace writefile with socket() and connect() from sys/socket.h ?
    WriteFile(hPipe, &header, sizeof(PacketHeader), &bytesWritten, NULL);
    WriteFile(hPipe, json_buffer, json_len, &bytesWritten, NULL);
}

void* ConnectionDiscord()
{
    // todod : replace createfilea 
	void* hipe = CreateFileA(DIS_PIPE_ADDR, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if (hipe == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    return hipe;
}

#elif _WIN32
#include ".\src\connection.h"

static HANDLE stdoutHandle;
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

    outModeInit = outMode;
    // Enable ANSI escape codes 
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(stdoutHandle, outMode)) exit(GetLastError());   
}

void RestoreConsole(void) {
    // Reset colors
    printf("\x1b[0m");  
    
    // Reset console mode
    if(!SetConsoleMode(stdoutHandle, outModeInit)) {
        exit(GetLastError());
    }
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
    // Send em
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
            "\"nonce\": \"1\"" // my "unique ID", required by discord
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
    Enum
}

#endif
#endif