# Port-scanner-with-c
### This C language code is used to scan the open ports on a specific range of IP addresses. The program takes three command line arguments: the IP address to be scanned, the start port, and the end port in the scan range. The program then iterates through the specified range of ports and calls the "scan_port" function to check if the port is open or closed.
![PORTSACN](https://user-images.githubusercontent.com/90658763/230355208-32763816-539d-418f-b6bb-a2f4e6a2a9ba.gif)

## Code operation:
The "scan_port" function creates a TCP socket, sets the IP and port, and then attempts to connect to the port at the specified IP address. If the connection is successful, the port is open and the function returns 1. Otherwise, the port is closed and the function returns 0.
``` C
int scan_port(char *ip_address, int port) {

    // Create a non-blocking TCP socket
    int socket_desc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_desc == -1) {
        printf("Failed to create socket");
        return -1;
    }
```
