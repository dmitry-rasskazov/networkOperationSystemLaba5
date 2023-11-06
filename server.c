#include "common.h"
#include <arpa/inet.h>

void serveripc();
void serv(int sock);

int main(void)
{
/*вызов функции, выполняющей специальную обpаботку */
    serveripc();
    exit(0);
}

/*функция, pеализующая специальную обpаботку */
void serveripc()
{
    int sock; /* дескриптор сокета */
    int nsock; /* дескриптор сокета */
    int ret; /* возвращаемое значение */
    unsigned int clientAddrLen;
    struct sockaddr_in server, client; /* адрес сервера */
    sock = socket(PF_INET, SOCK_STREAM, 0); /* создание сокета */
    bzero( &server, sizeof(server) );/* назначение адреса сокету */
    server.sin_family = PF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    bind(sock, (struct sockaddr *) &server, sizeof(server));
    listen(sock, 5); /* переход к прослушиванию приходящих связей */
    for (;;) {
        nsock = accept(sock, (struct sockaddr *) &client, &clientAddrLen); /* цикл по запросам на соединение */
        printf("Client accepted: address=%s, port=%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        serv(nsock); /* обращение к циклу чтение-запись */
        close (nsock);/* закрытие текущей связи */
    }
}

/*функция пpиема-пеpедачи*/
void serv(int sock) /* дескриптор сокета */
{
    int lbufres; /* целое число в формате сети */
    int lbuf;
    char buf[1024];
    int ret;
    while(1)
    {
        ret = readSocket(sock, (char *) &lbufres, sizeof(lbufres));
        if (ret==0) {
            exit(0);
        }
        lbuf=ntohs(lbufres);
        if (lbuf>1024) {
            exit(0);
        }
        if (lbuf==0) {
            break;
        }
        ret = readSocket(sock, (char *) &buf, lbuf);
        printf("Server: message=%s\n",buf);
    }
}
