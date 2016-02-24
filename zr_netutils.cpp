#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "zr_logger.h"
#include "zr_str.h"

#include "zr_netutils.h"

bool zr_http_request(char * url, HttpDownloadListener *listener) {
	zr_uri_t uri;
	if (!zr_uri_parse(url, &uri))
		return false;
	
	int err = 0;

	char *host = uri.host;
	int port =uri.port;
	char *path = uri.path;
	
	hostent* pHostent = gethostbyname(host);
	if (NULL == pHostent) {
		zr_log_error_ec(GetLastError(), "Unknown host [%s]", host);
		return false;
	}

	/**
	 * 连接pipe host
	 */
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN soAddr;
	memcpy(&soAddr.sin_addr.s_addr, pHostent->h_addr_list[0],
			pHostent->h_length);
	soAddr.sin_family=AF_INET;
	soAddr.sin_port=htons(port);
	if (NULL != listener) {
		listener->onConnect(host, port);
	}
	err = connect(sock, (SOCKADDR*)&soAddr, sizeof(SOCKADDR));
	if (SOCKET_ERROR == err) {
		zr_log_error_ec(WSAGetLastError(), "Connect host Failed! ");
		return false;
	}
	if (NULL != listener)
		listener->onConnected(host, port);

	char get_cmd[MAX_URL];
	sprintf(get_cmd, "GET http://%s:%d/%s HTTP/1.0\r\n\r\n", host, port, path);
	send(sock, get_cmd, strlen(get_cmd), 0);

	closesocket(sock);
	return true;
}
//TODO: now only support HTTP
bool zr_uri_parse(char * uristr, zr_uri_t * p_uri) {
	ZeroMemory(p_uri->protocol, sizeof (p_uri->protocol));
	ZeroMemory(p_uri->host, sizeof (p_uri->host));
	ZeroMemory(p_uri->path, sizeof (p_uri->path));

	if (NULL == uristr)
		return false;

	char buf[MAX_URL];
	zr_str2lower(uristr, buf);
	char * protocol_pos = strstr(buf, "://");
	if (protocol_pos < 0)
		return false;
	strncpy(p_uri->protocol, buf, protocol_pos - buf);

	if (strcmp("http", p_uri->protocol) != 0) {
		return false;
	}
	p_uri->port = 80;

	char * host_pos = strchr(protocol_pos + 3, '/');
	if (host_pos > 0) {
		*host_pos = '\0';
		strcpy(p_uri->path, uristr + (host_pos - buf) + 1);
	}
	char * port_pos = strchr(protocol_pos + 3, ':');
	if (port_pos <= 0) {
		strcpy(p_uri->host, protocol_pos + 3);
	} else {
		*port_pos = '\0';
		strcpy(p_uri->host, protocol_pos + 3);
		p_uri->port = atoi(port_pos + 1);
	}

	return true;
}

bool zr_http_download_url(char * url, char * dest_filepath,
		HttpDownloadListener *listener) {
	zr_uri_t uri;
	if (!zr_uri_parse(url, &uri))
		return false;
	return zr_http_download(uri.host, uri.port, uri.path, dest_filepath,
			listener);
}

