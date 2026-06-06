#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

    if (argc != 2){
        printf("Usage ./dns <hostname>\n");
        return EXIT_FAILURE;
    }

    struct addrinfo *presult;                               // variable that stores the IPs return by getaddrinfo()
    const char *node = argv[1];                             // host name passed
    const char *service = "https";                          // service used by getaddrinfo, it sets the port, e.g. You can use "http" to get TCP or set it equal to 0 to e get every port used by the IP address
    struct addrinfo hints;                                  // struct that helps getaddrinfo to filter the results
    char  ipstr[INET6_ADDRSTRLEN];                          // string that contains the IP address converted to string
    char *prot;                                             // string used to store the protocol used by the IP address

    memset(&hints, 0, sizeof(struct addrinfo));             // clearing the memory for hints
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = 0;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int result = getaddrinfo(node, service, &hints, &presult);
    printf("IP address for %s\n", node);

    // Looping and printing the results
    for (struct addrinfo *rp = presult; rp != NULL; rp = rp->ai_next) {
        void *addr;

        // converting the IP return to compitible type for inet_ntop()
        if (rp->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        printf("Family: %s\n", rp->ai_family == AF_INET ? "IPv4" : "IPv6");
        const char *ip_addr = inet_ntop(rp->ai_family, addr, ipstr, sizeof(ipstr));
        printf("Address: %s\n", ip_addr);
        switch (rp->ai_protocol)
        {
        case IPPROTO_IP: prot = "IP";
            break;
        case IPPROTO_TCP: prot = "TCP";
            break;
        case IPPROTO_UDP: prot = "UDP";
            break;
        default: prot = "Unknown";
            break;
        }
        printf("Protocol used: %s\n", prot);
        printf("-----------------------------------------------------\n");

    }

    freeaddrinfo(presult);

    return EXIT_SUCCESS;
}