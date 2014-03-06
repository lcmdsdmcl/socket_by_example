#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


int main(int argc, char** argv)
{

    int z;
    int s[2];
    char *msgp;
    int mlen;
    char buf[80];
    pid_t chpid;

    // create a pair of socket
    z = socketpair(AF_LOCAL, SOCK_STREAM, 0, s);
    if (z == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }

    // fork into two processes
    if ( (chpid = fork()) == (pid_t)-1) {
        fprintf(stderr, "%s", strerror(errno));
        exit(1);
    } else if (chpid == 0) {
        char rxbuf[80];
        printf("Parent PID is: %ld\n", (long)getppid());
        close(s[0]);
        s[0] = -1;

        msgp = "%A %d-%b-%Y %l:%M %p";
        mlen = strlen(msgp);

        printf("Child sending request '%s' \n", msgp);
        fflush(stdout);

        z = write(s[1], msgp, mlen);
        if( z < 0) {
            fprintf(stderr, "%s: write(2) \n", strerror(errno));
            exit(1);
        }

        if ( shutdown(s[1], SHUT_WR) == -1) {
            fprintf(stderr, "%s: shutdown(2)\n", strerror(errno));
            exit(1);
        }

        z = read(s[1], rxbuf, sizeof rxbuf);
        if (z < 0) {
            fprintf(stderr, "%s: read(2)\n", strerror(errno));
            exit(1);
        }
        rxbuf[z] = 0;

        printf("Server returned '%s'\n", rxbuf);
        fflush(stdout);

        close(s[1]);

    } else {

        int status;
        char txbuf[80];
        time_t td;

        printf("Child PID is: %ld\n", (long)chpid);
        fflush(stdout);
        close(s[1]);
        s[1] = -1;

        z = read(s[0], buf, sizeof buf);
        if (z < 0) {
            fprintf(stderr, "%s: read(2)\n", strerror(errno));
            exit(1);
        }
        buf[z] = 0;

        time(&td);

        strftime(txbuf, sizeof txbuf, buf, localtime(&td));

        z = write(s[0], txbuf, sizeof txbuf);
        if (z < 0) {
            fprintf(stderr, "%s: write(2)\n", strerror(errno));
            exit(1);
        }

        close(s[0]);

        waitpid(chpid, &status, 0);
    }


    return 0;
}
