
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

double Oblicz(char *wsk);
void changeSpaceTo0x00(char *wsk);
char* returnNextArgumentAsString(char *wsk);

void die(char *s)
{
    perror(s);
    exit(1);
}

int dodawanie(int a, int b){

	return a+b;
}

int main(void)
{
    struct sockaddr_in si_me, si_other;
    double wynik;

    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
    char buffor_nadawzy[BUFLEN];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }

        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n" , buf);
        wynik=Oblicz(buf);
        sprintf(buffor_nadawzy,"wynik %f",wynik);

        if (sendto(s, buffor_nadawzy, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        exit(0);

    }

    close(s);
    return 0;
}
double Oblicz(char *wsk){
	char* operacja;
	int a;
	int b;
	double wynik = 15;
	changeSpaceTo0x00(wsk);
	operacja=wsk;
	wsk=returnNextArgumentAsString(wsk);
	a=atoi(wsk);
	wsk=returnNextArgumentAsString(wsk);
	b=atoi(wsk);

	printf("sprawdzenie arumentor: %s ,%d ,%d \n",operacja,a,b);

	if (!strcmp(operacja, "dodawanie")) {

		wynik=dodawanie(a,b);
		printf("operacja dodania po stronie serwera zakonczona sukcesem\n");

	} else if (!strcmp(operacja, "odejmowanie")) {
		printf("operacja odejmowania po stronie serwera zakonczona sukcesem\n");
	} else if (!strcmp(operacja, "mnozenie")) {
		printf("operacja mnozenia po stronie serwera zakonczona sukcesem\n");
	} else if (!strcmp(operacja, "dzielenie")) {
		printf("operacja dzielenia po stronie serwera zakonczona sukcesem\n");
	} else {
			printf("błedna operacja");
	}
	return wynik;

}
void changeSpaceTo0x00(char *wsk){
	while(*wsk){
		if(*wsk==' '){
			*wsk=0x00;
			printf("dokonany konwesji z Space To 0x00 adres %x\n",wsk);
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
