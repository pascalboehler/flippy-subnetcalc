#include "subnet_ipv4.h"
#include <sys/_types/_u_int8_t.h>

#define OCTETS_AVAILABLE 4
#define HOSTS_PER_OCTET 256 

/** 
 * calculate_decimal_mask
 * Calculates subnet mask from cidr notation 
 * @param: int cidr 
 * @return: short *
 */

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

/**
 * count_one 
 * Counts all bits that are 1 in a number (bit counting)
 * @param: int x 
 * @return: int 
 */

int count_one(int x) {
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
    return x;
}

/**
 * calculate_cidr_id 
 * Calculates the cidr network id from a subnet mask 
 * @param: u_int8_t octets[4]
 * @return: int 
 */

int calculate_cidr_id(u_int8_t octets[4]) {
    u_int8_t count = 0;
    for(int i = 0; i < 4; i++) {
        count += count_one(octets[i]);
    }
    return count;
}

/**
 * calculate_hosts_available 
 * Calculate the number of available
 * @param: int cidr 
 * @return: int 
 */

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

/**
*   calculate_x_ip_in_network
*   return IP Addr
*   @param: short * network, int cidr, int xIp
*   @return: short *
*/

short * calculate_x_ip_in_network(short * network, int cidr, int xIp) {
    if (xIp > calculate_hosts_available(cidr))
        return NULL;
    
    for (int i = 0; i < OCTETS_AVAILABLE; i++) {

    } 
    
    return NULL;
}

/**
*   calculate_ip_network_from_mask
*   Calculates the IP Network representation from a given subnet mask 
*   @param: short * octets, short * ip 
*   @return: short *
*/

short * calculate_ip_network_from_mask(short * octets, short * ip) {
    short * network = (short *) malloc(sizeof(short[OCTETS_AVAILABLE]));
    
    for (int i = 0; i < OCTETS_AVAILABLE; i++) {
        short ipPart = ip[i];
        short octetPart = octets[i];
        short networkPart = (ipPart & octetPart);
        network[i] = networkPart;
    }
    
    return network;
}

/** Entry points for debugging */

int main() {
    short * octets = (short *) malloc(sizeof(short[4]));
    octets[0] = 255;
    octets[1] = 255;
    octets[2] = 255;
    octets[3] = 0;
    
    int cidr = calculate_cidr_id(octets);

    short ip[4];
    ip[0] = 192;
    ip[1] = 168;
    ip[2] = 178;
    ip[3] = 250;

    short * network = calculate_ip_network_from_mask(octets, ip);

    int help = (0 & 128);

    printf("IP: %i.%i.%i.%i\n", ip[0], ip[1], ip[2], ip[3]);
    printf("Network: %i.%i.%i.%i\n", network[0], network[1], network[2], network[3]);
    printf("Subnetmask: %i.%i.%i.%i\n", octets[0], octets[1], octets[2], octets[3]);
    printf("CIDR Notation: %i\n", cidr);
    printf("Hosts available: %i\n", calculate_hosts_available(cidr));
    
    calculate_x_ip_in_network(network, cidr, 1);

    free(octets);
    free(network);
}
