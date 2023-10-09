#ifndef SUBNET_IPV4_HEADERS
#define SUBNET_IPV4_HEADERS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

short* calculate_decimal_mask(int subnetid);
int calculate_subnet_id(u_int8_t octets[4]);
short* calculate_x_ip_in_network(short * network, int cidr, int xIp);

#endif
