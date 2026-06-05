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

    struct addrinfo *presult; 
    const char *node = argv[1];
    const char *service = "http";
    struct addrinfo hints;
    char  ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(struct addrinfo));
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

    //Printing the results
    for (struct addrinfo *rp = presult; rp != NULL; rp = rp->ai_next) {
        void *addr;

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

    }

    freeaddrinfo(presult);

    return EXIT_SUCCESS;
}