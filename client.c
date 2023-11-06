#include "common.h"
#include <arpa/inet.h>

void clientipc();
void client();

int main(void)
{
    clientipc();
    exit(0);
}

/*функция, pеализующая специальную обpаботку */
void clientipc()
{
    int sock; /* дескриптор сокета */
    struct sockaddr_in server; /* адрес сервера */
    struct in_addr *srv;
    unsigned long addr_s; /* создание сокета */
    sock = socket(PF_INET, SOCK_STREAM, 0); /* формирование сокет-адреса */
    bzero(&server, sizeof(server));
    server.sin_family = PF_INET;
    srv=&(server.sin_addr);
    addr_s = inet_addr("127.0.0.1");
    (*srv).s_addr = addr_s;
    server.sin_port = htons(PORT); /* соединение с сервером */
    connect(sock, (struct sockaddr *) &(server),sizeof(server));
    printf("connect to server\n"); /* вызов службы */
    client(sock); /* закрытие соединения */
    close(sock);
}

void client(int sock)
{
    int lbuf, lbufres; /* целое число в сетевом формате */
    char msg[]="Laba5 sockets! \n";
    int ret; /* начнем с пересылки размера буфера ; обратите внимание на то, что число надо передать в сетевом формате */
    lbuf=strlen(msg)+1;
    lbufres = htons(lbuf);
    ret = writeSocket(sock, (char *) &lbufres, sizeof(lbufres));
    ret = writeSocket(sock, msg, lbuf);
    lbuf=0;
    lbufres = htons(lbuf);
    ret = writeSocket(sock, (char *) &lbufres, sizeof(lbufres));
}