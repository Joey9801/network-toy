#ifndef PRINTING_H_
#define PRINTING_H_

#include <stddef.h>

#include "ipv4.h"
#include "ethernet.h"
#include "arp.h"

void stringify_mac(mac_addr mac, char* dest);
void stringify_ipv4(ipv4_addr ipv4, char* dest);

void print_iface(struct iface * interface);

void print_bytes(uint8_t bytes[], size_t length);

void print_arp(struct arp_body* a);

#endif
