#include <windows.h>

/* 
 * Copyright (c) 2005���Ϻ�����Ƽ����޹�˾ www.skymiracle.com
 * All right reserved.
 *
 * �ļ����ƣ�zr_file.c
 * ժ    Ҫ��
 *     �����ļ�����������д��������ɾ���ȡ�
 *
 * char *zr_file2str(char *fname)
 * char *zr_file2nstr(char *fname, unsigned long nsize)
 * int zr_str2file(char *s, char *fname)
 * int zr_filesize(char *fname)
 * void *zr_file2mem(char *fname, int *memsize)
 * int zr_mem2file(void *p, size_t psize, char *fname)
 * int zr_int2file(int i, char *fname)
 * int zr_stdin2file(char *fname)
 * int zr_stdin2file_maxsize(char *fname, size_t maxsize)
 * int zr_fcopy(char *src, char *dst)
 * int zr_fmove(char *src, char *dst)
 * int zr_fexist(char *fname)
 * int zr_file2strbuf(char *fname, char *buf)
 * 
 * ��    ����
 * zr_file2str()�����ļ�ȫ�����ݶ�ȡ��һ���ַ�����
 * zr_file2nstr()�����ļ��ж�ȡָ����С�����ݵ�һ���ַ�����
 * zr_str2file()�����ַ��������ļ���
 * zr_filesize()�����ļ���С��
 * zr_file2mem()�����ļ����ݶ����ڴ档
 * zr_mem2file()�����ڴ��е����ݴ����ļ���
 * zr_int2file()��������ת�����ַ��������ļ���
 * zr_stdin2file()���ӱ�׼�����ȡ���ݴ����ļ���
 * zr_stdin2file_maxsize()���ӱ�׼�����ȡ���������Դ��޶ȵ����ݴ����ļ���������
 *      �޶��Ǹ����������޶ȡ�
 * zr_fcopy()�������ļ���
 * zr_fmove()���ƶ��ļ���
 * zr_fexist()���ļ��Ƿ���ڣ�
 * zr_file2strbuf()�����ļ������ַ���������
 *
 * ˵    ����
 * 
 * ��ǰ�汾��9.0
 * ���ߣ�
 * ������ڣ�2004.12.31
 *
 * ȡ���汾��8.2
 * ԭ���ߣ�
 * ������ڣ�2002.07.17
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if 0
#include <error.h>
#endif

#include "zr_file.h"
#include "zr_bzero.h"

/* �������ܣ����ļ�ȫ�����ݶ�ȡ��һ���ַ�����
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ������ַ�ָ��
 * ��    �أ�NULL -> �򲻿��ļ�
 *			 ���� -> ָ��
 */
char *zr_file2str(char *fname) {
	char *str_buf;
	struct stat stat_buf;
	unsigned long len;
	FILE *fp;

	stat(fname, &stat_buf);
	len = stat_buf.st_size;
	if (!(stat_buf.st_mode & S_IFREG))
		return NULL;
	fp = fopen(fname, "r");
	if (!fp)
		return NULL;

	str_buf = (char *)malloc(len+1);
	fread(str_buf, len, 1, fp);
	printf("%d\r\n", len);

	str_buf[len] = '\0';

	fclose(fp);
	return str_buf;
}

/* �������ܣ����ļ��ж�ȡָ����С�����ݵ�һ���ַ�����
 * ��ڲ�����char *fname -> �ļ���
 *			 unsigned long nsize -> ��С
 * ���ڲ������ַ�ָ��
 * ��    �أ�NULL -> �򲻿��ļ�
 *			 ���� -> ָ��
 */
char *zr_file2nstr(char *fname, unsigned long nsize) {
	char *str_buf;
	unsigned long len;
	FILE *fp;

	len = nsize;
	fp = fopen(fname, "r");
	if (!fp)
		return NULL;

	str_buf = (char *)malloc(len+1);
	fread(str_buf, len, 1, fp);
	str_buf[len] = '\0';

	fclose(fp);
	return str_buf;
}

