/* ---------------------------------------------------------------------------
** ezsock.h
** This EZSock is intended for C++ user to access
** the basic interface of C socket, easily.
**
** Author: Siriwat Kasamwattanarote
** -------------------------------------------------------------------------*/

/* How a socket work?
 * 
 * 1. A socket is created with socket().
 * 2. The socket is bound to a local address using bind(),
 *    so that other sockets may be connect()ed to it.
 * 3. A willingness to accept incoming connections and a queue limit for incoming connections are specified with listen().
 * 4. Connections are accepted with accept().
 * 5. Any transmission can be done between server and client using read() and write() on the socket file descriptor (socksd)
 * 6. Terminating the connection by using close(socket)
 * */


using namespace std;


class ezsock
{	
	enum sock_role { Server, Client };
	int sockfd, newsockfd, portno;
	char *buffer;
	sock_role _role;
	
	// Server
	struct sockaddr_in cli_addr;
	unsigned int clilen;
	int queue = 10;
	
	// CLient
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int n;
		
public:
	ezsock(sock_role role, int port, const string& ip = string());	// Open
	~ezsock(void);													// Close
	string read_txt();												// Read
	int read_bin(char *in);
	void send_txt(const string &text);							// Write
	void send_bin(char *out, int size);
	
	void error(const string &msg);
	void release(void);
};
//;)
