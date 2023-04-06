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
  ## Example of SpeedScan Turbo:
![SpeedSacan-Turbo-Replit-Google-Chrome-2023-04-06-12-56-24](https://user-images.githubusercontent.com/90658763/230359068-a03a5258-b613-4472-bbd7-de6da453ece9.gif)
 # Sources:
 ## Stdlib.h:
 [![Stdlib.h](https://user-images.githubusercontent.com/90658763/230360437-bb4d1f84-8c0f-4641-8bc6-89882c644425.png)](https://es.wikipedia.org/wiki/Stdlib.h)
 ## <string.h>:
 [![string.h](https://user-images.githubusercontent.com/90658763/230360901-e9363243-d973-4c12-bd5f-81b72f7c7a6e.png)](https://www.scaler.com/topics/string-h-in-c/)
 ## <sys/socket.h>:
 [![string.h](https://user-images.githubusercontent.com/90658763/230361507-e39c4d04-4c0f-45d0-ab66-6144caa69bf6.png)](https://www.scaler.com/topics/string-h-in-c/)


