#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DieWithError(char *);
int prepare_server_sosket(int);
void commun(int);

int main(int argc, char *argv)
{
    struct sockaddr_in clientAddress;
    int cliSock;
    int servSock = prepare_server_socket(10001);

    listen(servSock, 5);

    while (1) /**/
    {
    }
}