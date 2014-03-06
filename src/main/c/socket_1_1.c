#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char**argv)
{
    int z;
    int sv[2];

    z = socketpair(AF_LOCAL, SOCK_STREAM, 0, sv);
    if (z == -1) {
        fprintf(stderr, "%s, socketpair(AF_LOCAL, SOCK_STREAM, 0)\n", strerror(errno));
        return 1;
    }

    printf("sv[0] = %d\n", sv[0]);
    printf("sv[1] = %d\n", sv[1]);

    printf("*** press ENTER***");
    getchar();

    system("netstat --unix -p | grep socket_1");


    return 0;
}