/* �������ܣ����ַ��������ļ���
 * ��ڲ�����char *s -> �ַ���
 *			 char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_str2file(char *s, char *fname) {
	FILE *fp;
	if (!s || !fname)
		return ZR_FILE_FAIL;
	if ((fp = fopen(fname, "w")) == 0)
		return ZR_FILE_FAIL;
	fprintf(fp, "%s", s);
	fclose(fp);
	return ZR_FILE_SUCC;
}

/* �������ܣ����ļ���С��
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�   0 -> 0
 *			 ���� -> �ļ���С
 */
int zr_filesize(char *fname) {
	HANDLE fh= CreateFile(fname, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == fh) {
		return -1;
		//		zr_log_error_ec(GetLastError(), "open file error. %s", fname);
	}
	DWORD size_h = -1;
	DWORD rsize = GetFileSize(fh, &size_h);
	if (INVALID_FILE_SIZE == rsize) {
		//		zr_log_error_ec(GetLastError(), "get size failed. %s", fname);
		return -1;
	}
	CloseHandle(fh);
	return rsize;
	//
	//	
	//	struct stat stat_buf;
	//	if (stat(fname, &stat_buf) < 0)
	//		return 0;
	//
	//	return (int)(stat_buf.st_size);
}

///* �������ܣ����ļ����ݶ����ڴ档
// * ��ڲ�����char *fname -> �ļ���
// *			 int *memsize -> �ļ���С�������أ�
// * ���ڲ�������
// * ��    �أ�NULL -> ʧ��
// *			 ���� -> �ڴ��ַ
// */
//void *zr_file2mem(char *fname, int *memsize)
//{
//	void *mem_buf;	
//	struct stat stat_buf;
//	size_t mem_size;
//	int fd;
//
//	stat(fname,&stat_buf);
//	mem_size = stat_buf.st_size;
//	if (!(stat_buf.st_mode & S_IFREG))
//		return NULL;
//	fd = open(fname, O_RDONLY);
//	if (fd == -1)
//		return NULL;
//
//	mem_buf = malloc(mem_size);
//	read(fd, mem_buf,mem_size);
//	
//	close(fd);
//	(*memsize) = mem_size;
//	return mem_buf;
//}

///* �������ܣ����ڴ��е����ݴ����ļ���
// * ��ڲ�����void *p -> �ڴ��ַ
// *			 size_t psize -> ��С
// *			 char *fname -> �ļ���
// * ���ڲ���������
// * ��    �أ�ZR_FILE_SUCC -> �ɹ�
// *			 ZR_FILE_FAIL -> ʧ��
// */
//int zr_mem2file(void *p, size_t psize, char *fname)
//{
//	FILE *fd;
//
//	fd = fopen(fname, "w");
//	if (fd == NULL)
//		return ZR_FILE_FAIL;
//	write(fd, p, psize);
//	close(fd);
//
//	return ZR_FILE_SUCC;
//}

/* �������ܣ�������ת�����ַ��������ļ���
 * ��ڲ�����int i -> ����
 *			 char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_int2file(int i, char *fname) {
	int res;
	char str[128];

	sprintf(str, "%d", i);
	res = zr_str2file(str, fname);

	return res;
}

/* �������ܣ��ӱ�׼�����ȡ���ݴ����ļ���
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_stdin2file(char *fname) {
	FILE *fp;
	size_t bufsize = 8192;
	void *buf;
	size_t rsize;

	buf = malloc(bufsize);
	zr_bzero(buf, bufsize);
	fp = fopen(fname, "w");
	if (!fp)
		return ZR_FILE_FAIL;

	rsize = bufsize;
	while (!feof(stdin)) {
		rsize = fread(buf, 1, bufsize, stdin);
		fwrite(buf, 1, rsize, fp);
	}
	fclose(fp);
	free(buf);

	return ZR_FILE_SUCC;
}

/* �������ܣ��ӱ�׼�����ȡ���������Դ��޶ȵ����ݴ����ļ����������޶��Ǹ�����
 *		�����޶ȡ�
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 *			 ZR_FILE_FULL -> �ﵽ�޶�
 */
