/* ---------------------------------------------------------------------------
** ezsock.h
** This EZSock is intended for C++ user to access
** the basic interface of C socket, easily.
**
** Author: Siriwat Kasamwattanarote
** -------------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

#include "ezsock.h"

using namespace std;

ezsock::ezsock(sock_role role)
{
	if (role == sock_role::server)
		exit(0);
}

ezsock::~ezsock(void)
{
	
}
	
void ezsock::release()
{
	
}
//;)
