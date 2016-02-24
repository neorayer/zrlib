#include "zr_logger.h"
#include "stdio.h"
#include "zr_TcpServer.h"
#include "time.h"

void zr_TcpServerThreadRun(zr_TcpServer * server) {
	server->run();
}

zr_TcpServer::zr_TcpServer(int port) {
	this->port = port;
	//this->isMultiThread = isMultiThread;
	//TODO::
	this->isMultiThread = false;
	sockaddr_in.sin_family=AF_INET;
	sockaddr_in.sin_addr.s_addr=INADDR_ANY;
	sockaddr_in.sin_port=htons((u_short)port);
}

zr_TcpServer::~zr_TcpServer() {
}

void zr_TcpServer::start() {
	zr_sock_startup();
	//建立一个tcp socket
	srvSock = socket(AF_INET, SOCK_STREAM, 0);

	//If the socket() function fails we exit
	if (INVALID_SOCKET == srvSock) {
		zr_log_error_ec(WSAGetLastError(), "ServerSocket CREATE failed!");
		return;
	}

	//绑定服务器的ip地址和端口号
	if (bind(srvSock, (sockaddr*)&sockaddr_in, sizeof(sockaddr_in))!=0) {
		zr_log_error_ec(WSAGetLastError(), "ServerSocket BIND failed!");
		return;
	}

	//监听客户端请求，最大同时连接数10
	if (listen(srvSock, 10) != 0) {
		zr_log_error_ec(WSAGetLastError(), "ServerSocket LISTEN failed!");
		return;
	}

	DWORD far threadID;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)zr_TcpServerThreadRun, this, 0, &threadID);

}

void zr_TcpServer::run() {
	while (true) {
		SOCKET cltSock;
		SOCKADDR_IN from;
		int fromlen=sizeof(from);
		zr_log_debug_ec(0, "TcpServer start at port %d", port);
		while (true) {
			//接受一个连接请求，并返回一个同客户端交互的socket给变量client
			cltSock=accept(srvSock, (struct sockaddr*)&from, &fromlen);
			if (INVALID_SOCKET == cltSock) {
				zr_log_error_ec(WSAGetLastError(), "Socket Accept Error.");
				break;
			}
			//得到客户端的ip地址，并写入缓冲区
			char clientIp[64];
			sprintf(clientIp, "%s", inet_ntoa(from.sin_addr));
//			zr_log_debug_ec(0, "a Connect from %s", clientIp);

			if (this->isMultiThread) {
				//TODO: createAThread
			} else {
				connHandle(cltSock);
			}

			//关闭连接
			closesocket(cltSock);
		}
		zr_log_debug("TcpServer END!!");
	}
}
