#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Lmcons.h>
#include "connexion.h"

#pragma push(pack, 1)
typedef struct PacketHeader
{
	int opcode;
	int oplength;
} PacketHeader;
#pragma pop(pack);

void HandShank(HANDLE hPipe)
{	// TODO !!!!
    // 1. make the JSON to send
    // 2. fill header
    // 3. send in hPipe :3
    printf("Sending handshake request...\n"); 
}

HANDLE ConnexionDiscord()
{
	HANDLE hipe = CreateFileA(DIS_PIPE_ADDR, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if (hipe == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    return hipe;
}

int main ()
{
	char username[UNLEN+1];
	HANDLE connect = NULL;
	printf("Attempting connexion to discord pipe...\n");
	int attempts = 10;
	do
	{
		connect = ConnexionDiscord();
		attempts--;
		Sleep(69);
	} while (connect == NULL && attempts > 0);
	if (attempts == 0)
	{	
		GetUserName(username, &u_len);
		printf("%sConnection terminated. I'm sorry to interrupt you, '%s%s%s', \nif you still even remember that name, But I'm afraid \nyou've been misinformed. You are not here to receive a gift,\nnor have you been called here by the individual you assume, \nalthough, you have indeed been called. You have all been called here, \ninto a labyrinth of sounds and smells, misdirection and misfortune. \nA labyrinth with no exit, a maze with no prize. \nYou don't even realize that you are trapped.\n\n\t%sthis is a silly copypasta message, the program failed.%s\n\n", KGRN, KRED, username, KGRN, KRED, KNRM);
		return EXIT_FAILURE;
	}
	printf("Connexion successfully established.\n");
	return EXIT_SUCCESS;
}