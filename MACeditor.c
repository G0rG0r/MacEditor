///// made by GorGor
//// Use at your own risk !


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char command[256];
char newMac[16];
char interface[64] = "Ethernet";
 
char* generate_random_mac() {
    static char mac_str[13]; 
    unsigned char mac[6];
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 6; i++) {
        mac[i] = rand() % 256;
    }

    mac[0] = (mac[0] & 0xFE) | 0x02; 

    sprintf(mac_str, "%02X%02X%02X%02X%02X%02X", 
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    return mac_str;
}

int main (int argc, char *argv[]) {
    char* macAddress = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-if=", 4) == 0) {
            strncpy(interface, argv[i] + 4, sizeof(interface) - 1);
            interface[sizeof(interface) - 1] = '\0';
        } else {
            macAddress = argv[i];
        }
    }
    
    if (macAddress == NULL) {
        macAddress = generate_random_mac();
    } else {
        strncpy(newMac, macAddress, sizeof(newMac) - 1);
        newMac[sizeof(newMac) - 1] = '\0';
        macAddress = newMac;
    }
    
    snprintf(command, sizeof(command),
             "powershell.exe -Command \"Set-NetAdapter -Name '%s' -MacAddress '%s'\"",
             interface, macAddress);
    
    system(command);
    
    return 0;
}