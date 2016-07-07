#ifndef ETHERNET_H_
#define ETHERNET_H_

#define ETHERTPYE_ARP  0x0806
#define ETHERTYPE IPV4 0x0800

typedef uint8_t mac_addr[6];

struct ethernet_header {
    mac_addr dest;
    mac_addr source;

    union {
        uint16_t protocol;
        uint16_t size;
    };

}__attribute__((packed));

#endif
