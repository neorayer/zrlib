#ifndef ZR_SOCKVARSRV_H_
#define ZR_SOCKVARSRV_H_
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include<iostream>
#include<map>
#include<string>
#include<iterator>
#include "zr_sock.h"
#include "zr_TcpServer.h"

#define ZR_SV_SET 0x0A
#define ZR_SV_GET 0x0B

#define ZR_SV_TYPE_INT	1
#define ZR_SV_TYPE_BOOL	2
#define ZR_SV_TYPE_CHAR	3
#define ZR_SV_TYPE_STR 4

using namespace std;

class zr_sockVarSrv:public zr_TcpServer
{
public:
	zr_sockVarSrv(int port);
	virtual ~zr_sockVarSrv();
protected:
	void connHandle(SOCKET cltSock);
	map<string, string> varMap;
};

/////////////////////////////
class zr_sockVarClt {
public:
	zr_sockVarClt(char *host, int port);
	virtual ~zr_sockVarClt();

	void setInt(char * varName, int varVal);
	int getInt(char * varName);

	void setStr(char * varName, char * varVal);
	bool getStr(char * varName, char * buf);
protected:
	char * host;
	int port;
};

#endif /*ZR_SOCKVARSRV_H_*/
