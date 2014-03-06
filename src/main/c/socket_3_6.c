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

int main()
{
    int x;
    const char *addr[] = {"44.1.2.3", "127.0.0.1", "172.16.2.1", "192.168.9.2"};
    unsigned long net_addr;

    for (x=0;x<4;x++) {
        net_addr = inet_network(addr[x]);
        printf("%14s = %x %x \n", addr[x], net_addr,
            (unsigned long)htonl(net_addr));

    }

    return 0;
}
