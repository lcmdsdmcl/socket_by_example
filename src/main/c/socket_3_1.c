#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>

int main()
{
    int x;
    struct sockaddr_in adr_inet;
    int len_inet;
    unsigned int msb;
    char class;
    char *netmask;
    static struct {
        unsigned char ip[4];
    } addresses[] = {
    {{44,135,86,12}},
    {{127,0,0,1}},
    {{172,16,23,95}},
    {{192,168,9,1}},
    };

    for (x=0; x<4; x++) {
        memset(&adr_inet, 0, sizeof adr_inet);
        adr_inet.sin_family = AF_INET;
        adr_inet.sin_port = htons(9000);
        memcpy(&adr_inet.sin_addr.s_addr, addresses[x].ip, 4);
        len_inet = sizeof adr_inet;

        msb = *(unsigned char *)&adr_inet.sin_addr.s_addr;

        printf("MSB = %d\n", msb);

        if ( (msb & 0x80 ) == 0x00 ) {      // 128
            class = 'A';
            netmask = "255.0.0.0";
        } else if ( (msb & 0xC0 ) == 0x80 ) { // 192
            class = 'B';
            netmask = "255.255.0.0";
        } else if ( (msb & 0xE0 ) == 0xC0 ) { // 224
            class = 'C';
            netmask = "255.255.255.0";
        } else if ( (msb & 0xF0 ) == 0xE0 ) { // 240
            class = 'D';
            netmask = "255.255.255.255";
        } else {
            class = 'E';
            netmask = "255.255.255.255";
        }

        printf("Address %u %u %u %u is class %c and netmask is %s \n", addresses[x].ip[0],
        addresses[x].ip[1], addresses[x].ip[2], addresses[x].ip[3], class, netmask );
    }

    return 0;
}