int zr_stdin2file_maxsize(char *fname, size_t maxsize) {
	FILE *fp;
	size_t bufsize = 8192;
	size_t rsize, nowsize = 0;
	void *buf[8192];

	zr_bzero(buf, bufsize);
	fp = fopen(fname, "w");
	if (!fp)
		return ZR_FILE_FAIL;

	if (maxsize <= 0)
		return zr_stdin2file(fname);

	rsize = bufsize;
	while (!feof(stdin)) {
		rsize = fread(buf, 1, bufsize, stdin);
		fwrite(buf, 1, rsize, fp);
		nowsize += rsize;
		if (nowsize > maxsize) {
			fclose(fp);
			return ZR_FILE_FULL;
		}
	}
	fclose(fp);

	return ZR_FILE_SUCC;
}

/* �������ܣ������ļ���
 * ��ڲ�����char *src -> Դ
 *			 char *dst -> Ŀ��
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_fcopy(char *src, char *dst) {
	FILE *fp_src, * fp_dst;
	size_t bufsize = 8192;
	void *buf;
	size_t rsize;

	buf = malloc(bufsize);
	zr_bzero(buf, bufsize);

	fp_src = fopen(src, "r");
	if (!fp_src)
		return ZR_FILE_FAIL;
	fp_dst = fopen(dst, "w");
	if (!fp_dst)
		return ZR_FILE_FAIL;

	rsize = bufsize;
	while (!feof(fp_src)) {
		rsize =fread(buf, 1, bufsize, fp_src);
		fwrite(buf, 1, rsize, fp_dst);
	}
	fclose(fp_dst);
	fclose(fp_src);

	free(buf);

	return ZR_FILE_SUCC;
}

/* �������ܣ��ƶ��ļ���
 * ��ڲ�����char *src -> Դ
 *			 char *dst -> Ŀ��
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_fmove(char *src, char *dst) {
	if (zr_fcopy(src, dst) != ZR_FILE_SUCC)
		return ZR_FILE_FAIL;

	remove(src);

	return ZR_FILE_SUCC;
}

/* �������ܣ��ļ��Ƿ���ڣ�
 * ��ڲ�����char *fname -> �ļ���
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> ���ļ���������
 *			 ZR_FILE_FAIL -> ��
 */
bool zr_fexist(char *fname) {
	HANDLE
			fh= CreateFile(fname, GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == fh) {
		return false;
	}
	CloseHandle(fh);
	return true;
}

/* �������ܣ����ļ������ַ���������
 * ��ڲ�����char *fname -> �ļ���
 *			 char *buf -> ������ָ��
 * ���ڲ���������
 * ��    �أ�ZR_FILE_SUCC -> �ɹ�
 *			 ZR_FILE_FAIL -> ʧ��
 */
int zr_file2strbuf(char *fname, char *buf) {
	struct stat stat_buf;
	unsigned long len;
	FILE *fp;

	stat(fname, &stat_buf);
	len = stat_buf.st_size;
	if (!(stat_buf.st_mode & S_IFREG))
		return ZR_FILE_FAIL;

	fp = fopen(fname, "r");
	if (!fp)
		return ZR_FILE_FAIL;

	fread(buf, len, 1, fp);
	buf[len] = '\0';

	fclose(fp);
	return ZR_FILE_SUCC;
}

int zr_file_get_systemtime(char * fpath, SYSTEMTIME *p_st) {
	HANDLE fh= CreateFile(fpath, GENERIC_READ, FILE_SHARE_READ,
			NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == fh)
		return ZR_FILE_FAIL;
	FILETIME ft;
	GetFileTime(fh, NULL, NULL, &ft);
	FileTimeToSystemTime(&ft, p_st);
	CloseHandle(fh);
	return ZR_FILE_SUCC;
}

