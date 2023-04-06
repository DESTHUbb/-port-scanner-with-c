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
# Result:
![image](https://user-images.githubusercontent.com/90658763/230356458-29a23413-73d7-4815-8f52-bb7ae090d8f6.png)

# SpeedScaner Turbo
## One way to make the above code scan ports faster is to use concurrency, that is, run multiple port checks at the same time instead of waiting for each check to complete before starting the next. One way to achieve this in C is through the use of threads.

## improved features

### Setting the socket to non-blocking mode allows the program to continue running while it waits for the server's response to connect to the port. This means it won't hang while you wait, which can improve program performance when scanning multiple ports or scanning ports on multiple IP addresses. Additionally, this can also help prevent the program from crashing if the server is down.
``` C
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
  ```
### The connect() function is used to establish a connection between the local socket and the remote socket (in this case, the server). If this function returns a value less than zero, it indicates that the connection failed.
### This code checks if the error that occurred on the connection is EINPROGRESS, which means that the connection is in progress and has not completed yet. This is because a non-blocking socket is being used, which means that the connect() function may return immediately before the connection is complete.
``` C
 // Start a non-blocking connect operation
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        if (errno == EINPROGRESS) {
 ```
### These codes are used to wait for a socket connection to complete in non-blocking mode using the select() function.
### First, an empty file descriptor set (fd_set) called write_fds is created and the socket descriptor (socket_desc) is added to the set using the FD_SET() function. Then, a timeout of 100ms is set using the timeval structure, which is used to specify the timeout in the select() function.
``` C
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
```

  # Example of SpeedScan Turbo:
![SpeedSacan-Turbo-Replit-Google-Chrome-2023-04-06-12-56-24](https://user-images.githubusercontent.com/90658763/230359068-a03a5258-b613-4472-bbd7-de6da453ece9.gif)
 # Sources:
 ## Stdlib.h:
 [![Stdlib.h](https://user-images.githubusercontent.com/90658763/230360437-bb4d1f84-8c0f-4641-8bc6-89882c644425.png)](https://es.wikipedia.org/wiki/Stdlib.h)
 ## <string.h>:
 [![string.h](https://user-images.githubusercontent.com/90658763/230360901-e9363243-d973-4c12-bd5f-81b72f7c7a6e.png)](https://www.scaler.com/topics/string-h-in-c/)
 ## <sys/socket.h>:
 [![string.h](https://user-images.githubusercontent.com/90658763/230361507-e39c4d04-4c0f-45d0-ab66-6144caa69bf6.png)](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/sys/socket.h.html)
 ## arpainet.h:
 [![arpainet.h](https://user-images.githubusercontent.com/90658763/230363791-ad1d21c4-713e-4f40-968f-69267492b9ea.png)](https://pubs.opengroup.org/onlinepubs/7908799/xns/arpainet.h.html)
## <unistd.h>:
[![<unistd.h>](https://user-images.githubusercontent.com/90658763/230364451-d337ef8d-c49d-4d5b-a63f-40a4fec54a5f.png)](https://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html)
## <fcntl.h>:
 [![<fcntl.h>](https://user-images.githubusercontent.com/90658763/230364888-2d4a42b5-9a85-4050-9edc-3c06430d071e.png)
](https://pubs.opengroup.org/onlinepubs/000095399/basedefs/fcntl.h.html)
## <errno.h>:
 [![<errno.h>](https://user-images.githubusercontent.com/90658763/230365415-253a4a3a-ac2e-4580-b420-c3b2348f7145.png)](https://www.linuxadictos.com/errno-h-un-poco-de-historia-unixlinux.html)
## <netinet/tcp.h>:
 [![<netinet/tcp.h>](https://user-images.githubusercontent.com/90658763/230366318-268d9388-514f-49f3-a1d4-5c2d27c5f26f.png)](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/netinet/tcp.h.html)


