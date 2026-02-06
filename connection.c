/***
DisRPC is an RPC tool made in C !
₍ᐢ. .ᐢ₎ ₊˚⊹ by @adiyn
***/

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif _WIN32
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "src/connection.h"

#pragma pack(push, 1)
typedef struct PacketHeader
{
	int opCode;
	int opLength;
} PacketHeader;
#pragma pack(pop)

void SetupConsole(void) {   
    unsigned long outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE) exit(GetLastError());
    if(!GetConsoleMode(stdoutHandle, &outMode)) exit(GetLastError());
    
    SetConsoleOutputCP(65001);

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
    char json_buffer[MAX_BUFFER_SIZE];
    // Init payload
    sprintf(json_buffer, "{\"v\": 1, \"client_id\": \"%s\"}", DIS_APP_ID);
    int json_len = strlen(json_buffer);

    // Init header
    PacketHeader header;
    header.opCode = 0;
    header.opLength = json_len;
    unsigned long bytesWritten;
    
    // Send
    WriteFile(hPipe, &header, sizeof(PacketHeader), &bytesWritten, NULL);
    WriteFile(hPipe, json_buffer, json_len, &bytesWritten, NULL);

    printf(" \tHandshank request sent ! %s(Opcode: %d, Len: %d)%s\n", KGRN, header.opCode, header.opLength, KNRM);
    printf(" \t%sPayload: %s\n", KGRN, json_buffer);
}

void UpdatePresence(HANDLE hPipe)
{
    char json_buffer[MAX_BUFFER_SIZE];
    int APP_PID = GetCurrentProcessId();

    sprintf(json_buffer, 
        "{"
            "\"cmd\": \"SET_ACTIVITY\"," 
            "\"args\": {"
                "\"pid\": %d,"
                "\"activity\": {"
                    "\"title\": \"%s\""
                    "\"details\": \"%s\","
                    "\"state\": \"%s\""
                "}"
            "},"
            "\"nonce\": \"1\""
        "}", APP_PID, "title", "details", "state"
    );
	int json_len = strlen(json_buffer);

    PacketHeader header;
    header.opCode = 1;
    header.opLength = json_len;
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

void getProcName(DWORD processID, char* buffer, size_t bufferSize)
{
}

#endif