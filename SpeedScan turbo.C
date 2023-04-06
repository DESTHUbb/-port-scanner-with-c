#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/tcp.h>

// Function to scan a port on a specific IP address
int scan_port(char *ip_address, int port) {

    // Create a non-blocking TCP socket
    int socket_desc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_desc == -1) {
        printf("Failed to create socket");
        return -1;
    }

    // Set the socket to non-blocking mode
    int flags = fcntl(socket_desc, F_GETFL, 0);
    if (flags == -1) {
        printf("Failed to get socket flags");
        close(socket_desc);
        return -1;
    }
    if (fcntl(socket_desc, F_SETFL, flags | O_NONBLOCK) == -1) {
        printf("Failed to set socket to non-blocking mode");
        close(socket_desc);
        return -1;
    }

    // Set TCP_NODELAY option to reduce latency
    int yes = 1;
    if (setsockopt(socket_desc, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(int)) == -1) {
        printf("Failed to set TCP_NODELAY option");
        close(socket_desc);
        return -1;
    }

    // Set SO_REUSEADDR option to reuse the port immediately after close
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        printf("Failed to set SO_REUSEADDR option");
        close(socket_desc);
        return -1;
    }

    // Set the IP address and port for the socket
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip_address);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // Start a non-blocking connect operation
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        if (errno == EINPROGRESS) {
            // The connection is in progress, wait for it to complete or timeout
            fd_set write_fds;
            struct timeval timeout;
            FD_ZERO(&write_fds);
            FD_SET(socket_desc, &write_fds);
            timeout.tv_sec = 0;
            timeout.tv_usec = 100000; // 100ms timeout
            int select_result = select(socket_desc + 1, NULL, &write_fds, NULL, &timeout);
            if (select_result == -1) {
                printf("Failed to select socket for non-blocking connect");
                close(socket_desc);
                return -1;
            } else if (select_result == 0) {
                // The connection timed out, close the socket
                close(socket_desc);
                return 0;
            }
        } else {
            // The connect operation failed
            close(socket_desc);
            return 0;
        }
    }

    // The connection succeeded, close the socket
    close(socket_desc);
    return 1;
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
