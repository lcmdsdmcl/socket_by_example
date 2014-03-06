#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>

int main()
{
    int x;
    struct hostent *hp;
    char *name = "www.google.com";
    hp = gethostbyname(name);

    printf("h_name=%s\t h_addrtype=%d\t h_length=%d\n",
        hp->h_name, hp->h_addrtype, hp->h_length);

    for(x = 0; hp->h_aliases[x]; x++)
        printf("Alias: %s\t", hp->h_aliases[x]);

    printf("\n");

    for(x = 0; hp->h_addr_list[x]; x++)
        printf("Addr_list: %s\t", inet_ntoa(hp->h_addr_list[x]));

    printf("\n");

    return 0;
}
