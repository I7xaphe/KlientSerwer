
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include<biblioteka.h>

#define BUFLEN 512  //Max length of buffer
#define PORT 7777   //The port on which to listen for incoming data
#define ADDRESS "127.10.13.13"

double Oblicz(char *wsk);
void changeSpaceTo0x00(char *wsk);
char* returnNextArgumentAsString(char *wsk);
void mExit(char *s);


int main(void)
{

    struct sockaddr_in si_serwer, si_klient;
    double wynik;
    socklen_t addr_size;
    int serwerSocket  , recv_len;
    char buf[BUFLEN];
    char buffor_nadawzy[BUFLEN];

    addr_size = sizeof(si_klient);
    //create a UDP socket
    if ((serwerSocket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        mExit("Error: socket\n");
    }

    // zero out the structure
    memset((char *) &si_serwer, 0, sizeof(si_serwer));

    si_serwer.sin_family = AF_INET;
    si_serwer.sin_port = htons(PORT);
    si_serwer.sin_addr.s_addr = inet_addr(ADDRESS);

    //bind socket to port
    if(bind(serwerSocket , (struct sockaddr*)&si_serwer, sizeof(si_serwer) ) == -1)
    {
        mExit("Error: bind\n");
    }
    while(1)
    {
        printf("Waiting for data...\n");
        fflush(stdout);

        //funkcja blokacja
        if ((recv_len = recvfrom(serwerSocket, buf, BUFLEN, 0, (struct sockaddr *) &si_klient, &addr_size)) == -1)
        {
            mExit("Error: recvfrom()\n");
        }


        printf("Nadawca %s \n", inet_ntoa(si_klient.sin_addr));
        printf("Dane: %s\n" , buf);
        wynik=Oblicz(buf);
        recv_len=sprintf(buffor_nadawzy,"wynik %.3f",wynik);
        recv_len++;
        printf("wynik %f\n",wynik);

        if (sendto(serwerSocket, buffor_nadawzy, recv_len, 0, (struct sockaddr*) &si_klient, addr_size) == -1)
        {
            mExit("Error: sendto()\n");
        }
    }
    return 0;
}

double Oblicz(char *wsk){
	double (*funkcja)(struct argumenty* arg);
	char* operacja;
	struct argumenty argx;

	changeSpaceTo0x00(wsk);
	operacja=wsk;
	wsk=returnNextArgumentAsString(wsk);
	argx.a=atof(wsk);
	wsk=returnNextArgumentAsString(wsk);
	argx.b=atof(wsk);


	printf("sprawdzenie argumentow: %s, %.3f, %.3f. \n",operacja,argx.a,argx.b);

	if (!strcmp(operacja, "dodawanie")) {
		funkcja=dodawanie;

	} else if (!strcmp(operacja, "odejmowanie")) {
		funkcja=odejmowanie;

	} else if (!strcmp(operacja, "mnozenie")) {

		funkcja=mnozenie;
	} else if (!strcmp(operacja, "dzielenie")) {

		funkcja=dzielenie;
	} else {
		printf("błedna operacja\n");
	}

	return funkcja(&argx);

}
void changeSpaceTo0x00(char *wsk){
	while(*wsk){
		if(*wsk==' '){
			*wsk=0x00;
		//	printf("dokonany konwesji z Space To 0x00 adres %x\n",wsk);
		}
		wsk++;
	}

}

char* returnNextArgumentAsString(char *wsk){
	while(*wsk!=0x00){
		wsk++;
	}
	wsk++;
	return wsk;
}
void mExit(char *s)
{
	perror(s);
    exit(-1);
}
