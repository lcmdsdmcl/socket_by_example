#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>


int main(int agrc, char** argv)
{
    int z;
    int s[2];
    char *cp;
    char buf[80];

    // creating socket pair
    z = socketpair(AF_LOCAL, SOCK_STREAM, 0, s);
    if (z == -1) {
        fprintf(stderr, "%s: socketpair(AF_LOCAL, SOCK_STREAM, 0, sv)\n", strerror(errno));
        return 1;
    }

    // send something
    z = write(s[1], cp="Hello!", 6);
    if(z < 0) {
        fprintf(stderr, "%d, %s, %d\n", strerror(errno), s[1], strlen(cp));
        return 2;
    }
    printf("Wrote a message '%s' on s[1]\n", cp);

    // read it
    z = read(s[0], buf, sizeof buf);
    if (z < 0) {
        fprintf(stderr, "%s: read(%s, %d", strerror(errno), s[0], sizeof buf);
        return 3;
    }
    buf[z] = 0;
    printf("Recieved message '%s' from s[0]\n", buf);

    //send something back

    z = write(s[0], cp="GO away!", 8);
    if (z < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 4;
    }
    printf("Wrote message '%s' on s[0]\n", cp);

    //read it
    z = read(s[1], buf, sizeof buf);
     if (z < 0) {
        fprintf(stderr, "%s: read(%s, %d", strerror(errno), s[1], sizeof buf);
        return 3;
    }
    buf[z] = 0;
    printf("Recieved message '%s' from s[1]\n", buf);

    // closing
    close(s[0]);
    close(s[0]);

    puts("Done.");

    return 0;
}
