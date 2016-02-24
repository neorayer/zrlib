#ifndef ZR_TCPSERVER_H_
#define ZR_TCPSERVER_H_

#include "zr_sock.h"


class zr_TcpServer
{
public:
	zr_TcpServer(int port);
	virtual ~zr_TcpServer();

	void start();
	void run();
protected:
	virtual void connHandle(SOCKET cltSock) = 0;
	bool isMultiThread;
	int port;
	SOCKADDR_IN sockaddr_in;
	SOCKET srvSock;

};

#endif /*ZR_TCPSERVER_H_*/
