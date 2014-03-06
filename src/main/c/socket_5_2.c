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

char *sock_addr(int s, char *buf, size_t bufsiz) {
    int z;
    struct sockaddr_in adr_inet;
    int len_inet;

    len_inet = sizeof adr_inet;

    z = getsockname(s, (struct sockaddr*)&adr_inet, &len_inet);
    if (z == -1)
        return NULL;

    snprintf(buf, bufsiz, "%s:%u", inet_ntoa(adr_inet.sin_addr),
        (unsigned)ntohs(adr_inet.sin_port));

    return buf;
}

int main()
{
    int z;
    int sck_inet;
    struct sockaddr_in adr_inet;
    int len_inet;
    char buf[64];

    sck_inet = socket(AF_INET, SOCK_STREAM, 0);
    if (sck_inet == -1)
        bail("socket()");

    memset(&adr_inet, 0, sizeof adr_inet);
    adr_inet.sin_family = AF_INET;
    adr_inet.sin_port = htons(9000);
    inet_aton("127.0.0.1", &adr_inet.sin_addr);
    len_inet = sizeof adr_inet;

    z = bind(sck_inet, (struct sockaddr*)&adr_inet, len_inet);
    if (z == -1)
        bail("bind()");

    if (!sock_addr(sck_inet, buf, sizeof buf))
        bail("sock_addr()");

    printf("The address is: %s\n", buf);

    close(sck_inet);

    return 0;
}
