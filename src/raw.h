#ifndef RAW_H_
#define RAW_H_

#include <stdint.h>
#include <stddef.h>

//To get IFNAMSIZ, nothing else in this header..
#include <sys/socket.h>
#include <linux/if.h>

#include "ethernet.h"
#include "ipv4.h"

struct iface {
    char name[IFNAMSIZ];
    int sockfd;
    int index;
    int mtu;
    ipv4_addr ipv4_addr;
    mac_addr mac;
};

int get_raw_interface(struct iface* interface, char* interface_name);

int get_interface_info(struct iface* interface);
int send_packet(struct iface* interface, void* packet, size_t length);

ssize_t recv_packet(struct iface* interface, void* buffer, size_t length);
ssize_t recv_type(struct iface* interface, void* buffer, size_t length, uint16_t type);

#endif
