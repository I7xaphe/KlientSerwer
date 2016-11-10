/*
 ============================================================================
 Name        : KlientGorKol.c
 Author      : KMH
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

struct argumenty {
	char* operacja;
	double a;
	double b;
	char* adres;
};


int main(int argc, char* argv[]) {
	if (argc != 5) {
		printf("printf podano błedna liczbe argumentów");
		return 0;
	}

	printf("wynik liczba argumentow %d \n", argc);
	if (atof(argv[2]) == 0) {
		if (*argv[2] != 48) {
			printf("błedny 2 argument");
			return -1;
		}
	}

	if (atof(argv[3]) == 0) {
		if (*argv[3] != 48) {
			printf("błedny 3 argument");
			return -1;
		}
	}
	struct argumenty userArgs;
	userArgs.operacja = argv[1];
	userArgs.a = atof(argv[2]);
	userArgs.b = atof(argv[3]);
	userArgs.adres = atoi(argv[4]);

	if (!strcmp(userArgs.operacja, "dodawanie")) {

	} else if (!strcmp(userArgs.operacja, "odejmowanie")) {

	} else if (!strcmp(userArgs.operacja, "mnozenie")) {

	} else if (!strcmp(userArgs.operacja, "dzielenie")) {

	} else {
		printf("błedna operacja");
		return -1;
	}

	int clientSocket, portNum, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

	/*Configure settings in address struct*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr(userArgs.adres);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	addr_size = sizeof serverAddr;

	nBytes=sprintf (buffer,"%.3f %.3f %s", userArgs.a,userArgs.b, userArgs.operacja);
	nBytes++;

	/*Send message to server*/
	sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *) &serverAddr,
			addr_size);

	/*Receive message from server*/
	nBytes = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);

	printf("Received from server: %s\n", buffer);

	return 0;
}
