/* ---------------------------------------------------------------------------
** ezsock.cpp
** This EZSock is intended for C++ user to access
** the basic interface of C socket, easily.
**
** Author: Siriwat Kasamwattanarote
** -------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>			// memset,memcpy
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>			// gethostbyname
#include <cstdlib>
#include <iostream>
#include <string>

#include "ezsock.h"

using namespace std;

ezsock::ezsock(sock_role role, int port, const string& ip)
{
	// Socket initialization
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");

	// Get general parameters
	portno = port;
	_role = role;

	switch (_role) {
	case sock_role::Server: {
		// Set server params
		memset((char *) &serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);		
		clilen = sizeof(cli_addr);
		
		// Binding
		if (bind(sockfd, (struct sockaddr *) &serv_addr,
		         sizeof(serv_addr)) < 0)
			error("ERROR on binding");
		
		// Listening for a connection
		listen(sockfd, queue);
		
		// Accepting connection
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
			error("ERROR on accept");

		break;
	}
	case sock_role::Client: {
		// Get target server
		server = gethostbyname(ip.c_str());

		if (server == NULL) {
			fprintf(stderr,"ERROR, no such host\n");
			exit(0);
		}
		
		// Set server params
		memset((char *) &serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		memcpy(	(char *)server->h_addr,
		        (char *)&serv_addr.sin_addr.s_addr,
		        server->h_length);
		serv_addr.sin_port = htons(portno);
		
		// Request for connection
		if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
			error("ERROR connecting");

		break;
	}}
}

ezsock::~ezsock(void)
{
	release();
}

string ezsock::read_txt()
{		
	memset(buffer, 0, 256);
	n = read(newsockfd, buffer, 255);
	cout << "n: " << n << endl;
	if (n < 0) error("ERROR reading from socket");
	//cout << "Here is the message: " << string(buffer) << "[" << strlen(buffer) << "]" << endl;
	n = write(newsockfd, "I got your message", 18);
	cout << "n: " << n << endl;
	
}

void ezsock::send_txt(const string &text)
{
	printf("Please enter the message: ");
	memset(buffer, 0, 256);
	cin >> buffer;
	int cnt = 10;
	while (cnt--) {
		
		n = write(sockfd,buffer,256);
		cout << "n: " << n << endl;
		if (n < 0)
			error("ERROR writing to socket");
		memset(buffer, 0, 256);
		n = read(sockfd,buffer, 255);
		cout << "n: " << n << endl;
		if (n < 0)
			error("ERROR reading from socket");
		printf("%s\n",buffer);
		
	}
}

void ezsock::error(const string &msg)
{
	error(msg);
	exit(0);
}

void ezsock::release()
{
	if (_role == sock_role::Server)
		close(newsockfd);
	close(sockfd);
}
//;)
