/*
 * Library for socket management
 */

#include "winsock.h"
#include <stdio.h>
#include <winsock2.h>

struct sockaddr_in server, client;
SOCKET server_fd, new_socket;

int c, recv_size;
char buffer[BUFFER_SIZE];

// Initialize Winsock
int init_win_sock(void){
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            printf("WSAStartup failed");
            return 1;
    }

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT_NUMBER);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed");
        return 1;
    }
}

// Listen
void server_listen(){
    listen(server_fd, 3);
    printf("Waiting for connections...\n");
    
    c = sizeof(struct sockaddr_in);
    if ((new_socket = accept(server_fd, (struct sockaddr *)&client, &c)) == INVALID_SOCKET) {
        printf("Accept failed");
    }

    // Received data from the client (Arduino ->ESP shield)
    if ((recv_size = recv(new_socket, buffer, BUFFER_SIZE, 0)) == SOCKET_ERROR) {
        printf("Receive failed");
    }
    printf("Received size = %d\n", recv_size);
    printf("Received data:\n");
}

//Cleanup
void socket_cleanup(){
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
}