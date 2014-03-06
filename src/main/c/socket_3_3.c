#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <arpa/inet.h>

static void bail(const char *get) {
    perror(get);
    exit(1);
}

int main()
{
    int z;
    int sock;
    struct sockaddr_in sck_inet;
    int sck_len;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        bail("socket()");

    memset(&sck_inet, 0, sizeof sck_inet);
    sck_inet.sin_family = AF_INET;
    sck_inet.sin_port = htons(9000);
    sck_inet.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ( sck_inet.sin_addr.s_addr == INADDR_NONE )
        bail("inet_addr()");

    sck_len = sizeof sck_inet;

    z = bind(sock, (struct sockaddr*)&sck_inet, sck_len);
    if ( z == -1 )
        bail("bind()");

    system("netstat -pa --tcp | grep socket_3_3");

    return 0;
}
