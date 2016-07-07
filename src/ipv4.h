#ifndef IPV4_H_
#define IPV4_H_

#include <stdint.h>

typedef uint8_t ipv4_addr[4];

struct ipv4_header {
    uint8_t ihl:4,
            version:4;
    uint8_t dscp:6,
            ecp:2;
    uint16_t total_length;
    uint16_t identification;
    uint16_t _res0:1,
             do_not_fragment:1,
             more_fragments:1,
             fragment_offset:13;

    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;

    ipv4_addr source;
    ipv4_addr dest;
}__attribute__((packed));


uint16_t ipv4_checksum(struct ipv4_header * hdr);

#endif
