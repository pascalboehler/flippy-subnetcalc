#include "subnet_ipv4.h"

#define OCTETS_AVAILABLE 4
#define TESTSUBNET 28
#define HOSTS_PER_OCTET 256 

short* calculate_decimal_mask(int cidr_id) {
    short* octetsDec = (short*)malloc(sizeof(short[OCTETS_AVAILABLE]));

    int networkBitsAvailable = cidr_id;

    for(int i = 0; i < OCTETS_AVAILABLE; i++) {
        if((networkBitsAvailable - 8) > 0) {
            octetsDec[i] = 0 + (1 << 8) - 1; // creates 255
            networkBitsAvailable -= 8;
        } else {
            octetsDec[i] = 0 + (1 << 8) - (1 << (8 - networkBitsAvailable));
            networkBitsAvailable = 0;
        }
        //printf("%d\n", octetsDec[i]);
    }
    return octetsDec;
}

// TODO: Understand this code and its values
int count_one(int x) {
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
    return x;
}

int calculate_cidr_id(u_int8_t octets[4]) {
    u_int8_t count = 0;
    for(int i = 0; i < 4; i++) {
        count += count_one(octets[i]);
    }
    return count;
}

int calculate_hosts_available(int cidr) {
    short* octets = calculate_decimal_mask(cidr);
    int hosts_available = 1;

    for(int i = 0; i < OCTETS_AVAILABLE; i++) {
        int hosts = (HOSTS_PER_OCTET - octets[i]);
        if(hosts == 0)
            continue;
        else
            hosts_available *= hosts;
    }
    free(octets);
    return hosts_available - 2;
}

void calculate_x_ip_in_network(short * network, int cidr, int xIp) {
    for (int i = 0; i < OCTETS_AVAILABLE; i++) {
        printf("%i\n", network[i]);
    }
    
}

int main() {
    u_int8_t octets[4];
    octets[0] = 255;
    octets[1] = 255;
    octets[2] = 255;
    octets[3] = 0;
    int cidr = calculate_cidr_id(octets);

    short network[4];
    network[0] = 192;
    network[1] = 168;
    network[2] = 172;
    network[3] = 0;

    printf("CIDR Notation: %i\n", cidr);
    printf("Hosts available: %i\n", calculate_hosts_available(cidr));
    
    calculate_x_ip_in_network(network, cidr, 1);
}
