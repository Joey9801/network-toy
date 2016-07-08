#include <string.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if_ether.h> //ETH_P_ALL
#include <linux/if_packet.h>
#include <netinet/in.h>

#include "raw.h"
#include "ethernet.h"

int get_raw_interface(struct iface* interface, char * name) {
    strcpy(interface->name, name);

    interface->sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(interface->sockfd == -1) {
        return -1;
    }

    get_interface_info(interface);

    return 0;
}

/* Fills out the rest of the iface struct based on the name field */
int get_interface_info(struct iface* interface) {
    struct ifreq buffer;
    memset(&buffer, 0x00, sizeof(buffer));
    strncpy(buffer.ifr_name, interface->name, IFNAMSIZ);

    //MAC address
    ioctl(interface->sockfd, SIOCGIFHWADDR, &buffer);
    memcpy(interface->mac, buffer.ifr_hwaddr.sa_data, 6);

    //IPv4 address
    ioctl(interface->sockfd, SIOCGIFADDR, &buffer);
    memcpy(interface->ipv4_addr, &((struct sockaddr_in*)&buffer.ifr_addr)->sin_addr, 4);

    //Internal IF index
    ioctl(interface->sockfd, SIOCGIFINDEX, &buffer);
    interface->index = buffer.ifr_ifindex;

    //MTU
    ioctl(interface->sockfd, SIOCGIFMTU, &buffer);
    interface->mtu = buffer.ifr_mtu;

    //Set promiscuous mode
    ioctl(interface->sockfd, SIOCGIFFLAGS, &buffer);
    buffer.ifr_flags |= IFF_PROMISC;
    ioctl(interface->sockfd, SIOCSIFFLAGS, &buffer);

    return 0;
}


int send_packet(struct iface* i, void* packet, size_t length) {
    struct sockaddr_ll send_addr;

    //Most of the struct is not needed, since we're custom writing
    //all of the headers
    send_addr.sll_ifindex = i->index;
    send_addr.sll_halen = 6;
    memcpy(send_addr.sll_addr, i->mac, 6);
    struct sockaddr* s = (struct sockaddr*)&send_addr;

    return sendto(i->sockfd, packet, length, 0, s, sizeof(struct sockaddr_ll));
}

ssize_t recv_packet(struct iface* interface, void* buffer, size_t length) {
    return recv(interface->sockfd, buffer, length, 0);
}

ssize_t recv_type(struct iface* interface, void* buffer, size_t length, uint16_t type) {
    memset(buffer, 0x00, length);
    struct ethernet_header* e = (struct ethernet_header*)buffer;

    ssize_t size = recv_packet(interface, buffer, length);

    while(e->protocol != type) {
        size = recv_packet(interface, buffer, length);
    }

    return size;
}
