#include <stdio.h>

#include "zr_logger.h"
#include "zr_file.h"
#include "zr_sock.h"
#include "zr_TcpServer.h"
#include "zr_sockVarSrv.h"


#include "zr_netutils.h"

void out_zr_logger() {
	zr_log_detail("Hello World!");
	zr_log_debug("Hello World!");
	zr_log_info("Hello World!");
	zr_log_warn("Hello World!");
	zr_log_error("Hello World!");
	zr_log_ferror("Hello World!");
}

void test_zr_logger() {
	printf("### zr_log_set_level(ZR_LOG_LV_DETAIL)\r\n");
	zr_log_set_level(ZR_LOG_LV_DETAIL);
	out_zr_logger();
	printf("\r\n");

	printf("### zr_log_set_level(ZR_LOG_LV_DEBUG)\r\n");
	zr_log_set_level(ZR_LOG_LV_DEBUG);
	out_zr_logger();
	printf("\r\n");

	printf("### zr_log_set_level(ZR_LOG_LV_INFO)\r\n");
	zr_log_set_level(ZR_LOG_LV_INFO);
	out_zr_logger();
	printf("\r\n");

	printf("### zr_log_set_level(ZR_LOG_LV_WARN)\r\n");
	zr_log_set_level(ZR_LOG_LV_WARN);
	out_zr_logger();
	printf("\r\n");

	printf("### zr_log_set_level(ZR_LOG_LV_ERROR)\r\n");
	zr_log_set_level(ZR_LOG_LV_ERROR);
	out_zr_logger();
	printf("\r\n");

	printf("### zr_log_set_level(ZR_LOG_LV_FERROR)\r\n");
	zr_log_set_level(ZR_LOG_LV_FERROR);
	out_zr_logger();
	printf("\r\n");

	////////////////////////////

	printf("### zr_log_set_level(ZR_LOG_LV_DETAIL)\r\n");
	zr_log_set_level(ZR_LOG_LV_DETAIL);
	out_zr_logger();
	printf("\r\n");

	zr_log_set_target(ZR_LOG_TG_FILE);

	out_zr_logger();

	zr_log_set_target(ZR_LOG_TG_FILE);
	zr_log_set_filepath("c:\\temp\\test.zr_log");
	out_zr_logger();
}

void test_zr_file() {
	if (ZR_FILE_SUCC == zr_fexist("c:\\windows\\notepad.exe"))
		printf("The file exist!\r\n");
	else
		printf("The file doesn't exist!\r\n");
}

void test_zr_uri() {
	zr_uri_t uri;
	if (!zr_uri_parse("hTtp://www.skymIrAcle:2323/asd", &uri)) {
		printf("URI parse error!!!\r\n");
	}
	printf("protocol=%s\r\n", uri.protocol);
	printf("host    =%s\r\n", uri.host);
	printf("port    =%d\r\n", uri.port);
	printf("path    =%s\r\n", uri.path);
}

int main() {
	byte KEY[] = { (byte)0x3F,(byte)0x41,(byte)0x55, (byte)0x50, (byte)0x72, 
					(byte)0x65, (byte)0x66,(byte)0x53, (byte)0x74, (byte)0x72,
					(byte)0x69, (byte)0x6E,(byte)0x67,(byte)0x40,(byte)0x40 };
	printf("size = %d", sizeof KEY);
	return 0;
	zr_sock_startup();
	ZrUdpSocket * zus = new ZrUdpSocket();
	zus->sendto("10.1.1.35", 27016, "adsf", 4);
	return 0;
	
	zr_sockVarSrv * server = new zr_sockVarSrv(9999);
	server->start();
	Sleep(1000);
	
	zr_sockVarClt * clt = new zr_sockVarClt("127.0.0.1", 9999);
	for (int i=0; i<100; i++) {
		char varName[128];
		sprintf(varName, "varName_%d", i);
		clt->setInt(varName, i);
	}
	for (i=0; i<100; i++) {
		char varName[128];
		sprintf(varName, "varName_%d", i);
		int getVal = clt->getInt(varName);
		if (getVal == i) {
			printf("getVal = %d OK!!\r\n", i);
		}else {
			printf("getVal = %d , i= %d ERROR!!\r\n",getVal, i);
		}
	}
	int a;
	scanf("%d", &a);
	return 0;
	
	char verBuf[1024];
	zr_fileGetAppVersion("C:\\Applications\\WarCraft RepKing\\Data\\Patches\\1.22\\game.dll", verBuf);
	printf("version=%s\r\n", verBuf);
	
	return 0;
	
	zr_fileVarInt_set("TestInt", time(NULL));
	printf("int=%d\r\n", zr_fileVarInt_get("TestInt"));
	
	zr_fileVarBool_set("TestBool", false);
	printf("bool=%d\r\n", zr_fileVarBool_get("TestBool"));
	

//	zr_sock_startup();
//	zr_http_request("http://10.1.1.199:8080/GameHall/pg/if/gh/if_game_res.jsp?username=zhourui&res=1||zhourui|test111||luodong222", NULL);
	
	return 0;
	
	HANDLE h = (HANDLE)123456;
	zr_handle2file(h, "c:\\temp\\h.txt");
	HANDLE h2;
	zr_file2handle("c:\\temp\\h.txt", &h2);
	printf("handle=%d\r\n", h2);
	
	test_zr_logger();
	test_zr_file();

	test_zr_uri();
	
	char timeStr[1024];
	zr_file_get_timestr("C:\\Applications\\WC3\\replay\\LastReplay.w3g", timeStr);
	printf("%s\r\n", timeStr);
	zr_sock_cleanup();
	return 1;
}