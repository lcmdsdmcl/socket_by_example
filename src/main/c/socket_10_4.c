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
#include <arpa/inet.h>
#include <ctype.h>

int mkaddr(void *addr, int *addrlen, char *str_addr, char *protocol) {
    char *inp_addr = strdup(str_addr);
    char *host_part = strtok(inp_addr, ":");
    char *port_part = strtok(inp_addr,"\n");

    struct sockaddr_in *ap = (struct sockaddr_in*)&addr;
    struct hostent *hp = NULL;
    struct servent *sp = NULL;

    char *cp;
    long lv;

    if(!host_part)
        host_part = "*";
    if(!port_part)
        port_part = "*";
    if(!protocol)
        protocol = "tcp";

    memset(ap, 0, *addrlen);
    ap->sin_family = AF_INET;
    ap->sin_port = 0;
    ap->sin_addr.s_addr = INADDR_ANY;

    if( !strcmp(host_part, "*") ) {
        ; // ap->sin_addr.s_addr = INADDR_ANY;
    } else if(isdigit(*host_part)) {
        ap->sin_addr.s_addr = inet_addr(host_part);
        if(ap->sin_addr.s_addr == INADDR_ANY)
            return -1;
    } else {
        hp = gethostbyname(host_part);
        if(!hp)
            return -1;
        if(hp->h_addrtype != AF_INET)
            return -1;

        ap->sin_addr = *(struct in_addr*)hp->h_addr_list[0];
    }

    if(!strcmp(port_part, "*")) {
        ; // ap->sin_port = 0;
    } else if(isdigit(*port_part)) {
        lv = strtol(port_part, &cp, 10);
        if(cp != NULL && *cp)
            return -2;
        if(lv <0L || lv >= 32768)
            return -2;

        ap->sin_port = htons((short)lv);
    } else {
        sp = getservbyname(port_part, protocol);
        if(!sp)
            return -2;

        ap->sin_port = (short)sp->s_port;
    }

    *addrlen = sizeof *ap;
    free(inp_addr);

    return 0;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
