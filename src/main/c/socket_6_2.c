#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <time.h>

static void bail(const char *get) {
    fputs(strerror(errno), stderr);
    fputs(": ", stderr);
    fputs(get, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char **argv)
{
    int z;
    size_t x;
    char *srvr_addr = NULL;
    struct sockaddr_in inet_srvr;
    struct sockaddr_in adr;
    int len_inet;
    int s;
    char dgram[512];

    if (argc >= 2)
        srvr_addr = argv[1];
     else
        srvr_addr = "127.0.0.23";

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if ( s == -1 )
        bail("socket()");

    memset(&inet_srvr, 0, sizeof inet_srvr);
    inet_srvr.sin_family = AF_INET;
    inet_srvr.sin_port = htons(9000);

    if ( inet_aton(srvr_addr, &inet_srvr.sin_addr) == -1 )
        bail("inet_aton()");

    len_inet = sizeof inet_srvr;

    for(;;) {
        fputs("\nEnter string format: ", stdout);
        if(!fgets(dgram, sizeof dgram, stdin))
            break;

        z = strlen(dgram);
        if (z > 0 && dgram[--z] == '\n')
            dgram[z] = 0;

        z = sendto(s, dgram, strlen(dgram), 0, (struct sock_addr*)&inet_srvr,
            len_inet);
        if (z < 0)
            bail("sendto()");

        if(!strcasecmp(dgram, "QUIT"))
            break;

        x = sizeof adr;
        z = recvfrom(s, dgram, sizeof dgram, 0, (struct sockaddr*)&adr, &x);
        if ( z < 0)
            bail("recvfrom()");
        dgram[z] = 0;

        printf("Result from %s port %u : \n\t'%s'\n",
        inet_ntoa(adr.sin_addr), (unsigned) ntohs(adr.sin_port), dgram);
    }

    close(s);

    putchar('\n');


    return 0;
}
