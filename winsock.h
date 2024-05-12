/*
 * Library for socket management
 */

#ifndef WINSOCK_H
#define WINSOCK_H

#include <stdio.h>

int init_win_sock(void);
void server_listen();
void socket_cleanup();

#define PORT_NUMBER 12345
#define BUFFER_SIZE 254

#endif

