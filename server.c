//
//  server.c
//  simple_sock
//
//  Created by wgj on 13-6-1.
//  Copyright (c) 2013年 wgj. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "utility.h"

int echo_service(int sock)
{
    int n;
    char buffer[512];
    
    while (1)
    {
        n = read(sock, buffer, sizeof(buffer));
        if (n<0 && errno==EINTR)
            continue;
        else if (n<0)
        {
            perror("sys-call [read]");
            exit(0);
        }
        write(sock, buffer, n);
    }
}

int main(int argc, char *argv[])
{
    struct sockaddr_in client_addr, server_addr;
    int listen_fd, conn_fd, ret;
    pid_t child_pid;
    socklen_t client_len;
    
    listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    VERIFY_FATAL(listen_fd, -1, "sys-call [socket]");
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8008);
    
    ret = bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    VERIFY_FATAL(ret, -1, "sys-call [bind]");
    
    ret = listen(listen_fd, 1024);
    VERIFY_FATAL(ret, -1, "sys-call [listen]");
    
    while (1)
    {
        char str_addr[256];
        client_len = sizeof(client_addr);
        conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
        VERIFY_FATAL(conn_fd, -1, "sys-call [accept]");
        printf("connection from %s : %d\n",
               inet_ntop(AF_INET, &client_addr.sin_addr, str_addr, sizeof(str_addr)),
               client_addr.sin_port);
        if ( (child_pid = fork()) == 0 )
        { // in child
            close(listen_fd);
            echo_service(conn_fd);
            return 0;
        }
        else
        { // in parent
            close(conn_fd);
        }        
    }
}