#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

static void bail(const char *get) {
    perror(get);
    exit(1);
}

int main(int argc, char **argv)
{
    int z;
    int s;
    int c;
    int n;
    int len_inet;
    time_t td;
    char dtbuf[128];

    char *srvr_addr = NULL;
    char *srvr_port = NULL;
    struct sockaddr_in adr_srvr;
    struct sockaddr_in adr_clnt;

    struct hostent *hp;
    FILE *logf;

    if ( !(logf = fopen("srvr.log", "w")))
        bail("fopen()");




    if (argc >= 2)
        srvr_addr = argv[1];
     else
        srvr_addr = "127.0.0.1";

    if (argc >= 3)
        srvr_port = argv[2];
     else
        srvr_port ="9000";

    s = socket (AF_INET, SOCK_STREAM, 0);
    if (s == -1)
        bail("socket()");

    memset(&adr_srvr, 0, sizeof adr_srvr);
    adr_srvr.sin_family = AF_INET;
    adr_srvr.sin_port = htons(atoi(srvr_port));

    if ( strcmp(srvr_addr, "*") != 0) {
        if ( inet_aton(srvr_addr, &adr_srvr.sin_addr) == -1)
            bail("inet_aton()");
    } else {
        adr_srvr.sin_addr.s_addr = INADDR_ANY;
    }

    len_inet = sizeof adr_srvr;

    z = bind(s, (struct sockaddr*)&adr_srvr, len_inet);
    if (z == -1)
        bail("bind()");

    z = listen(s, 10);
    if (z == -1)
        bail("listen()");

    for (;;) {
        len_inet = sizeof adr_clnt;

        c = accept(s, (struct sockaddr*)&adr_clnt, &len_inet);
        if (c == -1)
            bail("accept()");

        fprintf(logf, "Client: %s\n", inet_ntoa(adr_clnt.sin_addr));
        hp = gethostbyaddr((char*)&adr_clnt.sin_addr, sizeof adr_clnt.sin_addr,
            adr_clnt.sin_family);
        if (!hp)
            fprintf(logf, "Error: %s\n", hstrerror(h_errno));
         else
            fprintf(logf, " %s\n", hp->h_name);
        fflush(logf);

        time(&td);
        n = (int) strftime(dtbuf, sizeof dtbuf, "%A %b %d %H:%M %Y\n",localtime(&td));

        z = write(c, dtbuf, n);
        if ( z == -1 )
            bail("write()");

        close(c);
    }

    close(logf);

    return 0;
}
