#ifndef ARP_H_
#define ARP_H_

#include "raw.h"
#include "ethernet.h"
#include "ipv4.h"

struct arp_body {
    uint16_t hardware_type;
    uint16_t protocol_type;

    uint8_t hardware_addr_len;
    uint8_t protocol_addr_len;

    uint16_t operation;

    mac_addr sender_mac;
    ipv4_addr sender_ip;

    mac_addr target_mac;
    ipv4_addr target_ip;
}__attribute__((packed));


int _send_arp_request(struct iface * i, ipv4_addr target_ip);

#endif
