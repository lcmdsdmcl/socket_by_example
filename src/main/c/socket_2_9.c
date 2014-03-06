#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>

static void bail(const char *get) {
    perror(get);
    exit(1);
}


int main()
{
    int z;
    int sck_inet;
    struct sockaddr_in adr_inet;
    int len_inet;
    const unsigned char IPno[] = {127, 0, 0, 23};

    // socket
    sck_inet = socket(AF_INET, SOCK_STREAM, 0);
    if (sck_inet == -1)
        bail("socket()");

    memset(&adr_inet, 0, sizeof adr_inet);
    adr_inet.sin_family = AF_INET;
    adr_inet.sin_port = htons(9000);
    memcpy(&adr_inet.sin_addr.s_addr, IPno, 4);
    len_inet = sizeof adr_inet;

    // bind
    z = bind(sck_inet, (struct socketaddr*)&adr_inet, len_inet);
    if (z == -1)
        bail("bind()");

    system("netstat -pa --unix | grep socket_2_9");

    close(sck_inet);


    return 0;
}
