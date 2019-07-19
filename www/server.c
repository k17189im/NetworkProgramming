#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
#define BUF_SIZE 256

void DieWithError(char *errorMessage){
    perror(errorMessage); 
    exit(1);
}

void commun(int sock){
	char *uri;
	regex_t regBuf;
	regmatch_t regMatch[1];
    char buf[BUF_SIZE];
	char buf_old[BUF_SIZE];
	char buf2[2*BUF_SIZE];
    int len_r;
	char response[BUF_SIZE];
	const char*pattern="GET[^\\n]+HTTP";
	char result[100];
	result[0]='\0';
	if(regcomp(&regBuf,pattern,REG_EXTENDED|REG_NEWLINE)!=0)
	DieWithError("regcomp failed");
	buf_old[0]='\0';
		while((len_r = recv(sock,buf,BUF_SIZE,0)) >0){
			buf[len_r]='\0';
			
			sprintf(buf2,"%s%s",buf_old,buf);
			printf("%s",buf);
			if(regexec(&regBuf,buf2,0,regMatch,0)!=0){
			int startindex = regMatch[0].rm_so;
			int endindex = regMatch[0].rm_eo;
				strncpy(result,buf2 + startindex,endindex-starindex);
			}
			if(strstr(buf2,"\r\n\r\n")){
				break;
			}
			sprintf(buf_old,"%s",buf);
		}
	if(result[0]!='\0'){
		uri = strtok(result,"");
		uri = strtok(NULL,"");
		printf("%s\n",uri);
	}else{
		DieWithError("No URI");
	}
	regfree(&regbuf);
			if(len_r <= 0){
				DieWithError("received() failed.");
			}
			
			printf("recieved HTTP request.\n");

			if((len_r=recv(sock,buf,BUF_SIZE,0))<=0)
        DieWithError("recv()failed");
    
    buf[len_r] = '\0';
    printf("%s\n",buf);
    if((send(sock,buf,strlen(buf),0))!=strlen(buf))
        DieWithError("send()sent a message of unexpected bytes");
}
int main(int argc, char **argv) {
    int servSock = socket(PF_INET,SOCK_STREAM,0);

    int cliSock;
    struct sockaddr_in clientAddress;
    unsigned int szClientAddr;

    struct sockaddr_in servAddress;
    servAddress.sin_family = AF_INET;
    servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddress.sin_port = htons(10001);
    bind(servSock,(struct sockaddr *)&servAddress,sizeof(servAddress));
    listen(servSock,5);
    while(1){
        szClientAddr = sizeof(clientAddress);
        cliSock = accept(servSock,(struct sockaddr*)&clientAddress,&szClientAddr);
        commun(cliSock);
    }
    return 0;
}