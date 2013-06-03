//
//  client.c
//  simple_sock
//
//  Created by wgj on 13-6-3.
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

int echo_client(int sock)
{
	char sendline[512], recvline[512];
	int n;
	
	while (fgets(sendline, 512, stdin)!= NULL)
	{
		write(sock, sendline, strlen(sendline));
		
		n=read(sock, recvline, 512);
		if (n<0)
		{
			perror("server timinate");
			exit(0);
		}
		else
		{
			recvline[n] = 0;
			printf("server send: %s\n", recvline);
		}
	}
	return 0;
}


int main(int argc, char *argv[])
{
	int sockfd, ret;
	struct sockaddr_in server_addr;
	
	if (argc != 3)
	{
		printf("usage: client <server ip> <server port>\n");
		exit(0);
	}
	
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
	
	ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	VERIFY_FATAL(ret, -1, "sys-call [connet]");
	
	echo_client(sockfd);
	
	return 0;
}

