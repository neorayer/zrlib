#include "windows.h"
#include "zr_logger.h"

#include "zr_sock.h"

bool zr_sock_startup() {
	WSAData wsaData;
	u_short wVersionRequested= MAKEWORD( 2, 1);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return false;

	return true;
}

void zr_sock_cleanup() {
	WSACleanup();
}

////////////// ZrSocket //////////////////
ZrSocket::ZrSocket() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
}

ZrSocket::~ZrSocket() {
	close();
}

bool ZrSocket::setSoTimeout(int millSeconds) {
	int timeout = millSeconds;
	int bOptLen = sizeof timeout;
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, bOptLen)
			== SOCKET_ERROR)
		return false;
	if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, bOptLen)
			== SOCKET_ERROR)
		return false;
	return true;
}

bool ZrSocket::setKeepAlive(boolean on) {
	BOOL bOptVal= on;
	int bOptLen = sizeof(BOOL);
	if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&bOptVal, bOptLen)
			== SOCKET_ERROR)
		return false;

	return true;
}

bool ZrSocket::connect(char * host, int port) {
	SOCKADDR_IN soAddr;
	soAddr.sin_addr.S_un.S_addr = inet_addr(host);
	soAddr.sin_family=AF_INET;
	soAddr.sin_port=htons(port);
	if (SOCKET_ERROR == ::connect(sock, (SOCKADDR*)&soAddr, sizeof(SOCKADDR)))
		return false;
	return true;
}

void ZrSocket::close() {
	if (NULL == sock)
		return;
	closesocket(sock);
	sock = NULL;
}

int ZrSocket::send(char * data, int dataLen) {
	return:: send(sock, data, dataLen, 0);
}

int ZrSocket::recv(char * buf, int bufLen) {
	return ::recv(sock, buf, bufLen, 0);
}


void blockRead(int sock, char * buf, int len){
	int c = 0;
	do {
		int ret = recv(sock, buf + c, len - c, 0);
		if (ret < 0)
			throw 1;
		if (ret == 0) { 
			Sleep(1);
			continue;
		}
		c += ret;
	}while(c < len);
}

bool ZrSocket::blockRecv(char * buf, int wantLen) {
	try {
		blockRead(this->sock, buf, wantLen);
		return true;
	}catch(int) {
		return false;
	}
}






////////////// ZrUdpSocket //////////////////
ZrUdpSocket::ZrUdpSocket() {
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
}

ZrUdpSocket::~ZrUdpSocket() {
}

bool ZrUdpSocket::setSoTimeout(int millSeconds) {
	int timeout = millSeconds;
	int bOptLen = sizeof timeout;
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, bOptLen)
			== SOCKET_ERROR)
		return false;
	if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, bOptLen)
			== SOCKET_ERROR)
		return false;
	return true;
}

bool ZrUdpSocket::setKeepAlive(boolean on) {
	BOOL bOptVal= on;
	int bOptLen = sizeof(BOOL);
	if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&bOptVal, bOptLen)
			== SOCKET_ERROR)
		return false;

	return true;
}

int ZrUdpSocket::sendto(char * host, u_short port, char * data, int dataLen) {
	sockaddr_in to;  
	memset(&to, 0, sizeof(to));
	to.sin_family=AF_INET;  
	to.sin_port=htons(port);  
	to.sin_addr.s_addr = inet_addr(host);

	return ::sendto(sock, data, dataLen, 0, (sockaddr*)&to, sizeof(to));
}

int ZrUdpSocket::recv(char * buf, int bufLen) {
	return ::recv(sock, buf, bufLen, 0);
}