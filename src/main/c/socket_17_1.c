#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>

int main()
{
    struct iovec iov[3];
    char p1[] = "***Beginning ";
    char p2[] = "::IOVEC:: ";
    char p3[] = "End***\n";

    iov[0].iov_base = p1;
    iov[0].iov_len = strlen(p1);

    iov[1].iov_base = p2;
    iov[1].iov_len = strlen(p2);

    iov[2].iov_base = p3;
    iov[2].iov_len = strlen(p3);

    writev(1, iov, 3);

    return 0;
}
