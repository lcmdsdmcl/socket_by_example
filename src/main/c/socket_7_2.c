#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>

int main()
{
    int x;
    struct servent *sp;

    for(;;) {
        errno = 0;
        if (!(sp = getservent()))
            break;

        printf("%s:\n \tPort: %d\n \tProtocol: %s\n \tAliases: ",
            sp->s_name, ntohs(sp->s_port), sp->s_proto);
        for(x=0; sp->s_aliases[x] != NULL; x++)
            printf("%s ", sp->s_aliases[x]);

        putchar('\n');

    }

    if (errno != 0 && errno != ENOENT)
        fprintf(stderr, "%s: getservent(3) %d\n", strerror(errno), errno);

    return 0;
}
