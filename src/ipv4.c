#include <stdint.h>
#include <arpa/inet.h>

#include "ipv4.h"

uint16_t ipv4_checksum(struct ipv4_header * hdr) {
    uint16_t* ptr = (uint16_t*)hdr;
    uint32_t sum = 0xffff;

    /* Fixed size
     * This wont work if we want any of the options fields
     */
    for(unsigned int i=0; i<10; i++) {
        sum += ntohs(*(ptr+i));
        if(sum > 0xffff) {
            sum -= 0xffff;
        }
    }

    uint16_t res = (sum & 0x0000ffff) + ((sum & 0xffff0000) >> 16);
    return htons(~res);
}
