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

#define PORT 8777
#define BUFLEN 512

struct argumenty {
	char* operacja;
	int a;
	int b;
	char* adres;
};
void die(char *s)
{   //       perror - print a system error message
	puts(s);
    exit(-1);
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		die("podano błedna liczbe argumentów\n");
	}

	printf("argumenty :%s, %s, %s, %s \n", argv[1],argv[2],argv[3],argv[4]);
	if (atoi(argv[2]) == 0) {
		if (*argv[2] != 48) {
			die("błedny 2 argument\n");
		}
	}

	if (atoi(argv[3]) == 0) {
		if (*argv[3] != 48) {
			die("błedny 3 argument\n");
		}
	}
	struct argumenty userArgs;
	userArgs.operacja = argv[1];
	userArgs.a = atoi(argv[2]);
	userArgs.b = atoi(argv[3]);
	userArgs.adres = argv[4];

	if (!(strcmp(userArgs.operacja, "dodawanie")||strcmp(userArgs.operacja, "odejmowanie")
			||strcmp(userArgs.operacja, "mnozenie")||strcmp(userArgs.operacja, "dzielenie"))) {

		die("błedna operacja \n");
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

	nBytes=sprintf(buffer,"%s %d %d",userArgs.operacja,userArgs.a,userArgs.b);
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

	printf("Zwrocony wynik operacji %s liczb %d i %d wynosi %s\n",userArgs.operacja,userArgs.a,userArgs.b, buffer);

	return 0;
}
