#include <stdio.h>              /* printf(),fprintf()�ɕK�v */
#include <stdlib.h>             /* perror(),atoi()�ɕK�v */
#include <sys/socket.h>         /* socket(),bind(),accept()�ɕK�v */
#include <arpa/inet.h>          /* sockaddr_in,inet_addr()�ɕK�v */
#include <string.h>             /* strlen()�ɕK�v */
#include <unistd.h>             /* close()�ɕK�v */
#define BUF_SIZE 256            /* �}�W�b�N�i���o�[��256�̒�` */

void DieWithError(char *errorMessage){
    perror(errorMessage);                                                               /* �W���G���[�o�͂ɃG���[���b�Z�[�W��Ԃ� */
    exit(1);                                                                            /* �����́u�I���X�e�[�^�X�v�� �G���[�̎��͂P�ȏ��Ԃ� */
}

void commun(int sock){
    char buf[BUF_SIZE];                                                                 /* �G�R�[������p�̃o�b�t�@ */
    int len_r;                                                                          /* ��M������ */

    if((len_r=recv(sock,buf,BUF_SIZE,0))<=0)                                            /* ��M�f�[�^���o�b�t�@�Ɋi�[ */
        DieWithError("recv()failed");                                                   /* ��M���G���[(�����ʈᔽ) */
    
    buf[len_r] = '\0';                                                                  /* ����EOS�̒ǉ� */
    printf("%s\n",buf);                                                                 /* ��M�f�[�^���o�� */
    if((send(sock,buf,strlen(buf),0))!=strlen(buf))                                     /* �N���C�A���g�Ɏ󂯎�����f�[�^��ԋp */
        DieWithError("send()sent a message of unexpected bytes");                       /* ���M���G���[(�f�[�^�̕s��v) */
}
int main(int argc, char **argv) {
    int servSock = socket(PF_INET,SOCK_STREAM,0);                                       /* �҂��󂯗p�\�P�b�g�̍쐬(PF_INET=IPv4,SOCKET_STREAM=TCP,0=�c��͂��C��) */

    int cliSock;                                                                        /* �ʐM�p�̃\�P�b�g */
    struct sockaddr_in clientAddress;                                                   /* �N���C�A���g�́uIP�A�h���X&�|�[�g�ԍ��v�̂ӂ����i�[ */
    unsigned int szClientAddr;                                                          /* �N���C�A���g�́uIP�A�h���X+�|�[�g�ԍ��v�̃T�C�Y */

    struct sockaddr_in servAddress;                                                     /* �T�[�o�[�̏����i�[����\���� */
    servAddress.sin_family = AF_INET;                                                   /* �C���^�[�l�b�g�A�h���X�t�@�~�� */
    servAddress.sin_addr.s_addr = htonl(INADDR_ANY);                                    /* �T�[�o�[��IP�A�h���X(ANY�͔C�ӂ̏ꏊ���\�ł��邱�Ƃ�����) */
    servAddress.sin_port = htons(10001);                                                /* �󂯎��|�[�g�ԍ� */
    bind(servSock,(struct sockaddr *)&servAddress,sizeof(servAddress));                 /* �T�[�o�[�̐ݒ��servSock�Ɍ��т��� */
    listen(servSock,5);                                                                 /* ���ԑ҂�(�����������ԑ҂����Ă��ǂ��N���C�A���g��) */
    while(1){
        szClientAddr = sizeof(clientAddress);                                           /* ��M�f�[�^�̌`���̃������T�C�Y���擾 */
        cliSock = accept(servSock,(struct sockaddr*)&clientAddress,&szClientAddr);      /*  */
        commun(cliSock);                                                                /* ���[�U�[��` */
    }
    close(servSock);                                                                    /* server���N���[�Y���� */
    return 0;
}
