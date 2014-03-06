#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>

int main()
{
    int z;
    struct utsname u;
    char buf[30];

    z = uname(&u);
    if (z == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    printf("sysname=%s\t nodename=%s\t release=%s\t version=%s\t machine=%s\n",
        u.sysname, u.nodename, u.release, u.version, u.machine);

    z = gethostname(buf, sizeof buf);
    if (z == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    printf("Hostname: %s\n", buf);

    z = getdomainname(buf, sizeof buf);
    if (z == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    printf("Domainname: %s\n", buf);

    return 0;
}