void zr_file_get_timestr(char * fpath, char *str_buf) {
	SYSTEMTIME st;
	zr_file_get_systemtime(fpath, &st);
	SYSTEMTIME lt;
	SystemTimeToTzSpecificLocalTime(NULL, &st, &lt);

	sprintf(str_buf, "%d-%02d-%02d_%02d-%02d-%02d", lt.wYear, lt.wMonth,
			lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
}

int zr_handle2file(HANDLE h, char *fname) {
	int res;
	char str[128];

	sprintf(str, "%d", h);
	res = zr_str2file(str, fname);

	return res;
}

int zr_file2handle(char *fname, HANDLE *ph) {
	int res;
	char str[128];
	HANDLE h;
	FILE * fp = fopen(fname, "r");
	if (NULL == fp)
		return ZR_FILE_FAIL;
	fscanf(fp, "%d", ph);
	fclose(fp);
	return ZR_FILE_SUCC;
}

int zr_mem2file(void *p, size_t psize, char *fname) {
	HANDLE
			fh= CreateFile(fname, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == fh)
		return ZR_FILE_FAIL;
	DWORD NumberOfBytesWritten;
	if (!WriteFile(fh, p, psize, &NumberOfBytesWritten, NULL))
		return ZR_FILE_FAIL;
	CloseHandle(fh);
	return ZR_FILE_SUCC;
}

int zr_file2memBuf(char *fname, void * memBuf, int bufLen) {
	HANDLE
			fh= CreateFile(fname, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == fh)
		return ZR_FILE_FAIL;
	DWORD NumberOfBytesRead;
	if (!ReadFile(fh, memBuf, bufLen, &NumberOfBytesRead, NULL))
		return ZR_FILE_FAIL;
	CloseHandle(fh);
	return ZR_FILE_SUCC;
}

int zr_fileVarStr_set(char * varName, char * varValue) {
	char tmpPath[MAX_PATH];
	GetTempPath(sizeof tmpPath, tmpPath);
	char path[MAX_PATH];
	sprintf(path, "%s\\fileVar_%s", tmpPath, varName);
	return zr_str2file(varValue, path);
}

int zr_fileVarStr_get(char * varName, char * varValueBuf) {
	char tmpPath[MAX_PATH];
	GetTempPath(sizeof tmpPath, tmpPath);
	char path[MAX_PATH];
	sprintf(path, "%s\\fileVar_%s", tmpPath, varName);
	return zr_file2strbuf(path, varValueBuf);
}

int zr_fileVarBool_set(char * varName, bool val) {
	if (val)
		return zr_fileVarStr_set(varName, "1");
	else
		return zr_fileVarStr_set(varName, "0");
}

bool zr_fileVarBool_get(char * varName) {
	char buf[1024];
	int res = zr_fileVarStr_get(varName, buf);
	if (ZR_FILE_FAIL == res)
		return false;
	return buf[0] == '1';
}

int zr_fileVarInt_set(char * varName, int val) {
	char buf[128];
	sprintf(buf, "%d", val);
	return zr_fileVarStr_set(varName, buf);
}

int zr_fileVarInt_get(char * varName) {
	char buf[128];
	int res = zr_fileVarStr_get(varName, buf);
	if (ZR_FILE_FAIL == res)
		return -99999;
	int val = atoi(buf);
	return val;
}

bool zr_fileGetAppVersion(char* AppName, char * verBuf) {
	DWORD RessourceVersionInfoSize;
	DWORD JustAJunkVariabel;
	char* VersionInfoPtr;
	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	}*TranslationPtr;
	char* InformationPtr;
	UINT VersionInfoSize;
	char VersionValue[255];

	RessourceVersionInfoSize=GetFileVersionInfoSize(AppName,&JustAJunkVariabel);
	if (0!=RessourceVersionInfoSize) {
		VersionInfoPtr=new char[RessourceVersionInfoSize];
		if (GetFileVersionInfo(AppName,0,RessourceVersionInfoSize,VersionInfoPtr)) {
			if (!VerQueryValue(
					VersionInfoPtr,
					TEXT("VarFileInfo\\Translation"),
					(LPVOID*)&TranslationPtr,
					&VersionInfoSize)) {
				delete[] VersionInfoPtr;
				return false;
			}
		}

		//   retrieve   File   Description  
		wsprintf(VersionValue,
				TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
				TranslationPtr[0].wLanguage,
				TranslationPtr[0].wCodePage);

		if (!VerQueryValue(
				VersionInfoPtr,
				VersionValue,
				(LPVOID*)&InformationPtr,
				&VersionInfoSize)) {
			delete[] VersionInfoPtr;
			return false;
		}
		if (strlen(InformationPtr)>0) //Not   Null  
		{
			strcpy(verBuf, InformationPtr);
		}
		delete[] VersionInfoPtr;
	}
	return true;
}