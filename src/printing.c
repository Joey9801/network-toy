#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "ethernet.h"
#include "ipv4.h"
#include "raw.h"

int stringify_mac(mac_addr addr, char* dest) {
    sprintf(dest, "%02X:%02X:%02X:%02X:%02X:%02X",
            addr[0],
            addr[1],
            addr[2],
            addr[3],
            addr[4],
            addr[5]
           );

    return 0;
}

int stringify_ipv4(ipv4_addr addr, char* dest) {
    sprintf(dest, "%i.%i.%i.%i",
            addr[0],
            addr[1],
            addr[2],
            addr[3]
           );

    return 0;
}

int print_iface(struct iface * interface) {
    printf("Interface properties:\n");
    printf("\tName    : %s\n", interface->name);
    printf("\tIndex   : %i\n", interface->index);
    printf("\tMTU     : %i\n", interface->mtu);

    char mac_string[17];
    stringify_mac(interface->mac, mac_string);
    printf("\tHW Addr : %s\n", mac_string);

    char ipv4_string[15];
    stringify_ipv4(interface->ipv4_addr, ipv4_string);
    printf("\tIP Addr : %s\n", ipv4_string);

    return 0;
}

void print_bytes(uint8_t bytes[], size_t length) {

    for(int i=0; i<length; i++) {
        printf("%02X ", bytes[i]);

        if((i+1) % 8 == 0) {
            printf(" ");
            if((i+1) % 16 == 0) {
                printf("\n");
            }
        }
    }

    return;
}
