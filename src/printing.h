#ifndef PRINTING_H_
#define PRINTING_H_

#include "ipv4.h"
#include "ethernet.h"

void stringify_mac(mac_addr, char* dest);
void stringify_ipv4(ipv4_addr, char* dest);

int print_iface(struct iface * interface);

#endif
