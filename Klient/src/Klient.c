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
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 7777
#define BUFLEN 512

struct argumenty {
	char* operacja;
	double a;
	double b;
	char* adres;
};
void mExit(char *s)
{   //       perror - print a system error message
	puts(s);
    exit(-1);
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		mExit("podano błedna liczbe argumentów\n");
	}

	printf("argumenty :%s, %s, %s, %s \n", argv[1],argv[2],argv[3],argv[4]);
	if (atoi(argv[2]) == 0) {
		if (*argv[2] != 48) {
			mExit("błedny 2 argument\n");
		}
	}
//
	if (atoi(argv[3]) == 0) {
		if (*argv[3] != 48) {
			mExit("błedny 3 argument\n");
		}
	}
	struct argumenty userArgs;
	userArgs.operacja = argv[1];
	userArgs.a = atof(argv[2]);
	userArgs.b = atof(argv[3]);
	userArgs.adres = argv[4];

	if (!(strcmp(userArgs.operacja, "dodawanie")||strcmp(userArgs.operacja, "odejmowanie")
			||strcmp(userArgs.operacja, "mnozenie")||strcmp(userArgs.operacja, "dzielenie"))) {

		mExit("błedna operacja \n");
	}

	int clientSocket, nBytes;
	char buffer[BUFLEN]="";
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

	/*Configure settings in address struct*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(userArgs.adres);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	addr_size = sizeof serverAddr;

	nBytes=sprintf(buffer,"%s %.3f %.3f",userArgs.operacja,userArgs.a,userArgs.b);
	nBytes++;

	/*Send message to server*/
	//argumenty sendto
	//(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
	sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *) &serverAddr, addr_size);

	/*Receive message from server*/
	//argumenty recvfrom
	//(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
	//ostanie 2 argumenty moga byc null
	nBytes = recvfrom(clientSocket, buffer, BUFLEN, 0,(struct sockaddr *) &serverAddr, &addr_size);

	printf("Zwrocony wynik operacji %s liczb %.3f i %.3f wynosi %s\n",userArgs.operacja,userArgs.a,userArgs.b, buffer);

	return 0;
}
