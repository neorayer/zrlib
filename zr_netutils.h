#ifndef ZR_NETUTILS_H_
#define ZR_NETUTILS_H_

#include <windows.h>
#include <time.h>

#ifndef MAX_URL
#define MAX_URL	1024
#endif

typedef struct zr_uri {
	char protocol[64];
	char host[MAX_PATH];
	int port;
	char path[MAX_URL];
} zr_uri_t;

bool zr_uri_parse(char * uristr, zr_uri_t * p_uri);

class HttpDownloadListener {
public:
	HttpDownloadListener() {
		
	}
	~HttpDownloadListener() {
		
	}
	
	 virtual void onConnect(char * host, int port) = 0;
	 virtual void onConnected(char * host, int port) = 0;
	 virtual void onGetContentLength(int length) = 0;
	 virtual void onProgress(time_t spentSeconds, long allRecvSize) = 0;
	 virtual void onFinished() = 0;
private:
};

bool zr_http_download_url(char * url, char * dest_filepath,
		HttpDownloadListener *listener);

bool zr_http_download(char * host, int port, char * path, char * dest_filepath,
		HttpDownloadListener *listener);

bool zr_http_request(char * url, HttpDownloadListener *listener);
#endif /*ZR_NETUTILS_H_*/