bool zr_http_download(char * host, int port, char * path, char * dest_filepath,
		HttpDownloadListener *listener) {
	int err = 0;

	hostent* pHostent = gethostbyname(host);
	if (NULL == pHostent) {
		zr_log_error_ec(0, "Unknown host %s", host);
		return false;
	}

	/**
	 * 连接pipe host
	 */
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN soAddr;
	memcpy(&soAddr.sin_addr.s_addr, pHostent->h_addr_list[0],
			pHostent->h_length);
	soAddr.sin_family=AF_INET;
	soAddr.sin_port=htons(port);
	if (NULL != listener) {
		listener->onConnect(host, port);
	}
	err = connect(sock, (SOCKADDR*)&soAddr, sizeof(SOCKADDR));
	if (SOCKET_ERROR == err) {
		zr_log_error_ec(WSAGetLastError(), "Connect host Failed! ");
		return false;
	}
	if (NULL != listener)
		listener->onConnected(host, port);

	char get_cmd[MAX_URL];
	sprintf(get_cmd, "GET http://%s:%d/%s HTTP/1.0\r\n\r\n", host, port, path);
	send(sock, get_cmd, strlen(get_cmd), 0);

	time_t tm_bgn = time(NULL);

	// recv head
#define HEAD_BUF_LEN  4096
	char head_buf[HEAD_BUF_LEN];
	ZeroMemory(head_buf, HEAD_BUF_LEN);
	int head_len = 0;

	DWORD RecvBytes = 0, Flags;
	WSAOVERLAPPED RecvOverlapped = {0};

	// Create an event handle and setup an overlapped structure.
	RecvOverlapped.hEvent = WSACreateEvent();
	if (RecvOverlapped.hEvent == NULL) {
		zr_log_error_ec(WSAGetLastError(), "WSACreateEvent failed");
		return false;
	}

	WSABUF DataBuf;
	DataBuf.len = HEAD_BUF_LEN;
	DataBuf.buf = head_buf;

	Flags = 0;
	int rc;
	bool headParsed = false;
	int all_recv_size = 0;
	int content_length = 0;
	int last_show_size = 0;

	HANDLE
			fh= CreateFile(dest_filepath, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	while (true) {
		rc = WSARecv(sock, &DataBuf, 1, &RecvBytes, &Flags, &RecvOverlapped, 
		NULL);
		if ( (rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError()))) {
			zr_log_error_ec(err, "WSARecv failed");
			break;
		}
		rc = WSAWaitForMultipleEvents(1, &RecvOverlapped.hEvent, TRUE, 
		INFINITE, TRUE);
		if (rc == WSA_WAIT_FAILED) {
			zr_log_error_ec(WSAGetLastError(),
					"WSAWaitForMultipleEvents failed");
			break;
		}
		rc = WSAGetOverlappedResult(sock, &RecvOverlapped, &RecvBytes, FALSE,
				&Flags);
		if (rc == FALSE) {
			zr_log_error_ec(WSAGetLastError(), "WSARecv operation failed:");
			break;
		}

		// If 0 bytes are received, the connection was closed
		if (RecvBytes == 0)
			break;

		all_recv_size += RecvBytes;

		DWORD NumberOfBytesWritten;
		if (headParsed) {
			time_t tm_now = time(NULL);
			time_t tm_spent = tm_now - tm_bgn;
			if (NULL != listener)
				listener->onProgress(tm_spent, all_recv_size - head_len);
			WriteFile(fh, DataBuf.buf, RecvBytes, &NumberOfBytesWritten, NULL);
			continue;
		}
		char * pos = strstr(head_buf, "\r\n\r\n");
		if (pos <= 0) {
			zr_log_error("No HTTP header.");
			break;
		}
		head_len = pos - head_buf + 4;
		*pos = '\0';
		int head_off = pos - head_buf + 4;
		char lower_buf[HEAD_BUF_LEN];
		zr_str2lower(head_buf, lower_buf);
		pos = strstr(lower_buf, "content-length:");
		if (pos < 0) {
			zr_log_warn("No Content-Length");
		}
		pos += strlen("content-length:");
		char * pos_end = strchr(lower_buf, '\n');
		if (pos_end < 0) {
			zr_log_warn("Content-Length parse error.");
		}
		*pos_end = '\0';
		content_length = atoi(pos);
		if (NULL != listener)
			listener->onGetContentLength(content_length);

		headParsed = true;
		WriteFile(fh, DataBuf.buf+ head_off, RecvBytes - head_off,
				&NumberOfBytesWritten, NULL);
		continue;
	}
	CloseHandle(fh);

	WSACloseEvent(RecvOverlapped.hEvent);
	closesocket(sock);
	if (NULL != listener)
		listener->onFinished();

	return true;
}