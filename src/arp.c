#include <string.h>

#include <netinet/in.h> //htons et. al.

#include "raw.h"
#include "ethernet.h"
#include "ipv4.h"
#include "arp.h"

int _send_arp_request(struct iface * i, ipv4_addr target_ip) {
    unsigned int packet_size = sizeof(struct ethernet_header) + sizeof(struct arp_body);
    uint8_t send_buffer[packet_size];

    struct ethernet_header * e = (struct ethernet_header*)&send_buffer[0];
    struct arp_body * a = (struct arp_body*)&send_buffer[sizeof(struct ethernet_header)];

    memcpy(e->source, i->mac, 6);
    memset(e->dest, 0xff, 6);           //Broadcast
    e->protocol = htons(ETHERTYPE_ARP);

    a->hardware_type = htons(0x01);     //Ethernet
    a->protocol_type = htons(0x0800);   //IPv4
    a->hardware_addr_len = 0x06;
    a->protocol_addr_len = 0x04;
    a->operation = htons(0x0001);       //Request operation

    //Sender details
    memcpy(a->sender_mac, i->mac, 6);
    memcpy(a->sender_ip, i->ipv4_addr, 4);

    //Target details
    memset(a->target_mac, 0x00, 6);     //Zero out the target hwaddr
    memcpy(a->target_ip, target_ip, 4); //Set the target IP


    return send_packet(i, send_buffer, packet_size);
}
