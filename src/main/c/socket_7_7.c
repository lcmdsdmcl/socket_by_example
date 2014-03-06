#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>

static void bail(const char *get) {
    perror(get);
    exit(1);
}

int main(int argc, char **argv)
{
    int z;
    int s;
    char dtbuf[128];
    char *srvr_addr = NULL;
    int len_inet;
    struct sockaddr_in adr_srvr;
    struct servent *sp;

    if (argc >= 2)
        srvr_addr = argv[1];
     else
        srvr_addr = "127.0.0.23";

    sp = getservbyname("daytime", "tcp");
    if (!sp)
        bail("getservbyname()");

    memset(&adr_srvr, 0, sizeof adr_srvr);
    adr_srvr.sin_family = AF_INET;
    adr_srvr.sin_port = sp->s_port;
    if(inet_aton(srvr_addr, &adr_srvr.sin_addr) == -1 )
        bail("inet_aton()");

    len_inet = sizeof adr_srvr;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
        bail("socket()");

    z = connect(s, (struct sockaddr*)&adr_srvr, len_inet);
    if(z == -1)
        bail("connect()");

    z = read(s, &dtbuf, sizeof dtbuf-1);
    if ( z == -1)
        bail("read()");
    dtbuf[z] = 0;

    printf("Date is: %s\n", dtbuf);

    close(s);
    putchar('\n');

    return 0;
}
