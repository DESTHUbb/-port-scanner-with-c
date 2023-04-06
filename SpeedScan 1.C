#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Function to scan a port on a specific IP address
int scan_port(char *ip_address, int port) {

    // Create a TCP socket
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Failed to create socket");
        return -1;
    }

    
// Set the IP address and port for the socket
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip_address);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    
// Connect the socket to the port at the IP address
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        
    // The port is not open
        close(socket_desc);
        return 0;
    } else {
        
    // The port is open
        close(socket_desc);
        return 1;
    }
}

int main(int argc, char *argv[]) {
    
    // Check if the proper arguments were provided
    if (argc != 4) {
        printf("Uso: %s <IP adress> <initial port> <final port>\n", argv[0]);
        return 1;
    }


    
    // Get the IP address and port range from the command line arguments
    char *ip_address = argv[1];
    int port_start = atoi(argv[2]);
    int port_end = atoi(argv[3]);
 
    // Scan the ports in the specified range and display the results on the screen
    int port;
    for (port = port_start; port <= port_end; port++) {
        if (scan_port(ip_address, port)) {
            printf("Port %d is open\n", port);
        } else {
            printf("Puerto %d is closed\n", port);
        }
    }

    return 0;
}

