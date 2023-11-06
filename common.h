#ifndef LABA5_SOCKET_COMMON_H
#define LABA5_SOCKET_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 6259 /* номер порта */

/* запись в сокет буфера, состоящего из пос байт */
int writeSocket(
    register int sock, /* дескриптор сокета */
    register char *pbuf, /* буфер */
    register int noc /* число записываемых байт */
) {
    int nreste, necrit;
    nreste = noc;
    while (nreste > 0) {
        necrit = write(sock, pbuf, nreste);
        if (necrit < 0) {
            return necrit;
        }

        nreste -= necrit;
        pbuf += necrit;
    }

    return noc - nreste;
}

/* считывание в буфер пос байт из сокета */
int readSocket(
    register int sock, /* дескриптор сокета */
    register char *pbuf, /* буфер */
    register int noc /* число считываемых байт */
) {
    int nreste, nlit;
    nreste = noc;
    while (nreste > 0) {
        nlit = read(sock, pbuf, nreste);
        if (nlit < 0) {
            return nlit;
        } else if(nlit == 0){
            break;
        }

        nreste -= nlit;
        pbuf += nlit;
    }

    return noc - nreste;
}

#endif //LABA5_SOCKET_COMMON_H
