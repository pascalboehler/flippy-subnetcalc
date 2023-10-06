#ifndef SUBNET_IPV4_HEADERS
#define SUBNET_IPV4_HEADERS

void calculate_decimal_mask(int subnetid);
int calculate_subnet_id(u_int8_t octets[4]);

#endif