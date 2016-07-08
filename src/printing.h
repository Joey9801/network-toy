#ifndef PRINTING_H_
#define PRINTING_H_

#include <stddef.h>

#include "ipv4.h"
#include "ethernet.h"

void stringify_mac(mac_addr, char* dest);
void stringify_ipv4(ipv4_addr, char* dest);

int print_iface(struct iface * interface);

void print_bytes(uint8_t bytes[], size_t length);

#endif
