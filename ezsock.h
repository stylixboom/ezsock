/* ---------------------------------------------------------------------------
** ezsock.h
** This EZSock is intended for C++ user to access
** the basic interface of C socket, easily.
**
** Author: Siriwat Kasamwattanarote
** -------------------------------------------------------------------------*/


using namespace std;


class ezsock
{
	int sockfd, newsockfd, portno;
	unsigned int clilen;
	char* buffer;
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
public:
	enum sock_role { server, client };
	ezsock(sock_role role);				// Open
	~ezsock(void);						// Close
	string read_txt();					// Read
	int read_bin(char* in);
	string send_txt(string text);		// Write
	void send_bin(char* out, int size);
	
	
	void release(void);
};
//;)
