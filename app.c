#include "connexion.h"

int main ()
{
	DWORD u_len = UNLEN+1;
	char username[u_len];
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
		printf("%sConnection terminated. I'm sorry to interrupt you '%s%s%s'. \nIf you still even remember that name, But I'm afraid \nyou've been misinformed. You are not here to receive a gift,\nnor have you been called here by the individual you assume, \nalthough, you have indeed been called. You have all been called here, \ninto a labyrinth of sounds and smells, misdirection and misfortune. \nA labyrinth with no exit, a maze with no prize. \nYou don't even realize that you are trapped.\n\n\t%sthis is a silly copypasta message, the program failed.%s\n\n", KGRN, KRED, username, KGRN, KRED, KNRM);
		return EXIT_FAILURE;
	}
	printf("Connexion successfully established.\n");
    printf("Sending handshank request...\n"); 
	SendHandshake(connect);
    Sleep(1000);
	UpdatePresence(connect);
    
    printf("press enter to exit.\n");
    getchar();
	return EXIT_SUCCESS;
}