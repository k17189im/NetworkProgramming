#include<sys/socket.h>	/*socket�֐�����`����Ă�*/
#include<unistd.h>	
#define BUF_SIZE 256
#include<string.h>
#include <stdio.h>              /* printf(),fprintf()�ɕK�v */
#include <stdlib.h>             /* perror(),atoi()�ɕK�v */
#include <sys/socket.h>         /* socket(),connect()�ɕK�v */
#include <arpa/inet.h>          /* sockaddr_in,inet_addr()�ɕK�v */




	void commun(int sock){
		char buf[BUF_SIZE];
		int len_r;
		if((len_r=recv(sock,buf,BUF_SIZE,0))<=0)
		DieWithError("recv()failed");
		buf[len_r]='\0';
		printf("%s\n",buf);
		if(send(sock,buf,strlen(buf),0)!=strlen(buf))
		DieWithError("send()sent a messafe of unecpected bytes");
}

int main(int argc,char**argv){
	int servSock=socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in servAddress;
	struct sockaddr_in servAddress;
	int cliSock;
	
	servAddress.sin_family=AF_INET;
	servAddress.sin_addr.s_addr=htol(INADDR_ANY);
	servAddress.sin_port=htons(10001);
	
	bind(servsosk,(struct sockaddr*)&servAddress,sizeof(servAddress));
	listen(servsock,5);
	while(1){
		szClientAddr=sizeof(clientAddress);
		cliSock=accept(servSock,(struct sockaddr*)&clientAddress,&szClientAddr);
		
		commun(cliSock);
	}
	
	close(servSosk);
	return 0;
}