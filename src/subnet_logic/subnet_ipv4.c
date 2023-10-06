#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subnet_ipv4.h"

#define OCTETS_AVAILABLE 4
#define TESTSUBNET 28

void calculate_decimal_mask(int subnetid) {
    short octetsDec[OCTETS_AVAILABLE];

    int networkBitsAvailable = subnetid;

    for(int i = 0; i < OCTETS_AVAILABLE; i++) {
        if((networkBitsAvailable - 8) > 0) {
            octetsDec[i] = 0 + (1 << 8) - 1; // creates 255
            networkBitsAvailable -= 8;
        } else {
            octetsDec[i] = 0 + (1 << 8) - (1 << (8 - networkBitsAvailable));
            networkBitsAvailable = 0;
        }
        printf("%d\n", octetsDec[i]);
    }
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

int calculate_subnet_id(u_int8_t octets[4]) {
    u_int8_t count = 0;
    for(int i = 0; i < 4; i++) {
        count += count_one(octets[i]);
    }
    return count;
}

int main() {
    u_int8_t octets[4];
    octets[0] = 255;
    octets[1] = 255;
    octets[2] = 240;
    octets[3] = 0;

    printf("%i\n", calculate_subnet_id(octets));
}
