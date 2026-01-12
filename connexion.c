#include "connexion.h"

void SetupConsole(void) {
    DWORD outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE) {
        exit(GetLastError());
    }
    
    if(!GetConsoleMode(stdoutHandle, &outMode)) {
        exit(GetLastError());
    }

    outModeInit = outMode;
    
    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(stdoutHandle, outMode)) {
        exit(GetLastError());
    }   
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
    sprintf(json_buffer, "{\"v\": 1, \"client_id\": \"%s\"}", DIS_APP_ID);
    int json_len = strlen(json_buffer);

    PacketHeader header;
    header.opcode = 0;
    header.oplength = json_len;
    DWORD bytesWritten;

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
    DWORD bytesWritten;
	
    WriteFile(hPipe, &header, sizeof(PacketHeader), &bytesWritten, NULL);
    WriteFile(hPipe, json_buffer, json_len, &bytesWritten, NULL);
}

HANDLE ConnexionDiscord()
{
	HANDLE hipe = CreateFileA(DIS_PIPE_ADDR, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if (hipe == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    return hipe;
}