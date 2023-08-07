#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from client!";

    // Create TCP socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send data to the server
    send(client_fd, message, strlen(message), 0);
    printf("Message sent to server: %s\n", message);

    // Receive response from the server
    read(client_fd, buffer, BUFFER_SIZE);
    printf("Server response: %s\n", buffer);

    // Close the connection
    close(client_fd);

    return 0;
}