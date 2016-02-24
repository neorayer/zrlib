#ifndef ZR_SOCK_H_
#define ZR_SOCK_H_

#include <windows.h>

bool zr_sock_startup();
void zr_sock_cleanup();

class ZrSocket {
public:
	ZrSocket();
	~ZrSocket();
	
	bool setSoTimeout(int millSeconds);
	bool setKeepAlive(boolean on);
	bool connect(char * host, int port);
	void close();
	int send(char * data, int dataLen);
	int recv(char * buf, int bufLen);
	bool blockRecv(char * buf, int wantLen);
private:
	SOCKET sock;
	int lastError;
};


class ZrUdpSocket {
public:
	ZrUdpSocket();
	~ZrUdpSocket();
	
	bool setSoTimeout(int millSeconds);
	bool setKeepAlive(boolean on);
	bool connect(char * host, int port);
	int sendto(char * host, u_short port, char * data, int dataLen);
	int recv(char * buf, int bufLen);
private:
	SOCKET sock;
	int lastError;
};


#endif /*ZR_SOCK_H_*/
