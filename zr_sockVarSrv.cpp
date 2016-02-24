#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include<iostream>
#include<map>
#include<string>
#include<iterator>

#include "zr_logger.h"
#include "zr_sock.h"
#include "zr_sockVarSrv.h"

using namespace std;

class zr_runnable {
public:
	void run();
};

zr_sockVarSrv::zr_sockVarSrv(int port) :
	zr_TcpServer(port) {
}

zr_sockVarSrv::~zr_sockVarSrv() {
}

void zr_sockVarSrv::connHandle(SOCKET cltSock) {
	char recvBuf[1024];
	if (recv(cltSock, recvBuf, sizeof recvBuf, 0) <= 0)
		return;

	// 头部标记
	char tag = recvBuf[0];
	//变量名
	char * varName = recvBuf + 1;
	if (ZR_SV_SET == tag) {
		//变量值
		string nameS = varName;
		char * varVal = recvBuf + 64;
		string varValS = varVal;
		//记入Map
		varMap[nameS] = varValS;
	}else if (ZR_SV_GET == tag) {
		char buf[1024];
		string varValS = varMap[varName];
		strcpy(buf, varValS.c_str());
		send(cltSock, buf, strlen(buf) + 1, 0);
	}else {
		return;
	}
}


/////////////////////////////////////////////
zr_sockVarClt::zr_sockVarClt(char *host, int port) {
	this->host = new char[128];
	strcpy(this->host, host);
	this->port = port;
}

zr_sockVarClt::~zr_sockVarClt() {
}

int zr_sockVarClt::getInt(char * varName) {
	char  buf[64];
	if (getStr(varName, buf))
		return atoi(buf);
	return 
		-9999;
}


bool zr_sockVarClt::getStr(char * varName, char * buf) {
	ZrSocket * sock = new ZrSocket();
	sock->connect(host, port);
	char sendBuf[128];
	sendBuf[0] = ZR_SV_GET;
	sendBuf[1] = '\0';
	sendBuf[2] = '\0';
	sprintf(sendBuf + 1, varName);
	sock->send(sendBuf, strlen(sendBuf) + 1);
	char recvBuf[1024];
	int rLen = sock->recv(recvBuf, 1024);
	sock->close();
	if (rLen <=0)
		return false;
	strcpy(buf, recvBuf);
	return true;
}


void zr_sockVarClt::setStr(char * varName, char * varVal) {
	ZrSocket * sock = new ZrSocket();
	sock->connect(host, port);
	char sendBuf[128];
	sendBuf[0] = ZR_SV_SET;
	sendBuf[1] = '\0';
	sendBuf[2] = '\0';
	sprintf(sendBuf + 1, "%s", varName);
	sprintf(sendBuf + 64,"%s",  varVal);
	sock->send(sendBuf, 64 + strlen(varVal) + 1);
	sock->close();
}

void zr_sockVarClt::setInt(char * varName, int varVal) {
	char buf[32];
	sprintf(buf, "%d", varVal);
	setStr(varName, buf);
}






