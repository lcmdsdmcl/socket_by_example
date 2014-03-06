#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

static void bail(const char *get) {
    perror(get);
    exit(1);
}

int main()
{
    int n, z;
    time_t td;
    char buf[128];

    time(&td);
    n = (int)strftime(buf, sizeof buf, "%A %Y\n", localtime(&td));

    z = write(1, buf, n);
    if (z == -1)
    bail("write()");

    return 0;
}
